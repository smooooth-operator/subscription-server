#ifndef SUBSRIPTIONSERVER_H
#define SUBSRIPTIONSERVER_H

#include <QMainWindow>
#include "pipehandler.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class SubsriptionServer;
}
QT_END_NAMESPACE

class SubsriptionServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit SubsriptionServer(QWidget *parent = nullptr);
    ~SubsriptionServer();

private slots:
    void on_messageReceived(const QString &message);
    void handleMessage(const QString &message);
    void on_connectionStatusChanged(const QString& message);
    void on_pushButton_subscribe_clicked();
    void clearUI();

private:
    Ui::SubsriptionServer *ui;
    PipeHandler *pipeHandler;
    QTimer* messagePollingTimer;
    QThread* workerThread;
};
#endif // SUBSRIPTIONSERVER_H
