#ifndef CHECKCARD_H
#define CHECKCARD_H

#include "checkcard_global.h"
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QDebug>
#include <QSqlQuery>

class CHECKCARDSHARED_EXPORT CheckCard
{

public:
    CheckCard();
    bool Connect();
    void DisConnect();
    QString GetCard(QString CardID);
private:
    QSqlDatabase connect;
    QSqlQuery query;
};

#endif // CHECKCARD_H
