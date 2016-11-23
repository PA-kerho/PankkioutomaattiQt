#ifndef SLRFID_H
#define SLRFID_H

#include "slrfid_global.h"
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QByteArray>
#include <QObject>
#include <QEventLoop>


class SLRFIDSHARED_EXPORT SLRFID : public QObject
{

    Q_OBJECT

public:
     SLRFID();

public slots:
    QByteArray ReturnData();
    bool Connect(QString Device);
    void ReadSerialPort();
signals:
    void ReadyRead();
private:
    QSerialPort olioSerialPort;
    QByteArray data;
};

#endif // SLRFID_H
