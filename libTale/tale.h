// *******************************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,21.10.2019</created>
/// <changed>ʆϒʅ,23.10.2019</changed>
// *******************************************************************************************

#ifndef TALE_H
#define TALE_H


#include <string>
#include <exception>

#include "../libLogic/logic.h"


// game's story wrapper
class Tale
{
private:
  GameLogic* logic;

  std::string title;
  std::string idleSentences [4];

  bool initialized;
public:
  Tale ( GameLogic* ); // game's story constructor
  //~Tale ( void );
};


#endif // !TALE_H
