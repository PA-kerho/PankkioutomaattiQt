#include "checkcard.h"


CheckCard::CheckCard(){

}

bool CheckCard::Connect(){
    connect = QSqlDatabase::addDatabase("QMYSQL");
    //db = &connect;
    connect.setHostName("mysli.oamk.fi");
    connect.setDatabaseName("opisk_t4etni00");
    connect.setUserName("t4etni00");
    connect.setPassword("NPGW4p6X6t57nkgb");
    if(connect.open()){
        QSqlQuery Query(connect);
        query = Query;
        qDebug() << "Yhteys MySQL-tietokantaan auki!";
        return true;
    }
    return false;
}
void CheckCard::DisConnect(){
    connect.close();
}

QString CheckCard::GetCard(QString CardID){
    query.prepare("SELECT PinKoodi FROM Kortit WHERE KortinNumero = :CardID");
    query.bindValue(":CardID", CardID);
    query.exec();
    if(query.size() > 0){
        query.first();
        return query.value(0).toString();
    }
    return "false";
}
