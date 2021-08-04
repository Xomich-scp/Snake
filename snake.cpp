#include "snake.h"

Snake::Snake(MapObject* value)
{

    snakeHead = (nodeLocation*)malloc(sizeof(nodeLocation)*2);

    gameMap=value;
    this->setStartLocation();

    this->inGame=true;
    QStringList listOfColors=QColor::colorNames();
    this->snakeHeadColor= listOfColors.at(RANDOM%listOfColors.length());
    this->snakeBodyColor= listOfColors.at(RANDOM%listOfColors.length());
    while (this->snakeHeadColor==Qt::red||this->snakeHeadColor==Qt::white)
    {
         this->snakeHeadColor= listOfColors.at(RANDOM%listOfColors.length());
    }
    while (this->snakeBodyColor==Qt::red||this->snakeBodyColor==Qt::white)
    {
         this->snakeBodyColor= listOfColors.at(RANDOM%listOfColors.length());
    }
}

Snake::~Snake()
{

}


void Snake::setReverseStep(int value)
{
    this->snakeReverseStep=value;
}

void Snake::setDirection(int value)
{
    leftDirection=rightDirection=upDirection=downDirection=false;

    switch (value)
    {
        case 0: leftDirection=true;break;
        case 1: rightDirection=true;break;
        case 2: upDirection=true;break;
        case 3: downDirection=true;break;
    default:break;
    }
}
int Snake::getDirection()
{
    if(leftDirection) return 0;
    if(rightDirection) return 1;
    if(upDirection) return 2;
    if(downDirection) return 3;
    return 5;
}
void Snake::move()
{

    if(snakeReverseStepLeft>0)
    {
        moveReverse();
        snakeReverseStepLeft--;

    }
    else
        moveForward();
}
void Snake::moveForward()
{
    nodeLocation headTemp=snakeHead[0];



    for (unsigned int i=RANDOM%4, counter=0; counter<4; counter++, i++)
    {
        setDirection(i%4);
        if (checkMove(0))
        {

            for (unsigned int z = snakeLen; z > 1; z--)
            {
                snakeHead[z]=snakeHead[z-1];

            }
            snakeHead[1]=headTemp;
            return;
        }
    }


    snakeReverseStepLeft=snakeReverseStep;

}

void Snake::moveReverse()
{

    nodeLocation headTemp=snakeHead[snakeLen-1];

    for (unsigned int i=RANDOM%4, counter=0; counter<4; counter++, i++)
    {
        setDirection(i%4);
        if (checkMove(snakeLen-1))
        {
            for (int z = 0; z <snakeLen-1; z++)
            {
                snakeHead[z]=snakeHead[z+1];

            }
            snakeHead[snakeLen-2]=headTemp;//snHead[2]

            return;
        }
    }

    snakeReverseStepLeft=0;


}


bool Snake::checkMove(int headOrTail)
{
    if (leftDirection)
    {
        snakeHead[headOrTail].y--;
        if (!check(headOrTail)) snakeHead[headOrTail].y++;
        else return true;
    }

    if (rightDirection)
    {
        snakeHead[headOrTail].y++;
        if (!check(headOrTail)) snakeHead[headOrTail].y--;
        else return true;
    }

    if (upDirection)
    {
        snakeHead[headOrTail].x--;
         if (!check(headOrTail)) snakeHead[headOrTail].x++;
         else  return true;
    }

    if (downDirection)
    {
        snakeHead[headOrTail].x++;
         if (!check(headOrTail))  snakeHead[headOrTail].x--;
         else return true;
    }
    return false;
}


int Snake::getSnakeSize()
{
    return snakeLen;
}


void Snake::setSnake()
{

    for (int i=1; i<snakeLen; i++)
    {

        gameMap->getMap()[snakeHead[i].x][snakeHead[i].y]=2*(snakeID+1);
    }
    gameMap->getMap()[snakeHead[0].x][snakeHead[0].y]=2*(snakeID+1)+1;

}


void Snake::deleteSnake()
{

    for (int i=0; i<this->getSnakeSize(); i++)
    {
        //if(this->snakeHead[i].x>0 && this->snakeHead[i].y>0 && this->snakeHead[i].y<mapSize && this->snakeHead[i].x<mapSize)
        gameMap->getMap()[this->snakeHead[i].x][this->snakeHead[i].y]=0;

    }



}

