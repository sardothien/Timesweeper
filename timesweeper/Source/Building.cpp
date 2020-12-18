#include "Headers/Building.h"

Building::Building(Building::Buildings b)
{
    if(b == Buildings::sheriff)
        setPixmap(QPixmap(":/Other/Resources/Other/sheriff_level_4.png"));
    else if (b == Buildings::saloon)
        setPixmap(QPixmap(":/Other/Resources/Other/saloon_level_4.png"));
    else if (b == Buildings::bank)
        setPixmap(QPixmap(":/Other/Resources/Other/bank_level_4.png"));
    else if (b == Buildings::cantina)
        setPixmap(QPixmap(":/Other/Resources/Other/cantina_level_4.png"));
    else if (b == Buildings::drugStore)
        setPixmap(QPixmap(":/Other/Resources/Other/drugstore_level_4.png"));
    else if (b == Buildings::generalStore)
        setPixmap(QPixmap(":/Other/Resources/Other/general_store_level_4.png"));
    else if (b == Buildings::office)
        setPixmap(QPixmap(":/Other/Resources/Other/office_level_4.png"));
    else if (b == Buildings::hotel)
        setPixmap(QPixmap(":/Other/Resources/Other/hotel_level_4.png"));
    else if (b == Buildings::post)
        setPixmap(QPixmap(":/Other/Resources/Other/post_level_4.png"));
}
