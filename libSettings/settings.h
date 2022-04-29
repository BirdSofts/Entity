// *******************************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,03.10.2019</created>
/// <changed>ʆϒʅ,29.04.2022</changed>
// *******************************************************************************************

#ifndef SETTINGS_H
#define SETTINGS_H


#include <string>
#include <exception>
#include <fstream>
#include <sstream>
#include <qquickitem.h>
#include <qquickview.h>
#include <qstring.h>


// configuration's sphere enumeration container
enum Sphere { enumFontSize = 0, enumFontName, enumColour };
// game's configuration container
struct Settings
{
  unsigned short width;
  unsigned short height;
  int fontSize;
  QString fontName;
  QString colour;
};


// game's configuration wrapper
class Configuration : public QObject
{
  Q_OBJECT
private:
  QQuickView* view; // pointer to QtQml application view (application engine)
  QObject* property; // pointer to QtQml application base component (view)

  std::string path; // path to application's settings XML file

  bool loaded; // true if loading was successful
  bool saved; // true if write procedure succeeded

  bool debug;

  bool load ( void ); // settings file loader
public:
  Settings current; // current/all settings container

  Configuration ( QQuickView* );
  //~Configuration ( void );
  Q_INVOKABLE void setDefaults ( void ); // defaults (if the settings file is corrupt)
  Q_INVOKABLE void setGetDebug ( bool ); // set debug
  Q_INVOKABLE bool setGetDebug ( void ); // get debug
  Q_INVOKABLE void set ( int, QString, QString ); // QmlApp's configurations saver
  Q_INVOKABLE bool const getLoaded ( void ); // get loaded status
  Q_INVOKABLE unsigned short const getWidth ( void ); // get screen width
  Q_INVOKABLE unsigned short const getHeight ( void ); // get screen height
  Q_INVOKABLE int const getFontSize ( void ); // get font size
  Q_INVOKABLE QString const getFontName ( void ); // get font name
  Q_INVOKABLE QString const getColour ( void ); // get colour
};


#endif // !SETTINGS_H
