#include "Headers/DialogueBox.h"
#include "Headers/Game.h"

extern Game *game;

DialogueBox::DialogueBox(QPair<DialogueHandler::Speaker, QString> &text)
{
    m_currentText = new QGraphicsTextItem(this);
    m_currentText->setPlainText(text.second);
    m_currentText->setFont(QFont("Adventure", 11));

    if(text.first == DialogueHandler::Speaker::Strauss)
    {
        setPixmap(QPixmap(":/Other/Resources/Other/dialogue_box_strauss.png"));
        m_currentText->setTextWidth(280);
        m_currentText->setPos(5, 15); //from top left of the pixmap
    }
    else
    {
        setPixmap(QPixmap(":/Other/Resources/Other/dialogue_box.png"));
        m_currentText->setTextWidth(300);
        m_currentText->setPos(2, 2);
    }

    QPointF playerPosition = game->m_player->pos();
    setPos(playerPosition + QPointF(50, -100));
}
