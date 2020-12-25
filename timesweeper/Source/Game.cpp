#include <QDebug>
#include <QStyle>

#include "Headers/DialogueHandler.h"
#include "Headers/Game.h"
#include "Headers/Level.h"
#include "ui_Game.h"


int Game::levelID;

Game::Game()
{
    ui->setupUi(this);
    setWindowTitle("timesweeper");

    label = new QLabel(this);
    label->setGeometry(10,10,155,55);
    label->setProperty("foo", "hb8");

    makeGameOverLabel();

    setMouseTracking(true);
    cursor = QCursor(QPixmap(":/Other/Resources/Other/crosshair.png"), 25 , 25);
    setCursor(cursor);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200, 700);

    player = new PlayerCharacter();
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    connect(player, &PlayerCharacter::enteredPortal, this, &Game::changeLevel);
    connect(player, &PlayerCharacter::startDialogue, this, &Game::triggerDialogue);
    connect(player, &PlayerCharacter::healthChanged, this, &Game::setHealthBar);
    connect(player, &PlayerCharacter::playerIsDead, this, &Game::gameOver);

    music = new QMediaPlayer();

    //NOTE: ne dirati ovde levelID
    levelID = 1;
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
    if((event->button() == Qt::LeftButton) && (levelID - 1 != 1))
    {
        player->shootProjectile();
    }
    player->setFocus();
}

void Game::playMusic()
{
    music->setMedia(QUrl("qrc:/Sounds/Resources/Sounds/bgsound_level_" + QString::number(levelID) + ".mp3"));
    if(soundOn && levelID != 1)
    {
        music->play();
    }
}

void Game::makeGameOverLabel()
{
    gameOverLabel = new QLabel(this);
    gameOverLabel->setGeometry(300,120,590,360);
    gameOverLabel->setPixmap(QPixmap(":/Other/Resources/Other/gameover.png"));
    gameOverLabel->hide();
}

//----------GETERI/SETERI---------------

Portal *Game::getCurrentLevelPortal()
{
    return currentLevelPortal;
}

void Game::setCurrentLevelPortal(Portal *portal)
{
    currentLevelPortal = portal;
}

int Game::getLevelID()
{
    return levelID;
}

bool Game::getSoundOn() const
{
    return soundOn;
}

void Game::setSoundOn(bool value)
{
    soundOn = value;
}

bool Game::getIsGameOver() const
{
    return isGameOver;
}

Ui::Game *Game::getUi() const
{
    return ui;
}

QLabel *Game::getGameOverLabel() const
{
    return gameOverLabel;
}

//----------SLOTOVI----------------

void Game::changeLevel()
{
    //NOTE: pitati asistenta ovde za dealokaciju
    if(levelID != 1){
        auto allItems = currentLevel->items();
        for (auto item : allItems)
        {
            if(typeid (*item) != typeid (PlayerCharacter))
            {
                currentLevel->removeItem(item);
                //delete item;
            }
        }
    }

    currentLevel = Level::LoadLevel();
    QObject::connect(mainTimer, SIGNAL(timeout()), currentLevel, SLOT(advance()) );
    mainTimer->start(40);

    DialogueHandler::initializeDialogue();
    setScene(currentLevel);
    player->setFocus();
    player->setPos(currentLevelPlayerStartPosition);

    if(levelID != 1)
    {
        player->setPixmap(QPixmap(":/CharacterModels/Resources/CharacterModels/player_right.png"));
        player->setScale(0.8);
    }
    currentLevel->addItem(player);
    //NOTE: ovaj if ne sme da se spoji sa ovim iznad jer se pixmap igraca iscrta iznad pixmapa puske
    if(levelID != 1)
    {
        currentLevel->addItem(player->getGunArm());

    }
    centerOn(player);
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
    for (int i = 1; i <= 8; i++)
    {
        health = QString::number(i);
        health = "hb" + health;

        if (player->getHealth() == i)
            label->setProperty("foo", health);
    }

    label->style()->unpolish(label);
    label->style()->polish(label);
    label->update();
}

void Game::gameOver()
{
    isGameOver = true;
    gameOverLabel->show();

//    if (isGameOver == false)
//    {

//        gameOverScreen = new QGraphicsPixmapItem;
//        gameOverScreen->setPixmap(QPixmap(":/Other/Resources/Other/gameover.png"));
//        gameOverScreen->setOpacity(0.9);
//        // TODO - popraviti pozicije za 3. i 5. nivo
//        if(player->x() < 450)
//            gameOverScreen->setPos(300, scene()->sceneRect().center().y()-180);
//        else
//            gameOverScreen->setPos(player->x()-200, scene()->sceneRect().center().y()-180);

//        currentLevel->addItem(gameOverScreen);
//    }

}
