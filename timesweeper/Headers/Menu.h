#ifndef MENU_H
#define MENU_H

#include <QMainWindow>

namespace Ui
{
    class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT
    public:
        explicit Menu(QWidget *parent = nullptr);
        ~Menu();

    private slots:
        void on_startButton_clicked();
        void on_quitButton_clicked();
        void on_optionsButton_clicked();
        void on_helpButton_clicked();

private:
        Ui::Menu *ui;
};

#endif // MENU_H
