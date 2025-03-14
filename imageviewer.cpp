#include "imageviewer.h"

ImageViewer::ImageViewer(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Image Viewer");
    imageLabel = new QLabel(this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout -> addWidget(imageLabel);
    setLayout(layout);
    resize(600, 400);
    setAcceptDrops(true);
}

void ImageViewer::dragEnterEvent(QDragEnterEvent* event)
{
    if (event -> mimeData() -> hasUrls())
    {
        event -> acceptProposedAction();
    }
}

void ImageViewer::dropEvent(QDropEvent* event)
{
    const QUrl url = event -> mimeData() -> urls().first();
    const QString filePath = url.toLocalFile();

    loadImage(filePath);
    event -> acceptProposedAction();
}

void ImageViewer::loadImage(const QString &imagePath)
{
    QPixmap pixmap(imagePath);
    this -> imageLabel -> setPixmap(pixmap);
    this -> imageLabel -> setScaledContents(true);
}
