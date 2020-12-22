#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QObject>
#include <QtMultimedia/QMediaPlayer>
#include <QWidget>
#include <QLabel>

#include "Headers/PlayerCharacter.h"
#include "Headers/NPCharacter.h"
#include "Headers/Portal.h"

namespace Ui
{
    class Game;
}

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
        static QPointF currentLevelPlayerStartPosition;
        QMediaPlayer *music;
        QCursor cursor;
        QTimer *projectileTimer;
        QTimer *enemyWalkTimer;
        QTimer *enemyShootTimer;
        QTimer *tileMoveTimer;

        static NPCharacter *getCurrentLevelNpc();
        static void setCurrentLevelNpc(NPCharacter *npc);
        static Portal *getCurrentLevelPortal();
        static void setCurrentLevelPortal(Portal *portal);
        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent * event);
        void playMusic();

        static int getLevelID();

        void setSoundOn(bool value);

        bool getSoundOn() const;

        QTimer *getProjectileTimer() const;
        QTimer *getEnemyWalkTimer() const;
        QTimer *getEnemyShootTimer() const;
        QTimer *getTileMoveTimer() const;

        QGraphicsPixmapItem *gameOverScreen;

        bool getIsGameOver() const;

public slots:
        void changeLevel();
        void triggerDialogue();
        void setHealthBar();
        void gameOver();
private:
        Ui::Game *ui;
        QLabel *label;
        bool soundOn = true;
        bool isGameOver = false;
};

#endif // GAME_H

