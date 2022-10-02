#include "smartcalc.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SmartCalc w;
    w.show();
    return a.exec();
}
