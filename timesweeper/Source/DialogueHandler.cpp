#include <QDebug>
#include "Headers/DialogueHandler.h"
#include "Headers/DialogueBox.h"
#include "Headers/Game.h"

//inicijalizacija statickih promenljivih klase DialogueHandler
QVector<QPair<DialogueHandler::Speaker, QString>> DialogueHandler::recenice;
int DialogueHandler::current_index;
DialogueBox *DialogueHandler::box;
bool DialogueHandler::isDialogueActive;

extern Game *game;

void DialogueHandler::initializeDialogue()
{
    current_index = 0;
    recenice = {};
    isDialogueActive = false;

    //prologue
    if(game->levelID == 1)
    {
        recenice.append(QPair(Speaker::Strauss, "Hey there intern! So, good news and bad news."));
        recenice.append(QPair(Speaker::Strauss, "Bad news is that we are in a bit of a predicament."));
        recenice.append(QPair(Speaker::Strauss, "The alien swarm has sorounded our base outside, and that big angry boy in the middle is their alpha and is going to blow us  up any minute now."));
        recenice.append(QPair(Speaker::Strauss, "AAAnyway, the good news is that you got a promotion!."));
        recenice.append(QPair(Speaker::Strauss, "Congratulations intern, you are the worlds first Timesweeper!"));
        recenice.append(QPair(Speaker::Strauss, "Take this special Time Gun and this special Time Communicator and jump right into that Time Portal there, ill explain everything when you get there"));
        recenice.append(QPair(Speaker::Player, "Get where?"));
        recenice.append(QPair(Speaker::Strauss, "You were not following me I see. It's not WHERE, it's WHEN!"));
        recenice.append(QPair(Speaker::Game, "endsection"));
    }
    //maya
    else if(game->levelID == 2)
    {
        recenice.append(QPair(Speaker::Strauss, "Okay, listen up!"));
        recenice.append(QPair(Speaker::Strauss, "These aliens invented time travel, and inserted themselves in various points throughout our history so they can start building the different components for their Alpha aliens' body."));
        recenice.append(QPair(Speaker::Strauss, "Apparently it takes them many centuries to do so."));
        recenice.append(QPair(Speaker::Strauss, "Their plan is to blow up our planet when the Alpha is finished in 2020. "));
        recenice.append(QPair(Speaker::Player, "Okay, but that is a pretty stupid plan."));
        recenice.append(QPair(Speaker::Player, "Why not just build their Alpha on their planet, wherever that is, and get him to our planet and then blow us up?"));
        recenice.append(QPair(Speaker::Player, "And when even am I?"));
        recenice.append(QPair(Speaker::Strauss, "I have aboslutely no clue, im just a scientist, not an alien army strategist! "));
        recenice.append(QPair(Speaker::Strauss, "Yeah, now that I think about it they, are a pretty big dissapointment."));
        recenice.append(QPair(Speaker::Strauss, "Anyway, you are currently on May 4th 944 AD, in Chichen Itza."));
        recenice.append(QPair(Speaker::Strauss, "Me and the boys in the lab found this to be the first ever recorded alien sighting."));
        recenice.append(QPair(Speaker::Player, "Hey, uumm... didn't the Mayas sacrifice people? Did they do it while worshiping aliens?"));
        recenice.append(QPair(Speaker::Strauss, "Probably, so try not to get sacrificed."));
        recenice.append(QPair(Speaker::Strauss, "Just find those aliens intern! And blow them up with your Time Gun!"));
        recenice.append(QPair(Speaker::Game, "endsection"));
        //ubijen prvi vanzemaljac
        recenice.append(QPair(Speaker::Player, "I got him doctor Strauss!"));
        recenice.append(QPair(Speaker::Strauss, "Aw heck, I forgot about one small detail."));
        recenice.append(QPair(Speaker::Strauss, "We all share the same timeline, so when you change something in the past, it could change other things in the future, not just the aliens!"));
        recenice.append(QPair(Speaker::Strauss, "For some reason killing that particular alien, caused my office walls to change color! "));
        recenice.append(QPair(Speaker::Strauss, "Its okay, lets jsut hope your actions only have minor consequences like this one."));
        recenice.append(QPair(Speaker::Strauss, "Also, try not to cause any paradoxes!"));
        recenice.append(QPair(Speaker::Game, "endsection"));
        //na kraju
        recenice.append(QPair(Speaker::Strauss, "You are doing great intern! The aliens you killed must have started some alien family trees! "));
        recenice.append(QPair(Speaker::Strauss, "About a quarter of the swarm outside just dissapeared, and the others look really confused."));
        recenice.append(QPair(Speaker::Strauss, "We will open another Time Portal for you. Jump in!"));
        recenice.append(QPair(Speaker::Game, "endsection"));
    }
    //dinosaurusi
    else if(game->levelID == 3)
    {
       recenice.append(QPair(Speaker::Player, "Wait, what? Dinosaurs?"));
       recenice.append(QPair(Speaker::Strauss, "Yep."));
       recenice.append(QPair(Speaker::Player, "But didn't you say the first alien encoutner was in 944 AD?"));
       recenice.append(QPair(Speaker::Strauss, "I did. And that is correct. They jump to different points in our timeline but they do so out of order."));
       recenice.append(QPair(Speaker::Strauss, "You get it? I know you don't."));
       recenice.append(QPair(Speaker::Strauss, "It's okay my boy, don't worry yourself with little details, leave to me and the lab boys."));
       recenice.append(QPair(Speaker::Game, "endsection"));
       //kasnije
       recenice.append(QPair(Speaker::Player, "Hey, uumm, doctor? Doesn't this gun run out of ammo?"));
       recenice.append(QPair(Speaker::Strauss, "HA!. Do you really think we would invent something sounding as cool as \"Time Gun\" and make you worry about ammunition while using that? "));
       recenice.append(QPair(Speaker::Strauss, "Don't make me laugh"));
       recenice.append(QPair(Speaker::Game, "endsection"));
       //pred kraj
       recenice.append(QPair(Speaker::Strauss, "Wow i guess that last alien was pretty important."));
       recenice.append(QPair(Speaker::Strauss, "When you killed him, some of the Alphas' rocket pods just dropped and squished some aliens"));
       recenice.append(QPair(Speaker::Strauss, "It was hilalrious! Keep up the good work"));
       recenice.append(QPair(Speaker::Game, "endsection"));
    }
    //wild west
    else if(game->levelID == 4)
    {
        recenice.append(QPair(Speaker::Strauss, "Oh nice, I didn't know we were sending you to the wild wild west untill right now!"));
        recenice.append(QPair(Speaker::Strauss, "You're a rootin' tootin' alien shootin' Time Cowboy now, boy!"));
        recenice.append(QPair(Speaker::Strauss, "Yeah, okay, I know the old west was not actually all gunslingers and saloon fights, but we all still like the myths."));
        recenice.append(QPair(Speaker::Player, "Yeehaw!"));
        recenice.append(QPair(Speaker::Strauss, "Oh yeah, I probabaly should have said this when you were in the 10th century, but maybe don't show your Time Gun to the locals, they might get confused."));
        recenice.append(QPair(Speaker::Game, "endsection"));
        //...
        //pred kraj
        recenice.append(QPair(Speaker::Strauss, "Intern, quick! Come back to the future!"));
        recenice.append(QPair(Speaker::Strauss, "No, wait. Come back to the present?"));
        recenice.append(QPair(Speaker::Strauss, "Oh never mind! Come back quick! You have to see something!"));
        recenice.append(QPair(Speaker::Game, "endsection"));
    }
    //final lvl
    else if(game->levelID == 5)
    {
        recenice.append(QPair(Speaker::Strauss, "Good, you're here! "));
        recenice.append(QPair(Speaker::Strauss, "I don't know what you did back there, but You crippled the Alpha so much, he's trying to make a run for it!"));
        recenice.append(QPair(Speaker::Strauss, "Look, He's going to our rocket launch rig. He's trying to climb it and launch himself into space and escape!"));
        recenice.append(QPair(Speaker::Strauss, "You have to stop him!"));
        recenice.append(QPair(Speaker::Player, "On it doctor!"));
        recenice.append(QPair(Speaker::Game, "endsection"));
        //na kraju
        recenice.append(QPair(Speaker::Player, "Is that it? Did I do it?"));
        recenice.append(QPair(Speaker::Strauss, "Wow I think you did. I guess the planet is safe."));
        recenice.append(QPair(Speaker::Strauss, "At least untill some other aliens get the same idea."));
        recenice.append(QPair(Speaker::Player, "Lets just hope we didn't miss any"));
        recenice.append(QPair(Speaker::Game, "endsection"));

        //TODO:
        //mozda ovde emit signal za roll credits
    }
    else
    {
        qDebug() << "Los level Id za DialogueHandler::initializeDialogue";
    }
}

void DialogueHandler::advanceDialogue()
{
    //qDebug() << current_index << recenice.size();
    if(box != nullptr)
    {
        game->scene()->removeItem(box);
    }

    if(QString::compare(recenice[current_index].second, "endsection") == 0)
    {
        setDialogueActive(false);
    }
    else if(current_index < recenice.size())
    {
            box = new DialogueBox(recenice[current_index]);
            game->scene()->addItem(box);
    }

    if(current_index < recenice.size() - 1)
    {
        current_index++;
    }
}

void DialogueHandler::setDialogueActive(bool isActive)
{
    isDialogueActive = isActive;
}


