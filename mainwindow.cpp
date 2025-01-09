#include "diary.h"
#include "util.h"
#include "mainwindow.h"

using namespace std;


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
    QPixmap image(QString::fromStdString(getWorkingDir() + "/img/image.jpg"));
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
            diaryDialog.saveFileContent();
        }
    });
}

MainWindow::~MainWindow() {}
