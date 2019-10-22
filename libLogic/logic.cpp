// *******************************************************************************************
/// <summary>
///
/// </summary>
/// <created>ʆϒʅ,04.10.2019</created>
/// <changed>ʆϒʅ,22.10.2019</changed>
// *******************************************************************************************

#include <ctime>
#include <random>
#include <qqmlengine.h>
#include <qobject.h>
#include <qmath.h>
#include <qrandom.h>
//#include <qstring.h>

#include "../libLogic/logic.h"


GameLogic::GameLogic ( Configuration* configsObj, QQuickView* viewObj )
  : view ( viewObj ), component ( nullptr ), configs ( configsObj ),
  gaming ( false )
{

  viewWidth = configs->getWidth ();
  viewHeight = configs->getHeight () - 100;

  player.x = 0;
  player.y = 0;
  playerObj = nullptr;
  health = 3;

  fragments = nullptr;
  itemSize = 0;
  states = nullptr;
  count = 20;

};


//GameLogic::~GameLogic ( void )
//{
//
//};


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

      QObject* temp = view->findChild<QObject*> ( "gameCanvas" );
      if (temp)
      {
        fragments [index]->setParentItem ( qobject_cast<QQuickItem*> (temp) );

        fragments [index]->setProperty ( "type", qFloor ( qRand.generateDouble () * 8 ) + 1 ); // Note: for the time being

        fragments [index]->setProperty ( "objData", (qFloor ( dis ( gen ) * 2 ) + 1) * 100 );

        // randomized creation location (probably somehow out of blue! :))
        int sphere { qFloor ( dis ( gen ) * 200 ) };
        int tempData;
        if (sphere <= 50)
        {
          fragments [index]->setProperty ( "x", 1 );
          fragments [index]->setProperty ( "y", dis ( gen ) * viewHeight );
          tempData = fragments [index]->property ( "objData" ).toInt ();
          fragments [index]->setProperty ( "objData", tempData + 11 ); // Note: for the time being
        } else
          if (sphere > 50 && sphere <= 100)
          {
            fragments [index]->setProperty ( "x", dis ( gen ) * viewWidth );
            fragments [index]->setProperty ( "y", 1 );
            tempData = fragments [index]->property ( "objData" ).toInt ();
            fragments [index]->setProperty ( "objData", tempData + 11 ); // Note: for the time being
          } else
            if (sphere > 100 && sphere <= 150)
            {
              fragments [index]->setProperty ( "x", viewWidth - 1 );
              fragments [index]->setProperty ( "y", dis ( gen ) * viewHeight - 1 );
              tempData = fragments [index]->property ( "objData" ).toInt ();
              fragments [index]->setProperty ( "objData", tempData + 22 ); // Note: for the time being
            } else
              if (sphere > 150 && sphere <= 200)
              {
                fragments [index]->setProperty ( "x", dis ( gen ) * viewWidth - 1 );
                fragments [index]->setProperty ( "y", viewHeight - 1 );
                tempData = fragments [index]->property ( "objData" ).toInt ();
                fragments [index]->setProperty ( "objData", tempData + 22 ); // Note: for the time being
              }

            itemSize = temp->property ( "itemSize" ).toInt ();
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
        fragments [i]->setProperty ( "dirty", true );

    }
  }

}


Q_INVOKABLE bool const GameLogic::isGaming ( void )
{
  return gaming;
};


Q_INVOKABLE void GameLogic::newGame ( void )
{

  //QObject* canvas = view->findChild<QObject*> ( "gameCanvas" );
  //canvas->setProperty ( "health", health );

  fragments = new (std::nothrow) QQuickItem * [20];
  states = new (std::nothrow) Fragment [20];

  component = new QQmlComponent ( view->engine (), QUrl ( "qrc:/qml/Fragment.qml" ) );
  if (component->isReady () && states && fragments)
  {

    for (unsigned short i = 0; i < count; i++)
    {
      fragments [i] = nullptr;
      createItem ( i );
      states [i].id = i;
      states [i].onBusiness = true;
      states [i].delay = 3;
    }
    gaming = true;

  } else
  {
    gaming = false;
    // Todo: logger service invoker
  }

};


Q_INVOKABLE void GameLogic::tick ( void )
{

  // Todo: each tick:
  // 1. updates to game's timer
  // 2. updates to game's universe based on the user input

  // Todo: randomized movement based on current entity position
  // Todo: speed based on game level

  if (gaming)
  {

    for (unsigned short i = 0; i < count; i++)
    {
      if (fragments [i])
      {
        // movement direction based on the randomized location (for the time being)
        int tempData = fragments [i]->property ( "objData" ).toInt ();
        states [i].x = fragments [i]->property ( "x" ).toInt ();
        states [i].y = fragments [i]->property ( "y" ).toInt ();

        if ((states [i].x >= viewWidth)
             || (states [i].y >= viewHeight)
             || (states [i].x <= 0) || (states [i].y <= 0))
        {
          delete fragments [i];
          fragments [i] = nullptr;
          states [i].id = 0;
          states [i].x = 0;
          states [i].y = 0;
          states [i].onBusiness = false;
          states [i].delay = 0;
        } else
        {
          if ((tempData / 100) == 2)
          {
            if ((tempData % 100) == 11)
            {
              fragments [i]->setProperty ( "x", states [i].x + 5 );
              fragments [i]->setProperty ( "y", states [i].y + 5 );
              states [i].x += 5;
              states [i].y += 5;
            } else
            {
              fragments [i]->setProperty ( "x", states [i].x - 5 );
              fragments [i]->setProperty ( "y", states [i].y - 5 );
              states [i].x -= 5;
              states [i].y -= 5;
            }
          } else
          {
            if ((tempData % 100) == 11)
            {
              fragments [i]->setProperty ( "x", states [i].x + 3 );
              fragments [i]->setProperty ( "y", states [i].x + 3 );
              states [i].x += 3;
              states [i].y += 3;
            } else
            {
              fragments [i]->setProperty ( "x", states [i].x - 3 );
              fragments [i]->setProperty ( "y", states [i].y - 3 );
              states [i].x -= 3;
              states [i].y -= 3;
            }
          }
        }
        collision ();
      } else
      {
        createItem ( i );
        states [i].id = i;
        states [i].x = 0;
        states [i].y = 0;
        states [i].onBusiness = true;
        states [i].delay = 3;
      }


    }
  }

};


Q_INVOKABLE void GameLogic::update ( QString objName, int x, int y )
{

  // game's universe actions/input preparations

  player.x = x;
  player.y = y;

};


Q_INVOKABLE void GameLogic::endGame ( void )
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
