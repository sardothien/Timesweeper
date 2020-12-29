#include "Headers/Help.h"
#include "Headers/Menu.h"
#include "ui_Help.h"

Help::Help(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Help)
{
    ui->setupUi(this);
    setFixedSize(800, 500);
    setWindowTitle("timesweeper");

    connect(ui->backButton, &QPushButton::clicked, this, &Help::backButtonClicked);
}

Help::~Help()
{
    delete ui;
}

void Help::backButtonClicked()
{
    this->~Help();
}
