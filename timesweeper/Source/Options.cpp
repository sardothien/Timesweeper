#include "Headers/Options.h"
#include "Headers/Game.h"
#include "ui_Options.h"

#include <QDebug>

extern Game *game;

Options::Options(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Options)
{
    ui->setupUi(this);
    setFixedSize(800, 500);
    setWindowTitle("timesweeper");
}

Options::~Options()
{
    delete ui;
}

void Options::on_backButton_clicked()
{
    this->hide();
}

void Options::on_volume_valueChanged()
{
    qDebug() << ui->volume->value();
    game->music->setVolume(ui->volume->value());
}

void Options::on_sound_stateChanged()
{
    if(ui->sound->checkState() == Qt::Unchecked)
    {
        game->setSoundOn(false);
    }
    else
    {
        game->setSoundOn(true);
    }
}
