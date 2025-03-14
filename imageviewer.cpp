#include "imageviewer.h"

ImageViewer::ImageViewer(const QString& imagePath, QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Image Viewer");

    QLabel* imageLabel = new QLabel(this);
    QPixmap pixmap(imagePath);
    imageLabel -> setPixmap(pixmap);
    imageLabel -> setScaledContents(true);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout -> addWidget(imageLabel);
    setLayout(layout);

    this -> setFixedSize(600, 400);
}
