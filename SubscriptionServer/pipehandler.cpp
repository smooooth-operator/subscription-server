#include "pipehandler.h"
#include <QDebug>
#include <QString>
#include <windows.h>
#include <QMutex>
#include <QThread>
#include <QTimer>

QMutex mutex;
const wchar_t* PIPE_NAME = L"\\\\.\\pipe\\InfoServicePipe";

PipeHandler::PipeHandler(QObject *parent)
    :QObject(parent), pipe(INVALID_HANDLE_VALUE), connected(false) {}

PipeHandler::~PipeHandler() {
    if(connected) {
        CloseHandle(pipe);
        connected = false;
    }
}

bool PipeHandler::connectToServer() {
    if (pipe != INVALID_HANDLE_VALUE) {
        CloseHandle(pipe);
        pipe = INVALID_HANDLE_VALUE;
    }

    qDebug() << "Attempting to connect to pipe...";

    pipe = CreateFile(PIPE_NAME, GENERIC_READ | GENERIC_WRITE,
                      0, NULL, OPEN_EXISTING, 0, NULL);

    if (pipe == INVALID_HANDLE_VALUE) {
        DWORD errorCode = GetLastError();
        emit connectionStatusChanged(QString("Failed to connect to server. Error code: %1").arg(errorCode));
        return false;
    }

    connected = true;
    emit connectionStatusChanged("Connected to server.");

    //readMessage();

    // Use a timer to poll the pipe periodically
    // QTimer* timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this, &PipeHandler::readMessage);
    // timer->start(100); // Check every 100ms

    return true;
}

bool PipeHandler::sendMessage(const QString& message){
    //QMutexLocker locker(&mutex);
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

    qDebug() << "Message sent successfully.";
    return true;
}

void PipeHandler::readMessage(){
    QMutexLocker locker(&mutex);

    if (!connected || pipe == INVALID_HANDLE_VALUE) {
        emit connectionStatusChanged("Not connected or invalid pipe.");
        return;
    }

    DWORD bytesAvailable = 0;
    if (!PeekNamedPipe(pipe, NULL, 0, NULL, &bytesAvailable, NULL)) {
        DWORD errorCode = GetLastError();
        if (errorCode == ERROR_PIPE_NOT_CONNECTED) {
            emit connectionStatusChanged("Pipe is not connected. Please reconnect.");
            connected = false;
            return;
        }

        emit connectionStatusChanged(QString("PeekNamedPipe failed. Error code: %1").arg(errorCode));
        return;
    }

    if (bytesAvailable > 0) {
        char buffer[512] = {0};
        DWORD bytesRead = 0;

        if (ReadFile(pipe, buffer, sizeof(buffer) - 1, &bytesRead, nullptr)) {
            if (bytesRead > 0) {
                buffer[bytesRead] = '\0';  // Null-terminate the string
                emit messageReceived(QString::fromStdString(buffer));
            } else {
                qDebug() << "No data read.";
            }
        } else {
            DWORD errorCode = GetLastError();
            emit connectionStatusChanged(QString("Failed to read message. Error code: %1").arg(errorCode));
        }
    }
}


void PipeHandler::switchSubscription(const QString& newSubscription){

    // Disconnect the current subscription
    QMutexLocker locker(&mutex);
    if (connected && pipe != INVALID_HANDLE_VALUE) {
        CloseHandle(pipe);
        connected = false;
    }

    if (!connectToServer()) {
        emit connectionStatusChanged("Failed to reconnect to server for new subscription.");
        qDebug() << "Reconnection failed";
        return;
    }

    // Send the new subscription message
    //QString subscribeMessage = "subscribe:" + newSubscription;
    if (!sendMessage(newSubscription)) {
        emit connectionStatusChanged("Failed to send subscription message after reconnection.");
        return;
    }

    emit connectionStatusChanged(QString("Subscribed to %1").arg(newSubscription));
    qDebug() << "Switched subscription to: " << newSubscription;
}
