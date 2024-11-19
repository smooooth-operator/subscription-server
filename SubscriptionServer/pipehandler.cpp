#include "pipehandler.h"
#include <QDebug>
#include <QString>
#include <windows.h>

const wchar_t* PIPE_NAME = L"\\\\.\\pipe\\SubscriptionServerPipe";

PipeHandler::PipeHandler(QObject *parent)
    :QObject(parent), pipe(INVALID_HANDLE_VALUE), connected(false) {}

PipeHandler::~PipeHandler() {
    if(connected) {
        CloseHandle(pipe);
    }
}

bool PipeHandler::connectToServer() {
    pipe = CreateFile(PIPE_NAME, GENERIC_READ | GENERIC_WRITE,
                      0, NULL, OPEN_EXISTING, 0, NULL);

    if (pipe == INVALID_HANDLE_VALUE) {
        DWORD errorCode = GetLastError();
        emit connectionStatusChanged(QString("Failed to connect to server. Error code: %1").arg(errorCode));
        return false;
    }

    connected = true;
    emit connectionStatusChanged("Connected to server.");
    return true;
}

bool PipeHandler::sendMessage(const QString& message){
    if (!connected || pipe == INVALID_HANDLE_VALUE) {
        emit connectionStatusChanged("Failed to send message: not connected to the server.");
        return false;
    }

    DWORD bytesWritten;
    bool result = WriteFile(pipe, message.toStdString().c_str(), message.size(), &bytesWritten, NULL);

    if (!result || bytesWritten != message.size()) {
        emit connectionStatusChanged("Failed to send message: pipe error.");
        return false;
    }

    return true;
}

void PipeHandler::readMessage(){
    if (connected) {
        char buffer[512] = {0}; // Initialize the buffer to avoid garbage data.
        DWORD bytesRead = 0;

        if (ReadFile(pipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
            buffer[bytesRead] = '\0';
            emit messageReceived(QString::fromStdString(buffer));
        } else {
            DWORD errorCode = GetLastError();
             QString errorMessage = QString("Failed to read message. Error code: %1").arg(errorCode);

            // Handle specific error codes for better diagnostics
            if (errorCode == ERROR_BROKEN_PIPE) {
                errorMessage = "The pipe was closed by the server.";
            } else if (errorCode == ERROR_MORE_DATA) {
                errorMessage = "Not enough data read. More data is available.";
            }

            emit connectionStatusChanged(errorMessage);  // Emit error message
        }
    }
}
