#include "nostodialog.h"
#include "ui_nostodialog.h"

NostoDialog::NostoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NostoDialog)
{   
    ui->setupUi(this);
    Summa = "0"; //Alustetaan summa muuttuja nolaksi
    ui->NostoLabel->setText(Summa); //Asetetaan Summa-muuttujan arvo Summa-kenttään
    MaksimiSumma = 1000;  //Määritellään maksimi nostettava summa
    ui->pushButtonValmis->setEnabled(false); //Poistetaan painike käytöstä
}

NostoDialog::~NostoDialog(){
    delete ui;
}


void NostoDialog::on_pushButtonPeruuta_clicked(){
    Summa = "0"; //Alustetaan summa muuttuja nolaksi
    ui->NostoLabel->setText(Summa); //Asetetaan Summa-muuttujan arvo Summa-kenttään
    ui->pushButtonValmis->setEnabled(false); //Poistetaan painike käytöstä
    this->close(); //Suljetaan tämä dialogi
}

void NostoDialog::on_Num1_clicked(){
    /*** Luvun lisääminen summaan ***/
    Summa += "1"; //Lisätään Summa-muuttujaan luku 1
    HandleUi(); //Käsitellään summa
}

void NostoDialog::on_Num2_clicked(){
    /*** Luvun lisääminen summaan ***/
    Summa += "2";
    HandleUi();
}

void NostoDialog::on_Num3_clicked(){
    /*** Luvun lisääminen summaan ***/
    Summa += "3";
    HandleUi();
}

void NostoDialog::on_Num4_clicked(){
    /*** Luvun lisääminen summaan ***/
    Summa += "4";
   HandleUi();
}

void NostoDialog::on_Num5_clicked(){
    /*** Luvun lisääminen summaan ***/
    Summa += "5";
    HandleUi();
}

void NostoDialog::on_Num6_clicked(){
    /*** Luvun lisääminen summaan ***/
    Summa += "6";
    HandleUi();
}

void NostoDialog::on_Num7_clicked(){
    /*** Luvun lisääminen summaan ***/
    Summa += "7";
    HandleUi();
}

void NostoDialog::on_Num8_clicked(){
    /*** Luvun lisääminen summaan ***/
    Summa += "8";
    HandleUi();
}

void NostoDialog::on_Num9_clicked(){
    /*** Luvun lisääminen summaan ***/
    Summa += "9";
    HandleUi();
}

void NostoDialog::on_Num0_clicked(){
    /*** Luvun lisääminen summaan ***/
    Summa += "0";
    HandleUi();
}

void NostoDialog::on_pushButtonPyyhi_clicked(){
    Summa = Summa.remove(Summa.length()-1, 1); //Poistetaan Summam-muuttujasta viimeinen merkki
    ui->NostoLabel->setText(Summa); //Asetetaan Summa-muuttujan arvo summa-kenttään
    if(Summa.toInt()%5 != 0 || Summa.toInt() == 0 || Summa == ""){ //Jos summa ei ole jaollinen 5 tai summa on 0 tai summa on tyhjä merkkijono
        ui->pushButtonValmis->setEnabled(false); //Poistetaan painike käytöstä
    } else { //Muutoin
        ui->pushButtonValmis->setEnabled(true); //Otetaan painike käyttöön
    }
}

void NostoDialog::on_pushButtonValmis_clicked(){
    infoDialog.Start(Summa.toInt(), CardID, query); //Tehdään tietokanta tarkistukset
    infoDialog.showFullScreen(); //Avataan infoDialog kokoruututilaan
    Summa = "0"; //Alustetaan Summa-muuttuja nollaksi
    ui->NostoLabel->setText(Summa); //Asetetaan Summa-muuttujan arvo summa-kenttään
    ui->pushButtonValmis->setEnabled(false); //Poistetaan painike käytöstä
    this->close(); //Suljetaan tämä dialogi
}
void NostoDialog::HandleUi(){
    /*** Muutetaan Summa-muuttujan arvo kokonaisluvuksi ja vertaillaan sitä maksimisummaan
     * Jos Summa-muuttuja arvo on suurempi, asetetaan Summa-muuttujan arvoksi MaksimiSumma-muuttuja arvo
     * Muutoin muutetaan Summam muuttujan arvo ensin kokonaisluvuksi ja sitte takaisin QStringisi ja asetetaan saatu arvo Summa-muuttujaan
     *   -Näin saadaan poistettua turhat nollat summan edestä ***/
    Summa = Summa.toInt() > MaksimiSumma ? QString::number(MaksimiSumma) : QString::number(Summa.toInt());
    ui->NostoLabel->setText(Summa); //Asetetaan Summa-muuttujan arvo summa-kenttään
    if(Summa.toInt()%5 != 0 || Summa.toInt() == 0 || Summa == ""){ //Jos summa ei ole jaollinen 5 tai summa on 0 tai summa on tyhjä merkkijono
        ui->pushButtonValmis->setEnabled(false); //Poistetaan painike käytöstä
    } else {
        ui->pushButtonValmis->setEnabled(true); //Otetaan painike käyttöön
    }
}
