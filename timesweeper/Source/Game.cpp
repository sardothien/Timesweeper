#include <QDebug>
#include <QStyle>

#include "Headers/DialogueHandler.h"
#include "Headers/EnemyBoss.h"
#include "Headers/EnemyCharacter.h"
#include "Headers/Game.h"
#include "Headers/Level.h"
#include "Headers/Pickup.h"
#include "Headers/Tile.h"
#include "ui_Game.h"

int Game::m_levelID;

Game::Game()
{
    ui->setupUi(this);
    setWindowTitle("timesweeper");

    m_label = new QLabel(this);
    m_label->setGeometry(10, 10, 155, 55);
    m_label->setProperty("foo", "hb8");

    makeGameOverLabel();
    makePauseLabel();

    setMouseTracking(true);
    m_cursor = QCursor(QPixmap(":/Other/Resources/Other/crosshair.png"), 17, 17);
    setCursor(m_cursor);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setFixedSize(1200, 700);

    m_player = new PlayerCharacter();
    m_player->setFlag(QGraphicsItem::ItemIsFocusable);
    m_player->setFocus();

    connect(m_player, &PlayerCharacter::enteredPortal, this, &Game::changeLevel, Qt::QueuedConnection);
    connect(m_player, &PlayerCharacter::startDialogue, this, &Game::triggerDialogue);
    connect(m_player, &PlayerCharacter::healthChanged, this, &Game::setHealthBar);
    connect(m_player, &PlayerCharacter::playerIsDead, this, &Game::gameOver);

    m_music = new QMediaPlayer();

    m_levelID   = 1;
    m_mainTimer = new QTimer(this);

    changeLevel();
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    m_player->aimAtPoint(event->pos());
    m_player->setFocus();
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if((event->button() == Qt::LeftButton) && (getLevelID() - 1 != 1))
    {
        m_player->shootProjectile();
    }
    m_player->setFocus();
}

void Game::showCredits()
{
    QLabel *m_creditsLabel = new QLabel(this);
    m_creditsLabel->setGeometry(0, 0, 1200, 700);
    m_creditsLabel->setPixmap(QPixmap(":/Other/Resources/Other/credits.png"));
    m_creditsLabel->show();
}

void Game::playMusic()
{
    m_music->setMedia(QUrl("qrc:/Sounds/Resources/Sounds/bgsound_level_"
                           + QString::number(getLevelID()) + ".mp3"));
    if(m_soundOn && getLevelID() != 1)
    {
        m_music->play();
    }
}

void Game::makeGameOverLabel()
{
    m_gameOverLabel = new QLabel(this);
    m_gameOverLabel->setGeometry(300, 120, 590, 360);
    m_gameOverLabel->setPixmap(QPixmap(":/Other/Resources/Other/gameover.png"));
    m_gameOverLabel->hide();
}

void Game::makePauseLabel()
{
    m_pauseLabel = new QLabel(this);
    m_pauseLabel->setGeometry(300, 120, 590, 360);
    m_pauseLabel->setPixmap(QPixmap(":/Other/Resources/Other/pause.png"));
    m_pauseLabel->hide();
}

//----------GETERI/SETERI---------------
void Game::setCurrentLevelPortal(Portal *portal) { m_currentLevelPortal = portal; }

int Game::getLevelID() { return m_levelID; }

bool Game::getSoundOn() const { return m_soundOn; }

void Game::setSoundOn(bool value) { m_soundOn = value; }

bool Game::getIsGameOver() const { return m_isGameOver; }

void Game::setIsGameOver(bool isGameOver) { m_isGameOver = isGameOver; }

Ui::Game *Game::getUi() const { return ui; }

QLabel *Game::getGameOverLabel() const { return m_gameOverLabel; }

QLabel *Game::getPauseLabel() const { return m_pauseLabel; }

//----------SLOTOVI---------------------

void Game::changeLevel()
{
    if(getLevelID() != 1)
    {
        auto allItems = m_currentLevel->items();
        for(auto item : allItems)
        {
            if(typeid(*item) == typeid(Tile) || typeid(*item) == typeid(EnemyCharacter) ||
               typeid(*item) == typeid(Portal) || typeid(*item) == typeid(EnemyBoss) ||
               typeid(*item) == typeid(Pickup))
            {
                m_currentLevel->removeItem(item);
                delete item;
            }
        }
    }

    m_currentLevel = Level::LoadLevel();
    QObject::connect(m_mainTimer, SIGNAL(timeout()), m_currentLevel, SLOT(advance()));
    m_mainTimer->start(20);

    DialogueHandler::initializeDialogue();

    setScene(m_currentLevel);

    m_player->setFocus();
    m_player->setPos(m_currentLevelPlayerStartPosition);

    if(getLevelID() != 1)
    {
        m_player->setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_right.png"));
        m_player->setScale(0.8);
    }
    m_currentLevel->addItem(m_player);

    if(getLevelID() != 1)
    {
        m_currentLevel->addItem(m_player->getGunArm());

    }
    centerOn(m_player);

    playMusic();

    m_levelID++;
}

void Game::triggerDialogue()
{
    DialogueHandler::setDialogueActive(true);
    DialogueHandler::advanceDialogue();
}

void Game::setHealthBar()
{
    QString health;
    for(int i = 1; i <= 8; i++)
    {
        health = QString::number(i);
        health = "hb" + health;

        if(m_player->getHealth() == i)
        {
            m_label->setProperty("foo", health);
        }
    }

    m_label->style()->unpolish(m_label);
    m_label->style()->polish(m_label);
    m_label->update();
}

void Game::gameOver()
{
    m_isGameOver = true;
    m_gameOverLabel->show();
}
