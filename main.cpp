// *******************************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,03.10.2019</created>
/// <changed>ʆϒʅ,29.04.2022</changed>
// *******************************************************************************************

#include <qguiapplication.h>
#include <qdir.h>
#include <qquickview.h>
#include <qqmlfileselector.h>
#include <qqmlcontext.h>

#include "./libLogic/logic.h"
#include "./libSettings/settings.h"
#include "./libTale/tale.h"

bool debugVariable { true };


int main ( int argc, char* argv [] )
{
  //  QCoreApplication::setAttribute ( Qt::AA_EnableHighDpiScaling );

  QGuiApplication app ( argc, argv );

  app.setOrganizationName ( "BirdSofts" );
  app.setOrganizationDomain ( "https://github.com/BirdSofts/" );
  app.setApplicationName ( QFileInfo ( app.applicationFilePath () ).baseName () );

  QQuickView view;

  if (qgetenv ( "QT_QUICK_CORE_PROFILE" ).toInt ())
  {
    QSurfaceFormat surfaceFormat = view.format ();
    surfaceFormat.setProfile ( QSurfaceFormat::CoreProfile );
    surfaceFormat.setVersion ( 4, 4 );
    view.setFormat ( surfaceFormat );
  }

  if (qgetenv ( "QT_QUICK_MULTISAMPLE" ).toInt ())
  {
    QSurfaceFormat surfaceFormat = view.format ();
    surfaceFormat.setSamples ( 4 );
    view.setFormat ( surfaceFormat );
  }

  const QUrl url ( QStringLiteral ( "qrc:/entity.qml" ) );

  view.connect ( view.engine (), &QQmlEngine::quit, &app, &QCoreApplication::quit );
  new QQmlFileSelector ( view.engine (), &view );

  Configuration configs ( &view );
  view.rootContext ()->setContextProperty ( "configs", &configs );

  configs.setGetDebug ( debugVariable );

  Tale tale;
  view.rootContext ()->setContextProperty ( "tale", &tale );

  GameLogic logic ( &view, &configs, &tale );
  view.rootContext ()->setContextProperty ( "logic", &logic );

  view.setSource ( url );

  if (view.status () == QQuickView::Error)
    return-1;

  view.setResizeMode ( QQuickView::SizeRootObjectToView );

  view.show ();

  return app.exec ();
}
