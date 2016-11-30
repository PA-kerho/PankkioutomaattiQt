#include "slrfid.h"


SLRFID::SLRFID(){
    /*** Yhdistetään QSerialPort-luokan readyRead-signaali ja ReadSerialPort-funktio.
     * readyRead-signaali emitoituu, kun sarjaportista on luettavissa dataa. ***/
    connect(&olioSerialPort, SIGNAL(readyRead()), this, SLOT(ReadSerialPort()));
}

void SLRFID::ReadSerialPort(){
    data = olioSerialPort.readAll(); //Luetaan data sarjaportista data-muuttujaan
    emit this->ReadyRead(); //Emitoidaan kirjaston sisäinen signaali, joka kertoo pääohjelmalle, että dataa on luettavissa.
}

QByteArray SLRFID::ReturnData(){
    return data; //Palautetaan data pääohjelmalle
}
bool SLRFID::Connect(QString Device){
    /*** Yritetään yhdistää RFID-lukijaan ***/
    olioSerialPort.setPortName(Device); //Asetetaan oliolle laitteen portinnimi
    olioSerialPort.setBaudRate(QSerialPort::Baud9600); //Asetetaan oliolle baudrate
    if(olioSerialPort.open(QIODevice::ReadOnly)){ // Yritetään avata yhteyttä, jos onnistui
        return true; //Palautetaan tosi
    }
    //Jos tänne päästää, yhteys on epäonnistunut
    return false; //Palautetaan false
}

