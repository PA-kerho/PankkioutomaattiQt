#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog)
{  
    ui->setupUi(this);
}

InfoDialog::~InfoDialog()
{
    delete ui;
}
void InfoDialog::MoneyReady(){
    disconnect(Con);
    qDebug() << "Called";
    ui->Text->setText("Ota rahat");
    Con = connect(&Timer1, SIGNAL(timeout()), this, SLOT(Close()));
    Timer1.start(3000);
}

void InfoDialog::Close(){
    disconnect(Con);
    ui->Text->setText("Rahat tulossa, odota ole hyvä");
    this->close();
}

void InfoDialog::Start(){
    Con = connect(&Timer1, SIGNAL(timeout()), this, SLOT(MoneyReady()));
    Timer1.start(5000);
}

