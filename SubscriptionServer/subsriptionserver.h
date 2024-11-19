#ifndef SUBSRIPTIONSERVER_H
#define SUBSRIPTIONSERVER_H

#include <QMainWindow>
#include "pipehandler.h"

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
    //void on_messageReceived();
    void on_connectionStatusChanged(const QString& message);
    void on_pushButton_subscribe_clicked();
    void on_pushButton_unsubscribe_clicked();

private:
    Ui::SubsriptionServer *ui;
    PipeHandler *pipeHandler;
};
#endif // SUBSRIPTIONSERVER_H
