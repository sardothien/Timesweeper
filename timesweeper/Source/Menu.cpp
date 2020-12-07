#include "Headers/Menu.h"
#include "Headers/Game.h"
#include "ui_Menu.h"

#include <iostream>

Game * game;

Menu::Menu(QWidget *parent) : QMainWindow(parent), ui(new Ui::Menu)
{
    ui->setupUi(this);
    setFixedSize(800,500);
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
