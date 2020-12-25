#include "Headers/DialogueBox.h"
#include "Headers/Game.h"

extern Game *game;

DialogueBox::DialogueBox(QPair<DialogueHandler::Speaker, QString> &text)
{
    m_currentText = new QGraphicsTextItem(this);
    m_currentText->setPlainText(text.second);

    if(text.first == DialogueHandler::Speaker::Strauss)
    {
        setPixmap(QPixmap(":/Other/Resources/Other/dialogue_box_strauss.png"));
        m_currentText->setTextWidth(280);
        m_currentText->setPos(10, 20); //pozicija od gornjeg levog ugla pixmapa
    }
    else
    {
        setPixmap(QPixmap(":/Other/Resources/Other/dialogue_box.png"));
        m_currentText->setTextWidth(300);
        m_currentText->setPos(5, 5);
    }

    QPointF playerPosition = game->player->pos();
    setPos(playerPosition + QPointF(50, -100));
}
