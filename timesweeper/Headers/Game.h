#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QLabel>
#include <QMouseEvent>
#include <QTimer>
#include <QtMultimedia/QMediaPlayer>

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
        //metode
        Game();
        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void playMusic();
        void makeGameOverLabel();

        //geteri/seteri
        static Portal *getCurrentLevelPortal();
        static void setCurrentLevelPortal(Portal *portal);     
        static int getLevelID();
        bool getSoundOn() const;
        void setSoundOn(bool value);
        bool getIsGameOver() const;
        Ui::Game *getUi() const;
        QLabel *getGameOverLabel() const;

        //polja
        static PlayerCharacter *player;
        static int levelID;
        QGraphicsScene *currentLevel;
        static Portal *currentLevelPortal;
        static QPointF currentLevelPlayerStartPosition;
        QMediaPlayer *music;
        QCursor cursor;
        QTimer *mainTimer;
        QGraphicsPixmapItem *gameOverScreen;

public slots:
        void changeLevel();
        void triggerDialogue();
        void setHealthBar();
        void gameOver();

private:
        Ui::Game *ui;
        QLabel *label;
        QLabel *gameOverLabel;
        bool soundOn = true;
        bool isGameOver = false;
};

#endif // GAME_H

