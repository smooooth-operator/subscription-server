#include <windows.h>
#include <winhttp.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#pragma comment(lib, "winhttp.lib")
using namespace std;

std::string HttpGetRequest(const std::wstring& server, const std::wstring& uri) {
    HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL;
    std::string response;

    hSession = WinHttpOpen(L"MyApp/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (hSession) {
        hConnect = WinHttpConnect(hSession, server.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
        if (hConnect) {
            hRequest = WinHttpOpenRequest(hConnect, L"GET", uri.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
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

vector<string> GetWeatherInfo() {

    vector<string> weatherInfo; //Вектор, в якому 3 поля (температура, тиск, вологість)
    std::wstring server = L"api.openweathermap.org";
    std::wstring uri = L"/data/2.5/weather?q=Lviv&appid=6e40e88884e9158103f7fead74988026";

    std::string response = HttpGetRequest(server, uri);

    if (!response.empty()) {
        std::string temp = FindJsonValue(response, "temp");
        std::string pressure = FindJsonValue(response, "pressure");
        std::string humidity = FindJsonValue(response, "humidity");

        double tempCelsius = std::stod(temp) - 273.15;
   
        std::ostringstream tempStream;
        tempStream << std::fixed << std::setprecision(2) << tempCelsius << "°C";
       
        weatherInfo.push_back(tempStream.str()); // Додаємо температуру
        weatherInfo.push_back(pressure + " hPa"); // Додаємо тиск
        weatherInfo.push_back(humidity + "%");   // Додаємо вологість
    }
    else {
        //Якщо не зчиталось, то у всіх полях "-"
        weatherInfo.push_back("-");
        weatherInfo.push_back("-"); 
        weatherInfo.push_back("-");   
    }
    return weatherInfo;
}
