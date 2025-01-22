#include "Food.h"
#include "MacUILib.h"
#include "GameMechs.h"
#include <stdio.h>

Food::Food(){
    //Rand seeding only once
    srand(static_cast<unsigned int>(time(0)));
    foodBucket = new objPosArrayList(5);
}

Food::~Food(){
    delete foodBucket;
}

void Food::generateFood(GameMechs* gameMechsPtr, objPosArrayList* blockOff)
{
    //Clearing out previous food bucket to avoid overlap
    foodBucket->clearArray();
    int specialItems = 0;
    int xFood, yFood;
    char foodSymbol;

    //generating 2 special items: + that increase length of snake
    while(specialItems < 2){
        bool valid = false;
        while(!valid){
            //Assuming validity initially, set to false in case of overlap
            valid = true;
            //Initial random positions to check
            xFood = rand() % ((gameMechsPtr->getBoardSizeX()) - 2) + 1;
            yFood = rand() % ((gameMechsPtr->getBoardSizeY()) - 2) + 1;
            foodSymbol = '+';

            //Iterating through each element of the snake body, checking for rand-position overlap
            for(int i = 0; i < blockOff->getSize(); i++){
                objPos snakePos = blockOff->getElement(i);
                if(xFood == snakePos.pos -> x && yFood == snakePos.pos -> y){
                        valid = false;
                        //breaking since as soon as the food item overlaps with one part of snake, it needs new rand x and y values
                        //Memory conservation ^_^
                        break;
                    }        
                }
                //check if x-y coordinate pair already exists in food bucket
                for (int i = 0; i < foodBucket->getSize(); i++){
                    objPos itemToCheck = foodBucket->getElement(i);
                    if(itemToCheck.pos -> x == xFood && itemToCheck.pos -> y == yFood){
                        valid = false;
                        //Also breaking, need new positions
                        break;
                    }
                }       
            }
            //After confirming validity, assign x and y pair to symbol and insert at tail!
            objPos specialFoods(xFood, yFood, foodSymbol);
            foodBucket->insertTail(specialFoods);
            specialItems++;
    }

    //Generating 3 normal items: o that increases score
    int normalItems = 0;
    while(normalItems < 3){
        bool valid = false;
        while(!valid){
            valid = true;
            xFood = rand() % ((gameMechsPtr->getBoardSizeX()) - 2) + 1;
            yFood = rand() % ((gameMechsPtr->getBoardSizeY()) - 2) + 1;
            foodSymbol = 'o';

            for(int i = 2; i < blockOff->getSize(); i++){
                //Checking normal food items against each element of the snake's body
                objPos snakePos = blockOff->getElement(i);
                if(xFood == snakePos.pos -> x && yFood == snakePos.pos -> y){
                        valid = false;
                        //breaking since as soon as the food item overlaps with one part of snake, it needs new rand x and y values
                        break;
                }        
            }
            //check for duplicated x and y positions
            for (int i = 0; i < foodBucket->getSize(); i++){
                    objPos itemToCheck = foodBucket->getElement(i);
                    if(itemToCheck.pos -> x == xFood && itemToCheck.pos -> y == yFood){
                        valid = false;
                        break;
                    }
            }
        }
        //After confirming validity, assign symbol to x and y pair, then insert at tail!
        objPos normalFoods(xFood, yFood, foodSymbol);
        foodBucket->insertTail(normalFoods);
        normalItems++;
    }
}

//return last used food position
objPos const Food::getFoodPos(){
    if (foodBucket->getSize() > 0) {
        return foodBucket->getElement(foodBucket->getSize() - 1);
    }
}

//return foodbucket
objPosArrayList* Food::getFoodBucket() {
    return foodBucket;
}