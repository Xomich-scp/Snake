
#include "map.h"

  //Default constructor. Map with side 10x10.
MapObject::MapObject()
{
    mapSideSize=10;
    mapID=0;
    genNewMap(mapSideSize);
}

 //Custom constructor. Will create map side mapSideSize x mapSideSize.
MapObject::MapObject(unsigned int value)
{
    mapSideSize=value;
    mapID=0;
    genNewMap(mapSideSize);
}


MapObject::~MapObject()
{
    free(mapPointer);
}

void MapObject::genNewMap()
{
    mapID++;
    for (unsigned int i=0; i<mapSideSize; i++)
    {
        for (unsigned int j=0; j<mapSideSize; j++)
        {
            if(RANDOM>RANDOM)
            {
                mapPointer[i][j]=WALL;
                mapWallCounter++;

            }
            else
            {
                mapPointer[i][j]=EMPTY;

            }

        }

    }

}


void MapObject::genNewMap(MAPPARAMTYPE value)
{
    setMapSize(value);
    free(mapPointer);
    mapPointer=(MAPTYPE**)malloc(mapSideSize*sizeof(MAPTYPE*));
    for (unsigned int i=0; i<mapSideSize; i++)
    {

        mapPointer[i]=(MAPTYPE*)malloc(sizeof(MAPTYPE)*mapSideSize);
    }
    genNewMap();
}

void MapObject::refreshMap()
{

}

MAPTYPE** MapObject::getMap()
{
    return mapPointer;
}

MAPPARAMTYPE MapObject::getMapID()
{
    return mapID;
}

MAPPARAMTYPE MapObject::getMapSize()
{
    return mapSideSize;
}

void MapObject::setMapSize(MAPPARAMTYPE value)
{
    mapSideSize=value;
}
