#include "imageviewer.h"

ImageViewer::ImageViewer(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Image Viewer");
    imageLabel = new QLabel(this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout -> addWidget(imageLabel);
    statusBar = new QStatusBar(this);
    layout -> addWidget(statusBar);
    statusBar -> setFixedHeight(20);

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
    int width = pixmap.width();
    int height = pixmap.height();
    QFileInfo fileInfo(imagePath);
    int byteSize = fileInfo.size();

    QString statusInfo = QString("(Width * Height): %1x%2, File size: %3 bytes")
                             .arg(width)
                             .arg(height)
                             .arg(byteSize);
    this -> statusBar -> showMessage(statusInfo);

    this -> imageLabel -> setPixmap(pixmap);
    this -> imageLabel -> setScaledContents(true);
}
