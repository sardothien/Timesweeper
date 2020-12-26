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
        // metode
        Game();
        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void playMusic();
        void makeGameOverLabel();

        // geteri/seteri
        static Portal *getCurrentLevelPortal();
        static void setCurrentLevelPortal(Portal *portal);
        static int getLevelID();
        bool getSoundOn() const;
        void setSoundOn(bool value);
        bool getIsGameOver() const;
        Ui::Game *getUi() const;
        QLabel *getGameOverLabel() const;

        // polja
        static PlayerCharacter *m_player;
        static int m_levelID;
        QGraphicsScene *m_currentLevel;
        static Portal *m_currentLevelPortal;
        static QPointF m_currentLevelPlayerStartPosition;
        QMediaPlayer *m_music;
        QCursor m_cursor;
        QTimer *m_mainTimer;
        QGraphicsPixmapItem *m_gameOverScreen;

    public slots:
        void changeLevel();
        void triggerDialogue();
        void setHealthBar();
        void gameOver();

    private:
        Ui::Game *ui;
        QLabel *m_label;
        QLabel *m_gameOverLabel;
        bool m_soundOn    = true;
        bool m_isGameOver = false;
};

#endif // GAME_H
