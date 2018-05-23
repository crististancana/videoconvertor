include "cmdwrapper.h"

CmdWrapper::CmdWrapper(QObject *parent) : QObject(parent)
{
    this->moveToThread(&mThread);
    mThread.start();

    connect(&mThread,SIGNAL(started()),this,SLOT(executeCommand(QString)));
}

void CmdWrapper::executeCommand(QString data)
{
    QProcess proc;
    QString command = "cmd.exe";
    QStringList arguments =QStringList() << data ;

    proc.start(command, arguments);
    if(proc.waitForStarted()){
        qDebug() << "Starting";
    }
    proc.waitForFinished(-1);
        qDebug() << "finish";
}
