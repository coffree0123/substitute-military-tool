#include "videoviewer.h"
#include <QTime>

VideoViewer::VideoViewer(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Video Viewer");
    resize(800, 600);

    // Create media player and video widget
    mediaPlayer = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    videoWidget->setMinimumSize(640, 360);
    
    mediaPlayer->setVideoOutput(videoWidget);
    
    // Create control buttons
    openButton = new QPushButton("Open Video", this);
    playButton = new QPushButton("Play", this);
    pauseButton = new QPushButton("Pause", this);
    
    // Create slider for video position
    positionSlider = new QSlider(Qt::Horizontal, this);
    positionSlider->setRange(0, 0);
    
    // Create label for time display
    timeLabel = new QLabel("00:00 / 00:00", this);
    
    // Set up layouts
    controlLayout = new QHBoxLayout();
    controlLayout->addWidget(openButton);
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(pauseButton);
    controlLayout->addWidget(positionSlider);
    controlLayout->addWidget(timeLabel);
    
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(videoWidget);
    mainLayout->addLayout(controlLayout);
    
    setLayout(mainLayout);
    
    // Connect signals and slots
    connect(openButton, &QPushButton::clicked, this, &VideoViewer::openFile);
    connect(playButton, &QPushButton::clicked, this, &VideoViewer::play);
    connect(pauseButton, &QPushButton::clicked, this, &VideoViewer::pause);
    connect(positionSlider, &QSlider::sliderMoved, this, &VideoViewer::setPosition);
    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &VideoViewer::updatePosition);
    connect(mediaPlayer, &QMediaPlayer::durationChanged, this, &VideoViewer::updateDuration);
}

VideoViewer::~VideoViewer()
{
}

void VideoViewer::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Video File", "", 
                                                  "Video Files (*.mp4 *.avi *.mov *.mkv *.wmv)");
    if (!fileName.isEmpty()) {
        mediaPlayer->setSource(QUrl::fromLocalFile(fileName));
        playButton->setEnabled(true);
        pauseButton->setEnabled(true);
    }
}

void VideoViewer::play()
{
    mediaPlayer->play();
}

void VideoViewer::pause()
{
    mediaPlayer->pause();
}

void VideoViewer::setPosition(int position)
{
    mediaPlayer->setPosition(position);
}

void VideoViewer::updatePosition(qint64 position)
{
    positionSlider->setValue(position);
    
    QTime currentTime(0, 0);
    currentTime = currentTime.addMSecs(position);
    
    QTime totalTime(0, 0);
    totalTime = totalTime.addMSecs(mediaPlayer->duration());
    
    QString timeFormat = "mm:ss";
    timeLabel->setText(currentTime.toString(timeFormat) + " / " + totalTime.toString(timeFormat));
}

void VideoViewer::updateDuration(qint64 duration)
{
    positionSlider->setRange(0, duration);
}
