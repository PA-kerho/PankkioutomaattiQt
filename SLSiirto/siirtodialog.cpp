#include "siirtodialog.h"
#include "ui_siirtodialog.h"

SiirtoDialog::SiirtoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SiirtoDialog)
{
    num = "";
    ui->setupUi(this);
    ui->lineEditSumma->setText(num);
}

void SiirtoDialog::Show()
{
    ui->comboBoxTilille->clear();
    ui->comboBoxTililta->clear();
    ui->lineEditSumma->setText("");
    num = "";
    query.prepare("SELECT TilinNimi\
                  FROM Tilit AS T\
                  INNER JOIN AsiakasTili AS AT ON AT.TiliID = T.ID\
                  INNER JOIN KorttiTili AS KT ON KT.TiliID = T.ID\
                  INNER JOIN Kortit AS K ON K.ID = KT.KorttiID\
                  WHERE AT.TiliID = T.ID");
    //query.bindValue(":CardID", CardID);
    query.exec();
    //query.first();
    while(query.next())
    {
    QString Nimi = query.value(0).toString();
    ui->comboBoxTililta->addItem(Nimi);

    }

    query.prepare("SELECT TilinNimi\
                  FROM Tilit AS T\
                  INNER JOIN AsiakasTili AS AT ON AT.TiliID = T.ID\
                  INNER JOIN KorttiTili AS KT ON KT.TiliID = T.ID\
                  INNER JOIN Kortit AS K ON K.ID = KT.KorttiID\
                  WHERE AT.TiliID = T.ID");
    query.exec();
    while(query.next())
    {
    QString Nimi = query.value(0).toString();
    ui->comboBoxTilille->addItem(Nimi);

    }
    this->showFullScreen();


}

SiirtoDialog::~SiirtoDialog()
{
    delete ui;
}

void SiirtoDialog::on_pushButton0_clicked()
{
    num += "0";
    ui->lineEditSumma->setText(num =num.mid(0,20));
}

void SiirtoDialog::on_pushButton1_clicked()
{
    num += "1";
    ui->lineEditSumma->setText(num =num.mid(0,20));
}

void SiirtoDialog::on_pushButton2_clicked()
{
    num += "2";
    ui->lineEditSumma->setText(num =num.mid(0,20));
}

void SiirtoDialog::on_pushButton3_clicked()
{
    num += "3";
    ui->lineEditSumma->setText(num =num.mid(0,20));
}

void SiirtoDialog::on_pushButton4_clicked()
{
    num += "4";
    ui->lineEditSumma->setText(num =num.mid(0,20));
}

void SiirtoDialog::on_pushButton5_clicked()
{
    num += "5";
    ui->lineEditSumma->setText(num =num.mid(0,20));
}

void SiirtoDialog::on_pushButton6_clicked()
{
    num += "6";
    ui->lineEditSumma->setText(num =num.mid(0,20));
}

void SiirtoDialog::on_pushButton7_clicked()
{
    num += "7";
    ui->lineEditSumma->setText(num =num.mid(0,20));
}

void SiirtoDialog::on_pushButton8_clicked()
{
    num += "8";
    ui->lineEditSumma->setText(num =num.mid(0,20));
}

void SiirtoDialog::on_pushButton9_clicked()
{
    num += "9";
    ui->lineEditSumma->setText(num =num.mid(0,20));
}

void SiirtoDialog::on_pushButtonPiste_clicked()
{
    num += ".";
    ui->lineEditSumma->setText(num =num.mid(0,20));

}

void SiirtoDialog::on_pushButtonDel_clicked()
{
    num = num.remove(num.length()-1,1);
    ui->lineEditSumma->setText(num);

}


void SiirtoDialog::on_pushButtonCancel_clicked()
{
    num.clear();
    ui->lineEditSumma->setText("");
    this->close();
}


void SiirtoDialog::on_pushButtonHyvaksy_clicked()
{
    Maksaja = ui->comboBoxTililta->currentText();
    Saaja = ui->comboBoxTilille->currentText();

    query.prepare("SELECT ID,IBAN FROM Tilit WHERE TilinNimi = :Saaja");
    query.bindValue(":Saaja", Saaja);
    query.exec();
    query.first();
    TiliID = query.value(0).toString();
    SaajanTilnro = query.value(1).toString();

    query.prepare("SELECT ID FROM Tilit WHERE TilinNimi = :Maksaja");
    query.bindValue(":Maksaja", Maksaja);
    query.exec();
    query.first();
    TilimID = query.value(0).toString();
    maara = "-"+num;


if(checkSaldo())
{
    qDebug()<<checkSaldo();
    query.prepare("INSERT INTO Tilitapahtumat (Aika, TapahtumanTyyppi, TuloMeno, TiliID, Saaja, SaajanTilinro, Viesti) \
                    VALUES(NOW(), 'Tilisiirto', :num, :TiliID, :Saaja, :SaajanTilnro, 'Siirto omalta tililtä')");
    query.bindValue(":num",num.toFloat());
    query.bindValue(":TiliID",TiliID);
    query.bindValue(":Saaja",Saaja);
    query.bindValue(":SaajanTilnro",SaajanTilnro);
    query.exec();
    query.clear();

    query.prepare("INSERT INTO Tilitapahtumat (Aika, TapahtumanTyyppi, TuloMeno, TiliID, Saaja, Viesti) \
                    VALUES(NOW(), 'Tilisiirto', :maara, :TilimID, :Maksaja, 'Siirto omalle tilille')");
    query.bindValue(":maara", maara.toFloat());
    query.bindValue(":TilimID",TilimID);
    query.bindValue(":Maksaja", Maksaja);
    query.exec();
    QMessageBox msgBox;
    msgBox.setText("Tilisiirto onnistui!");
    msgBox.setDefaultButton(QMessageBox::Save);
    msgBox.exec();
    this->close();

}
else
{

    QMessageBox msgBox1;
    msgBox1.setText("Tilisi saldo ei riitä!");
    msgBox1.setDefaultButton(QMessageBox::Save);
    msgBox1.exec();
    this->close();
}



}

bool SiirtoDialog::checkSaldo()
{
    Maksaja = ui->comboBoxTililta->currentText();
    query.prepare("SELECT SUM(TuloMeno), TT.TiliID                          \
                   FROM (Tilit as T                                       \
                   INNER JOIN KorttiTili as KT ON KT.TiliID = T.ID)      \
                   INNER JOIN Tilitapahtumat as TT ON TT.TiliID = KT.TiliID  \
                   WHERE T.TilinNimi = :Maksaja");
    query.bindValue(":Maksaja", Maksaja);
    query.exec();
    query.first();
    Saldo = query.value(0).toString();
    if(Saldo.toFloat() >= num.toFloat())
    {
        return true;
    }
    else
    {
        return false;
    }
}




