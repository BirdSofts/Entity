// *******************************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,03.10.2019</created>
/// <changed>ʆϒʅ,16.10.2019</changed>
// *******************************************************************************************

#ifndef SETTINGS_H
#define SETTINGS_H


#include <string>
#include <exception>
#include <fstream>
#include <sstream>
#include <qobject.h>
#include <qstring.h>


enum Sphare { enumFontSize = 0, enumFontName, enumFilePath, enumColour };
struct Settings
{
  unsigned short width;
  unsigned short height;
  int fontSize;
  QString fontName;
  QString filePath;
  QString colour;
};


class Configuration : public QObject
{
  Q_OBJECT
private:
  std::string path; // path to application XML settings file

  bool loaded; // true if loading was successful
  bool saved; // true if write procedure succeeded
  bool load ( void ); // settings file loader
public:
  Settings current; // current settings

  Configuration ();
  //~Configuration ( void );
  Q_INVOKABLE void setDefaults ( void ); // defaults (if the settings file is corrupt)
  Q_INVOKABLE void set ( int, QString, QString, QString ); // set QML properties to settings file
  Q_INVOKABLE bool const getLoaded ( void ); // get loaded status
  Q_INVOKABLE unsigned short const getWidth ( void ); // get screen width
  Q_INVOKABLE unsigned short const getHeight ( void ); // get screen height
  Q_INVOKABLE int const getFontSize ( void ); // get font size
  Q_INVOKABLE QString const getFontName ( void ); // get font name
  Q_INVOKABLE QString const getFilePath ( void ); // get file path
  Q_INVOKABLE QString const getColour ( void ); // get colour
};


#endif // !SETTINGS_H
