#include "Headers/Building.h"

Building::Building(Buildings b)
{
    if(b == Buildings::sheriff)
    {
        setPixmap(QPixmap(":/Other/Resources/Other/sheriff_level_4.png"));
    }
    else if(b == Buildings::saloon)
    {
        setPixmap(QPixmap(":/Other/Resources/Other/saloon_level_4.png"));
    }
    else if(b == Buildings::bank)
    {
        setPixmap(QPixmap(":/Other/Resources/Other/bank_level_4.png"));
    }
    else if(b == Buildings::office)
    {
        setPixmap(QPixmap(":/Other/Resources/Other/office_level_4.png"));
    }
    else if(b == Buildings::bigSaloon)
    {
        setPixmap(QPixmap(":/Other/Resources/Other/big_saloon_level_4.png"));
    }
    else if(b == Buildings::generalStore)
    {
        setPixmap(QPixmap(":/Other/Resources/Other/general_store_level_4.png"));
    }
    else if(b == Buildings::hotel)
    {
        setPixmap(QPixmap(":/Other/Resources/Other/hotel_level_4.png"));
    }
    else if(b == Buildings::church)
    {
        setPixmap(QPixmap(":/Other/Resources/Other/church_level_4.png"));
    }
}
