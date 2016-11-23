#include "slelasku.h"


SLeLasku::SLeLasku(){
}

void SLeLasku::Show(){
    eDialog.query = query;
    eDialog.CardID = CardID;
    eDialog.GetData();
    eDialog.showFullScreen();
}
