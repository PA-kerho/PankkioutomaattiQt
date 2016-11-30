#include "slelasku.h"


SLeLasku::SLeLasku(){
}

void SLeLasku::Show(){
    GetBills(); //Suoritetaan GetBills-funktio
    eDialog.query = query; //Välitetään query-olio eDialog-oliolle
    eDialog.CardID = CardID; //Välitetään kortin id eDialog-oliolle
    /**Kopioidaan eLaskut-taulukko osoittimina eDialog-olion eLaskut-tauluun**/
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 11; j++){
             eDialog.eLaskut[i][j] = &eLaskut[i][j];
        }
    }
    eDialog.GetData(); //Suoritetaan eDialog-olion GetData-funktio
    eDialog.showFullScreen(); //Aukaistaan dialogi kokoruututilaan
}
void SLeLasku::GetBills(){
    /**Muodostetaan kysely, jossa haetaan kaikki asiakkaan e-laskut**/
    query.prepare("SELECT E.ID, E.Saaja, E.AsiakasID, E.SaajanTilinro, E.Summa, E.Viitenumero, E.Viesti, E.Erapaiva, T.IBAN, T.TilinNimi, E.Tililta                                                  \
                   FROM (((Kortit as K                                          \
                   INNER JOIN KorttiTili as KT ON KT.KorttiID = K.ID)           \
                   INNER JOIN AsiakasTili as A ON A.TiliID = KT.TiliID)         \
                   INNER JOIN ELasku as E ON E.AsiakasID = A.AsiakasID)         \
                   INNER JOIN Tilit as T ON E.Tililta = T.ID                    \
                   WHERE K.KortinNumero = :CardID AND E.Maksettu = 0 AND E.Hyvaksytty = 0");
    query.bindValue(":CardID", CardID); //Syötetään kyselyyn kortin id
    query.exec(); //Suoritetaan kysely
    int i = 0; //Alustetaan muuttuja
    if(query.size() > 0){ //Jos kysely palauttaa yhden tai useamman rivin
        while(query.next()){ //Käydään läpi kaikki palautetut rivit
            /*** Syötetään haetut tiedot eLaskut-taulukkoon ***/
            eLaskut[i][0] = query.value(0).toString(); //ELasku.ID
            eLaskut[i][1] = query.value(1).toString(); //ELasku.Saaja
            eLaskut[i][2] = query.value(2).toString(); //ELasku.AsiakasID
            eLaskut[i][3] = query.value(3).toString(); //ELasku.Saajantilinro
            eLaskut[i][4] = query.value(4).toString(); //ELasku.Summa
            eLaskut[i][5] = query.value(5).toString(); //ELasku.Viitenumero
            eLaskut[i][6] = query.value(6).toString(); //ELasku.Viesti
            eLaskut[i][7] = query.value(7).toString(); //ELasku.Erapaiva
            eLaskut[i][8] = query.value(8).toString(); //Tilit.IBAN
            eLaskut[i][9] = query.value(9).toString(); //Tilit.Tilinnimi
            eLaskut[i][10] = query.value(10).toString(); //ELasku.Tililta
            i++;
        }
    } else { //Jos tietokannasta ei tullut yhtään riviä
        /*** Asetetaan taulukkoon ilmoitus ***/
        eLaskut[0][0] = "False";
        eLaskut[0][1] = "Ei hyväksymättömiä E-Laskuja.";
        i++;
    }
    /*** Täytetään taulukko looppuun tyhjillä merkkijonoilla ***/
    for(int k = i; k < 100-i; k++){
        for(int j = 0; j < 11; j++){
           eLaskut[k][j] = "";
        }
    }
}
