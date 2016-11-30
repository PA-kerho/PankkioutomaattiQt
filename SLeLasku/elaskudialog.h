#ifndef ELASKUDIALOG_H
#define ELASKUDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QCheckBox>
#include <QListWidgetItem>
#include <QDebug>
#include <QDate>
#include <infodialog.h>

namespace Ui {
class eLaskuDialog;
}
using namespace std;
class eLaskuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit eLaskuDialog(QWidget *parent = 0);
    ~eLaskuDialog();
    QSqlQuery query;
    QString CardID;
    void GetData();
    QString *eLaskut[100][11];

private slots:
    void on_pushButtonPeruuta_clicked();
    void Action();
    void on_pushButtonHyvaksy_clicked();
    bool PayeBills(int IDs[100], int Loops);
    bool inMyArray(QString array[100][3], QString Needle, int Loops);
    void on_pushButtonMaksaNyt_clicked();

private:
    Ui::eLaskuDialog *ui;
    QListWidgetItem item;
    QListWidgetItem item2;
    QString CheckedIDList;
    QDate Date;
    InfoDialog infoDialog;
};

#endif // ELASKUDIALOG_H
