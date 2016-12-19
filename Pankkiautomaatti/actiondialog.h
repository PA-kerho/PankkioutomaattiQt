#ifndef ACTIONDIALOG_H
#define ACTIONDIALOG_H

#include <QDialog>
#include "slnosto.h"
#include "slelasku.h"
#include "slsaldo2.h"
#include <QKeyEvent>
#include "slsiirto.h"

namespace Ui {
class ActionDialog;
}

class ActionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ActionDialog(QWidget *parent = 0);
    ~ActionDialog();
    QString CardID;
    QSqlQuery query;
private slots:
    void on_pushButtonClose_clicked();
    void on_pushButtonSiirto_clicked();
    void on_pushButtonNosto_clicked();
    void on_pushButtonSaldo_clicked();
    void on_pushButtonELasku_clicked();
signals:
    void Hide();
private:
    Ui::ActionDialog *ui;
    SLNosto Nosto;
    SLeLasku eLasku;
    SLSaldo2 Saldo;
    SLSiirto Siirto;
    void keyPressEvent(QKeyEvent *e);
};

#endif // ACTIONDIALOG_H
