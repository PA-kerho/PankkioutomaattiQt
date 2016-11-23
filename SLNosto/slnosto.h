#ifndef SLNOSTO_H
#define SLNOSTO_H

#include <QWidget>
#include <QObject>
#include <QDialog>
#include <QDebug>
#include "slnosto_global.h"
#include "nostodialog.h"

class SLNOSTOSHARED_EXPORT SLNosto : public QObject
{
    Q_OBJECT
public:
    SLNosto();
public slots:
    void Show();
private:
    NostoDialog nostoDialog;

};

#endif // SLNOSTO_H