/*
     * 0 - empty
     * 1 - wall
     * 2 - snake1
     * 3 - snake2
*/
void Snake::setStartLocation()
{
    deleteSnake();
    snakeHead=(nodeLocation*)malloc(sizeof(nodeLocation));
    snakeHead[0].mass=1;
    snakeLen=1;
    QVector<nodeLocation> childList;

    int xHead=RANDOM%gameMap->getMapSize(), yHead=RANDOM%gameMap->getMapSize();
    while(gameMap->getMap()[xHead][yHead]!=0)
    {
        xHead=RANDOM%gameMap->getMapSize();
        yHead=RANDOM%gameMap->getMapSize();

    }
    snakeHead[0].x=xHead;
    snakeHead[0].y=yHead;
    gameMap->getMap()[snakeHead[0].x][snakeHead[0].y]=1;
    snakeBFSBuild(snakeHead[0],&childList);



    if(childList.length()>0)
    {
        int tailMark=RANDOM%childList.length();


        snakeLen=childList[tailMark].mass;
        snakeHead=(nodeLocation*) realloc(snakeHead, snakeLen*sizeof(nodeLocation)+sizeof(nodeLocation*) );
        snakeHead[snakeLen-1]=childList[tailMark];
        for(int j=snakeLen-1; j>0; j--)
        {
            int x[4]={1,-1,0,0},y[4]={0,0,1,-1};
    #define NEWX (snakeHead[j].x+x[i])
    #define NEWY (snakeHead[j].y+y[i])

            for(int i=0; i<4; i++)
            {
                if (NEWX<gameMap->getMapSize() && NEWY<gameMap->getMapSize() && NEWX>=0 && NEWY>=0)
                if (gameMap->getMap()[NEWX][NEWY]!=255 && gameMap->getMap()[NEWX][NEWY]<snakeHead[j].mass)
                {
                    snakeHead[j-1].x=NEWX;
                    snakeHead[j-1].y=NEWY;
                    snakeHead[j-1].mass=gameMap->getMap()[NEWX][NEWY];
                    break;
                }
            }
    #undef NEWX
    #undef NEWY
        }

        for(int i=0; i<childList.length(); i++)
        {
            gameMap->getMap()[childList[i].x][childList[i].y]=0;
        }
    }
    for (int i=0; i<snakeLen; i++)
    {
        gameMap->getMap()[snakeHead[i].x][snakeHead[i].y]=255;
    }







}

void Snake::snakeBFSBuild(nodeLocation lookNode, QVector<nodeLocation>* childList)
{

    int new_nodes=0;
    int x[4]={1,-1,0,0},y[4]={0,0,1,-1};
    ;
    for (int i=0; i<4; i++)
    {
#define NEWX (lookNode.x+x[i])
#define NEWY (lookNode.y+y[i])

        if (NEWX<gameMap->getMapSize() && NEWY<gameMap->getMapSize() && NEWX>=0 && NEWY>=0)
            if (gameMap->getMap()[NEWX][NEWY]==0)
            {

                    nodeLocation temp;
                    temp.x=NEWX;
                    temp.y=NEWY;
                    temp.mass=lookNode.mass+1;
                    childList->append(temp);
                    gameMap->getMap()[NEWX][NEWY]=temp.mass;
                    new_nodes++;
                    gameMap->getMap()[NEWX][NEWY]=lookNode.mass+1;

            }
    }
#undef NEWX
#undef NEWY
    if(lookNode.mass==1&&new_nodes>0)
    for(int i=0; i<childList->length(); i++)
    {
         snakeBFSBuild(childList->at(i),childList);
    }



}


bool Snake::check(int headOrTail)
{
    for (int z=snakeLen-1; z>=0; z--)
    {
        if ( (headOrTail!=z)&& (snakeHead[z].x==snakeHead[headOrTail].x) && (snakeHead[z].y==snakeHead[headOrTail].y)  )
        {
            return false;
        }

        if ( (snakeHead[headOrTail].x>=gameMap->getMapSize()) || (snakeHead[headOrTail].x<0) || (snakeHead[headOrTail].y<0) || (snakeHead[headOrTail].y>=gameMap->getMapSize()))
        {
            return false;
        }

        if ( gameMap->getMap()[snakeHead[headOrTail].x][snakeHead[headOrTail].y]!=0)
        {
            return false;
        }
    }
    return true;

}

QColor Snake:: getHeadColor(bool needHead)
{
    if(needHead) return  snakeHeadColor;
    else         return  snakeBodyColor;
}


void Snake:: setHeadColor(bool needHead, QColor value)
{
    if(needHead) this->snakeHeadColor=value;
    else         this->snakeBodyColor=value;
}


void Snake::setSnakeID(int value)
{
    snakeID=value;
}


bool Snake::checkBite(Snake* anotherSnake)
{
    for(int i=0; i<snakeLen; i++)
    {
        for(int j=0; j<anotherSnake->snakeLen; j++)
        {
            if (snakeHead[i].x==anotherSnake->snakeHead[j].x
                    &&
                        snakeHead[i].y==anotherSnake->snakeHead[j].y)
            {
                return true;
            }
        }
    }
    return false;
}
