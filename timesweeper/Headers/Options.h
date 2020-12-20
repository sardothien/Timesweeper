#ifndef OPTIONS_H
#define OPTIONS_H

#include <QMainWindow>

namespace Ui
{
    class Options;
}

class Options : public QMainWindow
{
    Q_OBJECT
    public:
        explicit Options(QWidget *parent = nullptr);
        ~Options();

    private slots:
        void on_backButton_clicked();
        void on_volume_valueChanged();
        void on_sound_stateChanged();

    private:
        Ui::Options *ui;
};

#endif // MENU_H

