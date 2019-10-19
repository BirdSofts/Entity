// *******************************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,04.10.2019</created>
/// <changed>ʆϒʅ,19.10.2019</changed>
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

  Configuration* configs;

  unsigned short screenWidth;
  unsigned short screenHeight;

  unsigned short health;
  QQuickItem* items;
  QQuickItem* object;

  bool state;
public:

  GameLogic ( Configuration*, QQuickView* );
  //~GameLogic ( void );
  Q_INVOKABLE bool const getState ( void ); // get game state
  Q_INVOKABLE void newGame (); // start a new game
  Q_INVOKABLE void endGame (); // end the game
};


#endif // !LOGIC_H
