#ifndef NOSTODIALOG_H
#define NOSTODIALOG_H

#include <QDialog>
#include <QDebug>
#include "infodialog.h"

namespace Ui {
class NostoDialog;
}

class NostoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NostoDialog(QWidget *parent = 0);
    ~NostoDialog();

private slots:
    void on_pushButtonPeruuta_clicked();
    void on_Num1_clicked();
    void on_Num2_clicked();
    void on_Num3_clicked();
    void on_Num4_clicked();
    void on_Num5_clicked();
    void on_Num6_clicked();
    void on_Num7_clicked();
    void on_Num8_clicked();
    void on_Num9_clicked();
    void on_Num0_clicked();
    void on_pushButtonPyyhi_clicked();
    void on_pushButtonValmis_clicked();
    void HandleUi();

private:
    Ui::NostoDialog *ui;
    QString Summa;
    int MaksimiSumma;
    InfoDialog infoDialog;
};

#endif // NOSTODIALOG_H
