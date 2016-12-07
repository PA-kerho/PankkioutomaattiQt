#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "slrfid.h"
#include <QByteArray>
#include <QString>
#include <QTimer>
#include "checkcard.h"
#include "actiondialog.h"
#include "slpinkoodi.h"
#include "pinkoodidialogi.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonClose_clicked();
    void FuncCheckCard();

    void GoToStart();
    void CheckPinCode(QString PinCode);
    void ShowActions();


public slots:
    void ReadCard();
    void Restart(int Time, QString Error);
private:
    Ui::MainWindow *ui;
    SLRFID *olioSLRFID;
    SLPinKoodi *olioSLPinKoodi;
    QString CardID;
    QTimer timer;
    CheckCard *olioCheckCard;
    bool CanUseReadCard;
    bool CheckCardCalled;
    QMetaObject::Connection Connect;
    ActionDialog ActionWindow;
};

#endif // MAINWINDOW_H
