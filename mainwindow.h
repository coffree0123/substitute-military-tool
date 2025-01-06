#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

class DiaryDialog : public QDialog {
public:
    DiaryDialog(QWidget *parent = nullptr);
    ~DiaryDialog() = default;

    QString getText() const;

private:
    QTextEdit *textEdit;
    QDialogButtonBox *buttonBox;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QDateTime& dischargeDateTime, QWidget *parent = nullptr);
    void SetupMainLayout();
    void SetupBackground();
    void SetupCountDown(QDateTime& dischargeDateTime);
    ~MainWindow();

private:
    QWidget* centralWidget = nullptr;
    QLabel* backgroundImage = nullptr;
    QPushButton* noteButton = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    CountDownWidget* countDown = nullptr;
};

#endif // MAINWINDOW_H
