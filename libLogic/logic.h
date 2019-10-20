// *******************************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,04.10.2019</created>
/// <changed>ʆϒʅ,20.10.2019</changed>
// *******************************************************************************************


#ifndef LOGIC_H
#define LOGIC_H


#include <string>
#include <exception>
#include <fstream>
#include <sstream>
#include <qquickitem.h>
#include <qquickview.h>

// need to be provided through a smart pointer but for the time being:
#include "..\libSettings\settings.h"


class GameLogic : public QQuickItem
{
  Q_OBJECT
private:
  QQuickView* view;
  QQmlComponent* component;
  QQuickItem** items;
  unsigned short health;

  Configuration* configs;
  unsigned short screenWidth;
  unsigned short screenHeight;

  bool state;

  void createItem ( unsigned short ); // objects instantiation
public:

  GameLogic ( Configuration*, QQuickView* );
  //~GameLogic ( void );
  Q_INVOKABLE bool const getState ( void ); // get game state
  Q_INVOKABLE void newGame ( void ); // start a new game
  Q_INVOKABLE void tick ( void ); // tick the timer
  Q_INVOKABLE void conflict ( void ); // conflicts
  Q_INVOKABLE void endGame ( void ); // end the game
};


#endif // !LOGIC_H
