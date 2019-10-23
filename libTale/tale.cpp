// *******************************************************************************************
/// <summary>
///
/// </summary>
/// <created>ʆϒʅ,21.10.2019</created>
/// <changed>ʆϒʅ,23.10.2019</changed>
// *******************************************************************************************

#include "tale.h"


Tale::Tale ( GameLogic* logicObj )
  : logic ( logicObj ), initialized ( false )
{

  title = "A funny Business";

  idleSentences [0] = "Ask and you shall receive...\n";
  idleSentences [1] = "Expect and you shall persuade...\n";
  idleSentences [2] = "Deceive and you shall answer...\n";
  idleSentences [3] = "Force and you shall be doomed...\n";

  initialized = true;

};


//Tale::~Tale ( void )
//{
//
//};
