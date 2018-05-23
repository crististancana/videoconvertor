#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cmdwrapper.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    sizeConvertedFile(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setup_gui_elements();

    configure_videoplayer();

    //TODO check if that works with big files also
    connect(player,&QMediaPlayer::durationChanged,slider,&QSlider::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,slider,&QSlider::setValue);
    connect(slider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);

    connect(player,&QMediaPlayer::durationChanged,bar,&QProgressBar::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,bar,&QProgressBar::setValue);
}
//Setup for gui elements
void MainWindow::setup_gui_elements()
{
    ui->comboBox->addItem("mp4");
    ui->comboBox->addItem("mov");
    ui->comboBox->addItem("h264");
    ui->comboBox->addItem("f4v");
    ui->comboBox->addItem("wmv");

    ui->comboBox_2->addItem("libx264");
    ui->comboBox_2->addItem("libx265");
    ui->comboBox_2->addItem("libxvid");
}
//Configure de videoplayer
void MainWindow::configure_videoplayer()
{
    //Allocate memory for the widgets
    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    slider = new QSlider(this);
    bar = new QProgressBar(this);
    player->setVideoOutput(vw);

    //Set the position on the screen for video player
    vw->setGeometry(170,50,800,500);
    vw->show();

    slider->setOrientation(Qt::Horizontal);

    ui->statusBar->addPermanentWidget(slider);
    ui->statusBar->addPermanentWidget(bar);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//Open file button press
void MainWindow::on_pushButton_clicked()
{
    //Open a file
    QString filename = QFileDialog::getOpenFileName(this,"Open a File","","Video File(*.*)");

    //Video should be stoped at the begining
    on_pushButton_4_clicked();

    int lastIndexDot = filename.lastIndexOf(".");

    if(lastIndexDot > 0)
    {
        extension = filename.mid(lastIndexDot+1);

        fileName_witoutextention = filename.left(lastIndexDot);
    }
    else
    {
        //TODO pop up with eroare
    }
    QFileInfo fileinfo(filename);
    if(fileinfo.exists(filename))
    {
        sizeOriginalFile = fileinfo.size();
        ui->label_7->setText(QString::number(sizeOriginalFile)+" bytes");
    }
    //set the media
    player->setMedia(QUrl::fromLocalFile(filename));
    mfilename=filename;
}

void MainWindow::on_pushButton_2_clicked()
{
    //Start video
    player->play();
    ui->statusBar->showMessage("Playing");
}

void MainWindow::on_pushButton_3_clicked()
{
    //Pause video
    player->pause();
    ui->statusBar->showMessage("Paused");
}

void MainWindow::on_pushButton_4_clicked()
{
    //Stop video
    player->stop();
    ui->statusBar->showMessage("Stoped");
}
//Execute command in system cmd(usually done on a separate thread by the caller)
void executeCommand(QString data)
{
    QByteArray ba = data.toLatin1();
    const char *c_str2 = ba.data();
    system(c_str2);
}
//Convert video button press
void MainWindow::on_pushButton_5_clicked()
{
    QString dataFile = FFMPEG_INPUT_FILE_COMMAND;

    dataFile += getOriginalFileName() + CODEC_OPTION + getCodecType() +" ";

    convertedFileName = getFileNameWithoutExtension() + "_converted."+getCovertFormat();

    dataFile += convertedFileName;

    //Run that task on a different thread to not freeze the application
    QFuture<void> future1 = QtConcurrent::run(executeCommand,dataFile);
}
//Cut video button press
void MainWindow::on_pushButton_6_clicked()
{
    QString dataFile2 = FFMPEG_INPUT_POSITION_COMMAND;
    dataFile2 += ui->lineEdit->text();
    dataFile2 += " -i ";
    dataFile2 += getOriginalFileName();
    dataFile2 += " -c copy -t ";
    dataFile2 += ui->lineEdit_2->text()+" ";
    dataFile2 += getFileNameWithoutExtension() +"_cut."+getOriginalFileFormat();

    //Execute task on a different thread
    QFuture<void> future2 = QtConcurrent::run(executeCommand,dataFile2);
}

QString MainWindow::getCovertFormat()
{
    return ui->comboBox->currentText();
}

QString MainWindow::getCodecType()
{
    return ui->comboBox_2->currentText();
}

QString MainWindow::getOriginalFileFormat()
{
    return extension;
}

QString MainWindow::getOriginalFileName()
{
    return mfilename;
}

QString MainWindow::getFileNameWithoutExtension()
{
    return fileName_witoutextention;
}
//Get converted file size button
void MainWindow::on_pushButton_7_clicked()
{
    QFileInfo fileInfo1(convertedFileName);

    if(fileInfo1.exists(convertedFileName))
    {
        sizeConvertedFile = fileInfo1.size();
        ui->label_9->setText(QString::number(sizeConvertedFile)+" bytes");
    }
}
//Calculate conversion rate
void MainWindow::on_pushButton_8_clicked()
{
    if(sizeConvertedFile != 0)
    {
        double compressionRate = (double)sizeConvertedFile/(double)sizeOriginalFile;
        ui->label_8->setText(QString::number(compressionRate));
    }else
    {
        QMessageBox::warning(this,"Warning","No file converted yet!");
    }

}
//Help button for cutting a video input
void MainWindow::on_pushButton_9_clicked()
{
    QMessageBox::information(this,"Usage of cut video","The user should enter the timestamps in this format From : 00:10:00 To: 00:20:00 that means it will cut the video from second 10 to 20 of the video  ");
}
