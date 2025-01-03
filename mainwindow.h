#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDate>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget* centralWidget = nullptr;
};


class CountDownWidget : public QWidget
{
    Q_OBJECT

public:
    CountDownWidget(const QDateTime& dischargeDate, QWidget *parent = nullptr);
    ~CountDownWidget();

private:
    void updateDisplay();

private:
    QLabel* label;
    QTimer* timer;
    QDateTime dischargeDateTime;
};

#endif // MAINWINDOW_H
