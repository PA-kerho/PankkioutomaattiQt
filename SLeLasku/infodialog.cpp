#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(QWidget *parent) : QDialog(parent), ui(new Ui::InfoDialog){
    ui->setupUi(this);
}

InfoDialog::~InfoDialog(){
    delete ui;
}

void InfoDialog::SetMessage(QString Message){
    ui->label->setText(Message); //Asetetaan näytölle teksti
}

void InfoDialog::ShowWindow(){
    this->showFullScreen(); //Avataan dialogi kokoruututilassa
    /*** Asetetaan close-funktiolle 5000ms ajastin. close-funktio sulkee ikkunan. ***/
    connect(&timer, SIGNAL(timeout()), this, SLOT(close()));
    timer.start(5000);
}
