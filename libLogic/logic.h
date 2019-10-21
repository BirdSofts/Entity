// *******************************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,04.10.2019</created>
/// <changed>ʆϒʅ,21.10.2019</changed>
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
  bool onBusiness;
  unsigned short delay;
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
  QQuickItem* playerObj; // represents entity object
  unsigned short health; // entity's health
  QQuickItem** fragments; // collision seekers container
  Fragment* states; // collision seekers state container

  bool gaming;

  void createItem ( unsigned short ); // fragments instantiation
  void collision ( void ); // collisions detector / responder
public:

  GameLogic ( Configuration*, QQuickView* );
  //~GameLogic ( void );
  Q_INVOKABLE bool const isGaming ( void ); // currently gaiming
  Q_INVOKABLE void newGame ( void ); // new game starter
  Q_INVOKABLE void tick ( void ); // game's timer ticker / game universe updater
  Q_INVOKABLE void update ( QString, int, int ); // user input updater / updates initiator
  Q_INVOKABLE void endGame ( void ); // enough gaming :)
};


#endif // !LOGIC_H
