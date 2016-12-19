#ifndef SALDODIALOG_H
#define SALDODIALOG_H

#include <QDialog>
#include <QString>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class SaldoDialog;
}

class SaldoDialog : public QDialog
{
    Q_OBJECT
public slots:


public:
    explicit SaldoDialog(QWidget *parent = 0);
    ~SaldoDialog();
    QString CardID;
    QSqlQuery query;
    QString saldo;
    QString TilinSaldo;
    void ShowSaldo();
    void Show();



private slots:
    void on_pushButtonclose_clicked();

    void on_pushButtonHAE_clicked();

private:
    Ui::SaldoDialog *ui;

};

#endif // SALDODIALOG_H
