#include "elaskudialog.h"
#include "ui_elaskudialog.h"

eLaskuDialog::eLaskuDialog(QWidget *parent) : QDialog(parent),ui(new Ui::eLaskuDialog){
    ui->setupUi(this);
}

eLaskuDialog::~eLaskuDialog(){
    delete ui;
}
void eLaskuDialog::GetData(){
    query.prepare("SELECT *                                                  \
                   FROM ((Kortit as K                                        \
                   INNER JOIN KorttiTili as KT ON KT.KorttiID = K.ID)        \
                   INNER JOIN AsiakasTili as A ON A.TiliID = KT.TiliID)      \
                   INNER JOIN ELasku as E ON E.AsiakasID = A.AsiakasID       \
                   WHERE K.KortinNumero = :CardID");
    query.bindValue(":CardID", CardID);
    query.exec();
    if(query.size() > 0){
        int i = 0;
        while(query.next()){
           //query.value(0).toString();
           i++;
        }
    } else {
        // Ei hyväksymättömiä eLaskuja
    }
}

void eLaskuDialog::on_pushButtonPeruuta_clicked(){
    this->close();
}
