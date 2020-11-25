#ifndef DIALOGUEHANDLER_H
#define DIALOGUEHANDLER_H

#include <QObject>
#include <QVector>

class DialogueBox;

class DialogueHandler : public QObject
{
Q_OBJECT
public:
    //metode
    static void initializeDialogue(int levelId);
    static void advanceDialogue();
    static void setDialogueActive(bool isActive);
    enum Speaker{
        Strauss,
        Player,
        Game
    };
    //polja
    static bool isDialogueActive;
private:
    static int current_index;
    static QVector<QPair<Speaker, QString>> recenice;
    static DialogueBox *box;
};

#endif // DIALOGUEHANDLER_H
