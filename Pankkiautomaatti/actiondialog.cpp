#include "actiondialog.h"
#include "ui_actiondialog.h"

ActionDialog::ActionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActionDialog){
    ui->setupUi(this);
}

ActionDialog::~ActionDialog(){
    delete ui;
}
void ActionDialog::on_pushButtonClose_clicked(){
    this->hide(); //Piilotetaan tämä ikkuna
    emit this->Hide(); //Kerrotaan pääohjelmalle, että ikkuna on piilotettu
}

void ActionDialog::on_pushButtonSiirto_clicked(){
    Siirto.SiirtoDialogi.CardID = CardID; //Välitetään kortin id SaldoDialog-luokan oliolle
    Siirto.SiirtoDialogi.query = query; //Välitetään query-olio SaldoDialog-luokan oliolle
    Siirto.SiirtoDialogi.Show(); //Avataan dialogi
}

void ActionDialog::on_pushButtonNosto_clicked(){
   Nosto.nostoDialog.CardID = CardID; //Välitetään kortin id NostoDialog-luokan oliolle
   Nosto.nostoDialog.query = query; //Välitetään query-olio NostoDialog-luokan oliolle
   Nosto.nostoDialog.showFullScreen(); //Avataan dialogi
}

void ActionDialog::on_pushButtonSaldo_clicked(){
    Saldo.SaldoDialogi.CardID = CardID; //Välitetään kortin id SaldoDialog-luokan oliolle
    Saldo.SaldoDialogi.query = query; //Välitetään query-olio SaldoDialog-luokan oliolle
    Saldo.SaldoDialogi.Show(); //Avataan dialogi
}

void ActionDialog::on_pushButtonELasku_clicked(){
    eLasku.CardID = CardID; //Välitetään kortin id SLeLasku-luokan oliolle
    eLasku.query = query; //Välitetään query-olio SLeLasku-luokan oliolle
    eLasku.Show(); //Kutsutaan eLasku-olion Show-funktiota
}
void ActionDialog::keyPressEvent(QKeyEvent *e){
    if(e->key()==Qt::Key_Escape){
        emit this->Hide();
        this->hide();
    } else {
        QDialog::keyPressEvent(e);
    }
}
