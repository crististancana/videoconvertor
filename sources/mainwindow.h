#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>
#include <QtConcurrent/QtConcurrentRun>
#include <QFuture>
#include <QElapsedTimer>

//Define ffmpeg macros
#define FFMPEG_INPUT_FILE_COMMAND "ffmpeg -i "
#define FFMPEG_INPUT_POSITION_COMMAND "ffmpeg -ss "
#define CODEC_OPTION " -c:v "

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    QString getCovertFormat();

    QString getCodecType();

    QString getOriginalFileFormat();

    QString getOriginalFileName();

    QString getFileNameWithoutExtension();

    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void setup_gui_elements();

    void configure_videoplayer();

private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    QVideoWidget* vw;
    QProgressBar* bar;
    QTimer* timer;
    QElapsedTimer *eltimer;
    QSlider* slider;
    QString mfilename;
    QString fileName_witoutextention;
    QString extension;
    qint64 sizeOriginalFile;
    qint64 sizeConvertedFile;
    QString convertedFileName;

};

#endif // MAINWINDOW_H
