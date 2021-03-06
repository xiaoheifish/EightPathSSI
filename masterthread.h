#ifndef MASTERTHREAD_H
#define MASTERTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QHash>
class MasterThread : public QThread
{
    Q_OBJECT

public:
    MasterThread(QObject *parent = 0);
    ~MasterThread();

    void transaction(const QString &portName, int baudRate,int waitTimeout, const QString &request, int writeread);
    void run();
    void stop();
    void setReading(int isReading);
    void StringToHex(QString str, QByteArray &senddata);
    char ConvertHexChar(char ch);
    int getState();
signals:
    void response(const QString &s);
    void error(const QString &s);
    void timeout(const QString &s);
    void responserialall(const QString &s);
    void responserial(const QString &s);
    void pathtwosend();
private:
    QString portName;
    qint32 baudRate;
    QString request;
    int waitTimeout;
    int writeread;
    int isReading;
    QMutex mutex;
    //QMutex m_mutex;
    QHash<int, qint32> hash;
    QWaitCondition cond;
    bool quit;
    bool working;
};


#endif // MASTERTHREAD_H
