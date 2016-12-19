#ifndef SIIRTODIALOG_H
#define SIIRTODIALOG_H
#include <QSqlQuery>
#include <QDialog>
#include <QDebug>
#include <QDate>
#include <QMessageBox>

namespace Ui {
class SiirtoDialog;
}

class SiirtoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SiirtoDialog(QWidget *parent = 0);
    ~SiirtoDialog();
    QSqlQuery query;
    QString CardID;
    void Show();


private slots:
  // void on_comboBoxTililta_activated();

   //void on_comboBoxTilille_activated();

   void on_pushButton0_clicked();

   void on_pushButton1_clicked();

   void on_pushButton2_clicked();

   void on_pushButton3_clicked();

   void on_pushButton4_clicked();

   void on_pushButton5_clicked();

   void on_pushButton6_clicked();

   void on_pushButton7_clicked();

   void on_pushButton8_clicked();

   void on_pushButton9_clicked();

   void on_pushButtonDel_clicked();

   void on_pushButtonCancel_clicked();

   void on_pushButtonHyvaksy_clicked();

   void on_pushButtonPiste_clicked();



private:
    Ui::SiirtoDialog *ui;
    QString num;
    QString TiliID;
    QString TilimID;
    QString Maksaja;
    QString Saaja;
    QString MaksajanTilnro;
    QString SaajanTilnro;
    QString maara;
    QString Saldo;
    bool checkSaldo();



};

#endif // SIIRTODIALOG_H
