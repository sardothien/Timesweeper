#include "Headers/TimesweeperMainWindow.h"
#include "ui_TimesweeperMainWindow.h"

TimesweeperMainWindow::TimesweeperMainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TimesweeperMainWindow)
{
    ui->setupUi(this);
}

TimesweeperMainWindow::~TimesweeperMainWindow()
{
    delete ui;
}

