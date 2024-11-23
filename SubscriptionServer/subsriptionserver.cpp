#include "subsriptionserver.h"
#include "ui_subsriptionserver.h"
#include <QStatusBar>
#include "pipehandler.h"
#include <QTimer>
#include <QMessageBox>
#include <QThread>

SubsriptionServer::SubsriptionServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SubsriptionServer),
    pipeHandler(new PipeHandler(this))
{
    ui->setupUi(this);

    //workerThread = new QThread(this);
    //pipeHandler = new PipeHandler(this);

    //pipeHandler->moveToThread(workerThread);

    //connect(workerThread, &QThread::started, pipeHandler, &PipeHandler::connectToServer, Qt::QueuedConnection);
    connect(pipeHandler, &PipeHandler::connectionStatusChanged, this, &SubsriptionServer::on_connectionStatusChanged);
    connect(pipeHandler, &PipeHandler::messageReceived, this, &SubsriptionServer::on_messageReceived);

    // connect(workerThread, &QThread::finished, workerThread, &QObject::deleteLater);
    // connect(workerThread, &QThread::finished, pipeHandler, &QObject::deleteLater);

    //workerThread->start();
    // qDebug() << "Worker thread is running: " << workerThread->isRunning();

    messagePollingTimer = new QTimer(this);
    connect(messagePollingTimer, &QTimer::timeout, pipeHandler, &PipeHandler::readMessage);

    if (pipeHandler->connectToServer()) {
        ui->statusbar->showMessage("Connected to server.");

        // Start the polling timer after a successful connection
        messagePollingTimer->start(500); // Adjust the interval as needed
    } else {
        ui->statusbar->showMessage("Failed to connect to server.");
        messagePollingTimer->stop();
    }
}

SubsriptionServer::~SubsriptionServer()
{
    delete ui;
}


void SubsriptionServer::on_pushButton_subscribe_clicked() {
    qDebug() << "Subscribe button clicked.";

    if(!ui->radioButton_weather->isChecked() && !ui->radioButton_currency->isChecked() && !ui->radioButton_stock->isChecked()){
        QMessageBox::critical(this, "ERROR", "Please select a subscription service first.");
        return;
    }

    QString newSubscription = "";
    if (ui->radioButton_weather->isChecked()) {
        newSubscription = "weather";
    } else if (ui->radioButton_currency->isChecked()) {
        newSubscription = "currency";
    } else if (ui->radioButton_stock->isChecked()) {
        newSubscription = "stock";
    }

    clearUI();
    pipeHandler->switchSubscription("subscribe:" + newSubscription);
    //pipeHandler->sendMessage("subscribe:" + newSubscription);
    qDebug() << "Switching subscription to: " << newSubscription;

}

void SubsriptionServer::on_connectionStatusChanged(const QString& message){
    ui->statusbar->showMessage(message);
}

void SubsriptionServer::handleMessage(const QString& message){
    if (message.startsWith("Weather in Lviv:")) {
        qDebug() << "Weather message: " << message;
        // Parse the weather information
        QStringList lines = message.split("\n");

        QString temperature, pressure, humidity, weatherType;
        for (const QString &line : lines) {
            if (line.startsWith("Temperature:")) {
                temperature = line.mid(QString("Temperature: ").length());
            } else if (line.startsWith("Pressure:")) {
                pressure = line.mid(QString("Pressure: ").length());
            } else if (line.startsWith("Humidity:")) {
                humidity = line.mid(QString("Humidity: ").length());
            } else if (line.startsWith("Weather:")) {
                weatherType = line.mid(QString("Weather: ").length());
            }
        }

        // Update the UI with the parsed information
        ui->lineEdit_temperature->setText(temperature);
        ui->lineEdit_pressure->setText(pressure);
        ui->lineEdit_humidity->setText(humidity);
        ui->lineEdit_generalWeather->setText(weatherType);

        ui->statusbar->showMessage("Weather info updated.");
    }
    else if(message.startsWith("Currency Rates:")) {
        qDebug() << "Currency message: " << message;

        QStringList lines = message.split("\n");

        QString usdRate, eurRate;
        for(const QString &line : lines) {
            if(line.startsWith("USD:")) {
                usdRate = line.mid(QString("USD: ").length());
            } else if(line.startsWith("EUR:")){
                eurRate = line.mid(QString("EUR: ").length());
            }
        }

        ui->lineEdit_euro->setText(eurRate);
        ui->lineEdit_usd->setText(usdRate);

        ui->statusbar->showMessage("Currency info updated.");
    }
    else if(message.startsWith("Stock Info")) {
        qDebug() << "Stock message: " << message;

        QStringList lines = message.split("\n");

        QString stockSymbol, stockCurrent, stockHigh, stockLow;
        for (const QString &line : lines) {
            if (line.startsWith("Stock Info")) {
                stockSymbol = line.mid(QString("Stock Info ").length());
            } else if (line.startsWith("Current:")) {
                stockCurrent = line.mid(QString("Current: ").length());
            } else if (line.startsWith("High:")) {
                stockHigh = line.mid(QString("High: ").length());
            } else if (line.startsWith("Low:")) {
                stockLow = line.mid(QString("Low: ").length());
            }
        }

        ui->lineEdit_stockSymbol->setText(stockSymbol);
        ui->lineEdit_stockCurrent->setText(stockCurrent);
        ui->lineEdit_stockHigh->setText(stockHigh);
        ui->lineEdit_stockLow->setText(stockLow);

        ui->statusbar->showMessage("Stock info updated.");
    }
}

void SubsriptionServer::on_messageReceived(const QString &message) {
    qDebug() << "Received Message: " << message;
    handleMessage(message);
}

void SubsriptionServer::clearUI() {
    ui->lineEdit_temperature->clear();
    ui->lineEdit_pressure->clear();
    ui->lineEdit_humidity->clear();
    ui->lineEdit_generalWeather->clear();
    ui->lineEdit_usd->clear();
    ui->lineEdit_euro->clear();
    ui->lineEdit_stockSymbol->clear();
    ui->lineEdit_stockCurrent->clear();
    ui->lineEdit_stockHigh->clear();
    ui->lineEdit_stockLow->clear();
}


