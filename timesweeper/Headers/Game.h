#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QObject>
#include <QtMultimedia/QMediaPlayer>
#include <QWidget>

#include "Headers/PlayerCharacter.h"
#include "Headers/NPCharacter.h"
#include "Headers/Portal.h"

class Game : public QGraphicsView
{
    Q_OBJECT
    public:
        Game (QWidget *parent = nullptr);
        static PlayerCharacter *player;
        static int levelID;
        QGraphicsScene *currentLevel;
        static NPCharacter *currentLevelNpc;
        static Portal *currentLevelPortal;
        QMediaPlayer *music;

        static NPCharacter *getCurrentLevelNpc();
        static void setCurrentLevelNpc(NPCharacter *npc);
        static Portal *getCurrentLevelPortal();
        static void setCurrentLevelPortal(Portal *portal);
        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent * event);
        void playMusic();

        static int getLevelID();

public slots:
        void changeLevel();
        void triggerDialogue();
};

#endif // GAME_H

