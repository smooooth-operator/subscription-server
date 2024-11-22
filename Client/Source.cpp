#include <windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <sstream>

// ------------------- ������� ��� ������� ����� � ������ -------------------
void ReadFromServer(HANDLE hPipe) {
    char buffer[512];
    DWORD bytesRead;

    while (true) {
        BOOL result = ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL);
        if (!result || bytesRead == 0) {
            std::cerr << "Disconnected from server or read error. Error: " << GetLastError() << "\n";
            break;
        }
        buffer[bytesRead] = '\0'; // ��������� �����
        std::cout << "Message from server:\n" << buffer << "\n";
    }
}

// ------------------- �������� ��� �볺��� -------------------
int main() {
    const std::wstring pipeName = L"\\\\.\\pipe\\InfoServicePipe";
    HANDLE hPipe;

    // ϳ��������� �� ����������� ������
    while (true) {
        hPipe = CreateFileW(
            pipeName.c_str(),
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);

        if (hPipe != INVALID_HANDLE_VALUE) {
            break;
        }

        if (GetLastError() != ERROR_PIPE_BUSY) {
            std::cerr << "Failed to connect to pipe. Error: " << GetLastError() << "\n";
            return 1;
        }

        // �������, ���� ����� ����� ���������
        if (!WaitNamedPipeW(pipeName.c_str(), 5000)) {
            std::cerr << "Pipe busy. Retrying...\n";
            continue;
        }
    }

    std::cout << "Connected to server.\n";
    std::cout << "Available subscription types: [weather], [currency], [stock].\n";
    std::cout << "Enter subscription type: ";

    // �������� ������ ���� �������
    std::string command;
    std::cin >> command;

    std::istringstream ss(command);
    std::string subscriptionType;
    std::vector<std::string> subscriptions;

    // ��������� ������� ������ �� �������
    while (std::getline(ss, subscriptionType, ',')) {
        subscriptions.push_back(subscriptionType);
    }

    // ³���������� ������� ������ �� �������
    for (const auto& type : subscriptions) {
        std::string subscriptionCommand = "subscribe:" + type;
        DWORD bytesWritten;
        BOOL result = WriteFile(
            hPipe,
            subscriptionCommand.c_str(),
            subscriptionCommand.size(),
            &bytesWritten,
            NULL);

        if (!result || bytesWritten != subscriptionCommand.size()) {
            std::cerr << "Failed to send subscription request for " << type << ". Error: " << GetLastError() << "\n";
            CloseHandle(hPipe);
            return 1;
        }
    }

    std::cout << "Subscription requests sent. Waiting for messages...\n";
    std::cout << "Type 'exit' to unsubscribe and quit.\n";

    // ������ ������ ��� ������� ���������� �� �������
    std::thread readerThread(ReadFromServer, hPipe);

    // ������� ������ �� �����������
    std::string userCommand;

    while (true) {
        std::getline(std::cin, userCommand);
        if (userCommand == "exit") {
            std::cout << "Exiting...\n";
            break;
        }
    }

    // ���������� ������ �볺���
    readerThread.detach();
    CloseHandle(hPipe);
    return 0;
}
