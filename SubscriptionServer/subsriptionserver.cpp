#include "subsriptionserver.h"
#include "ui_subsriptionserver.h"
#include <QStatusBar>

SubsriptionServer::SubsriptionServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SubsriptionServer),
    pipeHandler(new PipeHandler(this))
{
    ui->setupUi(this);

    //connect(pipeHandler, &PipeHandler::messageReceived, this, &SubsriptionServer::on_messageReceived);
    connect(pipeHandler, &PipeHandler::connectionStatusChanged, this, &SubsriptionServer::on_connectionStatusChanged);

    if(!pipeHandler->connectToServer()){
        ui->statusbar->showMessage("Failed to connect to server.");
    } else {
        ui->statusbar->showMessage("Connected to server.");
    }
}

SubsriptionServer::~SubsriptionServer()
{
    delete ui;
}

void SubsriptionServer::on_pushButton_subscribe_clicked()
{
    QStringList subscriptions;

    if (ui->checkBox_weather->isChecked()) {
        subscriptions << "weather";
    }
    if (ui->checkBox_currency->isChecked()) {
        subscriptions << "currency";
    }
    if (ui->checkBox_stock->isChecked()) {
        subscriptions << "stock";
    }

    // Send subscriptions for all checked services
    for (const QString& service : subscriptions) {
        if (!pipeHandler->sendMessage("SUBSCRIBE|" + service)) {
            ui->statusbar->showMessage("Failed to subscribe to " + service);
        }
    }
}


void SubsriptionServer::on_pushButton_unsubscribe_clicked()
{
    QStringList subscriptions;

    if (ui->checkBox_weather->isChecked()) {
        subscriptions << "weather";
    }
    if (ui->checkBox_currency->isChecked()) {
        subscriptions << "currency";
    }
    if (ui->checkBox_stock->isChecked()) {
        subscriptions << "stock";
    }

    // Send unsubscriptions for all checked services
    for (const QString& service : subscriptions) {
        if (!pipeHandler->sendMessage("UNSUBSCRIBE|" + service)) {
            ui->statusbar->showMessage("Failed to unsubscribe from " + service);
        }
    }
}

void SubsriptionServer::on_connectionStatusChanged(const QString& message){
    ui->statusbar->showMessage(message);
}

