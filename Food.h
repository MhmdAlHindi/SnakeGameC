#ifndef FOOD_H
#define FOOD_H
#include <cstdlib>
#include <time.h>
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"
#include "MacUILib.h"

using namespace std;

class Food{
    private:
        objPos foodPos;
        objPosArrayList *foodBucket;
    
    public:
        //Constructor
        Food();
        //Destructor
        ~Food();
        //Getter Functions for single food item and food bucket, respectively
        objPos const getFoodPos();
        objPosArrayList* getFoodBucket();
        //Additional: Generating 5 food items method
        void generateFood(GameMechs* gameMechsPtr, objPosArrayList* blockOff);
};

#endif

