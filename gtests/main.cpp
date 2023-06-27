
// ===========================================================================
/// <summary>
/// main.cpp
/// Entity - gtest
/// created by Mehrdad Soleimanimajd on 04.10.2019
/// </summary>
/// <created>ʆϒʅ, 04.10.2019</created>
/// <changed>ʆϒʅ, 27.06.2023</changed>
// ===========================================================================

#include <gtest/gtest.h>
#include "../libSettings/settings.h"


int main ( int argc, char* argv [] )
{

    testing::InitGoogleTest ( &argc, argv );
    int ret = RUN_ALL_TESTS ();
    return ret;

}
