#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

//Player, mechanics, and food classes pointers
Player *myPlayer;
GameMechs *myGM;
Food *foodItem;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


int main(void)
{
    Initialize();
    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }
    CleanUp();
}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    //Allocating pointers on the heap
    myGM = new GameMechs();
    foodItem = new Food();
    myPlayer = new Player(myGM,foodItem);
    
    //Initalizing first set of food items
    foodItem->generateFood(myGM, myPlayer->getPlayerPos());
}

void GetInput(void)
{
    //Asynchronous input, non-blocking
    myGM->collectAsyncInput();
    if(myGM->getInput() == 27) //ESC Key
    {
        myGM->setEarlyEnd();
        myGM->setExitTrue();
    }
}

void RunLogic(void)
{   
    //Uses input to decide direction to move in
    myPlayer->updatePlayerDir();

    //Moves snake and detects collisions
    myPlayer->movePlayer();
    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    //////////////////////////////HEADER/////////////////////////////////
    MacUILib_printf("           Welcome to the 2SH4 Snake Game!\n");
    MacUILib_printf("WASD to move, ESC to exit the game, get all the food items!\n");
    MacUILib_printf("Get the '-' to shorten your snake! Don't let it collide with itself\n");

    objPosArrayList* foodBucket = foodItem->getFoodBucket();;
    objPos snakebody;

    //Iterating through every row, every column
    for(int y = 0; y < myGM->getBoardSizeY(); y++){
        for(int x = 0; x < myGM->getBoardSizeX(); x++){

            //Printing borders!
            if( y == 0 || y == myGM->getBoardSizeY() - 1)
                MacUILib_printf("=");
            else if( x == 0 || x ==  myGM->getBoardSizeX() - 1)
                MacUILib_printf("|");

            else {
                int printingHere = 0; //flag to assess whether a space should be placed or not

                for(int i = 0; i <  myPlayer->getPlayerPos()->getSize(); i++){
                    snakebody.setObjPos(myPlayer->getPlayerPos()->getElement(i));

                    //Checking if current x and y positions match part of the snake's body
                    if(x == snakebody.pos->x && y == snakebody.pos->y){
                        MacUILib_printf("%c", snakebody.symbol);
                        printingHere = 1; //this location is part of the snake's body
                        break; //break since only one segment of the snake's body exists per one pair of x and y coordinates
                        }
                    }

                    //If this x and y pair are NOT on a location where the snake body sits:
                    if(printingHere == 0){
                        //Iterate through every food item
                        for(int i = 0; i < foodBucket->getSize(); i++){
                            if (x == foodBucket->getElement(i).pos->x && y == foodBucket->getElement(i).pos->y) {
                                //Print food items from the bucket if any of their locations match
                                MacUILib_printf("%c", foodBucket->getElement(i).symbol);
                                printingHere = 1;
                            }
                        }
                        
                        //All conditions passed and nothing was printed at current x and y pair: Add a space
                        if(!printingHere){
                             MacUILib_printf(" ");
                        }
                    }
                }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("SCORE: %d\n", myPlayer->getScore());
    MacUILib_printf("o = score +1\n+ = score +1 and length +3");

    if(myGM->getEarlyEndStatus() == true)
        MacUILib_printf("\nYOU ARE A QUITTER! Game Exited\n");

    if (myGM->getLoseFlagStatus()){
        MacUILib_printf("\nYou Lost! Your Score is: %d\n", myPlayer->getScore());         
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    //MacUILib_clearScreen();
    delete myPlayer;
    delete myGM;
    delete foodItem;

    MacUILib_uninit();
}
