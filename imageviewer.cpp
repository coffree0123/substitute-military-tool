#include "imageviewer.h"

ImageViewer::ImageViewer(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Image Viewer");
    this -> setAttribute(Qt::WA_DeleteOnClose);
    imageLabel = new QLabel(this);
    imageLabel -> setAlignment(Qt::AlignCenter);
    
    scrollArea = new QScrollArea(this);
    scrollArea -> setWidget(imageLabel);
    scrollArea -> setWidgetResizable(true);
    scrollArea -> setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout -> addWidget(scrollArea);
    statusBar = new QStatusBar(this);
    layout -> addWidget(statusBar);
    statusBar -> setFixedHeight(20);

    setLayout(layout);
    resize(600, 400);
    setAcceptDrops(true);
}

void ImageViewer::dragEnterEvent(QDragEnterEvent *event)
{
    if (event -> mimeData() -> hasUrls())
    {
        event -> acceptProposedAction();
    }
}

void ImageViewer::dropEvent(QDropEvent *event)
{
    const QUrl url = event -> mimeData() -> urls().first();
    const QString filePath = url.toLocalFile();

    loadImage(filePath);
    updateImage();
    event -> acceptProposedAction();
}

void ImageViewer::loadImage(const QString &imagePath)
{
    originalPixmap.load(imagePath);
    int width = originalPixmap.width();
    int height = originalPixmap.height();
    QFileInfo fileInfo(imagePath);
    int byteSize = fileInfo.size();

    QString statusInfo = QString("(Width * Height): %1x%2, File size: %3 bytes")
                             .arg(width)
                             .arg(height)
                             .arg(byteSize);
    this -> statusBar -> showMessage(statusInfo);
}

void ImageViewer::updateImage()
{
    if (originalPixmap.isNull())
        return;

    QPixmap scaledPixmap = originalPixmap.scaled(
        originalPixmap.size() * scaleFactor,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation);

    imageLabel -> setPixmap(scaledPixmap);
    imageLabel -> resize(scaledPixmap.size());

    // Update status bar and show zoom information
    QString currentStatus = statusBar -> currentMessage();
    QString zoomInfo = QString(" | Zoom: %1%").arg(scaleFactor * 100);
    statusBar -> showMessage(currentStatus.split(" |").first() + zoomInfo);
}

void ImageViewer::wheelEvent(QWheelEvent *event)
{
    // Scrolling up gives positive delta, scrolling down gives negative delta
    int delta = event -> angleDelta().y();

    // Adjust the scaling factor, zoom 10% each time
    if (delta > 0)
    {
        // Zoom out
        scaleFactor -= 0.05;
    }
    else
    {
        // Zoom in
        scaleFactor += 0.05;
    }

    // Limit the scaling range to prevent excessive zooming
    if (scaleFactor < 0.1)
        scaleFactor = 0.1;
    if (scaleFactor > 2.0)
        scaleFactor = 2.0;

    updateImage();

    event -> accept();
}
