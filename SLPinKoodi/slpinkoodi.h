#ifndef SLPINKOODI_H
#define SLPINKOODI_H


#include "pinkoodidialogi.h"
#include "slpinkoodi_global.h"

class SLPINKOODISHARED_EXPORT SLPinKoodi
{

public:
    SLPinKoodi();
    void showdialog();
    QString PinKoodi;


    PinkoodiDialogi *olioPinKoodiDialogi;


};

#endif // SLPINKOODI_H
