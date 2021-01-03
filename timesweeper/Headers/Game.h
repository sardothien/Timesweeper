#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QLabel>
#include <QMouseEvent>
#include <QProgressBar>
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
        // Methods
        Game();
        void mouseMoveEvent(QMouseEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void showCredits();
        void playMusic();
        void makeGameOverLabel();
        void makePauseLabel();

        // Getters/Setters
        static void setCurrentLevelPortal(Portal *portal);
        static int getLevelID();
        bool getSoundOn() const;
        void setSoundOn(bool value);
        bool getIsGameOver() const;
        void setIsGameOver(bool isGameOver);
        Ui::Game *getUi() const;
        QLabel *getGameOverLabel() const;
        QLabel *getPauseLabel() const;

        // Fields
        static PlayerCharacter *player;
        static int levelID;
        QGraphicsScene *currentLevel;
        static Portal *currentLevelPortal;
        static QPointF currentLevelPlayerStartPosition;
        QMediaPlayer *music;
        QCursor cursor;
        QTimer *mainTimer;
        QGraphicsPixmapItem *gameOverScreen;
        QProgressBar *bossHealthBar;
        QLabel *bossHead;

    public slots:
        void changeLevel();
        void triggerDialogue();
        void setHealthBar();
        void gameOver();

    private:
        Ui::Game *ui;
        QLabel *m_label;
        QLabel *m_gameOverLabel;
        QLabel *m_pauseLabel;
        bool m_soundOn    = true;
        bool m_isGameOver = false;   
};

#endif // GAME_H
