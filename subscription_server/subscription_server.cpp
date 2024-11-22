#include <windows.h>
#include <winhttp.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <thread>
#include <mutex>
#include <set>
#pragma comment(lib, "winhttp.lib")

// М'ютекс для синхронізації роботи з клієнтами
std::mutex clientMutex;

// Структура для інформації про клієнта
struct ClientInfo {
    HANDLE pipe;
    std::string type;
    bool operator<(const ClientInfo& other) const {
        return pipe < other.pipe;
    }
};

std::set<ClientInfo> clients;

// ------------------- HTTP-запити -------------------
std::string HttpGetRequest(const std::wstring& server, const std::wstring& url) {
    HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL;
    std::string response;

    hSession = WinHttpOpen(L"MyApp/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (hSession) {
        hConnect = WinHttpConnect(hSession, server.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
        if (hConnect) {
            hRequest = WinHttpOpenRequest(hConnect, L"GET", url.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
            if (hRequest) {
                BOOL sent = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
                if (sent && WinHttpReceiveResponse(hRequest, NULL)) {
                    DWORD bytesRead = 0;
                    do {
                        char buffer[4096];
                        WinHttpReadData(hRequest, buffer, sizeof(buffer), &bytesRead);
                        if (bytesRead > 0) {
                            response.append(buffer, bytesRead);
                        }
                    } while (bytesRead > 0);
                }
            }
        }
    }

    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);
    return response;
}

// ------------------- Парсинг JSON -------------------
std::string FindJsonValue(const std::string& json, const std::string& key) {
    size_t start = json.find("\"" + key + "\":");
    if (start == std::string::npos) return "";

    start = json.find(":", start) + 1;
    size_t end = json.find(",", start);
    if (json[start] == '"') {
        start++;
        end = json.find("\"", start);
    }
    return json.substr(start, end - start);
}

// ------------------- Функції для отримання інформації -------------------
std::vector<std::string> GetWeatherInfo() {
    std::vector<std::string> weatherInfo;
    std::wstring server = L"api.openweathermap.org";
    std::wstring url = L"/data/2.5/weather?q=Lviv&appid=6e40e88884e9158103f7fead74988026";

    std::string response = HttpGetRequest(server, url);

    if (!response.empty()) {
        try {
            std::string temp = FindJsonValue(response, "temp");
            std::string pressure = FindJsonValue(response, "pressure");
            std::string humidity = FindJsonValue(response, "humidity");
            std::string weatherType = FindJsonValue(response, "main");

            double tempCelsius = std::stod(temp) - 273.15;

            std::ostringstream tempStream;
            tempStream << std::fixed << std::setprecision(2) << tempCelsius << "°C";

            weatherInfo.push_back(tempStream.str());
            weatherInfo.push_back(pressure + " hPa");
            weatherInfo.push_back(humidity + "%");
            weatherInfo.push_back(weatherType);
        }
        catch (...) {
            weatherInfo = { "-", "-", "-", "Error fetching data" };
        }
    }
    else {
        weatherInfo = { "-", "-", "-", "No response from server" };
    }
    return weatherInfo;
}


std::vector<std::string> GetCurrencyInfo() {
    std::vector<std::string> currencyInfo;
    std::wstring server = L"bank.gov.ua";
    std::wstring url = L"/NBUStatService/v1/statdirectory/exchange?json";

    std::string response = HttpGetRequest(server, url);

    if (!response.empty()) {
        std::string usdRate, eurRate;

        size_t usdPos = response.find("\"cc\":\"USD\"");
        if (usdPos != std::string::npos) {
            usdRate = FindJsonValue(response.substr(usdPos - 50, 100), "rate");
        }

        size_t eurPos = response.find("\"cc\":\"EUR\"");
        if (eurPos != std::string::npos) {
            eurRate = FindJsonValue(response.substr(eurPos - 50, 100), "rate");
        }

        currencyInfo.push_back(usdRate + " UAH");
        currencyInfo.push_back(eurRate + " UAH");
    }
    else {
        currencyInfo = { "-", "-" };
    }

    return currencyInfo;
}

// ------------------- Функція для отримання інформації про акції -------------------
std::vector<std::string> GetStockInfo() {
    std::vector<std::string> stockInfo;
    std::wstring server = L"finnhub.io";
    std::wstring url = L"/api/v1/quote?symbol=AAPL&token=c34391qad3i8edlcgrgg";

    std::string response = HttpGetRequest(server, url);

    if (!response.empty()) {
        try {
            std::string currentPrice = FindJsonValue(response, "c");
            std::string highPrice = FindJsonValue(response, "h");
            std::string lowPrice = FindJsonValue(response, "l");

            stockInfo.push_back("$" + currentPrice);
            stockInfo.push_back("$" + highPrice);
            stockInfo.push_back("$" + lowPrice);
        }
        catch (...) {
            stockInfo = { "-", "-", "-" };
        }
    }
    else {
        stockInfo = { "-", "-", "-" };
    }

    return stockInfo;
}

// ------------------- Оновлення даних -------------------
void BroadcastToClients(const std::string& message, const std::string& subscriptionType) {
    std::lock_guard<std::mutex> lock(clientMutex);
    for (auto it = clients.begin(); it != clients.end(); ) {
        if (it->type == subscriptionType) {
            DWORD bytesWritten;
            BOOL result = WriteFile(it->pipe, message.c_str(), message.size(), &bytesWritten, NULL);
            if (!result || bytesWritten != message.size()) {
                DisconnectNamedPipe(it->pipe);
                CloseHandle(it->pipe);
                it = clients.erase(it);
                continue;
            }
        }
        ++it;
    }
}

void WeatherUpdateService() {
    while (true) {
        auto weatherInfo = GetWeatherInfo();
        std::ostringstream oss;
        oss << "Weather in Lviv:\n"
            << "Temperature: " << weatherInfo[0] << "\n"
            << "Pressure: " << weatherInfo[1] << "\n"
            << "Humidity: " << weatherInfo[2] << "\n"
            << "Weather: " << weatherInfo[3] << "\n";
        BroadcastToClients(oss.str(), "weather");
        std::this_thread::sleep_for(std::chrono::seconds(10)); // Затримка для тестування
    }
}


void CurrencyUpdateService() {
    while (true) {
        auto currencyInfo = GetCurrencyInfo();
        std::ostringstream oss;
        oss << "Currency Rates:\n"
            << "USD: " << currencyInfo[0] << "\n"
            << "EUR: " << currencyInfo[1] << "\n";
        BroadcastToClients(oss.str(), "currency");
        std::this_thread::sleep_for(std::chrono::seconds(10)); // Затримка для тестування
    }
}

void StockUpdateService() {
    while (true) {
        auto stockInfo = GetStockInfo();
        std::ostringstream oss;
        oss << "Stock Info Apple Inc.(AAPL):\n"
            << "Current: " << stockInfo[0] << "\n"
            << "High: " << stockInfo[1] << "\n"
            << "Low: " << stockInfo[2] << "\n";
        BroadcastToClients(oss.str(), "stock");
        std::this_thread::sleep_for(std::chrono::seconds(10)); // Затримка для тестування
    }
}

// ------------------- Основний сервер -------------------
void HandleClient(HANDLE hPipe) {
    char buffer[256];
    DWORD bytesRead;

    if (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
        buffer[bytesRead] = '\0';
        std::string command(buffer);

        std::lock_guard<std::mutex> lock(clientMutex);

        if (command == "subscribe:weather") {
            clients.insert({ hPipe, "weather" });
            std::cout << "Client subscribed to weather updates." << std::endl;

            auto weatherInfo = GetWeatherInfo();
            std::ostringstream oss;
            oss << "Weather in Lviv:\n"
                << "Temperature: " << weatherInfo[0] << "\n"
                << "Pressure: " << weatherInfo[1] << "\n"
                << "Humidity: " << weatherInfo[2] << "\n"
                << "Weather: " << weatherInfo[3] << "\n";
            WriteFile(hPipe, oss.str().c_str(), oss.str().size(), &bytesRead, NULL);
        }
        else if (command == "subscribe:currency") {
            clients.insert({ hPipe, "currency" });
            std::cout << "Client subscribed to currency updates." << std::endl;

            auto currencyInfo = GetCurrencyInfo();
            std::ostringstream oss;
            oss << "Currency Rates:\n"
                << "USD: " << currencyInfo[0] << "\n"
                << "EUR: " << currencyInfo[1] << "\n";
            WriteFile(hPipe, oss.str().c_str(), oss.str().size(), &bytesRead, NULL);
        }
        else if (command == "subscribe:stock") {
            clients.insert({ hPipe, "stock" });
            std::cout << "Client subscribed to stock updates." << std::endl;

            auto stockInfo = GetStockInfo();
            std::ostringstream oss;
            oss << "Stock Info Apple Inc. (AAPL):\n"
                << "Current: " << stockInfo[0] << "\n"
                << "High: " << stockInfo[1] << "\n"
                << "Low: " << stockInfo[2] << "\n";
            WriteFile(hPipe, oss.str().c_str(), oss.str().size(), &bytesRead, NULL);
        }
        else {
            DisconnectNamedPipe(hPipe);
            CloseHandle(hPipe);
            std::cout << "Client disconnected (invalid subscription)." << std::endl;
            return;
        }
    }
    else {
        DisconnectNamedPipe(hPipe);
        CloseHandle(hPipe);
        std::cout << "Client disconnected (read error)." << std::endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const std::wstring pipeName = L"\\\\.\\pipe\\InfoServicePipe";

    std::thread weatherThread(WeatherUpdateService);
    std::thread currencyThread(CurrencyUpdateService);
    std::thread stockThread(StockUpdateService);
    weatherThread.detach();
    currencyThread.detach();
    stockThread.detach();
    std::cout << "Server starting..." << std::endl;

    while (true) {
        HANDLE hPipe = CreateNamedPipeW(
            pipeName.c_str(),
            PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            PIPE_UNLIMITED_INSTANCES,
            512, 512, 0, NULL);

        if (hPipe == INVALID_HANDLE_VALUE) {
            continue;
        }

        if (ConnectNamedPipe(hPipe, NULL)) {
            std::cout << "Client connected." << std::endl;
            std::thread clientThread(HandleClient, hPipe);
            clientThread.detach();
        }
        else {
            CloseHandle(hPipe);
        }
    }
    return 0;
}