// *******************************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,21.10.2019</created>
/// <changed>ʆϒʅ,24.10.2019</changed>
// *******************************************************************************************

#ifndef TALE_H
#define TALE_H


#include <exception>
#include <qquickitem.h>
#include <qstring.h>

#include "..\libLogic\logic.h"


// game's story wrapper
class Tale : public QObject
{
  Q_OBJECT
private:
  GameLogic* logic;

  QString title; // game story title

  QString idleSentences [4]; // idle state sentences
  unsigned short idleSentenceIndex; // current idle state sentence

  QString taleSentences [12]; // the story sentences
  unsigned short taleSentenceIndex; // current story sentence

  QString movementSentences [10]; // movement sentences
  unsigned short movementSentenceIndex; // current movement sentence

  QString collisionSentences [8][2]; // collision sentences

  bool initialized; // true in case of successful initialization
public:
  Tale ( GameLogic* ); // game's story constructor
  //~Tale ( void );
  Q_INVOKABLE bool const isInitialized ( void ); // get initialization state
  Q_INVOKABLE QString const getTitle ( void ); // get story's title from first hand handler! :)
  Q_INVOKABLE QString const getNextIdleSentence ( void ); // purposeful even in idle state! :)
  Q_INVOKABLE QString const getNextTaleSentence ( void ); // story teller
  Q_INVOKABLE QString const getMovementSentence ( void ); // movement comedian
  Q_INVOKABLE QString const getCollisionSentence ( void ); // collision comedian
};


#endif // !TALE_H
