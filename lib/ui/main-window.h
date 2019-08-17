#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onContextMenuRequested(const QPoint& position);
    void onOpenFileRequested();

    void on_volumeSpinBox_valueChanged(int volume);
    void onPlayerPositionChanged(const int value);

private:
    int volume() const;

private:
    Ui::MainWindow *ui;
    QMediaPlaylist playList;
    QMediaPlayer player;
};

#endif // MAINWINDOW_H
