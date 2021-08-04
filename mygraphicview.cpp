#include "mygraphicview.h"



MyGraphicView::MyGraphicView(QWidget *parent)
    : QGraphicsView(parent)
{


    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    this->setMinimumHeight(100);
    this->setMinimumWidth(100);

    this->dbase=QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("SnakeLog.sqlite");
    if (!dbase.open())
       {
           qDebug() << "Error while db process opening";
           qDebug() << dbase.lastError().text();
           return;
       }


    QSqlQuery my_query;

    QString str = "CREATE TABLE MAP_LOG ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
           "mapID INTEGER NOT NULL, "
           "mapRow VARCHAR(255) NOT NULL"
            ");";

    if (!my_query.exec(str))
    {
        qDebug() << "Error while createTable MAP_LOG";
         qDebug() << my_query.lastError().text();
    }

    str = "CREATE TABLE SNAKE_LOG ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "mapID INTEGER NOT NULL, "
               "snakeID INTEGER NOT NULL,"
               "path VARCHAR(255) NOT NULL"
                ");";

        if (!my_query.exec(str))
        {
            qDebug() << "Error while createTable MAP_LOG";
             qDebug() << my_query.lastError().text();
        }



    scene = new QGraphicsScene();

    this->setScene(scene);

    group_1 = new QGraphicsItemGroup();

    gameMap = new MapObject(100);

    for (int i=0; i<2; i++)
    {
        snakeVector.append(Snake(gameMap));

    }
    for (int i=0; i<2; i++)
    {

        snakeVector[i].setSnakeID(i);
    }
    saveSnakeSQL();

    scene->addItem(group_1);




    timerMove = new QTimer();

    timerMove->setSingleShot(true);

    timerMove->start(gameSpeed);

    connect(timerMove, SIGNAL(timeout()), this, SLOT(slotMove()));


}

MyGraphicView::~MyGraphicView()
{

}
void MyGraphicView::saveMapSQL()
{

    QSqlQuery my_query;
    for(unsigned int i=0; i<gameMap->getMapSize(); i++)
    {
        QString dbinput=NULL;
        for(unsigned int j=0; j<gameMap->getMapSize(); j++)
        {
            dbinput+=QString::number(gameMap->getMap()[i][j]) + " ";
        }
        my_query.prepare
                    (
                        "INSERT INTO MAP_LOG(mapID,mapRow) VALUES (:mapID, :mapRow);"

                    );

        my_query.bindValue(":mapID",gameMap->getMapID());
        my_query.bindValue(":mapRow",dbinput);
            if (!my_query.exec())
            {
                qDebug() << "Error while MAP Logging"<<  my_query.lastError().text();
            }

    }



}

void MyGraphicView::saveSnakeSQL()
{

    QSqlQuery my_query;
    for(int i=0; i<snakeVector.length(); i++)
    {
        QString dbinput=NULL;
        for(int j=0; j<snakeVector[i].getSnakeSize(); j++)
        {
            dbinput+="("+QString::number(snakeVector[i].snakeHead[j].x) + ","+QString::number(snakeVector[i].snakeHead[j].y) +"); ";
        }
        my_query.prepare
                    (
                        "INSERT INTO SNAKE_LOG(mapID,snakeID,path) VALUES (:mapID, :snakeID, :path);"

                    );

        my_query.bindValue(":mapID",gameMap->getMapID());
        my_query.bindValue(":snakeID",i);
        my_query.bindValue(":path",dbinput);
            if (!my_query.exec())
            {
                qDebug() << "Error while Snake Logging"<<  my_query.lastError().text();
            }

    }

/*
 *    qDebug() << "\n";
    if(!my_query.exec("select * from SNAKE_LOG"))
    {
        qDebug() << "Error while MAP select"<<  my_query.lastError().text();
    }
    QSqlRecord rec = my_query.record();
    while (my_query.next())
    {
        qDebug() <<    my_query.value(rec.indexOf("mapID")).toInt() << my_query.value(rec.indexOf("snakeID")).toInt() << my_query.value(rec.indexOf("path")).toString();
    }
     qDebug() << "\n";
     */

}



void MyGraphicView::slotNewSizeMap(const QString &text)
{
    if (text!=NULL && text.toInt()>2)
    tempNumberOfSQ=text.toInt();
}

