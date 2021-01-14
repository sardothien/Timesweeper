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
        void backButtonClicked();
        void volumeValueChanged();
        void soundStateChanged();
        void soundEffectStateChanged();

    private:
        Ui::Options *ui;
};

#endif // MENU_H

