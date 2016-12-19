


#include "elaskudialog.h"
#include "ui_elaskudialog.h"

eLaskuDialog::eLaskuDialog(QWidget *parent) : QDialog(parent),ui(new Ui::eLaskuDialog){
    ui->setupUi(this);

    /*** Yhdistetään listWidget-oloin itemChanged-signaali Action-funktioon. itemChanged-signaali emitoituu, kun jonkin checkboxin tilaa vaihetaan ***/
    connect(ui->listWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(Action()));

    /*** Poistetaan hyväksy ja makas nyt -painikkeet pois käytöstä ***/
    ui->pushButtonHyvaksy->setEnabled(false);
    ui->pushButtonMaksaNyt->setEnabled(false);
}

eLaskuDialog::~eLaskuDialog(){
    delete ui;
}
void eLaskuDialog::GetData(){
    ui->listWidget->clear(); //Tyhjennetään e-lasku lista
    item.setFlags(item.flags() | Qt::ItemIsUserCheckable); //Asetetaan tarkistettavissa(checkable) lippu
    item.setCheckState(Qt::Unchecked); //Alustetaan checkboxin tila
    if(*eLaskut[0][0] == "False"){ //Jos tietokanta kysely ei palauttanut yhtään riviä
        item2.setText(*eLaskut[0][1]); //Asetetaan ilmoitus itemin tekstiksi
        ui->listWidget->addItem(new QListWidgetItem(item2)); //Asetetaan item e-lasku listaan
    } else { //Jos tietokanta kysely palautti rivejä
        for(int i = 0; i < 100; i++){
            if(*eLaskut[i][0] == ""){ //Kun eLakut-taulukon alkio 0 on tyhjä, ollaan kaikki eLaskut käsitelty
                break; //Poistutaan silmukasta
            }
            /*** Luodaan teksti muuttujat ***/
            QString Data = "Saaja: " + *eLaskut[i][1];
            QString Data2 = "    Summa: "
                         + *eLaskut[i][4]
                         + "€\n    Viite: "
                         + *eLaskut[i][5]
                         + "\n     Eräpäivä: "
                         + *eLaskut[i][7]
                         + "\n     Tilille: "
                         + *eLaskut[i][3]
                         + "\n     Tililtä: "
                         + *eLaskut[i][8] +"("+*eLaskut[i][9] + ")"
                         + "\n\n";
            QVariant ID(QString::number(i)); //Luodaan QVariant muuttuja ID, johon tallennetaan käsiteltävä taulukon alkio
            item.setText(Data); //Asetetaan itemille teksti Data-muuttujasta
            item2.setText(Data2); //Asetetaan item2:lle teksti Data2-muuttujasta
            item.setData(Qt::UserRole, ID); //Asetetaan itemiin piilodataksi ID
            ui->listWidget->addItem(new QListWidgetItem(item)); //Asetetaan item e-lasku listaan
            ui->listWidget->addItem(new QListWidgetItem(item2));//Asetetaan item2 e-lasku listaan
        }
    }
}

void eLaskuDialog::on_pushButtonPeruuta_clicked(){
    /*** Poistetaan käytöstä painikkeet ***/
    ui->pushButtonHyvaksy->setEnabled(false);
    ui->pushButtonMaksaNyt->setEnabled(false);
    this->close(); //Suljetaan dialogi
}
void eLaskuDialog::Action(){
    int CheckedCount = 0; //Alustetaan muuttuja, johon lasketaan valittujen e-laskujen määrä
    /*** Lasketaan e-laskujen määrä ***/
    for(int i = 0; i < ui->listWidget->count(); i++){ //Käydään läpi kaikki listWidget-oliossa olevat itemit
        if(ui->listWidget->item(i)->checkState() == Qt::Checked){ //Jos item on valittu
            CheckedCount++; //Kasvatetaan laskurimuuttujan arvoa
        }
    }
    if(CheckedCount < 1){ //Jos yhtään e-laskua ei ole valittu
        /*** Poistetaan käytöstä painikkeet ***/
        ui->pushButtonHyvaksy->setEnabled(false);
        ui->pushButtonMaksaNyt->setEnabled(false);
    } else { //Jos e-laskuja on valittu
        /*** Otetaan painikkeet käyttöön ***/
        ui->pushButtonHyvaksy->setEnabled(true);
        ui->pushButtonMaksaNyt->setEnabled(true);
    }
}

