#ifndef SUBSRIPTIONSERVER_H
#define SUBSRIPTIONSERVER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class SubsriptionServer;
}
QT_END_NAMESPACE

class SubsriptionServer : public QMainWindow
{
    Q_OBJECT

public:
    SubsriptionServer(QWidget *parent = nullptr);
    ~SubsriptionServer();

private:
    Ui::SubsriptionServer *ui;
};
#endif // SUBSRIPTIONSERVER_H
