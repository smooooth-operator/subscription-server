#include "subsriptionserver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SubsriptionServer w;
    w.show();
    return a.exec();
}
