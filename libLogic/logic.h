// *******************************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,04.10.2019</created>
/// <changed>ʆϒʅ,05.10.2019</changed>
// *******************************************************************************************


#ifndef LOGIC_H
#define LOGIC_H


#include <string>
#include <exception>
#include <fstream>
#include <sstream>
#include <qobject.h>
#include <qstring.h>


class GameLogic : public QObject
{
  Q_OBJECT
private:
  bool state;
public:

  GameLogic ();
  //~GameLogic ( void );
  Q_INVOKABLE void newGame ( void ); // start a new game
  Q_INVOKABLE bool const getState ( void ); // get game state
};


#endif // !LOGIC_H