void eLaskuDialog::on_pushButtonHyvaksy_clicked(){
    QString DueDateNotToday; //Alustetaan muuttuja, johon tallenetaan e-laskut, joissa ei ole eräpäivä tänään tai mennyt
    int DueDateToday[100]; //Alustetaan taulukko, johon tallenetaan e-laskut, joissa on eräpäivä tänään tai mennyt
    DueDateNotToday.fill(1000); //Täytetään taulu arvoilla 1000
    Date = QDate::currentDate(); //Haeitaan nykyinen aika Date-muuttujaan
    QString Format = "yyyy-MM-dd"; //Aika formaatti tietokannassa
    int k = 0; //Apumuuttuja
    /*** Muodostetaan listat e-laskuista, joissa on eräpäivä tänään tai mennyt ja e-laskuista, joissa eräpäivä on tulevaisuudessa ***/
    for(int i = 0; i < ui->listWidget->count(); i++){ //Loopataan kaikki QListWidgetItemit
        if(ui->listWidget->item(i)->checkState() == Qt::Checked){ // Jos item on valittu
            int ID = ui->listWidget->item(i)->data(Qt::UserRole).toInt(); //Haetaan piilodataan tallennettu taulukon solunumero
            if(Date.operator >=(QDate::fromString(*eLaskut[ID][7], Format))){ //Jos eräpäivä on tänään tänään tai mennyt
                DueDateToday[k] = ID; //Lisätään solunumero listaan
                k++; //Kasvatetaan apumuuttujaa
            } else { //Jos eräpäivä ei ole tänään tai mennyt
                DueDateNotToday += *eLaskut[ID][0]+","; //Lisätään eLaskun id muuttujaan
            }
        }
    }
    if(PayeBills(DueDateToday, k)){ //Maksetaan eLaskut
        DueDateNotToday = DueDateNotToday.remove(DueDateNotToday.length()-1, 1); //Leikataan viimenen pilkku pois listasta
        query.prepare("UPDATE ELasku SET Hyvaksytty = 1 WHERE ID IN("+DueDateNotToday+")"); //Tehdään kysely, joka merkitsee e-laskut hyväksytyiksi
        query.exec(); //Suoritetaan kysely
        infoDialog.SetMessage("eLaskut maksettu ja hyväksytty."); //Asetetaan infoDialogin teksti
        infoDialog.ShowWindow(); //Avataan infoDialog
        this->close(); //Suljetaan tämä dialogi
    } else {
        infoDialog.SetMessage("Til(e)illäsi ei ole riittävästi katetta."); //Asetetaan infoDialogin teksti
        infoDialog.ShowWindow(); //Avataan infoDialog
        this->close(); //Suljetaan tämä dialogi
    }

}

