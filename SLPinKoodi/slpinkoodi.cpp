#include "slpinkoodi.h"


SLPinKoodi::SLPinKoodi()
{
    olioPinKoodiDialogi =new PinkoodiDialogi;
}
 void SLPinKoodi::showdialog(){
    olioPinKoodiDialogi->PinKoodi = PinKoodi;
    olioPinKoodiDialogi->showFullScreen();

 }
