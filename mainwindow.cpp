#include "diary.h"
#include "imageviewer.h"
#include "videoviewer.h"
#include "util.h"
#include "mainwindow.h"

using namespace std;


MainWindow::MainWindow(QDateTime& dischargeDateTime, QWidget *parent)
    : QMainWindow(parent)
{
    SetupBackground();
    SetupMainLayout();
    SetupCountDown(dischargeDateTime);
    SetupTools();
}

void MainWindow::SetupMainLayout()
{
    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);
    centralWidget -> setLayout(mainLayout);
    this -> setFixedSize(1200, 800);
    this -> setCentralWidget(centralWidget);
}

void MainWindow::SetupBackground()
{
    // Setup background image
    QString imagePath = QString::fromStdString(getWorkingDir() + "/img/image.jpg");

    // Setup style
    QString styleSheet = QString("QMainWindow { border-image: url(%1); }").arg(imagePath);
    this -> setStyleSheet(styleSheet);
}

void MainWindow::SetupCountDown(QDateTime& dischargeDateTime)
{
    // Setup count down widget and put it to the right place
    countDown = new CountDownWidget(dischargeDateTime, centralWidget);
    mainLayout -> addWidget(countDown);
}

void MainWindow::SetupTools()
{
    // Create tool widget and corresponding layout
    toolWidget = new QWidget(centralWidget);
    mainLayout -> addWidget(toolWidget);
    toolLayout = new QHBoxLayout(toolWidget);
    toolWidget -> setLayout(toolLayout);

    // Setup tools
    SetupNoteBook();
    SetupImgViewer();
    SetupVideoViewer();
}

void MainWindow::SetupNoteBook()
{
    QPushButton* noteButton = new QPushButton("Take note", toolWidget);

    connect(noteButton, &QPushButton::clicked, [&]{
        DiaryDialog diaryDialog;
        if (diaryDialog.exec() == QDialog::Accepted) {
            diaryDialog.saveFileContent();
        }
    });

    toolLayout -> addWidget(noteButton);
}

void MainWindow::SetupImgViewer()
{
    QPushButton* imgButton = new QPushButton("Image viewer", toolWidget);

    connect(imgButton, &QPushButton::clicked, [&]{
        ImageViewer* imgViewer = new ImageViewer();
        imgViewer -> show();
    });

    toolLayout -> addWidget(imgButton);
}

void MainWindow::SetupVideoViewer()
{
    QPushButton* videoButton = new QPushButton("Video viewer", toolWidget);

    connect(videoButton, &QPushButton::clicked, [&]{
        VideoViewer* videoViewer = new VideoViewer();
        videoViewer -> show();
    });

    toolLayout -> addWidget(videoButton);
}

MainWindow::~MainWindow() {}
