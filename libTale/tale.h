// *******************************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,21.10.2019</created>
/// <changed>ʆϒʅ,21.10.2019</changed>
// *******************************************************************************************

#ifndef TALE_H
#define TALE_H


#include <string>
#include <exception>


// game's story wrapper
class Tale
{
private:
  std::string title;

  bool initialized;
public:
  Tale ( void ); // game's story constructor
  //~Tale ( void );
};


#endif // !TALE_H
