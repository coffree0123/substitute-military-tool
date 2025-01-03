#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDate>
#include <QWidget>
#include <QTimer>
#include <QVBoxLayout>

class CountDownWidget : public QWidget
{
    Q_OBJECT

public:
    CountDownWidget(const QDateTime& dischargeDate, QWidget *parent = nullptr);
    ~CountDownWidget();

private:

private:
    QLabel* label;
    QTimer* timer;
    QDateTime dischargeDateTime;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QDateTime dischargeDateTime, QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget* centralWidget = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    CountDownWidget* countDown = nullptr;
};

#endif // MAINWINDOW_H
