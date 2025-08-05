#include "objPosArrayList.h"
#include <iostream>
#include "MacUILib.h"


using namespace std;

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[arrayCapacity];
    listSize = 0;
}

objPosArrayList::objPosArrayList(int bucketsize)
{
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[arrayCapacity];
    listSize = bucketsize;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize==arrayCapacity)
    {
        MacUILib_printf("Error: Array list full, no insertion allowed!\n");
        return;
    }

    for(int i = listSize; i>0; i--)
    {
        aList[i] = aList[i-1];
    }

    aList[0] = thisPos;
    listSize++;
        
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize==arrayCapacity)
    {
        MacUILib_printf("Error: Array list full, no insertion allowed!\n");
        return;
    }
    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{

    if(listSize == 0)
    {
         MacUILib_printf("Error: No elements in list to remove!\n");
        return;
    }

    for(int i = 0; i < listSize-1;i++)
    {
        aList[i] = aList[i+1];
    }
    listSize--;
    
}

void objPosArrayList::removeTail()
{
    if(listSize == 0)
    {
        MacUILib_printf("Error: List is empty, no elements to remove \n");
        return;
    }

    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    if(listSize > 0)
    {
        return aList[0];
    }
}

objPos objPosArrayList::getTailElement() const
{
    if(listSize > 0)
    {
        return aList[listSize-1];
    }
    
}

objPos objPosArrayList::getElement(int index) const
{
    if(index<0)
    {
        return aList[0];
    }
    else if(index >= listSize && listSize != 0)
    {
        return aList[listSize - 1];
    }
    
    return aList[index];
}

objPos objPosArrayList::setElementAt(int index, objPos fooditem) const{
    if(index > listSize || index < 0){
        MacUILib_printf("Error: Index out of Bounds!\n");
    }else{
        aList[index] = fooditem;
    }
}

void objPosArrayList::clearArray() {
    // for(int i = 0; i < listSize; i++){
    //     removeElementAt(i); // Remove elements from the beginning (or tail, depending on your design)
    // }
    listSize = 0;
}


// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.
