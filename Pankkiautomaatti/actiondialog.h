#ifndef ACTIONDIALOG_H
#define ACTIONDIALOG_H

#include <QDialog>
#include "slnosto.h"

namespace Ui {
class ActionDialog;
}

class ActionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ActionDialog(QWidget *parent = 0);
    ~ActionDialog();

private slots:
    void on_pushButtonClose_clicked();

    void on_pushButtonSiirto_clicked();

    void on_pushButtonNosto_clicked();

    void on_pushButtonSaldo_clicked();

    void on_pushButtonELasku_clicked();

private:
    Ui::ActionDialog *ui;
    SLNosto Nosto;
};

#endif // ACTIONDIALOG_H
