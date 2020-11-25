#ifndef DIALOGUEBOX_H
#define DIALOGUEBOX_H

#include <QGraphicsPixmapItem>
#include "Headers/DialogueHandler.h"

class DialogueBox : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    public:
        DialogueBox (QPair<DialogueHandler::Speaker, QString> &text);

    private:
        QGraphicsTextItem *currentText;
};

#endif // DIALOGUEBOX_H
