#include "pinkoodidialogi.h"
#include "ui_pinkoodidialogi.h"



PinkoodiDialogi::PinkoodiDialogi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PinkoodiDialogi)

{
    ui->setupUi(this);
    Pin = "";
    Tarkistus = 0;
    ui->lineEditPIN->setText(Pin);
    }

PinkoodiDialogi::~PinkoodiDialogi()
{
    delete ui;
}

void PinkoodiDialogi::on_pushButton0_clicked()
{
    Pin += "0";
    HandleUi();
}

void PinkoodiDialogi::on_pushButton1_clicked()
{
     Pin += "1";
     HandleUi();
}

void PinkoodiDialogi::on_pushButton2_clicked()
{
      Pin += "2";
      HandleUi();
}

void PinkoodiDialogi::on_pushButton3_clicked()
{
      Pin += "3";
      HandleUi();
}
void PinkoodiDialogi::on_pushButton4_clicked()
{
      Pin += "4";
      HandleUi();
}
void PinkoodiDialogi::on_pushButton5_clicked()
{
      Pin += "5";
      HandleUi();
}

void PinkoodiDialogi::on_pushButton6_clicked()
{
      Pin += "6";
      HandleUi();
}

void PinkoodiDialogi::on_pushButton7_clicked()
{
      Pin += "7";
      HandleUi();
}
void PinkoodiDialogi::on_pushButton8_clicked()
{
      Pin += "8";
      HandleUi();
}

void PinkoodiDialogi::on_pushButton9_clicked()
{
     Pin += "9";
     HandleUi();
}

void PinkoodiDialogi::on_pushButtonDel_clicked()

{
    Pin = Pin.remove(Pin.length()-4,4);
    HandleUi();
}
void PinkoodiDialogi::on_pushButtonLogin_clicked()

{
     SyotettyPinkoodi = ui->lineEditPIN->text();
     if (PinKoodi == SyotettyPinkoodi) {
         Pin.clear();
         ui->lineEditPIN->setText("");
         ui->labelLogin->setText("");
         OK=true;
         emit this->ReadyReadPIN();
         this->close();
         Tarkistus = 0;

     } else {
        OK=false;
        Tarkistus++;
        if(Tarkistus==3){
            Lukitse();
            QMessageBox msgBox;
            msgBox.setText("KORTTI LUKITTU");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
            emit this->ReadyReadPIN();
            this->close();
        }
        ui->labelLogin->setText("PIN VÄÄRIN");
    }
     Pin.clear();
     ui->lineEditPIN->setText("");

}

void PinkoodiDialogi::HandleUi() {
    ui->lineEditPIN->setText(Pin = Pin.mid(0,4));

    if (Pin.length() ==4) {
        ui->pushButtonLogin->setEnabled(true);}
    else {
        ui->pushButtonLogin->setEnabled(false);

    }
}

bool PinkoodiDialogi::Palauta(){
   return OK;
}


void PinkoodiDialogi::on_pushButtonCancel_clicked()
{
    Pin.clear();
    ui->lineEditPIN->setText("");
    ui->labelLogin->setText("");
    OK=false;
    emit this->ReadyReadPIN();
    this->close();
}
void PinkoodiDialogi::keyPressEvent(QKeyEvent *e){
    if(e->key()==Qt::Key_Escape){
        Pin.clear();
        ui->lineEditPIN->setText("");
        ui->labelLogin->setText("");
        OK=false;
        emit this->ReadyReadPIN();
    }
    QDialog::keyPressEvent(e);
}
void PinkoodiDialogi::Lukitse(){
    query.prepare("UPDATE Kortit SET Lukittu=1 WHERE KortinNumero = :CardID");
    query.bindValue(":CardID", CardID);
    query.exec();
}
