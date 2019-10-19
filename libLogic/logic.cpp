// *******************************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,04.10.2019</created>
/// <changed>ʆϒʅ,19.10.2019</changed>
// *******************************************************************************************

#include <ctime>
#include <qqmlengine.h>
#include <qobject.h>
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


Q_INVOKABLE bool const GameLogic::getState ( void )
{
  return state;
};


Q_INVOKABLE void GameLogic::newGame ()
{
  state = true;

  //items = new (std::nothrow) QObject [20];

  // random functionality seed provider
  std::time_t currentTime { std::chrono::system_clock::to_time_t ( std::chrono::system_clock::now () ) };
  std::time_t* currentTime_ptr { &currentTime };
  srand ( static_cast<unsigned int>(time ( currentTime_ptr ) * 1.123456789) );
  int rnd { 0 };

  QQmlComponent component ( view->engine (), QUrl ( "qrc:/qml/Fragment.qml" ) );
  if (component.isReady ())
  {
    object = qobject_cast<QQuickItem*> (component.create ());

    QQmlEngine::setObjectOwnership ( object, QQmlEngine::CppOwnership );
    object->setParent ( view->rootObject () );
    object->setVisible ( true );

    QObject* temp = view->findChild<QObject*> ( "gameCanvas" );
    if (temp)
    {
      object->setParentItem ( qobject_cast<QQuickItem*> (temp) );
    }
    if (object != nullptr)
    {
      rnd = (rand () % 3 + 1);
      object->setProperty ( "type", rnd );
      object->setProperty ( "x", 200 );
      object->setProperty ( "y", 200 );
      object->setProperty ( "width", 50 );
      object->setProperty ( "height", 50 );
    }
  }

};


Q_INVOKABLE void GameLogic::endGame ()
{
  state = true;
  if (object)
  {
    delete object;
    object = nullptr;
  }
}
