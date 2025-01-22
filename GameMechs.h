#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        bool earlyEnd;
        int score;

        int boardSizeX;
        int boardSizeY; 

    public:
        //Default constructor
        GameMechs();
        //Additional Constructor
        GameMechs(int boardX, int boardY);
        //Unneeded destructor
        ~GameMechs();
        
        bool getExitFlagStatus() const; 
        void setExitTrue();
        bool getLoseFlagStatus() const;
        void setLoseFlag();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX() const;
        int getBoardSizeY() const;
        
        int getScore() const;
        void incrementScore();
        
        //Additional methods:
        void collectAsyncInput();
        void setEarlyEnd();
        bool getEarlyEndStatus();
        
};

#endif