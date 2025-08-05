#include "Player.h"
#include "Food.h"
#include "MacUILib.h"
#include <iostream>


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef; 
    mainFoodRef = thisFoodRef;
    myDir = STOP;

    playerPosList = new objPosArrayList();


    objPos playerpos = objPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*');
    playerPosList-> insertHead(playerpos) ;
    // more actions to be included
// 
}


Player::~Player()
{
    // delete any heap members here
    delete [] playerPosList;
    // no keyword "new" in constructor therefore no destructor for now
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList;
    // return the reference to the playerPos arrray list
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
    switch(input)
        {                      
            case 'w':
                if(myDir != DOWN)
                {
                    myDir = UP;
                    break;
                }else
                    break;
    
            case 's':
                if(myDir != UP)
                {
                    myDir = DOWN;
                    break;  
                }else
                    break;
                
            case 'a':
                if(myDir != RIGHT)
                {
                    myDir = LEFT;
                    break;  
                }else
                    break;

            case 'd':
                if(myDir!= LEFT)
                {
                    myDir = RIGHT;
                    break;   
                }else
                    break;
        

        }
        // PPA3 input processing logic 
}

void Player::movePlayer()
{
    objPos currentHead = objPos(playerPosList->getHeadElement());
    objPosArrayList* foodBuckPos = mainFoodRef->getFoodBucket();

    int currentHeadX= currentHead.pos->x;
    int currentHeadY= currentHead.pos->y;

    if(myDir == UP)
    {
        currentHeadY--; 
    }
    else if(myDir == DOWN)
    {
        currentHeadY++;
    }
    else if(myDir == LEFT)
    {
        currentHeadX--;
    }
    else if(myDir == RIGHT)
    {
        currentHeadX++;  
    }

    int boardWrapX = mainGameMechsRef->getBoardSizeX() - 1;
    int boardWrapY = mainGameMechsRef->getBoardSizeY() - 1;

    if( currentHeadX <= 0)
    {
        currentHeadX  += boardWrapX - 1;
    }
    else if (currentHead.pos->x >= boardWrapX)
    {
        currentHeadX -= boardWrapX - 1;
    }

    if(currentHeadY  <= 0)
    {
        currentHeadY  += boardWrapY - 1;
    }
    else if (currentHeadY >= boardWrapY)
    {
        currentHeadY -= boardWrapY - 1;
    }  
    // PPA3 Finite State Machine logic


    //New head position
    objPos newHead(currentHeadX,currentHeadY,'s');
    objPos snakeEnd;

    for(int i = 1; i < playerPosList->getSize(); i++)
    {
        snakeEnd = playerPosList->getElement(i);
        if(newHead.pos->x == snakeEnd.pos->x && newHead.pos->y == snakeEnd.pos->y)
        {
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();
            return;
        }
    }

    playerPosList->insertHead(newHead);
    bool foodConsumed = false;

    for(int i = 0; i < foodBuckPos->getSize(); i++ )  //loop through each food item in food bucket.
    {
        //Check if each item is at the same position as the new inserted Head
        if(foodBuckPos->getElement(i).isPosEqual(&newHead))
        {
            if(foodBuckPos->getElement(i).getSymbol() == '-')
            {
                if(playerPosList->getSize() > 1){
                        playerPosList->removeHead();
                        playerPosList->removeTail();
                }
            }

            //Regenerate the Food Bucket in 5 new random spots on the board after collision.
            mainFoodRef->generateFood(mainGameMechsRef, playerPosList);
            mainGameMechsRef->incrementScore();
            foodConsumed = true;
            break;
        }
    
    }

    if(!foodConsumed)
    {
        if (playerPosList->getSize() > 1) {
            playerPosList->removeTail();
        }
    }

    
}

// More methods to be added

int Player::getScore() const
{
    return mainGameMechsRef->getScore();
}