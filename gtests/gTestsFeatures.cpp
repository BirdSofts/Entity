﻿// *******************************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,04.10.2019</created>
/// <changed>ʆϒʅ,06.10.2019</changed>
// *******************************************************************************************


#include <gtest/gtest.h>
#include <qguiapplication.h>
#include <qdir.h>
#include <qquickview.h>
#include <qqmlfileselector.h>
#include <qqmlcontext.h>

#include "../libLogic/logic.h"
#include "../libSettings/settings.h"


TEST ( Entity, Application_RunInWhole )
{

  QCoreApplication::setAttribute ( Qt::AA_EnableHighDpiScaling );

  int argc { 0 };
  char** argv { 0 };

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

  GameLogic logic;
  view.rootContext ()->setContextProperty ( "logic", &logic );

  Configuration configs;
  view.rootContext ()->setContextProperty ( "configs", &configs );

  view.setSource ( url );

  bool viewError { false };
  if (view.status () == QQuickView::Error)
    viewError = true;

  if (!viewError)
  {
    view.setResizeMode ( QQuickView::SizeRootObjectToView );

    view.show ();

    app.exec ();
  }

  EXPECT_FALSE ( viewError );

}

TEST ( Entity, libSettings_Instantiation )
{
  Configuration configs;
  EXPECT_TRUE ( configs.getLoaded () );
}

TEST ( Entity, Test_SuccessCase )
{
  EXPECT_EQ ( 1, 1 );
  EXPECT_TRUE ( !false );
}
