#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow){
    olioSLRFID = new SLRFID; //Luodaan RFID-kirjastosta olio
    olioSLSQL = new SLSQL; //Luodaan Kortintarkistus-kirjastosta olio
    ui->setupUi(this);
    ui->TextLabel->setAlignment(Qt::AlignCenter);
    //QApplication::setOverrideCursor(Qt::BlankCursor);
    CanUseReadCard = true; //Alustetaan apumuuttuja
    connect(&ActionWindow, SIGNAL(Hide()), this, SLOT(GoToStart())); /*Yhdistetään ActionWindown Hide()-signaali GoToStart-slottiin.
                                                                   Hide() emitoituu, kun ActionWindow suljetaan.*/
    if(!olioSLRFID->Connect("/dev/ttyACM0")){ //Muodostetaan yhteys RFID-lukijaan
        ui->TextLabel->setText("Automaatti ei ole käytössä"); //Jos yhdistys epäonnistui, vaihdetaan näytön teksti
    } else { //Jos yhdistys onnistui
        if(!olioSLSQL->Connect()){ //Muodostetaan yhteys MySQL-tietokantaan
            ui->TextLabel->setText("Automaatti ei ole käytössä"); //Jos yhdistys epäonnistui, vaihdetaan näytön teksti
        } else { //Jos yhdistys onnistui
            /* Laitetaan ohjelma käyntiin, määrämällä tapahtumasilmukka(event loop) kuuntelemaan RFID-kirjaston sisäistä ReadyRead()-signaalia.
             * Kun ReadyRead-signaali emitoituu, suoritetaan ReadCard-funktio. */
            connect(Pinkoodi.olioPinKoodiDialogi, SIGNAL(ReadyReadPIN()), this, SLOT(CheckPinCode()));
            connect(olioSLRFID, SIGNAL(ReadyRead()), this, SLOT(ReadCard()));
        }
    }
}

MainWindow::~MainWindow(){
    olioSLSQL->DisConnect(); //Suljetaan tietokantayhteys
    /**Tuohotaan oliot**/
    delete olioSLRFID;
    delete olioSLSQL;
    delete ui;
}
void MainWindow::on_pushButtonClose_clicked(){ //Suoritetaan, kun Close-painiketta(pieni x-painike, vain ohjelmointi vaiheen käytössä) painetaan
    this->close(); //Suljetaan ikkuna
}

void MainWindow::ReadCard(){
    if(CanUseReadCard){ //Jos CanUseReadCard on tosi. Tällä rajoitetaan se, ettei useampi peräkkäinen kortin lukeminen aiheiuta päälekkäistä suorittamista.
        CanUseReadCard = false; //Asetetaan muuttujan arvoksi false, eli estetään tämän funktion suorittaminen, kunnes toisin määrätään
        CardID = olioSLRFID->ReturnData().mid(3,10); //Haetaan RFID-kirjastosta RFID-kortin id ja leikataan siitä ylimääräiset merkit pois: otetaan merkistä 4 eteenpäin 10 merkkiä.
        ui->TextLabel->setText("Tarkistetaan korttia..."); //Vaihdetaan ikkunaan teksti
        Connect = connect(&timer, SIGNAL(timeout()), this, SLOT(FuncCheckCard())); //Kun ajastin on umpeutunut, suoritetaan FuncCheckCard-funktio
        timer.start(1000); //Käynistetään 1000ms ajastin
    }
}

void MainWindow::FuncCheckCard(){
    timer.stop(); //Pysäytetään ajastin
    disconnect(Connect); //Katkaistaan liitos timeout-signaalin ja FuncCheckCard-funktion väliltä
    QString PinCode = olioSLSQL->GetCard(CardID); //Tarkistetaan kortti ja haetaan pinkoodi
    if(PinCode.length() == 4){ //Jos paluuarvo on 4 merkkiä pitkä, haku on onnistunut
       Pinkoodi.PinKoodi = PinCode;
       Pinkoodi.olioPinKoodiDialogi->query = olioSLSQL->query;
       Pinkoodi.olioPinKoodiDialogi->CardID = CardID;
       Pinkoodi.showdialog();
    } else { //Jos paluu arvo on "false"
        Restart(3000, PinCode); //Annetaan virheilmoitus, joka saadaan olioSLSQL:ltä, näytetään sitä 3000ms ja aloitetaan ohjelma alusta
    }
}

void MainWindow::CheckPinCode(){
    if(Pinkoodi.olioPinKoodiDialogi->Palauta()){//Tarkistetaan onko pinkoodi oikein
        /***Asetetaan 1000ms ajastin ShowActions-funktiolle***/
        Connect = connect(&timer, SIGNAL(timeout()), this, SLOT(ShowActions()));
        timer.start(1000);
    } else {
        Restart(100,""); //Aloitetaan alusta 100ms viiveellä
    }
}

void MainWindow::ShowActions(){
    disconnect(Connect); //Katkaistaan liitos timeout-signaalin ja ShowActions-funktion väliltä
    timer.stop();//Pysäytetään ajastin
    ActionWindow.CardID = CardID; //Välitetään RFID-kortin id ActionWindow -luokalle
    ActionWindow.query = olioSLSQL->query; //Välitetään query-olio ActionDialog-luokan oliolle
    ActionWindow.showFullScreen(); //Avataan ActionDialog -ikkuna
}



void MainWindow::Restart(int Time, QString Error){
    ui->TextLabel->setText(Error); //Tulostetaan virheilmoitus näytölle
    disconnect(Connect); //Katkaistaan liitos timeout-signaalin ja Restart-funktion väliltä
    timer.stop(); //Pysäytetään ajastin
    /***Asetetaan Time-muuttujan mittainen ajastin GoToStart-funktiolle***/
    Connect = connect(&timer, SIGNAL(timeout()), this, SLOT(GoToStart()));
    timer.start(Time);
}

void MainWindow::GoToStart(){
    disconnect(Connect); //Katkaistaan liitos timeout-signaalin ja GoToStart-funktion väliltä
    timer.stop(); //Pysäytetään ajastin
    ui->TextLabel->setText("Laita kortti lukijaan aloittaaksesi"); //Vaihdetaan teksti näytölle
    CanUseReadCard = true; //Sallitaan RFID-kortin lukeminen
}
