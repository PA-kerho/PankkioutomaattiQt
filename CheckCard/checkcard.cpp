#include "checkcard.h"


CheckCard::CheckCard(){

}

bool CheckCard::Connect(){
    /*** Yritetään yhdistää tietokantaan ***/
    connect = QSqlDatabase::addDatabase("QMYSQL"); //Määritellään oliolle tietokannan tyyppi
    connect.setHostName("mysli.oamk.fi"); //Määritellään oliolle isäntänimi, eli osoite tietokantaan
    connect.setDatabaseName("opisk_t4etni00"); //Määritellään oliolle tietokannan nimi
    connect.setUserName("t4etni00"); //Määritellään oliolle tietokannan käyttäjänimi
    connect.setPassword("NPGW4p6X6t57nkgb"); //Määritellään oliolle tietokannan käyttäjän salasana
    if(connect.open()){ //Yritetään avata yhteys, jos onnistui
        QSqlQuery Query(connect); //Luodaan QSqlQuery-olio tietokanta kyselyitä varten
        query = Query;
        return true; //Palautetaan tosi
    }
    //Jos tänne päästään, yhteyden muodostus tietokantaan on epäonnistunut
    return false; //Palautetaan epätosi
}
void CheckCard::DisConnect(){
    connect.close(); //Suljetaan yhteys
}

QString CheckCard::GetCard(QString CardID){
    /*** Tarkistetaan, onko korttia olemassa, ja haetaan samalla pinkoodi ***/
    query.prepare("SELECT PinKoodi FROM Kortit WHERE KortinNumero = :CardID");
    query.bindValue(":CardID", CardID); //Syötetään kyselyyn kortin id
    query.exec(); //Suoritettaan kysely
    if(query.size() > 0){ //Jos kysely palauttaa rivin
        query.first(); //Valitaan ensimmäinen rivi
        return query.value(0).toString(); //Palautetaan rivin ensimmäinen alkio, joka sisältää pinkoodin
    }
    //Jos tänne päästään, ei tietokannasta löytynyt korttia
    return "false"; //Palautetaan "false", ei false, sillä paluuarvon tyyppinä on QString ei bool
}
