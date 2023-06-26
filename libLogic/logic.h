
// *******************************************************************************************
/// <summary>
/// logic.h
/// Entity - libLogic
/// created by Mehrdad Soleimanimajd on 04.10.2019
/// </summary>
/// <created>ʆϒʅ, 04.10.2019</created>
/// <changed>ʆϒʅ, 25.06.2023</changed>
// *******************************************************************************************

#ifndef LOGIC_H
#define LOGIC_H


#include <string>
#include <exception>
#include <fstream>
#include <sstream>
#include <qquickitem.h>
#include <qquickview.h>
#include <qstring.h>

#include "../libSettings/settings.h"
#include "../libTale/tale.h"

// todo: provided through a smart pointer

// entity's most needed properties container
struct Smily
{
    int x;
    int y;
};


// fragments state container
struct Fragment
{
    unsigned short id;
    int x;
    int y;
    int type;
    bool dirty;
    bool onBusiness;
};


// game's logic wrapper
class GameLogic : public QQuickItem
{
    Q_OBJECT
private:
    QQuickView* view; // pointer to QtQml application view (application engine)
    QObject* canvas; // pointer to game's canvas component
    QQmlComponent* component; // pointer to game's fragments component

    Configuration* configs; // pointer to application configuration
    unsigned short viewWidth; // screen width (prevents constant function calls)
    unsigned short viewHeight; // screen height (prevents constant function calls)

    Tale* tale; // pointer to game's story

    Smily player; // represents entity properties
    unsigned short moves; // player changed positions counter
    QQuickItem* playerObj; // pointer to entity object
    unsigned short health; // entity's health
    QQuickItem** fragments; // pointers to collision seekers (fragments)
    int itemSize; // fragments' width/height
    Fragment* states; // collision seekers state container
    unsigned short count; // fragment's count
    unsigned short collidedIndex; // index of last involved in a collision fragment
    QQuickItem* sentencesFieldOne; // pointer sentences (field one)
    QQuickItem* sentencesFieldTwo; // pointer sentences (field two)

    bool onDetection;
    bool gaming;
    //bool paused; // +smily animation

    bool initialized; // true in case of successful initialization

    void createItem ( unsigned short ); // fragments instantiation
    void collision ( void ); // collisions detector / responder
public:
    GameLogic ( QQuickView*, Configuration*, Tale* );
    //~GameLogic ( void );
    Q_INVOKABLE bool const isInitialized ( void ); // get initialization state
    Q_INVOKABLE bool const isGaming ( void ); // currently gaming
    Q_INVOKABLE void initializeGame ( QString ); // game's different states initializer
    Q_INVOKABLE void newGame ( void ); // new game starter
    Q_INVOKABLE void tick ( void ); // game's timer ticker / game universe updater
    Q_INVOKABLE void update ( QString, int, int ); // user input updater / updates initiator
    Q_INVOKABLE void endGame ( void ); // enough gaming :)
};


#endif // !LOGIC_H
