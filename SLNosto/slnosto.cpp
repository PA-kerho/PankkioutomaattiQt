#include "slnosto.h"


SLNosto::SLNosto(){

}

void SLNosto::Show(){
    nostoDialog.CardID = CardID;
    nostoDialog.query = query;
    nostoDialog.showFullScreen();
}
