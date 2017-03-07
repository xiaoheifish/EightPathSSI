#pragma comment(lib, "D:\\Qt\\Project\\EightPathSSI\\ftd2xx.lib")
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QMessageBox>
#include <iostream>
#include <QStringList>
#include <QtSerialPort/QSerialPort>
#define TxSector (1024*64)
#define RxSector (1024*64)
using namespace std;
inline string i2s(int number)
{
    //new code
    string s;
    if(number == 0){
        s = (char)(0 + '0');
    }
    while(number != 0)
    {
        s = (char)(number % 10 + '0') + s;
        number = number / 10;
    }
    return s;
}
inline QString s2q(const string &s)
{
    return QString(QString::fromLocal8Bit(s.c_str()));
}
inline QByteArray intToByte(int i)
{
    QByteArray abyte0;
    abyte0.resize(4);
    abyte0[0] = (uchar)  (0x000000ff & i);
    abyte0[1] = (uchar) ((0x0000ff00 & i) >> 8);
    abyte0[2] = (uchar) ((0x00ff0000 & i) >> 16);
    abyte0[3] = (uchar) ((0xff000000 & i) >> 24);
    return abyte0;
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qRegisterMetaType<DWORD>("DWORD");
    ui->setupUi(this);
    ui->tabWidget->setStyleSheet("QTabWidget:pane{border-top:0px solid #e8f3f9;background:transparent;}");
    timethread.start();
    channel = new QString;
    *channel = "";
    serialchannel = new QString;
    *serialchannel = "";
    //qDebug()<<(*channel).toInt();
    countpath1=0;
    countpath2=0;
    countpath3=0;
    countpath4=0;
    countpath5=0;
    countpath6=0;
    countpath7=0;
    countpath8=0;
    countpath1_2=0;
    countpath2_2=0;
    countpath3_2=0;
    countpath4_2=0;
    countpath5_2=0;
    countpath6_2=0;
    countpath7_2=0;
    countpath8_2=0;
    hash.insert(0,(ui->labelPath11));
    hash.insert(1,(ui->labelPath12));
    hash.insert(2,(ui->labelPath13));
    hash.insert(3,(ui->labelPath14));
    hash.insert(4,(ui->labelPath21));
    hash.insert(5,(ui->labelPath22));
    hash.insert(6,(ui->labelPath23));
    hash.insert(7,(ui->labelPath24));
    hash.insert(8,(ui->labelPath31));
    hash.insert(9,(ui->labelPath32));
    hash.insert(10,(ui->labelPath33));
    hash.insert(11,(ui->labelPath34));
    hash.insert(12,(ui->labelPath41));
    hash.insert(13,(ui->labelPath42));
    hash.insert(14,(ui->labelPath43));
    hash.insert(15,(ui->labelPath44));
    hash.insert(16,(ui->labelPath51));
    hash.insert(17,(ui->labelPath52));
    hash.insert(18,(ui->labelPath53));
    hash.insert(19,(ui->labelPath54));
    hash.insert(20,(ui->labelPath61));
    hash.insert(21,(ui->labelPath62));
    hash.insert(22,(ui->labelPath63));
    hash.insert(23,(ui->labelPath64));
    hash.insert(24,(ui->labelPath71));
    hash.insert(25,(ui->labelPath72));
    hash.insert(26,(ui->labelPath73));
    hash.insert(27,(ui->labelPath74));
    hash.insert(28,(ui->labelPath81));
    hash.insert(29,(ui->labelPath82));
    hash.insert(30,(ui->labelPath83));
    hash.insert(31,(ui->labelPath84));
    serialhash.insert(0,(ui->labelPath11_2));
    serialhash.insert(1,(ui->labelPath12_2));
    serialhash.insert(2,(ui->labelPath13_2));
    serialhash.insert(3,(ui->labelPath14_2));
    serialhash.insert(4,(ui->labelPath21_2));
    serialhash.insert(5,(ui->labelPath22_2));
    serialhash.insert(6,(ui->labelPath23_2));
    serialhash.insert(7,(ui->labelPath24_2));
    serialhash.insert(8,(ui->labelPath31_2));
    serialhash.insert(9,(ui->labelPath32_2));
    serialhash.insert(10,(ui->labelPath33_2));
    serialhash.insert(11,(ui->labelPath34_2));
    serialhash.insert(12,(ui->labelPath41_2));
    serialhash.insert(13,(ui->labelPath42_2));
    serialhash.insert(14,(ui->labelPath43_2));
    serialhash.insert(15,(ui->labelPath44_2));
    serialhash.insert(16,(ui->labelPath51_2));
    serialhash.insert(17,(ui->labelPath52_2));
    serialhash.insert(18,(ui->labelPath53_2));
    serialhash.insert(19,(ui->labelPath54_2));
    serialhash.insert(20,(ui->labelPath61_2));
    serialhash.insert(21,(ui->labelPath62_2));
    serialhash.insert(22,(ui->labelPath63_2));
    serialhash.insert(23,(ui->labelPath64_2));
    serialhash.insert(24,(ui->labelPath71_2));
    serialhash.insert(25,(ui->labelPath72_2));
    serialhash.insert(26,(ui->labelPath73_2));
    serialhash.insert(27,(ui->labelPath74_2));
    serialhash.insert(28,(ui->labelPath81_2));
    serialhash.insert(29,(ui->labelPath82_2));
    serialhash.insert(30,(ui->labelPath83_2));
    serialhash.insert(31,(ui->labelPath84_2));
    //qDebug()<<ui->labelPath84_2->pos();
    hashcount.insert(0,(ui->labelCount1));
    hashcount.insert(1,(ui->labelCount2));
    hashcount.insert(2,(ui->labelCount3));
    hashcount.insert(3,(ui->labelCount4));
    hashcount.insert(4,(ui->labelCount5));
    hashcount.insert(5,(ui->labelCount6));
    hashcount.insert(6,(ui->labelCount7));
    hashcount.insert(7,(ui->labelCount8));
    serialhashcount.insert(0,(ui->labelCount1_2));
    serialhashcount.insert(1,(ui->labelCount2_2));
    serialhashcount.insert(2,(ui->labelCount3_2));
    serialhashcount.insert(3,(ui->labelCount4_2));
    serialhashcount.insert(4,(ui->labelCount5_2));
    serialhashcount.insert(5,(ui->labelCount6_2));
    serialhashcount.insert(6,(ui->labelCount7_2));
    serialhashcount.insert(7,(ui->labelCount8_2));
    countlist<<countpath1<<countpath2<<countpath3<<countpath4<<countpath5<<countpath6<<countpath7<<countpath8;
    serialcountlist<<countpath1_2<<countpath2_2<<countpath3_2<<countpath4_2<<countpath5_2<<countpath6_2<<countpath7_2<<countpath8_2;
    connect(&thread, SIGNAL(usbresponse(QString, DWORD)),
            this,SLOT(usbresponsedata(QString,DWORD)));
    connect(&thread, SIGNAL(usbresponse2(QString,DWORD)),
            this,SLOT(usbresponsedata2(QString,DWORD)));
    connect(&thread, SIGNAL(close_USBsignal()),
            this, SLOT(close_USB()));
    connect(&timethread, SIGNAL(dataChanged(QString)),
            this,SLOT(handleComChange(QString)));
    connect(&serialthread, SIGNAL(response(QString)),
            this, SLOT(showResponse(QString)));
    connect(&serialthread, SIGNAL(pathtwosend()),
            this,SLOT(pathtwosenddata()));
    connect(&serialthread, SIGNAL(responserialall(QString)),
            this,SLOT(showserialall(QString)));
    connect(&serialthread, SIGNAL(responserial(QString)),
            this,SLOT(showserial(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    if(thread.isRunning()){
        thread.stop();
    }
    if(serialthread.isRunning()){
        serialthread.setReading(0);
        serialthread.stop();
    }
    if(timethread.isRunning()){
        timethread.setStopped(true);
    }
    timethread.quit();
    if(!timethread.wait(2000)){
        timethread.terminate();
        timethread.wait();
    }
    if(USBcomm == true){
        FT_Close(ftHandle);
    }
    if (channel != NULL){
        delete channel;
        channel = NULL;
    }
    if(serialchannel!=NULL){
        delete serialchannel;
        serialchannel = NULL;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //qDebug()<<event->pos();
}
//draw line between items
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor(221,221,221));
    painter.setPen(pen);
    if(ui->tabWidget->currentIndex()==0){
        //draw line for SSI digit
        painter.drawLine(QPointF(21,224),QPointF(300,224));
        painter.drawLine(QPointF(21,244),QPointF(300,244));
        painter.drawLine(QPointF(21,270),QPointF(300,270));
        painter.drawLine(QPointF(21,291),QPointF(300,291));
        painter.drawLine(QPointF(21,319),QPointF(300,319));
        painter.drawLine(QPointF(21,339),QPointF(300,339));
        painter.drawLine(QPointF(21,369),QPointF(300,369));
        painter.drawLine(QPointF(21,386),QPointF(300,386));
        painter.drawLine(QPointF(21,417),QPointF(300,417));
        painter.drawLine(QPointF(21,444),QPointF(300,444));
        painter.drawLine(QPointF(21,475),QPointF(300,475));
        painter.drawLine(QPointF(161,224),QPointF(161,474));
        //draw line for selftest
        painter.drawLine(QPointF(21,122),QPointF(300,122));
        painter.drawLine(QPointF(21,154),QPointF(300,154));
        painter.drawLine(QPointF(21,184),QPointF(300,184));
        painter.drawLine(QPointF(113,122),QPointF(113,184));
        painter.drawLine(QPointF(213,122),QPointF(213,184));
        //draw line for data show
        painter.drawLine(QPointF(310,125),QPointF(740,125));
        painter.drawLine(QPointF(310,159),QPointF(740,159));
        painter.drawLine(QPointF(310,202),QPointF(740,202));
        painter.drawLine(QPointF(310,240),QPointF(740,240));
        painter.drawLine(QPointF(310,280),QPointF(740,280));
        painter.drawLine(QPointF(310,318),QPointF(740,318));
        painter.drawLine(QPointF(310,356),QPointF(740,356));
        painter.drawLine(QPointF(310,397),QPointF(740,397));
        painter.drawLine(QPointF(310,438),QPointF(740,438));
        painter.drawLine(QPointF(310,472),QPointF(740,472));
        painter.drawLine(QPointF(378,125),QPointF(378,472));
        painter.drawLine(QPointF(453,125),QPointF(453,472));
        painter.drawLine(QPointF(526,125),QPointF(526,472));
        painter.drawLine(QPointF(597,125),QPointF(597,472));
        painter.drawLine(QPointF(670,125),QPointF(670,472));

    }
    if(ui->tabWidget->currentIndex()==1){
        //draw line for self test
        int pointx = 21;
        int pointy = 120;
        painter.drawLine(QPointF(pointx,pointy),QPointF(pointx+250,pointy));
        painter.drawLine(QPointF(pointx,pointy+34),QPointF(pointx+250,pointy+34));
        painter.drawLine(QPointF(pointx,pointy+65),QPointF(pointx+250,pointy+65));
        painter.drawLine(QPointF(pointx+127,pointy),QPointF(pointx+127,pointy+65));
        //draw line for SSI digit
        int pointx1 = 21;
        int pointy1 = 221;
        painter.drawLine(QPointF(pointx1,pointy1),QPointF(pointx1+250,pointy1));
        painter.drawLine(QPointF(pointx1,pointy1+22),QPointF(pointx1+250,pointy1+22));
        painter.drawLine(QPointF(pointx1,pointy1+49),QPointF(pointx1+250,pointy1+49));
        painter.drawLine(QPointF(pointx1,pointy1+70),QPointF(pointx1+250,pointy1+70));
        painter.drawLine(QPointF(pointx1,pointy1+98),QPointF(pointx1+250,pointy1+98));
        painter.drawLine(QPointF(pointx1,pointy1+118),QPointF(pointx1+250,pointy1+118));
        painter.drawLine(QPointF(pointx1,pointy1+148),QPointF(pointx1+250,pointy1+148));
        painter.drawLine(QPointF(pointx1,pointy1+168),QPointF(pointx1+250,pointy1+168));
        painter.drawLine(QPointF(pointx1,pointy1+193),QPointF(pointx1+250,pointy1+193));
        painter.drawLine(QPointF(pointx1,pointy1+223),QPointF(pointx1+250,pointy1+223));
        painter.drawLine(QPointF(pointx1,pointy1+253),QPointF(pointx1+250,pointy1+253));
        painter.drawLine(QPointF(pointx1+125,pointy1),QPointF(pointx1+125,pointy1+253));
        //draw line for data show
        int pointx2 = 300;
        int pointy2 = 125;
        painter.drawLine(QPointF(pointx2,pointy2),QPointF(pointx2+430,pointy2));
        painter.drawLine(QPointF(pointx2,pointy2+34),QPointF(pointx2+430,pointy2+34));
        painter.drawLine(QPointF(pointx2,pointy2+77),QPointF(pointx2+430,pointy2+77));
        painter.drawLine(QPointF(pointx2,pointy2+115),QPointF(pointx2+430,pointy2+115));
        painter.drawLine(QPointF(pointx2,pointy2+155),QPointF(pointx2+430,pointy2+155));
        painter.drawLine(QPointF(pointx2,pointy2+193),QPointF(pointx2+430,pointy2+193));
        painter.drawLine(QPointF(pointx2,pointy2+231),QPointF(pointx2+430,pointy2+231));
        painter.drawLine(QPointF(pointx2,pointy2+272),QPointF(pointx2+430,pointy2+272));
        painter.drawLine(QPointF(pointx2,pointy2+313),QPointF(pointx2+430,pointy2+313));
        painter.drawLine(QPointF(pointx2,pointy2+347),QPointF(pointx2+430,pointy2+347));
        //painter.drawLine(QPointF(pointx2+82,pointy2),QPointF(pointx2+82,pointy2+347));
        //painter.drawLine(QPointF(pointx2+168,pointy2),QPointF(pointx2+168,pointy2+347));
        //painter.drawLine(QPointF(pointx2+249,pointy2),QPointF(pointx2+249,pointy2+347));
        //painter.drawLine(QPointF(pointx2+336,pointy2),QPointF(pointx2+336,pointy2+347));
        painter.drawLine(QPointF(pointx2+68,pointy2),QPointF(pointx2+68,pointy2+347));
        painter.drawLine(QPointF(pointx2+140,pointy2),QPointF(pointx2+140,pointy2+347));
        painter.drawLine(QPointF(pointx2+215,pointy2),QPointF(pointx2+215,pointy2+347));
        painter.drawLine(QPointF(pointx2+285,pointy2),QPointF(pointx2+285,pointy2+347));
        painter.drawLine(QPointF(pointx2+359,pointy2),QPointF(pointx2+359,pointy2+347));
    }
}
//Start USB Communication
void MainWindow::on_radioButtonUSB_clicked()
{
    USBcomm = true;
    UCHAR LatencyTimer = 2;
    UCHAR Mode = 0x40;//Set single chanel synchronous FT245 mode
    UCHAR Mask = 0xff;//written to device
    FT_STATUS ftStatus = FT_Open(0, &ftHandle);
    if(ftStatus == FT_OK)
    {
        ftStatus = FT_SetBitMode(ftHandle, Mask, Mode);
    }
    if (ftStatus == FT_OK)
    {
        ftStatus = FT_SetLatencyTimer(ftHandle, LatencyTimer);
        ftStatus = FT_SetUSBParameters(ftHandle, RxSector, TxSector); // (64KB, 512B)
        ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_RTS_CTS, 0, 0);
        ftStatus = FT_Purge(ftHandle, FT_PURGE_RX | FT_PURGE_TX);
    }
}
//Stop USB Communication
void MainWindow::on_radioButtonUSBStop_clicked()
{
    if(thread.isRunning()){
        thread.setReading(0);
    }
    if(USBstatus == 1 || USBstatus == 2){
        FT_Close(ftHandle);
    }
}
//USB self test, send a number to FPGA
void MainWindow::on_buttonSelfWrite_clicked()
{
    USBstatus = 1;
    BYTE TxBufferAdd[2]={0};
    DWORD BytesWritten;
    TxBufferAdd[0]=0x01;
    TxBufferAdd[1]=(ui->textSelfWrite->text()).toInt();
    FT_STATUS ftStatus = FT_Write(ftHandle, TxBufferAdd, 2, &BytesWritten);
    if(ftStatus == FT_OK){
        QMessageBox::information(this, "Message", "自检数据已经写入硬件");
    }
}
//USB self test, get the number sent before to` FPGA
void MainWindow::on_buttonSelfRead_clicked()
{
    USBstatus = 2;
    BYTE TxBufferSelf[1]={0};
    BYTE RxBuffer[4]={0};
    DWORD BytesReceived;
    DWORD BytesWritten;
    TxBufferSelf[0]=0x08;
    FT_STATUS ftStatus = FT_Write(ftHandle, TxBufferSelf, 1, &BytesWritten);
    if (ftStatus == FT_OK)
    {
        ftStatus = FT_Read(ftHandle,RxBuffer,4,&BytesReceived);
        for(unsigned int i = 0; i < BytesReceived; i++){
            if (RxBuffer[i]!=0 ){
                ui->textSelfRead->setText(tr("Data:%1").arg(QString::number(RxBuffer[i],10)));
                //ui->textSelfRead->setText(QString::number(RxBuffer[i],10));
            }
        }
    }
}
//Choose which path to use and tell digits to FPGA
void MainWindow::on_buttonAddWrite_clicked()
{
    USBstatus = 3;
    BYTE TxBufferAdd[2]={0};
    DWORD BytesWritten;
    FT_STATUS ftStatus;
    *channel = "";
    if(ui->checkBoxPathAll->isChecked()){
        TxBufferAdd[0]=0x18;
        TxBufferAdd[1]=ui->textPathAll->text().toInt();
        ftStatus = FT_Write(ftHandle, TxBufferAdd, 2, &BytesWritten);
        channel->append("91");
    }
    else{
        if(ui->checkBoxPathOne->isChecked()){
            TxBufferAdd[0]=0x10;
            TxBufferAdd[1]=ui->textPathOne->text().toInt();
            ftStatus = FT_Write(ftHandle, TxBufferAdd, 2, &BytesWritten);
            channel->append("11");
        }
        if(ui->checkBoxPathTwo->isChecked()){
            TxBufferAdd[0]=0x11;
            TxBufferAdd[1]=ui->textPathTwo->text().toInt();
            ftStatus = FT_Write(ftHandle, TxBufferAdd, 2, &BytesWritten);
            channel->append("21");
        }
        if(ui->checkBoxPathThree->isChecked()){
            TxBufferAdd[0]=0x12;
            TxBufferAdd[1]=ui->textPathThree->text().toInt();
            ftStatus = FT_Write(ftHandle, TxBufferAdd, 2, &BytesWritten);
            channel->append("31");
        }
        if(ui->checkBoxPathFour->isChecked()){
            TxBufferAdd[0]=0x13;
            TxBufferAdd[1]=ui->textPathFour->text().toInt();
            ftStatus = FT_Write(ftHandle, TxBufferAdd, 2, &BytesWritten);
            channel->append("41");
        }
        if(ui->checkBoxPathFive->isChecked()){
            TxBufferAdd[0]=0x14;
            TxBufferAdd[1]=ui->textPathFive->text().toInt();
            ftStatus = FT_Write(ftHandle, TxBufferAdd, 2, &BytesWritten);
            channel->append("51");
        }
        if(ui->checkBoxPathSix->isChecked()){
            TxBufferAdd[0]=0x15;
            TxBufferAdd[1]=ui->textPathSix->text().toInt();
            ftStatus = FT_Write(ftHandle, TxBufferAdd, 2, &BytesWritten);
            channel->append("61");
        }
        if(ui->checkBoxPathSeven->isChecked()){
            TxBufferAdd[0]=0x16;
            TxBufferAdd[1]=ui->textPathSeven->text().toInt();
            ftStatus = FT_Write(ftHandle, TxBufferAdd, 2, &BytesWritten);
            channel->append("71");
        }
        if(ui->checkBoxPathEight->isChecked()){
            TxBufferAdd[0]=0x17;
            TxBufferAdd[1]=ui->textPathEight->text().toInt();
            ftStatus = FT_Write(ftHandle, TxBufferAdd, 2, &BytesWritten);
            channel->append("81");
        }
    }
    if(tempchannel != *channel){
        tempchannel = *channel;
    }
    QMessageBox::information(this, "Message", "位宽数据已经写入硬件");
}
//Choose all paths shortcut
void MainWindow::on_checkBoxPathAll_clicked()
{
    if(USBcheckFlag){
        ui->textPathOne->setText("");
        ui->textPathTwo->setText("");
        ui->textPathThree->setText("");
        ui->textPathFour->setText("");
        ui->textPathFive->setText("");
        ui->textPathSix->setText("");
        ui->textPathSeven->setText("");
        ui->textPathEight->setText("");
        ui->checkBoxPathOne->setCheckState(Qt::Checked);
        ui->checkBoxPathTwo->setCheckState(Qt::Checked);
        ui->checkBoxPathThree->setCheckState(Qt::Checked);
        ui->checkBoxPathFour->setCheckState(Qt::Checked);
        ui->checkBoxPathFive->setCheckState(Qt::Checked);
        ui->checkBoxPathSix->setCheckState(Qt::Checked);
        ui->checkBoxPathSeven->setCheckState(Qt::Checked);
        ui->checkBoxPathEight->setCheckState(Qt::Checked);
    }
    if(!USBcheckFlag){
        ui->checkBoxPathOne->setCheckState(Qt::Unchecked);
        ui->checkBoxPathTwo->setCheckState(Qt::Unchecked);
        ui->checkBoxPathThree->setCheckState(Qt::Unchecked);
        ui->checkBoxPathFour->setCheckState(Qt::Unchecked);
        ui->checkBoxPathFive->setCheckState(Qt::Unchecked);
        ui->checkBoxPathSix->setCheckState(Qt::Unchecked);
        ui->checkBoxPathSeven->setCheckState(Qt::Unchecked);
        ui->checkBoxPathEight->setCheckState(Qt::Unchecked);
    }
    USBcheckFlag = !USBcheckFlag;
}
//Start continuous USB communication
void MainWindow::on_buttonUSBstart_clicked()
{
    *channel = tempchannel;
    thread.setChannel(channel);
    thread.setFtHandle(ftHandle);
    thread.transaction();
    //*channel = "";
}

void MainWindow::usbresponsedata(const QString &s, DWORD bytesreceived)
{
    for(int i=0; i<bytesreceived; i++){
        hash[i]->setText(s.mid(i*2,2));
        if((i+1)%4==0){
            countlist[(i+1)%4]+=1;
            hashcount[(i+1)%4]->setText(QString::number(countlist[(i+1)%4],10));
        }
    }
}
//assume tempchannel = "112141",then currentPath = "124"
//hash[0]-hash[4],hash[5]-hash[8],hash[12]-hash[15]
//countlist[0],countlist[1],countlist[3]
//hashcount[0],hashcount[1],hashcount[3]
void MainWindow::usbresponsedata2(const QString &s, DWORD bytesreceived)
{
    //    if(tempchannel.length()*2!=bytesreceived){
    //        QMessageBox::information(this, "Message", "数据有误");
    //        return;
    //    }
    QString currentPath;
    for(int i=1; i<tempchannel.length(); i++){
        if(tempchannel.at(i)=="1"){
            currentPath.append(tempchannel.at(i-1));
        }
    }
//    if(currentPath.contains("11")){
//        currentPath = currentPath.mid(1);
//    }
    for(int i=0; i<currentPath.length(); i++){
        for(int j=0; j<4; j++){
            QString showtext = s.mid((i*4+j)*2,2);
            hash[(QString(currentPath.at(i)).toInt()-1)*4+j]->setText(showtext);
        }
        countlist[QString(currentPath.at(i)).toInt()-1]+=1;
        hashcount[QString(currentPath.at(i)).toInt()-1]->setText(QString::number(countlist[QString(currentPath.at(i)).toInt()-1],10));
    }
}

void MainWindow::handleComChange(const QString &s)
{
    QStringList myList;
    myList = s.split(" ");
    for(int i =0;i < ui->serialPortComboBox->count();i++){
        ui->serialPortComboBox->removeItem(0);
    }
    for(int i = 0;i<myList.size();i++){
        if(!(myList[i]==""))
            ui->serialPortComboBox->addItem(myList[i]);
    }
    ui->serialPortComboBox->setFocus();
}

void MainWindow::close_USB()
{
    FT_Close(ftHandle);
}

void MainWindow::on_radioButtonSerial_clicked()
{
    int writeread = 9;
    int timeout = 1000;
    if(ui->serialPortComboBox->currentText()!=""){
        currentBaudRate = ui->comboBoxBaud->currentIndex();
        serialthread.transaction(ui->serialPortComboBox->currentText(),
                                 ui->comboBoxBaud->currentIndex(),
                                 timeout,
                                 "FF",
                                 writeread);
    }
}

void MainWindow::on_radioButtonreadstop_clicked()
{
    serialthread.setReading(0);
    if(serialthread.getState()!=12){
        int writeread = 9;
        int timeout = 1000;
        if(ui->serialPortComboBox->currentText()!=""){
            currentBaudRate = ui->comboBoxBaud->currentIndex();
            serialthread.transaction(ui->serialPortComboBox->currentText(),
                                     ui->comboBoxBaud->currentIndex(),
                                     timeout,
                                     "88",
                                     writeread);
        }
    }
}

void MainWindow::on_buttonSelfWrite_2_clicked()
{
    int writeread = 10;
    int timeout = 1000;
    serialthread.transaction(ui->serialPortComboBox->currentText(),
                             ui->comboBoxBaud->currentIndex(),
                             timeout,
                             "01" + ui->textSelfWrite_2->text(),
                             writeread);
}

void MainWindow::on_pushButton_2_clicked()
{
    int writeread = 11;
    int timeout = 1000;
    serialthread.transaction(ui->serialPortComboBox->currentText(),
                             ui->comboBoxBaud->currentIndex(),
                             timeout,
                             "08",
                             writeread);
}

void MainWindow::showResponse(const QString &s)
{
    ui->textSelfRead_2->setText(tr("Data:%1").arg(s));
}

void MainWindow::on_checkBoxPathAll_2_clicked()
{
    if(serialCheckFlag){
        ui->textPathOne_2->setText("");
        ui->textPathTwo_2->setText("");
        ui->textPathThree_2->setText("");
        ui->textPathFour_2->setText("");
        ui->textPathFive_2->setText("");
        ui->textPathSix_2->setText("");
        ui->textPathSeven_2->setText("");
        ui->textPathEight_2->setText("");
        ui->checkBoxPathOne_2->setCheckState(Qt::Checked);
        ui->checkBoxPathTwo_2->setCheckState(Qt::Checked);
        ui->checkBoxPathThree_2->setCheckState(Qt::Checked);
        ui->checkBoxPathFour_2->setCheckState(Qt::Checked);
        ui->checkBoxPathFive_2->setCheckState(Qt::Checked);
        ui->checkBoxPathSix_2->setCheckState(Qt::Checked);
        ui->checkBoxPathSeven_2->setCheckState(Qt::Checked);
        ui->checkBoxPathEight_2->setCheckState(Qt::Checked);
    }
    if(!serialCheckFlag){
        ui->checkBoxPathOne_2->setCheckState(Qt::Unchecked);
        ui->checkBoxPathTwo_2->setCheckState(Qt::Unchecked);
        ui->checkBoxPathThree_2->setCheckState(Qt::Unchecked);
        ui->checkBoxPathFour_2->setCheckState(Qt::Unchecked);
        ui->checkBoxPathFive_2->setCheckState(Qt::Unchecked);
        ui->checkBoxPathSix_2->setCheckState(Qt::Unchecked);
        ui->checkBoxPathSeven_2->setCheckState(Qt::Unchecked);
        ui->checkBoxPathEight_2->setCheckState(Qt::Unchecked);
    }
    serialCheckFlag = !serialCheckFlag;
}

void MainWindow::on_buttonAddWrite_2_clicked()
{
    pathrecord = "";
    if(ui->checkBoxPathAll_2->isChecked()){
        serialchannel->append("38");
        QString bitwide;
        if(ui->textPathAll_2->text().length()==1){
            bitwide = "0"+ui->textPathAll_2->text();
        }
        else
            bitwide = ui->textPathAll_2->text();
        serialchannel->append(bitwide);
        pathrecord.contains("91");
    }
    else{
        if(ui->checkBoxPathOne_2->isChecked()){
            serialchannel->append("30");
            QString bitwide;
            if(ui->textPathOne_2->text().length()==1){
                bitwide = "0"+ui->textPathOne_2->text();
            }
            else
                bitwide = ui->textPathOne_2->text();
            serialchannel->append(bitwide);
            pathrecord.append("11");
        }
        if(ui->checkBoxPathTwo_2->isChecked()){
            serialchannel->append("31");
            QString bitwide;
            if(ui->textPathTwo_2->text().length()==1){
                bitwide = "0"+ui->textPathTwo_2->text();
            }
            else
                bitwide = ui->textPathTwo_2->text();
            serialchannel->append(bitwide);
            pathrecord.append("21");
        }
        if(ui->checkBoxPathThree_2->isChecked()){
            serialchannel->append("32");
            QString bitwide;
            if(ui->textPathThree_2->text().length()==1){
                bitwide = "0"+ui->textPathThree_2->text();
            }
            else
                bitwide = ui->textPathThree_2->text();
            serialchannel->append(bitwide);
            pathrecord.append("31");
        }
        if(ui->checkBoxPathFour_2->isChecked()){
            serialchannel->append("33");
            QString bitwide;
            if(ui->textPathFour_2->text().length()==1){
                bitwide = "0"+ui->textPathFour_2->text();
            }
            else
                bitwide = ui->textPathFour_2->text();
            serialchannel->append(bitwide);
            pathrecord.append("41");
        }
        if(ui->checkBoxPathFive_2->isChecked()){
            serialchannel->append("34");
            QString bitwide;
            if(ui->textPathFive_2->text().length()==1){
                bitwide = "0"+ui->textPathFive_2->text();
            }
            else
                bitwide = ui->textPathFive_2->text();
            serialchannel->append(bitwide);
            pathrecord.append("51");
        }
        if(ui->checkBoxPathSix_2->isChecked()){
            serialchannel->append("35");
            QString bitwide;
            if(ui->textPathSix_2->text().length()==1){
                bitwide = "0"+ui->textPathSix_2->text();
            }
            else
                bitwide = ui->textPathSix_2->text();
            serialchannel->append(bitwide);
            pathrecord.append("61");
        }
        if(ui->checkBoxPathSeven_2->isChecked()){
            serialchannel->append("36");
            QString bitwide;
            if(ui->textPathSeven_2->text().length()==1){
                bitwide = "0"+ui->textPathSeven_2->text();
            }
            else
                bitwide = ui->textPathSeven_2->text();
            serialchannel->append(bitwide);
            pathrecord.append("71");
        }
        if(ui->checkBoxPathEight_2->isChecked()){
            serialchannel->append("37");
            QString bitwide;
            if(ui->textPathEight_2->text().length()==1){
                bitwide = "0"+ui->textPathEight_2->text();
            }
            else
                bitwide = ui->textPathEight_2->text();
            serialchannel->append(bitwide);
            pathrecord.append("81");
        }
    }
    if(serialtempchannel != *serialchannel){
        serialtempchannel = *serialchannel;
    }
    *serialchannel = "";
    int writeread = 13;
    int timeout = 1000;
    serialthread.transaction(ui->serialPortComboBox->currentText(),
                             ui->comboBoxBaud->currentIndex(),
                             timeout,
                             serialtempchannel,
                             writeread);
}

void MainWindow::on_buttonSerialStart_clicked()
{
    int writeread = 12;
    int timeout = 1000;
    serialthread.transaction(ui->serialPortComboBox->currentText(),
                             ui->comboBoxBaud->currentIndex(),
                             timeout,
                             pathrecord,
                             writeread);
}
void MainWindow::pathtwosenddata(){
    int writeread = 9;
    int timeout = 1000;
    if(ui->serialPortComboBox->currentText()!=""){
        currentBaudRate = ui->comboBoxBaud->currentIndex();
        serialthread.transaction(ui->serialPortComboBox->currentText(),
                                 ui->comboBoxBaud->currentIndex(),
                                 timeout,
                                 "88",
                                 writeread);
    }
}
void MainWindow::showserialall(const QString &s)
{
    for(int i=0; i<s.length(); i++){
        serialhash[i]->setText(s.mid(i*2,2));
        if((i+1)%4==0){
            serialcountlist[(i+1)%4]+=1;
            serialhashcount[(i+1)%4]->setText(QString::number(serialcountlist[(i+1)%4],10));
        }
    }
}

void MainWindow::showserial(const QString &s)
{
//    QString currentPath = "";
//    for(int i=0; i<serialtempchannel.length(); i++){
//        if((!(serialtempchannel.at(i)=="1"))||(serialtempchannel.at(i)=="1" &&serialtempchannel.at(i+1)=="1")){
//            currentPath.append(serialtempchannel.at(i));
//        }
//    }
//    for(int i=0; i<currentPath.length(); i++){
//        for(int j=0; j<4; j++){
//            serialhash[(QString(currentPath.at(i)).toInt()-1)*4+j]->setText(s.mid((i-1)*4+j,2));
//        }
//        serialcountlist[QString(currentPath.at(i)).toInt()-1]+=1;
//        serialhashcount[QString(currentPath.at(i)).toInt()-1]->setText(QString::number(serialcountlist[QString(currentPath.at(i)).toInt()-1],10));
//    }
    QString currentPath;
    for(int i=1; i<pathrecord.length(); i++){
        if(pathrecord.at(i)=="1"){
            currentPath.append(pathrecord.at(i-1));
        }
    }
//    if(currentPath.contains("11")){
//        currentPath = currentPath.mid(1);
//    }
    for(int i=0; i<currentPath.length(); i++){
        for(int j=0; j<4; j++){
            QString showtext = s.mid((i*4+j)*2,2);
            serialhash[(QString(currentPath.at(i)).toInt()-1)*4+j]->setText(showtext);
        }
        serialcountlist[QString(currentPath.at(i)).toInt()-1]+=1;
        serialhashcount[QString(currentPath.at(i)).toInt()-1]->setText(QString::number(serialcountlist[QString(currentPath.at(i)).toInt()-1],10));
    }
}
