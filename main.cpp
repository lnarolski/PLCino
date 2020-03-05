#include "plcino.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PLCino w;
    w.show();

    return a.exec();
}
