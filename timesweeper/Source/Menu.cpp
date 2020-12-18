#include "Headers/Menu.h"
#include "Headers/Game.h"
#include "Headers/Help.h"
#include "Headers/Options.h"
#include "ui_Menu.h"

Game * game;

Menu::Menu(QWidget *parent) : QMainWindow(parent), ui(new Ui::Menu)
{
    ui->setupUi(this);
    setFixedSize(800,500);
    setWindowTitle("timesweeper");
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_startButton_clicked()
{
    game = new Game();
    game->show();
    this->hide();
}

void Menu::on_quitButton_clicked()
{
    exit(0);
}

void Menu::on_optionsButton_clicked()
{
    Options *options = new Options();
    options->show();
    this->hide();
}

void Menu::on_helpButton_clicked()
{
    Help *help = new Help();
    help->show();
    this->hide();
}
