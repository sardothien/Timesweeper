#include "Headers/DialogueHandler.h"
#include "Headers/DialogueBox.h"
#include "Headers/Game.h"

QVector<QPair<DialogueHandler::Speaker, QString>> DialogueHandler::m_sentances;
int DialogueHandler::m_currentIndex;
DialogueBox *DialogueHandler::m_box;
bool DialogueHandler::isDialogueActive;

extern Game *game;

void DialogueHandler::initializeDialogue()
{
    m_currentIndex   = 0;
    m_sentances      = {};
    isDialogueActive = false;

    QString filename = ":/Levels/Resources/Levels/level" + QString::number(game->getLevelID()) + "_dialogue.txt";
    QFile file(filename);

    if(!file.exists())
    {
        qDebug() << "File doesn't exist!\n";
        return ;
    }
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "File open failed!\n";
        return ;
    }

    QTextStream in(&file);

    // number of sentances is stored in the first line
    int numberOfLines = in.readLine().toInt();

    QStringList line;
    for(int i = 0; i < numberOfLines; i++)
    {
        line = in.readLine().split(" # ");

        int speaker = line.at(0).toInt();
        switch(speaker)
        {
            case 0:
                m_sentances.append(qMakePair(Speaker::Strauss, line.at(1)));
                break;
            case 1:
                m_sentances.append(qMakePair(Speaker::Player, line.at(1)));
                break;
            case 2:
                m_sentances.append(qMakePair(Speaker::Game, line.at(1)));
                break;
            default:
                qDebug() << "Invalid number given for enum!\n";
        }
    }

    file.close();
}

void DialogueHandler::advanceDialogue()
{
    if(m_box != nullptr)
    {
        game->scene()->removeItem(m_box);
    }

    if(QString::compare(m_sentances[m_currentIndex].second, "credits") == 0)
    {
        // kraj igre
        game->showCredits();
    }
    else if(QString::compare(m_sentances[m_currentIndex].second, "endsection") == 0)
    {
        setDialogueActive(false);
    }
    else if(m_currentIndex < m_sentances.size())
    {
            m_box = new DialogueBox(m_sentances[m_currentIndex]);
            game->scene()->addItem(m_box);
    }

    if(m_currentIndex < m_sentances.size() - 1)
    {
        m_currentIndex++;
    }
}

void DialogueHandler::setDialogueActive(bool isActive)
{
    isDialogueActive = isActive;
}
