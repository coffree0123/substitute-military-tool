#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "countdown.h"

#include <QDir>
#include <QLabel>
#include <QDate>
#include <QWidget>
#include <QTimer>
#include <QInputDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QMessageBox>
#include <QMainWindow>
#include <QFileDialog>

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QDateTime& dischargeDateTime, QWidget *parent = nullptr);
    void SetupMainLayout();
    ~MainWindow();

private:
    void SetupBackground();
    void SetupCountDown(QDateTime& dischargeDateTime);
    void SetupNoteBook();
    void SetupImgViewer();
    void SetupTools();

    QWidget* centralWidget = nullptr;
    QWidget* toolWidget = nullptr;
    QLabel* backgroundImage = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    QHBoxLayout* toolLayout = nullptr;
    CountDownWidget* countDown = nullptr;
};

#endif // MAINWINDOW_H
