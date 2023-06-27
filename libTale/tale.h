
// ===========================================================================
/// <summary>
/// tale.h
/// Entity - libTale
/// created by Mehrdad Soleimanimajd on 21.10.2019
/// </summary>
/// <created>ʆϒʅ, 21.10.2019</created>
/// <changed>ʆϒʅ, 27.06.2023</changed>
// ===========================================================================

#ifndef TALE_H
#define TALE_H


#include <exception>
#include <qquickitem.h>
#include <qstring.h>


// game's story wrapper
class Tale : public QObject
{
    Q_OBJECT
private:
    QString title; // game story title

    QString idleSentences [4]; // idle state sentences
    unsigned short idleSentenceIndex; // current idle state sentence

    QVariantList taleSentences; // the story sentences

    QString movementSentences [10]; // movement sentences

    QString collisionSentences [8][2]; // collision sentences

    bool initialized; // true in case of successful initialization

    int random ( int ); // provides a random integer
public:
    Tale ( void ); // game's story constructor
    //~Tale ( void );
    Q_INVOKABLE bool const isInitialized ( void ); // get initialization state
    Q_INVOKABLE QString const getTitle ( void ); // get story's title from first hand handler! :)
    Q_INVOKABLE QString const getNextIdleSentence ( void ); // purposeful even in idle state! :)
    Q_INVOKABLE QVariantList getTaleSentences ( void ); // story teller
    Q_INVOKABLE QString const getMovementSentence ( void ); // movement comedian
    Q_INVOKABLE QString const getCollisionSentence ( int ); // collision comedian
};


#endif // !TALE_H
