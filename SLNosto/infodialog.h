#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QTimer>
#include <QDebug>
#include <QSqlQuery>

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(QWidget *parent = 0);
    ~InfoDialog();
public slots:
    void Start(int Summa, QString CardID, QSqlQuery query);
private slots:
    void MoneyReady();
    void Close();

private:
    Ui::InfoDialog *ui;
    QTimer Timer1;
    QMetaObject::Connection Con;
    QSqlDatabase Connect;
};

#endif // INFODIALOG_H
