// *******************************************************************************************
/// <summary>
///
/// </summary>
/// <created>ʆϒʅ,04.10.2019</created>
/// <changed>ʆϒʅ,20.10.2019</changed>
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
  : configs ( configsObj ), view ( viewObj ), state ( false )
{
  screenWidth = configs->getWidth ();
  screenHeight = configs->getHeight ();

  health = 20;
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

    items [index] = qobject_cast<QQuickItem*> (component->create ());

    if (items [index])
    {
      QQmlEngine::setObjectOwnership ( items [index], QQmlEngine::CppOwnership );
      items [index]->setParent ( view->rootObject () );
      items [index]->setVisible ( true );

      QObject* temp = view->findChild<QObject*> ( "gameCanvas" );
      if (temp)
      {
        items [index]->setParentItem ( qobject_cast<QQuickItem*> (temp) );

        items [index]->setProperty ( "type", qFloor ( qRand.generateDouble () * 3 ) + 1 ); // Note: for the time being
        //int type = qFloor ( dis ( gen ) * 3 ) + 1;
        //switch (type)
        //{
        //  case 1:
        //    items [index]->setProperty ( "colour", "red" ); // Note: for the time being
        //    break;
        //  case 2:
        //    items [index]->setProperty ( "colour", "green" );
        //    break;
        //  case 3:
        //    items [index]->setProperty ( "colour", "blue" );
        //    break;
        //}

        items [index]->setProperty ( "objData", (qFloor ( dis ( gen ) * 2 ) + 1) * 100 );

        // randomized creation location (probably somehow out of blue! :))
        int sphere { qFloor ( dis ( gen ) * 200 ) };
        int tempData;
        if (sphere <= 50)
        {
          items [index]->setProperty ( "x", -20 );
          items [index]->setProperty ( "y", dis ( gen ) * screenHeight );
          tempData = items [index]->property ( "objData" ).toInt ();
          items [index]->setProperty ( "objData", tempData + 11 ); // Note: for the time being
        } else
          if (sphere > 50 && sphere <= 100)
          {
            items [index]->setProperty ( "x", dis ( gen ) * screenWidth );
            items [index]->setProperty ( "y", -20 );
            tempData = items [index]->property ( "objData" ).toInt ();
            items [index]->setProperty ( "objData", tempData + 11 ); // Note: for the time being
          } else
            if (sphere > 100 && sphere <= 150)
            {
              items [index]->setProperty ( "x", screenWidth + 20 );
              items [index]->setProperty ( "y", dis ( gen ) * screenHeight );
              tempData = items [index]->property ( "objData" ).toInt ();
              items [index]->setProperty ( "objData", tempData + 22 ); // Note: for the time being
            } else
              if (sphere > 150 && sphere <= 200)
              {
                items [index]->setProperty ( "x", dis ( gen ) * screenWidth );
                items [index]->setProperty ( "y", screenHeight + 20 );
                tempData = items [index]->property ( "objData" ).toInt ();
                items [index]->setProperty ( "objData", tempData + 22 ); // Note: for the time being
              }

            tempData = temp->property ( "itemSize" ).toInt ();
            items [index]->setProperty ( "width", tempData );
            items [index]->setProperty ( "height", tempData );
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


Q_INVOKABLE bool const GameLogic::getState ( void )
{
  return state;
};


Q_INVOKABLE void GameLogic::newGame ( void )
{

  //QObject* canvas = view->findChild<QObject*> ( "gameCanvas" );
  //canvas->setProperty ( "health", health );

  items = new (std::nothrow) QQuickItem * [20];

  component = new QQmlComponent ( view->engine (), QUrl ( "qrc:/qml/Fragment.qml" ) );
  if (component->isReady ())
  {
    for (unsigned short i = 0; i < health; i++)
    {
      items [i] = nullptr;
      createItem ( i );
      state = true;
    }
  } else
  {
    state = false;
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

  for (unsigned short i = 0; i < health; i++)
  {
    if (state && items [i])
    {
      // movement direction based on the randomized location (for the time being)
      int tempData = items [i]->property ( "objData" ).toInt ();
      int tempX = items [i]->property ( "x" ).toInt ();
      int tempY = items [i]->property ( "y" ).toInt ();
      if ((tempData / 100) == 2)
      {
        if ((tempData % 100) == 11)
        {
          items [i]->setProperty ( "x", tempX + 5 );
          items [i]->setProperty ( "y", tempY + 5 );
        } else
        {
          items [i]->setProperty ( "x", tempX - 5 );
          items [i]->setProperty ( "y", tempY - 5 );
        }
      } else
      {
        if ((tempData % 100) == 11)
        {
          items [i]->setProperty ( "x", tempX + 3 );
          items [i]->setProperty ( "y", tempY + 3 );
        } else
        {
          items [i]->setProperty ( "x", tempX - 3 );
          items [i]->setProperty ( "y", tempY - 3 );
        }
      }
    }
  }

};


Q_INVOKABLE void GameLogic::conflict ( void )
{
  // Todo: show some action
}


Q_INVOKABLE void GameLogic::endGame ( void )
{
  state = false;

  //delete [] * items;
  //items = nullptr;

  for (unsigned short i = 0; i < health; i++)
  {
    if (items [i])
    {
      delete items [i];
      items [i] = nullptr;
    }
  }
}
