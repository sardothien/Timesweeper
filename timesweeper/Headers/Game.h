#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QObject>
#include <QtMultimedia/QMediaPlayer>
#include <QWidget>
#include <QLabel>

#include "Headers/PlayerCharacter.h"
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
        static Portal *currentLevelPortal;
        static QPointF currentLevelPlayerStartPosition;
        QMediaPlayer *music;
        QCursor cursor;
        QTimer *projectileTimer;
        QTimer *enemyWalkTimer;
        QTimer *enemyShootTimer;
        QTimer *tileMoveTimer;
        QTimer *enemyHealthTimer;

        static Portal *getCurrentLevelPortal();
        static void setCurrentLevelPortal(Portal *portal);
        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent * event);
        void playMusic();
        void makeGameOverLabel();

        static int getLevelID();

        void setSoundOn(bool value);

        bool getSoundOn() const;

        QTimer *getProjectileTimer() const;
        QTimer *getEnemyWalkTimer() const;
        QTimer *getEnemyShootTimer() const;
        QTimer *getTileMoveTimer() const;
        QTimer *getEnemyHealthTimer() const;

        QGraphicsPixmapItem *gameOverScreen;

        bool getIsGameOver() const;
        Ui::Game *getUi() const;
        QLabel *getGameOverLabel() const;

public slots:
        void changeLevel();
        void triggerDialogue();
        void setHealthBar();
        void gameOver();
private:
        Ui::Game *ui;
        QLabel *label;
        QLabel* gameOverLabel;
        bool soundOn = true;
        bool isGameOver = false;
};

#endif // GAME_H

