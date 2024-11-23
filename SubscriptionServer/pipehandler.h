//for managing pipe connection to server
#ifndef PIPEHANDLER_H
#define PIPEHANDLER_H

#include <QObject>
#include <QDebug>
#include <windows.h>


class PipeHandler : public QObject {
  Q_OBJECT
public:
  explicit PipeHandler(QObject *parent = nullptr);
  ~PipeHandler();

    bool connectToServer();
    bool sendMessage(const QString& message);
    void readMessage();
    void switchSubscription(const QString& newSubscription);

signals:
    void messageReceived(const QString &message);
    void connectionStatusChanged(const QString &status);

private:
    HANDLE pipe;
    bool connected;
    QString currentSubscription;
};

#endif // PIPEHANDLER_H
