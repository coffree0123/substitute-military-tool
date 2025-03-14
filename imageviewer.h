#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>


class ImageViewer : public QWidget
{
public:
    ImageViewer(const QString& imagePath, QWidget* parent = nullptr);
};

#endif // IMAGEVIEWER_H
