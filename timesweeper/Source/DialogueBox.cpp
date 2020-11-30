#include "Headers/DialogueBox.h"
#include "Headers/Game.h"

extern Game *game;

DialogueBox::DialogueBox(QPair<DialogueHandler::Speaker, QString> &text)
{
    //TODO: napraviti da drugaciji dialog box bude u zavisnosti od DialogueHandler::Speaker
    currentText = new QGraphicsTextItem(this);
    currentText->setPlainText(text.second);

    if(text.first == DialogueHandler::Speaker::Strauss)
    {
        setPixmap(QPixmap(":/Other/Resources/Other/dialogue_box_strauss.png"));
        currentText->setTextWidth(280);
        currentText->setPos(10,20);   //pozicija od gornjeg levog ugla pixmapa
    }
    else
    {
        setPixmap(QPixmap(":/Other/Resources/Other/dialogue_box.png"));
        currentText->setTextWidth(300);
        currentText->setPos(5,5);
    }

    QPointF playerPosition = game->player->pos();
    setPos(playerPosition + QPointF(50, -100));
}
