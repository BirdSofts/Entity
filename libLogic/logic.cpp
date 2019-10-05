// *******************************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,04.10.2019</created>
/// <changed>ʆϒʅ,05.10.2019</changed>
// *******************************************************************************************


#include "../libLogic/logic.h"


GameLogic::GameLogic ()
  :state ( false )
{

};


//GameLogic::~GameLogic ( void )
//{
//
//};


Q_INVOKABLE void GameLogic::newGame ( void )
{
  state = true;
};


Q_INVOKABLE bool const GameLogic::getState ( void )
{
  return state;
};
