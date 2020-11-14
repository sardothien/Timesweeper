#ifndef TIMESWEEPERMAINWINDOW_H
#define TIMESWEEPERMAINWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class TimesweeperMainWindow; }
QT_END_NAMESPACE

class TimesweeperMainWindow : public QWidget
{
    Q_OBJECT

public:
    TimesweeperMainWindow(QWidget *parent = nullptr);
    ~TimesweeperMainWindow();

private:
    Ui::TimesweeperMainWindow *ui;
};
#endif // TIMESWEEPERMAINWINDOW_H
