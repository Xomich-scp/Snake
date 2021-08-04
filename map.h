#ifndef MAP_H
#define MAP_H
#include <QRandomGenerator>

#define MAPTYPE unsigned char
#define MAPPARAMTYPE unsigned int
#define RANDOM QRandomGenerator::global()->generate()


//This enum used to separate empty map points, which Snake can step, from walls
enum MapPointValues
{
    EMPTY=0,

    WALL=255

};


//This class used to describe game map.
class MapObject
{
private:
    //Pointer to 2D array, which represent out field. Filled with EMPTY or WALL values.
    MAPTYPE **mapPointer=nullptr;
    //Size of our map. Our map have shape of square.
    MAPPARAMTYPE   mapSideSize=100;
    //Number of walls in map.
    MAPPARAMTYPE   mapWallCounter=0;
    //ID of map. Used for logging.
    MAPPARAMTYPE   mapID=0;

public:
     //Default constructor. Map with side 10x10.
     MapObject();
     //Custom constructor. Will create map side mapSideSize x mapSideSize.
     MapObject(MAPPARAMTYPE mapSideSize);
     //Destructor.
    ~MapObject();

    //Getter of 2D array.
    MAPTYPE** getMap();
    //Getter of current map size
    MAPPARAMTYPE getMapSize();
    //Getter of current mapID.
    MAPPARAMTYPE getMapID();

    //Generation of new MAP with current mapSideSize value.
    void genNewMap();
    //Change mapSideSize value, generate map with new side.
    void genNewMap(MAPPARAMTYPE value);
    //?
    void refreshMap();
    //Change current mapSideSize without generating new map.
    void setMapSize(MAPPARAMTYPE value);

};

#endif // MAP_H
