#include "Headers/DialogueBox.h"
#include "Headers/Game.h"

extern Game *game;

DialogueBox::DialogueBox(QPair<DialogueHandler::Speaker, QString> &text)
{
    //TODO: napraviti da drugaciji dialog box bude u zavisnosti od DialogueHandler::Speaker
    setPixmap(QPixmap(":/Other/Resources/Other/dialogue_box.png"));
    currentText = new QGraphicsTextItem(this);
    currentText->setPlainText(text.second);
    currentText->setTextWidth(300);
    currentText->setPos(5,5);  //pozicija od gornjeg levog ugla pixmapa
    QPointF playerPosition = game->player->pos();
    setPos(playerPosition + QPointF(50, -100));
}
