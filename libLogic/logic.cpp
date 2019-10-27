// *******************************************************************************************
/// <summary>
///
/// </summary>
/// <created>ʆϒʅ,04.10.2019</created>
/// <changed>ʆϒʅ,27.10.2019</changed>
// *******************************************************************************************

#include <ctime>
#include <random>
#include <qqmlengine.h>
#include <qobject.h>
#include <qmath.h>
#include <qrandom.h>
//#include <qstring.h>

#include "../libLogic/logic.h"


GameLogic::GameLogic ( QQuickView* viewObj, Configuration* configsObj )
  : view ( viewObj ), canvas ( nullptr ), component ( nullptr ), configs ( configsObj ),
  gaming ( false ), initialized ( false )
{
  //RockAndRoll
  if (configs)
  {
    viewWidth = configs->getWidth ();
    viewHeight = configs->getHeight () - 100;
  }

  player.x = 0;
  player.y = 0;
  moved = false;
  playerObj = nullptr;
  health = 3;

  fragments = nullptr;
  itemSize = 0;
  states = nullptr;
  count = 20;

  initialized = true;

};


//GameLogic::~GameLogic ( void )
//{
//
//};


bool& GameLogic::move ()
{
  return moved;
};


Fragment* const GameLogic::getStates ( void )
{
  return &states [collidedIndex];
};


bool const GameLogic::isInitialized ( void )
{
  return initialized;
};


void GameLogic::createItem ( unsigned short index )
{
  try
  {

    // random functionality seed provider
    long long currentTime { std::chrono::system_clock::now ().time_since_epoch ().count () };
    unsigned int seed { static_cast<unsigned int>(currentTime + index * 3) };

    // random floating-point values provider
    std::default_random_engine gen ( seed ); // generator
    std::uniform_real_distribution<double> dis ( 0.0, 1.0 ); // distribution

    // qt random facility
    QRandomGenerator qRand;
    qRand.seed ( static_cast<unsigned int>(currentTime) + index * 3 );

    fragments [index] = qobject_cast<QQuickItem*> (component->create ());

    if (fragments [index])
    {
      QQmlEngine::setObjectOwnership ( fragments [index], QQmlEngine::CppOwnership );
      fragments [index]->setParent ( view->rootObject () );
      fragments [index]->setVisible ( true );

      if (canvas)
      {

        fragments [index]->setParentItem ( qobject_cast<QQuickItem*> (canvas) );

        states [index].type = qFloor ( qRand.generateDouble () * 8 ) + 1;
        fragments [index]->setProperty ( "type", states [index].type );

        // randomized creation location (probably somehow out of blue! :))
        int sphere { qFloor ( dis ( gen ) * 200 ) };

        // Todo: different fragments kind can be added
        int objData { (qFloor ( dis ( gen ) * 2 ) + 1) * 100 };

        if (sphere <= 50)
        {
          fragments [index]->setProperty ( "objData", objData + 11 );

          states [index].x = 1;
          states [index].y = qFloor ( dis ( gen ) * viewHeight ) + 1;
        } else

          if (sphere > 50 && sphere <= 100)
          {
            fragments [index]->setProperty ( "objData", objData + 11 );

            states [index].x = qFloor ( dis ( gen ) * viewWidth ) + 1;
            states [index].y = 1;
          } else

            if (sphere > 100 && sphere <= 150)
            {
              fragments [index]->setProperty ( "objData", objData + 22 );

              states [index].x = viewWidth - 1;
              states [index].y = qFloor ( dis ( gen ) * viewHeight - 1 );
            } else

              if (sphere > 150 && sphere <= 200)
              {
                fragments [index]->setProperty ( "objData", objData + 22 );

                states [index].x = qFloor ( dis ( gen ) * viewWidth - 1 );
                states [index].y = viewHeight - 1;
              }

            fragments [index]->setProperty ( "x", states [index].x );
            fragments [index]->setProperty ( "y", states [index].y );

            itemSize = canvas->property ( "itemSize" ).toInt ();
            fragments [index]->setProperty ( "width", itemSize );
            fragments [index]->setProperty ( "height", itemSize );

      } else
      {
        // Todo: logger service invoker
      }

    } else
    {
      // Todo: logger service invoker
    }

  }
  catch (const std::exception & ex)
  {
  }
}


