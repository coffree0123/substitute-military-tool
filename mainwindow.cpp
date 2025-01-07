#include "mainwindow.h"

#include <iostream>
using namespace std;

DiaryDialog::DiaryDialog(QWidget *parent)
    : QDialog(parent)
{
    textEdit = new QTextEdit(this);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(textEdit);
    layout->addWidget(buttonBox);

    setLayout(layout);

    setWindowTitle("Notebook");
}

QString DiaryDialog:: getText() const
{
    return textEdit->toPlainText();
}


MainWindow::MainWindow(QDateTime& dischargeDateTime, QWidget *parent)
    : QMainWindow(parent)
{
    SetupMainLayout();
    SetupBackground();
    SetupCountDown(dischargeDateTime);
    SetupNoteBook();
}

void MainWindow::SetupMainLayout()
{
    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);
    mainLayout -> setContentsMargins(0, 0, 0, 0);
    this -> setFixedSize(1200, 800);
    this -> setCentralWidget(centralWidget);
}

void MainWindow::SetupBackground()
{
    // Setup background image
    QPixmap image("/Users/coffree/program/substitute-military-tool/img/image.jpg");
    backgroundImage = new QLabel(centralWidget);
    backgroundImage -> setPixmap(image);
    backgroundImage -> setScaledContents(true);

    mainLayout -> addWidget(backgroundImage);
}

void MainWindow::SetupCountDown(QDateTime& dischargeDateTime)
{
    // Setup count down widget and put it to the right place
    countDown = new CountDownWidget(dischargeDateTime, centralWidget);
    countDown -> setStyleSheet("background-color: transparent;");
    countDown -> setFixedSize(800, 200);

    // Calculate best position for putting countDown widget
    int x = (this -> width() - countDown -> width()) / 2;
    int y = (this -> height() - countDown -> height()) / 4;

    countDown -> setGeometry(x, y, countDown -> width(), countDown -> height());
}

void MainWindow::SetupNoteBook()
{
    noteButton = new QPushButton("Take note", centralWidget);
    mainLayout -> addWidget(noteButton);

    connect(noteButton, &QPushButton::clicked, [&]{
        DiaryDialog diaryDialog;
        if (diaryDialog.exec() == QDialog::Accepted) {
            string text = diaryDialog.getText().toStdString();
            // 處理内容，例如保存到文件
            cout << text << endl;
        }
    });
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
