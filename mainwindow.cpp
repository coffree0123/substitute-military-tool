#include "mainwindow.h"

#include <QLabel>
#include <QWidget>
#include <QTimer>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centralWidget = new QWidget(this);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    QDateTime dischargeDateTime(QDate(2025, 5, 26), QTime(12, 0, 0));
    CountDownWidget* countDown = new CountDownWidget(dischargeDateTime, this);

    mainLayout -> addWidget(countDown);

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {}

CountDownWidget::CountDownWidget(const QDateTime& dischargeDateTime, QWidget *parent)
    : QWidget(parent), dischargeDateTime(dischargeDateTime)
{
    // Setup layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    label = new QLabel(this);
    layout->addWidget(label);

    // Setup Timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CountDownWidget::updateDisplay);
    timer->start(200); // Update every 0.2 sec

    updateDisplay();
}

void CountDownWidget::updateDisplay()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    qint64 leftSeconds = currentDateTime.secsTo(dischargeDateTime);

    // Calculate day, hour, minute, second left
    int daysLeft = leftSeconds / 86400;
    int hoursLeft = (leftSeconds % 86400) / 3600;
    int minutesLeft = (leftSeconds % 3600) / 60;
    int secondsLeft = leftSeconds % 60;

    label->setText(QString("<h1>距離退伍還有：%1 天 %2 時 %3 分 %4 秒<h1>")
                       .arg(daysLeft).arg(hoursLeft).arg(minutesLeft).arg(secondsLeft));
}

CountDownWidget::~CountDownWidget() {}
