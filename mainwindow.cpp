#include "mainwindow.h"

#include <QDir>
using namespace std;


MainWindow::MainWindow(QDateTime dischargeDateTime, QWidget *parent)
    : QMainWindow(parent)
{
    centralWidget = new QWidget(this);

    mainLayout = new QVBoxLayout(centralWidget);

    mainLayout -> setContentsMargins(0, 0, 0, 0);

    this -> setFixedSize(1200, 800);
    this -> setCentralWidget(centralWidget);

    // Setup background image
    QPixmap image("/Users/coffree/program/substitute-military-tool/img/image.jpg");
    backgroundImage = new QLabel(centralWidget);
    backgroundImage -> setPixmap(image);
    backgroundImage -> setScaledContents(true);

    mainLayout -> addWidget(backgroundImage);

    countDown = new CountDownWidget(dischargeDateTime, centralWidget);
    countDown -> setStyleSheet("background-color: transparent;");
    countDown -> setFixedSize(800, 200);

    // Calculate best position for putting countDown widget
    int x = (this -> width() - countDown -> width()) / 2;
    int y = (this -> height() - countDown -> height()) / 4;

    countDown -> setGeometry(x, y, countDown -> width(), countDown -> height());
}

MainWindow::~MainWindow() {}

CountDownWidget::CountDownWidget(const QDateTime& dischargeDateTime, QWidget *parent)
    : QWidget(parent), dischargeDateTime(dischargeDateTime)
{
    // Setup layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    label = new QLabel(this);
    label -> setAlignment(Qt::AlignCenter);
    layout -> addWidget(label);

    // Setup Timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [&]{
        QDateTime currentDateTime = QDateTime::currentDateTime();
        qint64 leftSeconds = currentDateTime.secsTo(dischargeDateTime);

        // Calculate day, hour, minute, second left
        int daysLeft = leftSeconds / 86400;
        int hoursLeft = (leftSeconds % 86400) / 3600;
        int minutesLeft = (leftSeconds % 3600) / 60;
        int secondsLeft = leftSeconds % 60;

        label -> setText(QString("<h1>Hi Coffree!<br>距離離開這個鬼地方還有：%1 天 %2 時 %3 分 %4 秒<h1>")
                           .arg(daysLeft).arg(hoursLeft).arg(minutesLeft).arg(secondsLeft));
    });
    timer -> start(200); // Update every 0.2 sec
}

CountDownWidget::~CountDownWidget() {}
