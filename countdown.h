#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QDir>
#include <QLabel>
#include <QDate>
#include <QWidget>
#include <QTimer>
#include <QPushButton>
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

#endif // COUNTDOWN_H
