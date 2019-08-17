#include "main-window.h"
#include "ui_main-window.h"
#include "config.h"
#include <QDebug>
#include <QMenu>
#include <QFileDialog>
#include <QMediaPlaylist>
#include <QMediaMetaData>

static const QString elapsedValueTemplate("%1/%2 seconds");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    config::init();

    ui->volumeSpinBox->setValue(config::volume());

    playList.setPlaybackMode(QMediaPlaylist::Loop);
    player.setPlaylist(&playList);
    player.setVolume(volume());

    connect(
        this, &MainWindow::customContextMenuRequested,
        this, &MainWindow::onContextMenuRequested
    );

    connect(
        &player, &QMediaPlayer::positionChanged,
        this, &MainWindow::onPlayerPositionChanged
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onContextMenuRequested(const QPoint &position)
{
    QMenu menu(QStringLiteral("Context menu"), this);

    QAction openAction(QStringLiteral("Open"), this);
    connect(
        &openAction, &QAction::triggered,
        this, &MainWindow::onOpenFileRequested
    );
    menu.addAction(&openAction);

    QAction pauseResumeAction;
    if(player.state() == QMediaPlayer::State::PlayingState){
        pauseResumeAction.setText(QStringLiteral("Pause"));
        connect(
          &pauseResumeAction, &QAction::triggered,
          &player, &QMediaPlayer::pause
        );
        menu.addAction(&pauseResumeAction);
    } else if (player.state() == QMediaPlayer::State::PausedState){
        pauseResumeAction.setText(QStringLiteral("Resume"));
        connect(
          &pauseResumeAction, &QAction::triggered,
          &player, &QMediaPlayer::play
        );
        menu.addAction(&pauseResumeAction);
    }

    menu.exec(mapToGlobal(position));
}

void MainWindow::onOpenFileRequested()
{
    const auto fileName = QFileDialog::getOpenFileName(
        this,
        QStringLiteral("Open Audio"),
        config::lastPath(),
        QStringLiteral("Audio Files (*.mp3 *.wav *.flac)")
    );

    if(fileName.isEmpty()){
        return;
    }

    const QFileInfo file(fileName);
    const auto dirPath = file.absoluteDir().path();

    config::setLastPath(dirPath);
    ui->nameValueLabel->setText(fileName);

    playList.removeMedia(0);
    playList.addMedia(QUrl::fromLocalFile(fileName));

    player.play();
}

void MainWindow::on_volumeSpinBox_valueChanged(int value)
{
    Q_UNUSED(value)
    player.setVolume(volume());
}

void MainWindow::onPlayerPositionChanged(const int value)
{
    const auto _uiVolume = volume();
    if(_uiVolume != config::volume()){
        config::setVolume(_uiVolume);
    }

    const auto elapsedValueText = elapsedValueTemplate
        .arg(value / 1000)
        .arg(player.duration() / 1000);
    ui->elapsedValueLabel->setText(elapsedValueText);
}

int MainWindow::volume() const
{
    return ui->volumeSpinBox->value();
}
