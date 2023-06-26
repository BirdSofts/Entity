
// *******************************************************************************************
/// <summary>
/// gTestFeatures.cpp
/// Entity - gtest
/// created by Mehrdad Solimanimajd on 04.10.2019
/// </summary>
/// <created>ʆϒʅ, 04.10.2019</created>
/// <changed>ʆϒʅ, 25.06.2023</changed>
// *******************************************************************************************

#include <gtest/gtest.h>
#include <qguiapplication.h>
#include <qdir.h>
#include <qquickview.h>
#include <qqmlfileselector.h>
#include <qqmlcontext.h>

#include "../libLogic/logic.h"
#include "../libSettings/settings.h"
#include "../libTale/tale.h"


TEST ( Entity, Application_RunInWhole )
{

    QCoreApplication::setAttribute ( Qt::AA_EnableHighDpiScaling );

    int argc { 0 };
    char** argv { 0 };

    QGuiApplication app ( argc, argv );

    app.setOrganizationName ( "BirdSofts" );
    app.setOrganizationDomain ( "https://github.com/s-mehrdad/" );
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

    Tale tale;
    view.rootContext ()->setContextProperty ( "tale", &tale );

    GameLogic logic ( &view, &configs, &tale );
    view.rootContext ()->setContextProperty ( "logic", &logic );

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
    Configuration configs ( nullptr );
    EXPECT_TRUE ( configs.getLoaded () );
    EXPECT_EQ ( configs.getWidth (), 600 );
}

TEST ( Entity, libLogic_Instantiation )
{
    GameLogic logic ( nullptr, nullptr, nullptr );
    EXPECT_TRUE ( logic.isInitialized () );
}

TEST ( Entity, libSettingsAndlibLogic_Instantiation )
{
    Configuration configs ( nullptr );
    GameLogic logic ( nullptr, &configs, nullptr );
    EXPECT_TRUE ( configs.getLoaded () );
    EXPECT_TRUE ( logic.isInitialized () );
}

TEST ( Entity, libTale_Instantiation )
{
    Tale tale;
    EXPECT_TRUE ( tale.isInitialized () );
}

TEST ( Entity, Test_SuccessCase )
{
    EXPECT_EQ ( 1, 1 );
    EXPECT_TRUE ( !false );
}
