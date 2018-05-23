#ifndef CMDWRAPPER_H
#define CMDWRAPPER_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QDebug>

class CmdWrapper : public QObject
{
    Q_OBJECT
public:
    explicit CmdWrapper(QObject *parent = nullptr);

    void executeCommand(QString data);
signals:

public slots:

private:
    QThread mThread;
};

#endif // CMDWRAPPER_H
