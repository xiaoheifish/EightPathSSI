#ifndef SERIALPORTINFOMANAGER_H
#define SERIALPORTINFOMANAGER_H
#include <QTimer>
#include <QThread>
class serialportinfomanager:public QThread
{
    Q_OBJECT
public:
    serialportinfomanager();
    ~serialportinfomanager();
    void queryinfo();
    void run();
    void stop();
    void setStopped(bool stopped);
signals:
    void dataChanged(const QString &s);
private:
    //QTimer *m_pTimer;
    bool stopped = false;
};

#endif // SERIALPORTINFOMANAGER_H
