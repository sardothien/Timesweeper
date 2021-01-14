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

    connect(ui->backButton, &QPushButton::clicked, this, &Options::backButtonClicked);
    connect(ui->volume, &QSlider::valueChanged, this, &Options::volumeValueChanged);
    connect(ui->sound, &QCheckBox::stateChanged, this, &Options::soundStateChanged);
    connect(ui->soundEffect, &QCheckBox::stateChanged, this, &Options::soundEffectStateChanged);
}

Options::~Options()
{
    delete ui;
}

void Options::backButtonClicked()
{
    this->hide();
}

void Options::volumeValueChanged()
{
    game->music->setVolume(ui->volume->value());
}

void Options::soundStateChanged()
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

void Options::soundEffectStateChanged()
{
    if(ui->soundEffect->checkState() == Qt::Unchecked)
    {
        game->player->setSoundEffectOn(false);
    }
    else
    {
        game->player->setSoundEffectOn(true);
    }
}

