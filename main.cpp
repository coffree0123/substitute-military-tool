#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDateTime dischargeDateTime(QDate(2025, 5, 26), QTime(12, 0, 0));
    MainWindow w(dischargeDateTime);
    w.show();
    return a.exec();
}
