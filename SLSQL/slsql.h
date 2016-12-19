#ifndef SLSQL_H
#define SLSQL_H

#include <QSqlQuery>

#include <QByteArray>
#include <QVariant>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QObject>
#include <QDebug>
#include <QString>
#include <QSqlError>
#include <QDate>

#include "slsql_global.h"

class SLSQLSHARED_EXPORT SLSQL : public QObject
{
    Q_OBJECT

public:
    SLSQL();
    QSqlQuery query;
    QString GetCard(QString CardID);
    void DisConnect();
    bool Connect();
    QString GetBills(QString CardID);
    bool GetSaldo(int Summa, QString CardID);
    bool CheckSaldo(QString IBANs[100][3], int IDs[], int k, int Loops);
    bool Lukitse(QString CardID);

private:
    QSqlDatabase db;
    QString eLaskut[100][11];
    QDate Date;
};

#endif // SLSQL_H
