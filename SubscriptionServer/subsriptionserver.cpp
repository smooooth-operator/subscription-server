#include "subsriptionserver.h"
#include "ui_subsriptionserver.h"

SubsriptionServer::SubsriptionServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SubsriptionServer)
{
    ui->setupUi(this);
}

SubsriptionServer::~SubsriptionServer()
{
    delete ui;
}
