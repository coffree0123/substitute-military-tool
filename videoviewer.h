#ifndef VIDEOVIEWER_H
#define VIDEOVIEWER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QSlider>
#include <QLabel>

class VideoViewer : public QWidget
{
    Q_OBJECT

public:
    explicit VideoViewer(QWidget *parent = nullptr);
    ~VideoViewer();

private slots:
    void openFile();
    void play();
    void pause();
    void setPosition(int position);
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);

private:
    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;
    QPushButton *openButton;
    QPushButton *playButton;
    QPushButton *pauseButton;
    QSlider *positionSlider;
    QLabel *timeLabel;
    QVBoxLayout *mainLayout;
    QHBoxLayout *controlLayout;
};

#endif // VIDEOVIEWER_H
