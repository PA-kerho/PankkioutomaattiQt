#include "slsql.h"


SLSQL::SLSQL(){
}

bool SLSQL::Connect(){
   db = QSqlDatabase::addDatabase("QMYSQL","db");
   db.setHostName("193.167.100.162");
   db.setDatabaseName("opisk_t4etni00");
   db.setUserName("t4etni00");
   db.setPassword("NPGW4p6X6t57nkgb");
   if(db.open())
   {
       QSqlQuery Query(db);
       query = Query;
       return true;
   }

    qDebug()<<"db: " << db.lastError();
    return false;

}




void SLSQL::DisConnect(){
   db.close();
}

QString SLSQL::GetCard(QString CardID){
    query.prepare("SELECT PinKoodi, Lukittu, Voimassaoloaika FROM Kortit WHERE KortinNumero = :CardID");
    query.bindValue(":CardID", CardID);
    query.exec();
    if(query.size() > 0){
        query.first();
        if(query.value(1).toInt() != 1){
            Date = QDate::currentDate();
            QString Format = "yyyy-MM-dd";
            QString Voimassaoloaika = query.value(2).toString();
            if(Date.operator <=(QDate::fromString(Voimassaoloaika, Format))){
                return query.value(0).toString();
            } else {
                qDebug() << Date;
                qDebug() << QDate::fromString(Voimassaoloaika, Format);
                return "Kortti ei ole voimassa";
            }
        } else {
            return "Kortti on lukittu";
        }
    }
    qDebug()<<query.lastError();
    return "Tuntematon kortti";
}