void MyGraphicView::slotRedrawMap()
{
    timerMove->stop();
//    qDebug() << "---------------\nNewMap";
    //this->numberofSQ=this->tempNumberOfSQ;

    for(int i=0; i<snakeVector.length(); i++)
    {
         snakeVector[i].deleteSnake();
    }
 //   qDebug() << "SnakeClean";
    gameMap->genNewMap();
   // qDebug() << "MapGen";

    for(int i=0; i<snakeVector.length(); i++)
    {        
        snakeVector[i].setStartLocation();
    }
   // qDebug() << "SnakeSet";

    saveSnakeSQL();
   // qDebug() << "SqlSave";

    refreshScreen();
   // qDebug() << "Refreshed. Start timer\n-------------";
    timerMove->start(gameSpeed);


}


 void MyGraphicView::refreshScreen()
 {
     this->deleteItemsFromGroup(group_1);

     int width = this->width();
     int height = this->height();
     int nodeHigh=height/gameMap->getMapSize();
     int nodeWidth=width/gameMap->getMapSize();

     scene->setSceneRect(0,0,width,height);

     for(int i=0; i<snakeVector.length(); i++)
     {
         snakeVector[i].setSnake();

     }
/*
     qDebug()<<"\n";
     for(int i=0; i<numberofSQ; i++)
     {
        QString str=NULL;
        for(int j=0; j<numberofSQ; j++)
        {
            if (mapSet[i][j]!=255)str+=QString::number(mapSet[i][j])+" ";
            else str+="* ";
        }
        qDebug()<<str;
     }
*/
     QPen penBlack(Qt::black);
     QBrush brushWall;
     brushWall.setStyle(Qt::SolidPattern);



     for(unsigned int i=(height%gameMap->getMapSize())/2, mapCounterI=0; i<nodeHigh*gameMap->getMapSize(); i+=nodeHigh,mapCounterI++)
         for(unsigned int j=(width%gameMap->getMapSize())/2, mapCounterJ=0; j<nodeWidth*gameMap->getMapSize(); j+=nodeWidth,mapCounterJ++)
     {
#define CURRENT_POINT (gameMap->getMap()[mapCounterI][mapCounterJ])
             switch (CURRENT_POINT)
             {
             case EMPTY: brushWall.setColor(Qt::white); break;
             case  WALL: brushWall.setColor(Qt::red);   break;
             default:
                     {
                         //if even - its body
                         for (int i=0; i<snakeVector.length(); i++)
                         {
                             if( (CURRENT_POINT/2 - 1)==i || ((CURRENT_POINT -1)/2-1)==i )
                             {
                                 brushWall.setColor(snakeVector[i].getHeadColor(CURRENT_POINT%2));
                                 break;
                             }
                         }

                         break;
                     }
             }
         group_1->addToGroup(scene->addRect(QRectF(j,i,nodeWidth,nodeHigh),penBlack,brushWall ) );

     }

 }

void MyGraphicView::slotMove()
{
    timerMove->stop();
    for(int i=0; i<snakeVector.length(); i++)
    {
        snakeVector[i].deleteSnake();

    }

    for(int i=0; i<snakeVector.length(); i++)
    {
        snakeVector[i].move();

    }

    refreshScreen();

    for(int i=0; i<snakeVector.length(); i++)
    {
       for(int j=i+1; j<snakeVector.length(); j++)
           if(snakeVector[i].checkBite(&snakeVector[j]))
           {
               slotGenNewSnake();
               return;
           }

    }

    timerMove->start(gameSpeed);

}

void  MyGraphicView::slotGenNewSnake()
{
    timerMove->stop();
    for(int z=0; z<snakeVector.length(); z++) snakeVector[z].deleteSnake();
    for(int z=0; z<snakeVector.length(); z++) snakeVector[z].setStartLocation();
    for(int i=0; i<snakeVector.length(); i++)
    {
       for(int j=i+1; j<snakeVector.length(); j++)
           if(snakeVector[i].checkBite(&snakeVector[j]))
           {
               slotGenNewSnake();
               return;
           }

    }
    saveSnakeSQL();
    refreshScreen();
    timerMove->start(gameSpeed);
    return;
}

void  MyGraphicView::slotChangeBodyColor()
{
    QStringList listOfColors=QColor::colorNames();
    snakeVector[snakeChangerId].setHeadColor(0,listOfColors.at(RANDOM%listOfColors.length()));
}
void  MyGraphicView::slotChangeHeadColor()
{
    QStringList listOfColors=QColor::colorNames();
    snakeVector[snakeChangerId].setHeadColor(1,listOfColors.at(RANDOM%listOfColors.length()));
}


void  MyGraphicView::slotRecStepBack(const QString &text)
{
    if(text!=NULL)
    {
        snakeVector[snakeChangerId].setReverseStep(text.toInt());
    }
}

void  MyGraphicView::slotSnakeAtID(const QString &text)
{
    if(text!=NULL && text.toInt()<snakeVector.length() )
    {
        snakeChangerId=text.toInt();
    }
}

void  MyGraphicView::slotNewGameSpeed(const QString &text)
{
    if(text!=NULL && text.toInt()>0) gameSpeed=text.toInt();
    timerMove->setInterval(gameSpeed);
}

void MyGraphicView::deleteItemsFromGroup(QGraphicsItemGroup *group)
{


    foreach( QGraphicsItem *item, scene->items(group->boundingRect()))
    {
       if(item->group() == group )
       {
          delete item;
       }
    }
}