void GameLogic::collision ( void )
{

  //xx Todo: show some action

  for (unsigned short i = 0; i < count; i++)
  {
    if (fragments [i])
    {

      if ((states [i].x + itemSize - 5 >= player.x + 25)
           && (states [i].x + itemSize - 5 <= player.x + 75)
           && (states [i].y + itemSize - 5 >= player.y + 25)
           && (states [i].y + itemSize - 5 <= player.y + 75))
      {
        fragments [i]->setProperty ( "dirty", true );
        collidedIndex = i;
      }
    }
  }

}


bool const GameLogic::isGaming ( void )
{
  return gaming;
};


void GameLogic::initializeGame ( QString gameState )
{
  //canvas->property("")
};


void GameLogic::newGame ( void )
{

  canvas = view->findChild<QObject*> ( "gameCanvas" );
  canvas->setProperty ( "health", health );

  fragments = new (std::nothrow) QQuickItem * [count];
  states = new (std::nothrow) Fragment [count];

  component = new QQmlComponent ( view->engine (), QUrl ( "qrc:/qml/Fragment.qml" ) );
  if (component->isReady () && states && fragments)
  {

    for (unsigned short i = 0; i < count; i++)
    {
      fragments [i] = nullptr;
      createItem ( i );
      states [i].id = i;
      states [i].onBusiness = true;
    }
    gaming = true;

  } else
  {
    gaming = false;
    // Todo: logger service can be added
  }

};


void GameLogic::tick ( void )
{

  // Todo: updates to game's universe based on the user input can be added
  // Todo: randomized movement based on current entity position can be added
  // Todo: speed based on game level can be added

  if (gaming)
  {

    for (unsigned short i = 0; i < count; i++)
    {
      if (states [i].onBusiness)
      {

        // movement direction based on the randomized location (for the time being)
        int tempData = fragments [i]->property ( "objData" ).toInt ();

        if ((tempData / 100) == 1)
        {

          if ((tempData % 100) == 11)
          {
            states [i].x += 5;
            states [i].y += 5;
            if ((states [i].x >= viewWidth) || (states [i].y >= viewHeight))
              states [i].onBusiness = false;
          } else
          {
            states [i].x -= 5;
            states [i].y -= 5;
            if ((states [i].x <= 0) || (states [i].y <= 0))
              states [i].onBusiness = false;
          }

        } else
        {

          if ((tempData % 100) == 11)
          {
            states [i].x += 3;
            states [i].y += 3;
            if ((states [i].x >= viewWidth) || (states [i].y >= viewHeight))
              states [i].onBusiness = false;
          } else
          {
            states [i].x -= 3;
            states [i].y -= 3;
            if ((states [i].x <= 0) || (states [i].y <= 0))
              states [i].onBusiness = false;
          }

        }
        if (states [i].onBusiness)
        {
          fragments [i]->setProperty ( "x", states [i].x );
          fragments [i]->setProperty ( "y", states [i].y );
        }
        collision ();

      } else
      {

        delete fragments [i];
        fragments [i] = nullptr;
        createItem ( i );
        states [i].onBusiness = true;

      }

    }
  }

};


void GameLogic::update ( QString objName, int x, int y )
{

  // game's universe actions/input preparations

  player.x = x;
  player.y = y;

  // Todo: different movement and pointing system can be added
  moved = true;

};


void GameLogic::endGame ( void )
{

  gaming = false;

  delete [] states;
  states = nullptr;

  //delete [] * fragments;
  //fragments = nullptr;

  for (unsigned short i = 0; i < count; i++)
  {
    if (fragments [i])
    {
      delete fragments [i];
      fragments [i] = nullptr;
    }
  }

}
