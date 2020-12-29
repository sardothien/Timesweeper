#include "Headers/Menu.h"
#include "Headers/Game.h"
#include "Headers/Help.h"
#include "Headers/Options.h"
#include "ui_Menu.h"

Game * game;

Menu::Menu(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Menu)
{
    ui->setupUi(this);
    setFixedSize(800, 500);
    setWindowTitle("timesweeper");
    game = new Game();

    connect(ui->startButton, &QPushButton::clicked, this, &Menu::startButtonClicked);
    connect(ui->quitButton, &QPushButton::clicked, this, &Menu::quitButtonClicked);
    connect(ui->optionsButton, &QPushButton::clicked, this, &Menu::optionsButtonClicked);
    connect(ui->helpButton, &QPushButton::clicked, this, &Menu::helpButtonClicked);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::startButtonClicked()
{
    if(game->getSoundOn())
    {
        game->m_music->play();
    }
    game->show();
    this->hide();
}

void Menu::quitButtonClicked()
{
    exit(0);
}

void Menu::optionsButtonClicked()
{
    Options *options = new Options();
    options->show();
    // this->hide();
}

void Menu::helpButtonClicked()
{
    Help *help = new Help();
    help->show();
    // this->hide();
}
