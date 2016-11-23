#ifndef ELASKUDIALOG_H
#define ELASKUDIALOG_H


#include <QDialog>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QCheckBox>

namespace Ui {
class eLaskuDialog;
}

class eLaskuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit eLaskuDialog(QWidget *parent = 0);
    ~eLaskuDialog();
    QSqlQuery query;
    QString CardID;
    void GetData();

private slots:
    void on_pushButtonPeruuta_clicked();

private:
    Ui::eLaskuDialog *ui;
    QTableWidgetItem item;
};

#endif // ELASKUDIALOG_H
