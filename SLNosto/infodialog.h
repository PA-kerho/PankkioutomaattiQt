#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QTimer>
#include <QDebug>

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
    void Start();
private slots:
    void MoneyReady();
    void Close();

private:
    Ui::InfoDialog *ui;
    QTimer Timer1;
    QMetaObject::Connection Con;
};

#endif // INFODIALOG_H
