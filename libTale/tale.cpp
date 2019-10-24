// *******************************************************************************************
/// <summary>
///
/// </summary>
/// <created>ʆϒʅ,21.10.2019</created>
/// <changed>ʆϒʅ,24.10.2019</changed>
// *******************************************************************************************

#include <ctime>
#include <random>
#include <qmath.h>

#include "tale.h"


Tale::Tale ( GameLogic* logicObj )
  : logic ( logicObj ), initialized ( false )
{

  title = "A funny Business\n";

  idleSentences [0] = "Ask and you shall receive...\n";
  idleSentences [1] = "Expect and you shall persuade...\n";
  idleSentences [2] = "Deceive and you shall answer...\n";
  idleSentences [3] = "Force and you shall be doomed...\n";
  idleSentenceIndex = 0;

  taleSentences [0] = "The movement is that essence, to survive with, while asking and hoping!";
  taleSentences [1] = "In the day or at night, this fact may shine bright...\n";
  taleSentences [2] = "In the stand still of time, alone you will drum...\n";
  taleSentences [3] = "The last sentence of the last player was...";
  taleSentences [4] = "Come on, I am just a different colour!\n";
  taleSentences [5] = "How unconventional you can move?!\n";
  taleSentences [6] = "How strange you might find this world?!\n";
  taleSentences [7] = "How curious will be your received packages!\n";
  taleSentences [8] = "Will you be able to solve and survive?!\n";
  taleSentences [9] = "In a survival environment, where expectations are secure-zipped, the wish for guidance my be with you!";
  taleSentences [10] = "The first tester of the game got blessed by God and is still alive!\n";
  taleSentences [11] = "To quote the famous Mr. Spock: \"Live long an prosper.\"\n";
  taleSentenceIndex = 0;

  movementSentences [0] = "I see what you are getting at...";
  movementSentences [1] = "Respect, respect!";
  movementSentences [2] = "Watch you nose!";
  movementSentences [3] = "How the stomach!";
  movementSentences [4] = "That going to end ugly...";
  movementSentences [5] = "Moving not dancing!";
  movementSentences [6] = "A supercomputer gave up seeing the last move!";
  movementSentences [7] = "Not bad, not bad.";
  movementSentences [8] = "I say start a petition, so they add jumps.";
  movementSentences [9] = "That could make a different scene.";
  movementSentenceIndex = 0;

  collisionSentences [0][0] = "Oops, just simplicity of collided package!"; // red
  collisionSentences [0][1] = "I just thought what a colour!";
  collisionSentences [1][0] = "Plain it was, trust your eyes!"; // white
  collisionSentences [1][1] = "Wasn't that a piece of cloud?!";
  collisionSentences [2][0] = "Yep, brown even under the feet..."; // brown
  collisionSentences [2][1] = "What a combination of colours!";
  collisionSentences [3][0] = "Lets start some sorrowing!."; // black
  collisionSentences [3][1] = "I must just say elegant!";
  collisionSentences [4][0] = "I doubt any connection with forests!"; // green
  collisionSentences [4][1] = "Watch out, seems an smelly one!";
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


Q_INVOKABLE QString const Tale::getNextTaleSentence ( void )
{
  QString temp = taleSentences [taleSentenceIndex];
  taleSentenceIndex++;
  if (taleSentenceIndex == 12)
    taleSentenceIndex = 0;
  return temp;
};


Q_INVOKABLE QString const Tale::getMovementSentence ( void )
{
  if (logic->move ())
  {
    QString temp = movementSentences [movementSentenceIndex];
    movementSentenceIndex++;
    if (movementSentenceIndex == 11)
      movementSentenceIndex = 0;
    return temp;
    logic->move () = false;
  }
};


Q_INVOKABLE QString const Tale::getCollisionSentence ( void )
{

  // random functionality seed provider
  long long currentTime { std::chrono::system_clock::now ().time_since_epoch ().count () };
  unsigned int seed { static_cast<unsigned int>(currentTime + logic->getStates ()->id * 3) };

  // random floating-point values provider
  std::default_random_engine gen ( seed ); // generator
  std::uniform_real_distribution<double> dis ( 0.0, 1.0 ); // distribution

  int rnd { qFloor ( dis ( gen ) * 2 ) + 1 };

  return collisionSentences [logic->getStates ()->type][rnd];

};
