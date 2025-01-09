#ifndef DIARY_H
#define DIARY_H

#include <QDir>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QMessageBox>


class DiaryDialog : public QDialog {
public:
    DiaryDialog(QWidget *parent = nullptr);
    ~DiaryDialog() = default;

    QString getText() const;
    void loadFileContent();
    void saveFileContent();

private:
    QString saveFolder;
    QString fileName;
    QTextEdit *textEdit;
    QDialogButtonBox *buttonBox;
};

#endif // DIARY_H
