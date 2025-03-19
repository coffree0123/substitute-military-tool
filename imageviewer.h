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
#include <QScrollArea>

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
    QScrollArea *scrollArea;
    QPixmap originalPixmap;
    double scaleFactor = 0.6;
};

#endif // IMAGEVIEWER_H