bool eLaskuDialog::PayeBills(int IDs[100], int Loops){
    QString IBANs[100][3]; //Alustetaan taulukko, johon tallennetaan IBANit ja niiden alle lista ID:stä, joilla on sama IBAN
    int k = 0;
    /********* Muodostetaan lista IBAN:eista, ja niiden taakse lista ID:stä, joilla on sama IBAN *********/
    for(int i = 0; i < Loops; i++){ //Käydään läpi ID:t
        if(!inMyArray(IBANs, *eLaskut[IDs[i]][8], k)){ //Tarkistetaan onko IBAN listassa
            IBANs[k][0] = *eLaskut[IDs[i]][8]; //Asetetaan IBANs-taulukkon IBAN
            IBANs[k][1] = *eLaskut[IDs[i]][0]; //Asetetaan IBANs-taulukkoon e-laskun id
            IBANs[k][2] = *eLaskut[IDs[i]][4]; //Asetetaan IBANs-taulukkoon e-laskun summa
            k++;
        } else {
            IBANs[k-1][1] += "," + *eLaskut[IDs[i]][0]; //Lisätään id-listaan id
            IBANs[k-1][2] = QString::number(IBANs[k-1][2].toFloat() + (*eLaskut[IDs[i]][4]).toFloat()); //Kasvatetaan e-laskujen yhteissummaa
        }
    }

    /*** Tarkistetaan, riittääkö tilien saldot **/
    query.prepare("SELECT SUM(TuloMeno) FROM Tilitapahtumat as TT LEFT JOIN Tilit as T ON T.ID = TT.TiliID WHERE T.IBAN = :IBAN");
    for(int i = 0; i < k; i++){ //Käydään läpi kaikki IBANit
        float Sum = 0.0; //Alustetaan summa nollaksi
        query.bindValue(":IBAN", IBANs[i][0]); //liitetään kyselyyn IBAN
        query.exec(); //Suoritetaan kysely
        if(query.size() > 0){ //Jos kysely palauttaa rivejä
            query.first(); //Valitaan ensimmäinen rivi
            Sum = query.value(0).toFloat(); //Muutetaan haettu arvo liukuluvuksi ja asetetaan se Sum-muuttujaan
        }
        if(Sum < IBANs[i][2].toFloat()){ //Muutetaan IBANs-taulukossa oleva summa liukuluvuksi, ja tarkistetaan, onko se suurempi kuin tietokannasta haettu summa
            return false; //Jos on, tilin kate ei riitä, ja palautetaan funktiosta false.
        }
    }

    /*** Merkitään kaikki e-laskut maksetuiksi ja hyväksytiksi ***/
    for(int i = 0; i < k; i++){
        query.prepare("UPDATE ELasku SET Maksettu = 1, Hyvaksytty = 1, MaksuAika = NOW() WHERE ID IN("+IBANs[i][1]+")"); //Asetetaan kysely
        query.exec(); //Suoritetaan kysely
    }

    /*** Lisätään tietokantaan tilitapahtuma rivit ***/
    query.prepare("INSERT INTO Tilitapahtumat (Aika, TapahtumanTyyppi, TuloMeno, TiliID, Saaja, SaajanTilinro, Viitenumero) \
                   VALUES(NOW(), 'eLasku', :Summa, :TiliID, :Saaja, :SaajanTilinro, :Viitenumero)");
    /*** Käydää läpi kaikki e-laskut, jotka on valittu ja joissa on eräpäivä tänään tai mennyt ***/
    for(int i = 0; i < Loops; i++){
        /*** Asetetaan kyselyyn arvoja ***/
        query.bindValue(":Summa", 0-((*eLaskut[IDs[i]][4]).toFloat()));
        query.bindValue(":TiliID", (*eLaskut[IDs[i]][10]).toInt());
        query.bindValue(":Saaja", *eLaskut[IDs[i]][1]);
        query.bindValue(":SaajanTilinro", *eLaskut[IDs[i]][3]);
        query.bindValue(":Viitenumero", *eLaskut[IDs[i]][5]);
        query.exec(); //Suoritetaan kysely
    }
    return true; //Palautetaan tosi
}

bool eLaskuDialog::inMyArray(QString array[100][3], QString Needle, int Loops){
    /*** Käydään läpi taulukon arvot ***/
    for(int i = 0; i < Loops; i++){
        if(array[i][0] == Needle){ //Jos taulukon arvo on haluttu arvo
            return true; //Palautetaan true
        }
    }
    //Jos tänne asti päästään, ei taulukosta löydy haluttua arvoa
    return false; //Palautetaan false
}

void eLaskuDialog::on_pushButtonMaksaNyt_clicked(){
    int IDs[100]; //Alustetaan IDs-taulukko eLaskut-taulukon indeksejä varten
    int k = 0;
    /*** Käydään läpi kaikki listWidgetin itemit ***/
    for(int i = 0; i < ui->listWidget->count(); i++){ //Loopataan kaikki QListWidgetItemit
        if(ui->listWidget->item(i)->checkState() == Qt::Checked){ // Jos item on valittu
            int ID = ui->listWidget->item(i)->data(Qt::UserRole).toInt(); //Haetaan piilodataan tallennettu taulukon solunumero
            IDs[k] = ID; //Asetetaan ID IDs-taulukkoon
            k++; //Kasvatetaan laskurimuuttujaa
        }
    }
    if(PayeBills(IDs, k)){ //Maksetaan laskut
        infoDialog.SetMessage("eLaskut maksettu."); //Asetetaan infoDialogin teksti
        infoDialog.ShowWindow(); //Avataan infoDialog
        this->close(); //Suljetaan tämä dialogi
    } else {
        infoDialog.SetMessage("Til(e)illäsi ei ole riittävästi katetta."); //Asetetaan infoDialogin teksti
        infoDialog.ShowWindow(); //Avataan infoDialog
        this->close(); //Suljetaan tämä dialogi
    }
}
