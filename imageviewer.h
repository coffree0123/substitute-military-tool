#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>


class ImageViewer : public QWidget
{
public:
    ImageViewer(QWidget* parent = nullptr);
private:
    void loadImage(const QString &fileName);
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

    QLabel* imageLabel = nullptr;
};

#endif // IMAGEVIEWER_H
