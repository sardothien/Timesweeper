#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>

#include "Headers/PlayerCharacter.h"
#include "Headers/NPCharacter.h"
#include "Headers/Portal.h"

class Game : public QGraphicsView
{
    Q_OBJECT
    public:
        Game (QWidget *parent = nullptr);
        PlayerCharacter *player;
        static int levelID;
        QGraphicsScene *currentLevel;
        static NPCharacter *currentLevelNpc;
        static Portal *currentLevelPortal;

        static NPCharacter *getCurrentLevelNpc();
        static void setCurrentLevelNpc(NPCharacter *npc);
        static Portal *getCurrentLevelPortal();
        static void setCurrentLevelPortal(Portal *portal);

    public slots:
        void changeLevel();
        void triggerDialogue();
};

#endif // GAME_H

