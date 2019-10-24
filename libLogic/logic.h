// *******************************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,04.10.2019</created>
/// <changed>ʆϒʅ,24.10.2019</changed>
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

// need to be provided through a smart pointer but for the time being:
#include "..\libSettings\settings.h"


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
  bool onBusiness;
};


// game's logic wrapper
class GameLogic : public QQuickItem
{
  Q_OBJECT
private:
  QQuickView* view; // pointer to QtQml application view (application engine)
  QQmlComponent* component; // pointer to QtQml fragments component

  Configuration* configs; // pointer to application configuration
  unsigned short viewWidth; // screen width (prevents constant function calls)
  unsigned short viewHeight; // screen height (prevents constant function calls)

  Smily player; // represents entity properties
  bool moved; // true if player changed position
  QQuickItem* playerObj; // represents entity object
  unsigned short health; // entity's health
  QQuickItem** fragments; // collision seekers container
  int itemSize; // fragments' width/height
  Fragment* states; // collision seekers state container
  unsigned short count; // fragment's count
  unsigned short collidedIndex; // index of last involved in a collision fragment

  bool gaming;
  //bool paused; // +smily animation

  void createItem ( unsigned short ); // fragments instantiation
  void collision ( void ); // collisions detector / responder

  bool initialized; // true in case of successful initialization
public:

  GameLogic ( QQuickView*, Configuration* );
  //~GameLogic ( void );
  bool& move ( void );
  Fragment* const getStates ( void );

  Q_INVOKABLE bool const isInitialized ( void ); // get initialization state
  Q_INVOKABLE bool const isGaming ( void ); // currently gaiming
  Q_INVOKABLE void newGame ( void ); // new game starter
  Q_INVOKABLE void tick ( void ); // game's timer ticker / game universe updater
  Q_INVOKABLE void update ( QString, int, int ); // user input updater / updates initiator
  Q_INVOKABLE void endGame ( void ); // enough gaming :)
};


#endif // !LOGIC_H
// todo set get paused   get pointer to player    get type of last collided one