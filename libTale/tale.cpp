
// *******************************************************************************************
/// <summary>
/// tale.cpp
/// Entity - libTale
/// created by Mehrdad Solimanimajd on 21.10.2019
/// </summary>
/// <created>ʆϒʅ, 21.10.2019</created>
/// <changed>ʆϒʅ, 01.03.2023</changed>
// *******************************************************************************************

#include <ctime>
#include <random>
#include <qmath.h>

#include "tale.h"


Tale::Tale ()
  : initialized ( false )
{

  title = "A funny Business";

  idleSentences [0] = "Ask and you shall receive...";
  idleSentences [1] = "Expect and you shall persuade...";
  idleSentences [2] = "Deceive and you shall answer...";
  idleSentences [3] = "Force and you shall be doomed...";
  idleSentenceIndex = 0;

  taleSentences.insert ( 0, "The movement is that essence, to survive with," );
  taleSentences.insert ( 1, "while asking and hoping!" );
  taleSentences.insert ( 2, "In the day or at night, this fact may shine bright..." );
  taleSentences.insert ( 3, "In the stand still of time, alone you will drum..." );
  taleSentences.insert ( 4, "The last sentence of the last player was:" );
  taleSentences.insert ( 5, "\"Come on, I am just a different colour!\"" );
  taleSentences.insert ( 6, "How unconventional you can move?!" );
  taleSentences.insert ( 7, "How strange you might find this world?!" );
  taleSentences.insert ( 8, "How curious will be your received packages!" );
  taleSentences.insert ( 9, "Will you be able to solve and survive?!" );
  taleSentences.insert ( 10, "In a survival environment," );
  taleSentences.insert ( 11, "where expectations are secure-zipped (:|)," );
  taleSentences.insert ( 12, "the wish for guidance my be with you!" );
  taleSentences.insert ( 13, "The player before you got blessed by God and is still alive!" );
  taleSentences.insert ( 14, "To quote the famous Mr. Spock: \"Live long and prosper!\"" );

  movementSentences [0] = "I see what you are getting at...";
  movementSentences [1] = "Respect, respect!";
  movementSentences [2] = "Watch your nose!";
  movementSentences [3] = "How the stomach!";
  movementSentences [4] = "The next one is going to end ugly...";
  movementSentences [5] = "Considering logic, better moving not dancing! :) ";
  movementSentences [6] = "A supercomputer gave up calculating the last move!";
  movementSentences [7] = "Not bad, not bad.";
  movementSentences [8] = "I say start a petition, so they add jumps!";
  movementSentences [9] = "That move could make such a scene on the Mars!";

  collisionSentences [0][0] = "Oops, just the simplicity of collided package!"; // red: developer himself!!! :|
  collisionSentences [0][1] = "I just thought what a colour!";
  collisionSentences [1][0] = "Plain it was, trust your eyes!"; // white
  collisionSentences [1][1] = "It was a piece of cloud, wasn't?!";
  collisionSentences [2][0] = "Yep, brown even under the feet..."; // brown
  collisionSentences [2][1] = "What a combination of colours!";
  collisionSentences [3][0] = "Lets start some sorrowing!."; // black
  collisionSentences [3][1] = "I must just say elegant!";
  collisionSentences [4][0] = "I doubt any connection with forests!"; // green
  collisionSentences [4][1] = "Watch out, seems like an smelly package!";
  collisionSentences [5][0] = "This kind is still lost."; // purple
  collisionSentences [5][1] = "Elegant and classy was it, yay!";
  collisionSentences [6][0] = "Some colour from the creator himself!"; // blue
  collisionSentences [6][1] = "Beams of independence are all around!";
  collisionSentences [7][0] = "Yay, free felt that one!"; // yellow
  collisionSentences [7][1] = "Yelled sky is the limit...";

  initialized = true;

};


//Tale::~Tale ( void )
//{
//
//};


int  Tale::random ( int number )
{

  // random functionality seed provider
  long long currentTime { std::chrono::system_clock::now ().time_since_epoch ().count () };
  unsigned int seed { static_cast<unsigned int>(currentTime + number * 3) };

  // random floating-point values provider
  std::default_random_engine gen ( seed ); // generator
  std::uniform_real_distribution<double> dis ( 0.0, 1.0 ); // distribution

  return qFloor ( dis ( gen ) * number ) + 1;

};


bool const Tale::isInitialized ( void )
{
  return initialized;
};


QString const Tale::getTitle ( void )
{
  return title;
};


QString const Tale::getNextIdleSentence ( void )
{

  QString temp = idleSentences [idleSentenceIndex];
  idleSentenceIndex++;
  if (idleSentenceIndex == 4)
    idleSentenceIndex = 0;
  return temp;

};


QVariantList Tale::getTaleSentences ( void )
{
  return taleSentences;
};


QString const Tale::getMovementSentence ( void )
{
  QString temp { "" };
  temp = movementSentences [random ( 10 )];
  return temp;
};


QString const Tale::getCollisionSentence ( int index )
{
  QString temp { "" };

  // logically index minus one but I have experienced some funny business in my environment! :)
  temp = collisionSentences [index - 2][random ( 2 )];

  return temp;
};
