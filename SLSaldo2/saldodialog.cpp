#include "saldodialog.h"
#include "ui_saldodialog.h"

SaldoDialog::SaldoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaldoDialog)
{
    ui->setupUi(this);

    ui->labelSaldo->setText(""); // Asettaa saldolabelin tyhjäksi


}

SaldoDialog::~SaldoDialog()
{
    delete ui;
}
void SaldoDialog::Show(){
    this->showFullScreen(); // Avaa saldodialog formin kokoruudun kokokoisena
    ShowSaldo();
}

void SaldoDialog::ShowSaldo()
{
    ui->labelSaldo->setText("");
    saldo = "";
    ui->comboBoxTili->clear();                  //Suorittaa tilien haun tietokannasta
    query.prepare("SELECT TilinNimi\
                  FROM Tilit AS T\
                  INNER JOIN AsiakasTili AS AT ON AT.TiliID = T.ID\
            INNER JOIN KorttiTili AS KT ON KT.TiliID = T.ID\
            INNER JOIN Kortit AS K ON K.ID = KT.KorttiID\
            WHERE AT.TiliID = T.ID");
            query.exec();
            while(query.next()){
        QString Nimi= query.value(0).toString();
        ui->comboBoxTili->addItem(Nimi);
    }

}





void SaldoDialog::on_pushButtonclose_clicked()
{

    this->close();                            //Sulkee
}

void SaldoDialog::on_pushButtonHAE_clicked()        //Suorittaa valitun tilin saldohaun kun HAE painike on painettu
{
    TilinSaldo= ui->comboBoxTili->currentText();
    query.prepare("SELECT SUM(TuloMeno), T.TilinNimi  \
                  FROM (Tilit as T           \
                  INNER JOIN KorttiTili as KT ON KT.TiliID = T.ID) \
                  INNER JOIN Tilitapahtumat as TT ON TT.TiliID = KT.TiliID\
                  WHERE T.TilinNimi = :TilinSaldo");


    query.bindValue(":TilinSaldo", TilinSaldo);   //Syötetään kyselyyn kortin id
    query.exec();                               //Suorittaa kyselyn
    query.first();
    saldo=query.value(0).toString();            //Määritetään alkion ensimmäinen muuttuja stringiksi ja tallennetaan saldo muuttujaan

    ui->labelSaldo->setText(saldo);             //Syöttää saldolabeliin salon

    TilinSaldo=query.value(0).toString();        //Määritetään alkion toinen muuttuja stringiksi ja tallennetaan TilinSaldo muuttujaan
}
