#include "nostodialog.h"
#include "ui_nostodialog.h"

NostoDialog::NostoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NostoDialog)
{   
    ui->setupUi(this);
    Summa = "0";
    ui->NostoLabel->setText(Summa);
    MaksimiSumma = 1000;   
    ui->pushButtonValmis->setEnabled(false);
}

NostoDialog::~NostoDialog(){
    delete ui;
}


void NostoDialog::on_pushButtonPeruuta_clicked(){
    Summa = "0";
    ui->NostoLabel->setText(Summa);
    ui->pushButtonValmis->setEnabled(false);
    this->close();
}

void NostoDialog::on_Num1_clicked(){
    Summa += "1";
    HandleUi();
}

void NostoDialog::on_Num2_clicked(){
    Summa += "2";
    HandleUi();
}

void NostoDialog::on_Num3_clicked(){
    Summa += "3";
    HandleUi();
}

void NostoDialog::on_Num4_clicked(){
    Summa += "4";
   HandleUi();
}

void NostoDialog::on_Num5_clicked(){
    Summa += "5";
    HandleUi();
}

void NostoDialog::on_Num6_clicked(){
    Summa += "6";
    HandleUi();
}

void NostoDialog::on_Num7_clicked(){
    Summa += "7";
    HandleUi();
}

void NostoDialog::on_Num8_clicked(){
    Summa += "8";
    HandleUi();
}

void NostoDialog::on_Num9_clicked(){
    Summa += "9";
    HandleUi();
}

void NostoDialog::on_Num0_clicked(){
    Summa += "0";
    HandleUi();
}

void NostoDialog::on_pushButtonPyyhi_clicked(){
    Summa = Summa.remove(Summa.length()-1, 1);
    ui->NostoLabel->setText(Summa);
    if(Summa.toInt()%5 != 0 || Summa.toInt() == 0 || Summa == ""){
        ui->pushButtonValmis->setEnabled(false);
    } else {
        ui->pushButtonValmis->setEnabled(true);
    }
}

void NostoDialog::on_pushButtonValmis_clicked(){
    infoDialog.showFullScreen();
    infoDialog.Start(Summa.toInt(), CardID, query);
    Summa = "0";
    ui->NostoLabel->setText(Summa);
    ui->pushButtonValmis->setEnabled(false);
    this->close();
}
void NostoDialog::HandleUi(){
    Summa = Summa.toInt() > MaksimiSumma ? QString::number(MaksimiSumma) : QString::number(Summa.toInt());
    ui->NostoLabel->setText(Summa);
    if(Summa.toInt()%5 != 0 || Summa.toInt() == 0 || Summa == ""){
        ui->pushButtonValmis->setEnabled(false);
    } else {
        ui->pushButtonValmis->setEnabled(true);
    }
}
