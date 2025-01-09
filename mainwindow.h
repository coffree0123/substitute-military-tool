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
    void SetupBackground();
    void SetupCountDown(QDateTime& dischargeDateTime);
    void SetupNoteBook();
    ~MainWindow();

private:
    QWidget* centralWidget = nullptr;
    QLabel* backgroundImage = nullptr;
    QPushButton* noteButton = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    CountDownWidget* countDown = nullptr;
};

#endif // MAINWINDOW_H
