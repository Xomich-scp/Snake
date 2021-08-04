#ifndef SNAKE_H
#define SNAKE_H
#include <QColor>

#include <QRandomGenerator>
#include <QtSql>
#include "map.h"




#define RANDOM QRandomGenerator::global()->generate()
struct nodeLocation
{
    unsigned int x=0;
    unsigned int y=0;
    unsigned int mass=0;
};
typedef nodeLocation nodeLocation;

class Snake
{
public:
    explicit Snake(MapObject* value);
    ~Snake();
    nodeLocation *snakeHead;/* array of nodes, which belong to snake. [0] - head, [snakelen-1] - tail;
*/
    QColor getHeadColor(bool needHead);
    void setHeadColor(bool needHead, QColor value);
    int getReverseStep();
    void setReverseStep(int value); /* *get/set methods for snakeReverseStep, which determine, how much reverse step snake will do, if it stuck */
    void move();

    void setStartLocation(); /* *set random free node as head.
                                *then using BFS-like method it finds all children nodes.
                                *Then it choose random node as a tail and build shortest way to it, using Deikstra-like method */
    void setDirection(int value);
    int getDirection();

    int getSnakeSize();

    bool isInGame();
    void setGame();


    void setSnake();
    void deleteSnake();



    int  getSnakeID();
    void setSnakeID(int value);

    bool checkBite(Snake* anotherSnake); /*check, if snake share any node with another snake*/



private:

    QColor snakeHeadColor;
    QColor snakeBodyColor;
    int    snakeReverseStep=3;
    int    snakeReverseStepLeft=0;
    int    snakeLen=0;

    MapObject* gameMap;

    bool leftDirection;
    bool rightDirection;
    bool upDirection;
    bool downDirection;
    int snakeID;


    bool inGame;
    void moveForward();
    void moveReverse();
    bool checkMove(int headOrTail);
    bool check(int headOrTail);
    void buildRandomSnake();
    void snakeBFSBuild(nodeLocation lookNode,QVector<nodeLocation>* childList);

};

#endif // SNAKE_H
