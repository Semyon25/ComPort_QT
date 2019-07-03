#include "comPort.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ComPort w;
    w.show();

    return a.exec();
}
