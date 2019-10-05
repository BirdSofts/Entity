// *******************************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,03.10.2019</created>
/// <changed>ʆϒʅ,06.10.2019</changed>
// *******************************************************************************************


#include "../libSettings/settings.h"


Configuration::Configuration () :
  loaded ( false ), saved ( false )
{

  current.width = 320;
  current.height = 480;
  current.fontSize = 0;
  current.fontName = "";
  current.filePath = "";
  current.colour = "";

  path = "./settings.xml";
  loaded = load ();

};


//Configuration::~Configuration ( void )
//{
//
//};


bool Configuration::load ( void )
{
  try
  {

    std::ifstream file ( path );
    if (file.is_open ())
    {
      std::string input { "" };
      std::string strSphere { "" };
      std::string strOut { "" };
      short sphere { 0 };
      std::stringstream stream;

      do
      {
        std::getline ( file, input );
      } while (input != "<settings>");

      if (input == "<settings>")
      {
        std::getline ( file, input );
        stream << input << std::endl;

        do
        {

          stream >> strSphere;

          if (strSphere == "<font_size>")
            sphere = enumFontSize;
          else
            if (strSphere == "<font_name>")
              sphere = enumFontName;
            else
              if (strSphere == "<file_path>")
                sphere = enumFilePath;
              else
                if (strSphere == "<colour>")
                  sphere = enumColour;
                else
                {
                  stream.str ( "" );
                  stream.clear ();
                  sphere = -1;
                  std::getline ( file, input );
                  stream << input << std::endl;
                }

          strSphere = "";

          switch (sphere)
          {
            case enumFontSize:
              stream >> current.fontSize;
              break;

            case enumFontName:
              stream >> strOut;
              current.fontName = strOut.c_str ();
              break;

            case enumFilePath:
              stream >> strOut;
              current.filePath = strOut.c_str ();
              break;

            case enumColour:
              stream >> strOut;
              current.colour = strOut.c_str ();
              break;
          }

        } while (input != "</settings>");
      } else
      {
        file.close ();
        setDefaults ();
        return false;
      }

      file.close ();
      return true;
    } else
    {
      setDefaults ();
      return false;
    }

  }
  catch (const std::exception & ex)
  {
    setDefaults ();
    return false;
  }
};


void Configuration::setDefaults ( void )
{
  current.fontSize = 12;
  current.fontName = "Arial";
  current.filePath = "desktop";
  current.colour = "blue";
};


void Configuration::set ( int fontSize, QString fontName, QString filePath, QString colour )
{

  try
  {

    current.fontSize = fontSize;
    current.fontName = fontName;
    current.filePath = filePath;
    current.colour = colour;

    std::ofstream writeStream ( path );
    if (writeStream.good ())
    {
      std::stringstream settingsLine;
      settingsLine << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n\n" <<
        "<settings>\n" <<
        "\t<font_size> " << current.fontSize << " </font_size>\n" <<
        "\t<font_name> " << current.fontName.toStdString () << " </font_name>\n" <<
        "\t<file_path> " << current.filePath.toStdString () << " </file_path>\n" <<
        "\t<colour> " << current.colour.toStdString () << " </colour>\n" <<
        "</settings>\n";
      writeStream << settingsLine.str ();
      writeStream.close ();

      saved = true;
    } else
      saved = false;

  }
  catch (const std::exception & ex)
  {
    saved = false;
  }

};


const bool Configuration::getLoaded ( void )
{
  return loaded;
};


unsigned short const Configuration::getWidth ( void )
{
  return current.width;
};


unsigned short const Configuration::getHeight ( void )
{
  return current.height;
};


int const Configuration::getFontSize ( void )
{
  return current.fontSize;
};


QString const Configuration::getFontName ( void )
{
  return current.fontName;
};


QString const Configuration::getFilePath ( void )
{
  return current.filePath;
};


QString const Configuration::getColour ( void )
{
  return current.colour;
};
