// *******************************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,04.10.2019</created>
/// <changed>ʆϒʅ,16.10.2019</changed>
// *******************************************************************************************

#include <gtest/gtest.h>
#include "../libSettings/settings.h"


int main ( int argc, char* argv [] )
{

  testing::InitGoogleTest ( &argc, argv );
  int ret = RUN_ALL_TESTS ();
  return ret;

}
