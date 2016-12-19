#ifndef PINKOODIDIALOGI_H
#define PINKOODIDIALOGI_H

#include <QDialog>
#include <QDebug>
#include <QLineEdit>
#include <QString>
#include <QKeyEvent>
#include <QSqlQuery>
#include <QMessageBox>



namespace Ui {
class PinkoodiDialogi;
}

class PinkoodiDialogi : public QDialog
{
    Q_OBJECT

public:
    explicit PinkoodiDialogi(QWidget *parent = 0);
    ~PinkoodiDialogi();
    QString PinKoodi;
    QString CardID;
    QSqlQuery query;

    bool Palauta();



private slots:
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

    void on_pushButtonLogin_clicked();

    void HandleUi();






    void on_pushButtonCancel_clicked();

private:
    Ui::PinkoodiDialogi *ui;
    QString Pin;
    QString SyotettyPinkoodi;
    int Tarkistus;
    bool OK;
    void keyPressEvent(QKeyEvent *e);
    void Lukitse();

signals:
    void ReadyReadPIN();

};

#endif // PINKOODIDIALOGI_H
