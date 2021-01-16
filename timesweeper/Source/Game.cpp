#include <QDebug>
#include <QStyle>

#include "Headers/DialogueHandler.h"
#include "Headers/EnemyBoss.h"
#include "Headers/EnemyCharacter.h"
#include "Headers/Game.h"
#include "Headers/Level.h"
#include "Headers/Menu.h"
#include "Headers/Pickup.h"
#include "Headers/Tile.h"
#include "ui_Game.h"

int Game::levelID;

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
    cursor = QCursor(QPixmap(":/Other/Resources/Other/crosshair.png"), 17, 17);
    setCursor(cursor);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 700);

    player = new PlayerCharacter();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    connect(player, &PlayerCharacter::enteredPortal, this, &Game::changeLevel, Qt::QueuedConnection);
    connect(player, &PlayerCharacter::startDialogue, this, &Game::triggerDialogue);
    connect(player, &PlayerCharacter::healthChanged, this, &Game::setHealthBar);
    connect(player, &PlayerCharacter::playerIsDead, this, &Game::gameOver);

    music = new QMediaPlayer();

    levelID   = 1;
    mainTimer = new QTimer(this);

    changeLevel();
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    player->aimAtPoint(event->pos());
    player->setFocus();
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if((event->button() == Qt::LeftButton) && (getLevelID() - 1 != 1))
    {
        player->shootProjectile();
    }
    player->setFocus();
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
    if(m_soundOn && getLevelID() != 1)
    {
        music->play();
    }
}

void Game::makeGameOverLabel()
{
    m_gameOverLabel = new QLabel(this);
    m_gameOverLabel->setGeometry(300, 120, 590, 360);
    m_gameOverLabel->setPixmap(QPixmap(":/Other/Resources/Other/gameover.png"));
    m_gameOverLabel->hide();

    delete Menu::options;
    delete Menu::help;
}

void Game::makePauseLabel()
{
    m_pauseLabel = new QLabel(this);
    m_pauseLabel->setGeometry(300, 120, 590, 360);
    m_pauseLabel->setPixmap(QPixmap(":/Other/Resources/Other/pause.png"));
    m_pauseLabel->hide();
}

//----------Getters/Setters---------------
void Game::setCurrentLevelPortal(Portal *portal) { currentLevelPortal = portal; }

int Game::getLevelID() { return levelID; }

bool Game::getSoundOn() const { return m_soundOn; }

void Game::setSoundOn(bool value) { m_soundOn = value; }

bool Game::getIsGameOver() const { return m_isGameOver; }

void Game::setIsGameOver(bool isGameOver) { m_isGameOver = isGameOver; }

Ui::Game *Game::getUi() const { return ui; }

QLabel *Game::getGameOverLabel() const { return m_gameOverLabel; }

QLabel *Game::getPauseLabel() const { return m_pauseLabel; }

//----------Slots---------------------

void Game::changeLevel()
{
    if(getLevelID() != 1)
    {
        auto allItems = currentLevel->items();
        for(auto item : allItems)
        {
            if(typeid(*item) == typeid(Tile) || typeid(*item) == typeid(EnemyCharacter) ||
               typeid(*item) == typeid(Portal) || typeid(*item) == typeid(EnemyBoss) ||
               typeid(*item) == typeid(Pickup))
            {
                currentLevel->removeItem(item);
                delete item;
            }
        }
    }

    currentLevel = Level::loadLevel();
    QObject::connect(mainTimer, SIGNAL(timeout()), currentLevel, SLOT(advance()));
    mainTimer->start(20);

    DialogueHandler::initializeDialogue();

    setScene(currentLevel);

    player->setFocus();
    player->setPos(currentLevelPlayerStartPosition);

    if(getLevelID() != 1)
    {
        player->setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_right.png"));
        player->setScale(0.8);
    }
    currentLevel->addItem(player);

    if(getLevelID() != 1)
    {
        currentLevel->addItem(player->getGunArm());

    }
    centerOn(player);

    music->setMedia(QUrl("qrc:/Sounds/Resources/Sounds/bgsound_level_"
                           + QString::number(getLevelID()) + ".mp3"));
    playMusic();

    levelID++;
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

        if(player->getHealth() == i)
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
    mainTimer->stop();
    music->pause();
    m_isGameOver = true;
    m_gameOverLabel->show();
}
