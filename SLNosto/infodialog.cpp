#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog)
{  
    ui->setupUi(this);
    ui->Text->setAlignment(Qt::AlignCenter);
}

InfoDialog::~InfoDialog()
{
    delete ui;
}
void InfoDialog::MoneyReady(){
    disconnect(Con); //Katkaistaan yhteys timeout-signaalin ja MoneyReady-funktion väliltä
    ui->Text->setText("Ota rahat"); //Asetetaan ikkunaan teksti
    /*** Käynnistetään 3000ms, jonka jälkeen suoritetaan Close-funktio ***/
    Con = connect(&Timer1, SIGNAL(timeout()), this, SLOT(Close()));
    Timer1.start(3000);
}

void InfoDialog::Close(){
    disconnect(Con); //Katkaistaan yhteys timeout-signaalin ja Close-funktion väliltä
    ui->Text->setText("Rahat tulossa, odota ole hyvä"); //Asetetaan oletus teksti ikkunaan
    this->close(); //Suljetaan tämä dialogi
}

void InfoDialog::Start(int Summa, QString CardID, QSqlQuery query){
    /*** Haetaan tietokannasta tilin saldo ***/
    query.prepare("SELECT SUM(TuloMeno), T.TiliID                          \
                   FROM (Kortit as K                                       \
                   INNER JOIN KorttiTili as KT ON KT.KorttiID = K.ID)      \
                   INNER JOIN Tilitapahtumat as T ON T.TiliID = KT.TiliID  \
                   WHERE K.KortinNumero = :CardID");
    query.bindValue(":CardID", CardID); //Syötetään kyselyyn kortin id
    query.exec(); // Suoritetaan kysely
    if(query.size() > 0){ // Jos kysely palauttaa rivin
        query.first(); //Valitaan esimmäinen rivi
        int Saldo = query.value(0).toInt(); //Muutetaan rivin ensimmäisen alkion arvo kokonaisluvuksi ja tallennetaan Saldo-muuttujaan
        if(Saldo >= Summa){ //Jos Saldo on suurempi kuin Summa, eli kate tilillä riittää
            int TiliID = query.value(1).toInt(); //Tallennetaan TiliID-muuttujaan rivin toinen alkio muutettuna kokonasluvuksi
            /*** Lisätään tietokantaan tilitapahtuma ***/
            query.prepare("INSERT INTO Tilitapahtumat (Aika, TapahtumanTyyppi, TuloMeno, TiliID) VALUES(NOW(),'Käteisnosto', :Summa, :TiliID)");
            query.bindValue(":Summa", (0-Summa)); //Syötetään kyselyyn summa negatiivisenä
            query.bindValue(":TiliID", TiliID); //Syötetään kyselyyn TiliID
            if(query.exec()){ //Suoritetaan kysely ja jos kysely onnistuu
                ui->Text->setText("Rahat tulossa, odota ole hyvä"); //Asetetaan näytölle teksti
                /*** Astetaan 5000ms ajastin MoneyReady-funktiolle ***/
                Con = connect(&Timer1, SIGNAL(timeout()), this, SLOT(MoneyReady()));
                Timer1.start(5000);
            } else { //Jos kysely epäonnistu
                ui->Text->setText("Nostaminen epäonnistui, yritä uudelleen"); //Asetetaan näytölle virheilmoitus
                /*** Asetetaan 3000ms ajastin close-funktiolla ***/
                Con = connect(&Timer1, SIGNAL(timeout()), this, SLOT(close()));
                Timer1.start(3000);
            }
        } else { //Jos tilillä ei ole riittävästi katetta
            ui->Text->setText("Tilin kate ei riitä"); //Asetetaan näytölle virheilmoitus
            /*** Asetetaan 3000ms ajastin close-funktiolle ***/
            Con = connect(&Timer1, SIGNAL(timeout()), this, SLOT(close()));
            Timer1.start(3000);
        }
    } else { //Jos tietokanta haku ei tuota yhtään tulosta, ei korttia ole liitetty mihinkään tiliin
        ui->Text->setText("Korttia ei ole liitetty tileihin"); //Asetetaan näytölle virheilmoitus
        /*** Asetetaan 3000ms ajastin close-funktiolle ***/
        Con = connect(&Timer1, SIGNAL(timeout()), this, SLOT(close()));
        Timer1.start(3000);
    }
}

