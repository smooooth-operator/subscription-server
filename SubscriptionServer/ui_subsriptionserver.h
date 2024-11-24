/********************************************************************************
** Form generated from reading UI file 'subsriptionserver.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBSRIPTIONSERVER_H
#define UI_SUBSRIPTIONSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SubsriptionServer
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QPushButton *pushButton_subscribe;
    QRadioButton *radioButton_weather;
    QRadioButton *radioButton_currency;
    QRadioButton *radioButton_stock;
    QGroupBox *groupBox_2;
    QLineEdit *lineEdit_generalWeather;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_temperature;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_pressure;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_humidity;
    QGroupBox *groupBox_3;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *lineEdit_euro;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *lineEdit_usd;
    QGroupBox *groupBox_4;
    QWidget *horizontalLayoutWidget_7;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QLineEdit *lineEdit_stockCurrent;
    QWidget *horizontalLayoutWidget_8;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_8;
    QLineEdit *lineEdit_stockHigh;
    QLineEdit *lineEdit_stockSymbol;
    QWidget *horizontalLayoutWidget_9;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QLineEdit *lineEdit_stockLow;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SubsriptionServer)
    {
        if (SubsriptionServer->objectName().isEmpty())
            SubsriptionServer->setObjectName("SubsriptionServer");
        SubsriptionServer->resize(800, 507);
        centralwidget = new QWidget(SubsriptionServer);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(60, 30, 691, 101));
        pushButton_subscribe = new QPushButton(groupBox);
        pushButton_subscribe->setObjectName("pushButton_subscribe");
        pushButton_subscribe->setGeometry(QRect(510, 60, 171, 31));
        radioButton_weather = new QRadioButton(groupBox);
        radioButton_weather->setObjectName("radioButton_weather");
        radioButton_weather->setGeometry(QRect(20, 60, 112, 26));
        radioButton_currency = new QRadioButton(groupBox);
        radioButton_currency->setObjectName("radioButton_currency");
        radioButton_currency->setGeometry(QRect(180, 60, 112, 26));
        radioButton_stock = new QRadioButton(groupBox);
        radioButton_stock->setObjectName("radioButton_stock");
        radioButton_stock->setGeometry(QRect(330, 60, 112, 26));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(60, 170, 191, 251));
        lineEdit_generalWeather = new QLineEdit(groupBox_2);
        lineEdit_generalWeather->setObjectName("lineEdit_generalWeather");
        lineEdit_generalWeather->setGeometry(QRect(10, 40, 171, 28));
        horizontalLayoutWidget = new QWidget(groupBox_2);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 80, 171, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEdit_temperature = new QLineEdit(horizontalLayoutWidget);
        lineEdit_temperature->setObjectName("lineEdit_temperature");

        horizontalLayout->addWidget(lineEdit_temperature);

        horizontalLayoutWidget_2 = new QWidget(groupBox_2);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(10, 130, 171, 41));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        lineEdit_pressure = new QLineEdit(horizontalLayoutWidget_2);
        lineEdit_pressure->setObjectName("lineEdit_pressure");

        horizontalLayout_2->addWidget(lineEdit_pressure);

        horizontalLayoutWidget_3 = new QWidget(groupBox_2);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(10, 180, 171, 41));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(horizontalLayoutWidget_3);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        lineEdit_humidity = new QLineEdit(horizontalLayoutWidget_3);
        lineEdit_humidity->setObjectName("lineEdit_humidity");

        horizontalLayout_3->addWidget(lineEdit_humidity);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(310, 170, 191, 151));
        horizontalLayoutWidget_4 = new QWidget(groupBox_3);
        horizontalLayoutWidget_4->setObjectName("horizontalLayoutWidget_4");
        horizontalLayoutWidget_4->setGeometry(QRect(10, 40, 171, 41));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(horizontalLayoutWidget_4);
        label_4->setObjectName("label_4");

        horizontalLayout_4->addWidget(label_4);

        lineEdit_euro = new QLineEdit(horizontalLayoutWidget_4);
        lineEdit_euro->setObjectName("lineEdit_euro");

        horizontalLayout_4->addWidget(lineEdit_euro);

        horizontalLayoutWidget_5 = new QWidget(groupBox_3);
        horizontalLayoutWidget_5->setObjectName("horizontalLayoutWidget_5");
        horizontalLayoutWidget_5->setGeometry(QRect(9, 90, 171, 41));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(horizontalLayoutWidget_5);
        label_5->setObjectName("label_5");

        horizontalLayout_5->addWidget(label_5);

        lineEdit_usd = new QLineEdit(horizontalLayoutWidget_5);
        lineEdit_usd->setObjectName("lineEdit_usd");

        horizontalLayout_5->addWidget(lineEdit_usd);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(560, 170, 191, 231));
        horizontalLayoutWidget_7 = new QWidget(groupBox_4);
        horizontalLayoutWidget_7->setObjectName("horizontalLayoutWidget_7");
        horizontalLayoutWidget_7->setGeometry(QRect(10, 80, 171, 41));
        horizontalLayout_7 = new QHBoxLayout(horizontalLayoutWidget_7);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(horizontalLayoutWidget_7);
        label_7->setObjectName("label_7");

        horizontalLayout_7->addWidget(label_7);

        lineEdit_stockCurrent = new QLineEdit(horizontalLayoutWidget_7);
        lineEdit_stockCurrent->setObjectName("lineEdit_stockCurrent");

        horizontalLayout_7->addWidget(lineEdit_stockCurrent);

        horizontalLayoutWidget_8 = new QWidget(groupBox_4);
        horizontalLayoutWidget_8->setObjectName("horizontalLayoutWidget_8");
        horizontalLayoutWidget_8->setGeometry(QRect(10, 130, 171, 41));
        horizontalLayout_8 = new QHBoxLayout(horizontalLayoutWidget_8);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(horizontalLayoutWidget_8);
        label_8->setObjectName("label_8");

        horizontalLayout_8->addWidget(label_8);

        lineEdit_stockHigh = new QLineEdit(horizontalLayoutWidget_8);
        lineEdit_stockHigh->setObjectName("lineEdit_stockHigh");

        horizontalLayout_8->addWidget(lineEdit_stockHigh);

        lineEdit_stockSymbol = new QLineEdit(groupBox_4);
        lineEdit_stockSymbol->setObjectName("lineEdit_stockSymbol");
        lineEdit_stockSymbol->setGeometry(QRect(10, 40, 169, 28));
        horizontalLayoutWidget_9 = new QWidget(groupBox_4);
        horizontalLayoutWidget_9->setObjectName("horizontalLayoutWidget_9");
        horizontalLayoutWidget_9->setGeometry(QRect(10, 180, 171, 41));
        horizontalLayout_9 = new QHBoxLayout(horizontalLayoutWidget_9);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(horizontalLayoutWidget_9);
        label_9->setObjectName("label_9");

        horizontalLayout_9->addWidget(label_9);

        lineEdit_stockLow = new QLineEdit(horizontalLayoutWidget_9);
        lineEdit_stockLow->setObjectName("lineEdit_stockLow");

        horizontalLayout_9->addWidget(lineEdit_stockLow);

        SubsriptionServer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SubsriptionServer);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        SubsriptionServer->setMenuBar(menubar);
        statusbar = new QStatusBar(SubsriptionServer);
        statusbar->setObjectName("statusbar");
        SubsriptionServer->setStatusBar(statusbar);

        retranslateUi(SubsriptionServer);

        QMetaObject::connectSlotsByName(SubsriptionServer);
    } // setupUi

    void retranslateUi(QMainWindow *SubsriptionServer)
    {
        SubsriptionServer->setWindowTitle(QCoreApplication::translate("SubsriptionServer", "SubsriptionServer", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SubsriptionServer", "CHOOSE SUBSCRIPTION", nullptr));
        pushButton_subscribe->setText(QCoreApplication::translate("SubsriptionServer", "SUBSCRIBE", nullptr));
        radioButton_weather->setText(QCoreApplication::translate("SubsriptionServer", "Weather", nullptr));
        radioButton_currency->setText(QCoreApplication::translate("SubsriptionServer", "Currency", nullptr));
        radioButton_stock->setText(QCoreApplication::translate("SubsriptionServer", "Stock prices", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SubsriptionServer", "WEATHER IN LVIV", nullptr));
        label->setText(QCoreApplication::translate("SubsriptionServer", "Temperature:", nullptr));
        label_2->setText(QCoreApplication::translate("SubsriptionServer", "Pressure:", nullptr));
        label_3->setText(QCoreApplication::translate("SubsriptionServer", "Humidity:", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("SubsriptionServer", "CURRENCY", nullptr));
        label_4->setText(QCoreApplication::translate("SubsriptionServer", "EUR:", nullptr));
        label_5->setText(QCoreApplication::translate("SubsriptionServer", "USD:", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("SubsriptionServer", "STOCK PRICE", nullptr));
        label_7->setText(QCoreApplication::translate("SubsriptionServer", "Current:", nullptr));
        label_8->setText(QCoreApplication::translate("SubsriptionServer", "High:", nullptr));
        label_9->setText(QCoreApplication::translate("SubsriptionServer", "Low:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SubsriptionServer: public Ui_SubsriptionServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBSRIPTIONSERVER_H
