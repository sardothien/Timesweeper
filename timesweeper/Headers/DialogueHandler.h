#ifndef DIALOGUEHANDLER_H
#define DIALOGUEHANDLER_H

#include <QObject>

class DialogueBox;

class DialogueHandler : public QObject
{
    Q_OBJECT
    public:
        // metode
        static void initializeDialogue();
        static void advanceDialogue();
        static void setDialogueActive(bool isActive);

        enum Speaker{
            Strauss,
            Player,
            Game
        };

        // polja
        static bool isDialogueActive;

    private:
        static int m_currentIndex;
        static QVector<QPair<Speaker, QString>> m_sentances;
        static DialogueBox *m_box;
};

#endif // DIALOGUEHANDLER_H
