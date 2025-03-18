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
#include <QStatusBar>
#include <QFileInfo>
#include <QWheelEvent>


class ImageViewer : public QWidget
{
public:
    ImageViewer(QWidget* parent = nullptr);
private:
    void loadImage(const QString &fileName);
    void updateImage();
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

    QLabel* imageLabel = nullptr;
    QStatusBar *statusBar;
    QPixmap originalPixmap;
    double scaleFactor = 1.0;
};

#endif // IMAGEVIEWER_H
