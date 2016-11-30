#ifndef SLELASKU_H
#define SLELASKU_H

#include <QWidget>
#include <QObject>
#include <QDebug>
#include "slelasku_global.h"
#include "elaskudialog.h"

class SLELASKUSHARED_EXPORT SLeLasku: public QObject
{
    Q_OBJECT
public:
    SLeLasku();
    QSqlQuery query;
    QString CardID;
    void Show();
    void GetBills();
private:
    eLaskuDialog eDialog;
    QString eLaskut[100][11];
};

#endif // SLELASKU_H
