#include "serialportinfomanager.h"

#include <QTimer>
#include <QDebug>
#include <QtSerialPort/QSerialPortInfo>

serialportinfomanager::serialportinfomanager()
{
    stopped = false;
}

serialportinfomanager::~serialportinfomanager()
{

}
void serialportinfomanager::run(){
    QString avaiPorts,currentPorts;
    while(!stopped){
        foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
            avaiPorts.append(info.portName());
            avaiPorts.append(" ");
        }
        if(!(currentPorts==avaiPorts)){
            currentPorts = avaiPorts;
            emit dataChanged(currentPorts);
        }
        avaiPorts = "";
        sleep(1);
    }
}

void serialportinfomanager::setStopped(bool stopped)
{
    this->stopped = stopped;
}


void serialportinfomanager::queryinfo(){

}
