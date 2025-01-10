#include "diary.h"
#include "util.h"


DiaryDialog::DiaryDialog(QWidget *parent)
    : QDialog(parent)
{
    textEdit = new QTextEdit(this);

    // Add button to text editor
    buttonBox = new QDialogButtonBox(this);
    buttonBox -> addButton(QDialogButtonBox::Ok);
    buttonBox -> addButton(QDialogButtonBox::Cancel);
    QPushButton *clearButton = buttonBox -> addButton("Clear", QDialogButtonBox::ActionRole);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(clearButton, &QPushButton::clicked, textEdit, &QTextEdit::clear);

    QVBoxLayout *layout = new QVBoxLayout;
    layout -> addWidget(textEdit);
    layout -> addWidget(buttonBox);

    setLayout(layout);

    setWindowTitle("Notebook");

    // Save and load content to notebook
    QDate currentDate = QDate::currentDate();
    QString dateString = currentDate.toString("yyyyMMdd"); // Format date string to "yyyyMMdd"

    saveFolder = QString::fromStdString(getWorkingDir() + "/note/");
    fileName = saveFolder + "Date_" + dateString + ".txt";
    loadFileContent();
}

QString DiaryDialog::getText() const
{
    return textEdit -> toPlainText();
}

void DiaryDialog::loadFileContent()
{
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    textEdit -> setPlainText(in.readAll());
    file.close();

    // Move cursor to the end of the file
    textEdit -> moveCursor(QTextCursor::End);
}

void DiaryDialog::saveFileContent()
{
    QString text = getText();
    cout << "Save content: '" << text.toStdString() << "'" << " to " << fileName.toStdString() << "." << endl;

    // Check if the path exist, if not then create one
    QDir dir(saveFolder);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QString fileContent = text;

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << fileContent << "\n";
        file.close();
    } else {
        qDebug() << "Cannot create file!";
    }
}
