#ifndef ACTIONDIALOG_H
#define ACTIONDIALOG_H

#include <QDialog>
#include "slnosto.h"
#include "slelasku.h"

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
};

#endif // ACTIONDIALOG_H
