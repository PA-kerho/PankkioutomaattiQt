#include "slrfid.h"


SLRFID::SLRFID(){
    connect(&olioSerialPort, SIGNAL(readyRead()), this, SLOT(ReadSerialPort()));
}

void SLRFID::ReadSerialPort(){
    data = olioSerialPort.readAll();
    emit this->ReadyRead();
}

QByteArray SLRFID::ReturnData(){
    return data;
}
bool SLRFID::Connect(QString Device){
    olioSerialPort.setPortName(Device);
    olioSerialPort.setBaudRate(QSerialPort::Baud9600);
    int i = 0;
    if(olioSerialPort.open(QIODevice::ReadOnly)){
        qDebug() << "Yhteyden muodostaminen RFID-lukijaan onnistui!";
        return true;
    }
    qDebug() << "Yhteyden muodostaminen RFID-lukijaan epäonnistui!";
    return false;
}

