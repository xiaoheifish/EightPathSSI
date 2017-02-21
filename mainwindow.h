#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include "ftd2xx.h"
#include "writethread.h"
#include "masterthread.h"
#include "serialportinfomanager.h"
#include <QLabel>
#include <QList>
#include <QHash>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
private slots:
    void on_radioButtonUSB_clicked();
    void on_radioButtonUSBStop_clicked();
    void on_buttonSelfWrite_clicked();
    void on_buttonSelfRead_clicked();
    void on_buttonAddWrite_clicked();
    void on_checkBoxPathAll_clicked();
    void on_buttonUSBstart_clicked();
    void usbresponsedata(const QString &s, DWORD bytesreceived);
    void usbresponsedata2(const QString &s, DWORD bytesreceived);
    void handleComChange(const QString &s);
    void close_USB();
    void on_radioButtonSerial_clicked();
    void on_radioButtonreadstop_clicked();
    void on_buttonSelfWrite_2_clicked();
    void on_pushButton_2_clicked();

    void showResponse(const QString &s);
    void on_checkBoxPathAll_2_clicked();
    void on_buttonAddWrite_2_clicked();
    void on_buttonSerialStart_clicked();
    void pathtwosenddata();
    void showserialall(const QString &s);
    void showserial(const QString &s);
private:
    Ui::MainWindow *ui;
    FT_HANDLE ftHandle;
    writethread thread;
    serialportinfomanager timethread;
    MasterThread serialthread;
    bool USBcomm = false;
    bool USBcheckFlag = true;
    bool serialCheckFlag = true;
    QHash<int, QLabel *> hash;
    QHash<int, QLabel *> serialhash;
    QHash<int, QLabel *> hashcount;
    QHash<int, QLabel *> serialhashcount;
    QList<int> countlist;
    QList<int> serialcountlist;
    QString *channel;
    QString tempchannel;
    QString *serialchannel;
    QString serialtempchannel;
    int currentBaudRate;
    int USBstatus;
    int countpath1,countpath2,countpath3,countpath4,countpath5,countpath6,countpath7,countpath8;
    int countpath1_2,countpath2_2,countpath3_2,countpath4_2,countpath5_2,countpath6_2,countpath7_2,countpath8_2;
};

#endif // MAINWINDOW_H
