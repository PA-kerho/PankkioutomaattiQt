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
    ui->Text->setText("Ota rahat");
    Con = connect(&Timer1, SIGNAL(timeout()), this, SLOT(Close()));
    Timer1.start(3000);
}

void InfoDialog::Close(){
    disconnect(Con);
    ui->Text->setText("Rahat tulossa, odota ole hyvä");
    this->close();
}

void InfoDialog::Start(int Summa, QString CardID, QSqlQuery query){
    disconnect(Con);
    query.prepare("SELECT SUM(TuloMeno), T.TiliID                          \
                   FROM (Kortit as K                                       \
                   INNER JOIN KorttiTili as KT ON KT.KorttiID = K.ID)      \
                   INNER JOIN Tilitapahtumat as T ON T.TiliID = KT.TiliID  \
                   WHERE K.KortinNumero = :CardID");
    query.bindValue(":CardID", CardID);
    query.exec();
    if(query.size() > 0){
        query.first();
        int Saldo = query.value(0).toInt();
        if(Saldo >= Summa){
            int TiliID = query.value(1).toInt();
            query.prepare("INSERT INTO Tilitapahtumat (Aika, TapahtumanTyyppi, TuloMeno, TiliID) VALUES(NOW(),'Käteisnosto', :Summa, :TiliID)");
            query.bindValue(":Summa", (0-Summa));
            query.bindValue(":TiliID", TiliID);
            if(query.exec()){
                ui->Text->setText("Rahat tulossa, odota ole hyvä");
                Con = connect(&Timer1, SIGNAL(timeout()), this, SLOT(MoneyReady()));
                Timer1.start(5000);
            } else {
                ui->Text->setText("Nostaminen epäonnistui, yritä uudelleen");
                Con = connect(&Timer1, SIGNAL(timeout()), this, SLOT(close()));
                Timer1.start(3000);
            }
        } else {
            ui->Text->setText("Tilin saldo ei riitä");
            Con = connect(&Timer1, SIGNAL(timeout()), this, SLOT(close()));
            Timer1.start(3000);
        }
    } else {
        ui->Text->setText("Korttia ei ole liitetty tiliisi");
        Con = connect(&Timer1, SIGNAL(timeout()), this, SLOT(close()));
        Timer1.start(3000);
    }
}

