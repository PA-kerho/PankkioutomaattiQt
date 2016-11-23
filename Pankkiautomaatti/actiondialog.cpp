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
    this->close();
}

void ActionDialog::on_pushButtonSiirto_clicked(){

}

void ActionDialog::on_pushButtonNosto_clicked(){
   Nosto.CardID = CardID;
   Nosto.query = query;
   Nosto.Show();
}

void ActionDialog::on_pushButtonSaldo_clicked(){

}

void ActionDialog::on_pushButtonELasku_clicked(){
    eLasku.CardID = CardID;
    eLasku.query = query;
    eLasku.Show();
}
