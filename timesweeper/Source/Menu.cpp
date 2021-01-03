#include "Headers/Menu.h"
#include "Headers/Game.h"
#include "Headers/Help.h"
#include "Headers/Options.h"
#include "ui_Menu.h"

Game * game;

Help* Menu::help;
Options* Menu::options;

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

    options = new Options();
    help = new Help();
}

void Menu::startButtonClicked()
{
    if(game->getSoundOn())
    {
        game->music->play();
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
    options->show();
}

void Menu::helpButtonClicked()
{
    help->show();
}
