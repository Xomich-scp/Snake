#ifndef ADDTIONALTYPES_H
#define ADDTIONALTYPES_H

enum mapNode
{
    NodeWall=-1,
    NodeEmpty=0,
    NodeSnake_1=1,
    NodeSnake_2=2,
};

#endif // ADDTIONALTYPES_H
/*
 *      qDebug()<<"-------------------------------";
     for(int i=0; i<numberofSQ; i++)
     {
         QString str=NULL;
         for (int j=0; j<numberofSQ; j++)
         {
             if(mapSet[i][j]==-1) str+="* ";
             else
             str+=QString::number(mapSet[i][j])+" ";
         }
         qDebug()<<str;
     }
     qDebug()<<"-------------------------------";

    if(!my_query.exec("select * from SNAKE_LOG"))
    {
        qDebug() << "Error while MAP select"<<  my_query.lastError().text();
    }
    QSqlRecord rec = my_query.record();
    while (my_query.next())
    {
        qDebug() <<    my_query.value(rec.indexOf("mapID")).toInt() << my_query.value(rec.indexOf("snakeID")).toInt() << my_query.value(rec.indexOf("path")).toString();
    }

    if(!my_query.exec("select * from MAP_LOG"))
    {
        qDebug() << "Error while MAP select"<<  my_query.lastError().text();
    }
    QSqlRecord rec = my_query.record();
    while (my_query.next())
    {
        qDebug() <<    my_query.value(rec.indexOf("mapID")).toInt() << my_query.value(rec.indexOf("mapRow")).toString();
    }
    QSqlQuery a_query;
   // DDL query
    QString str = "DROP TABLE MAP_LOG ;";
    if (!a_query.exec(str))
    {
        qDebug() << "Error while createTable MAP_LOG";
         qDebug() << a_query.lastError().text();
    }
    str = "DROP TABLE SNAKE_LOG ;";
    if (!a_query.exec(str))
    {
        qDebug() << "Error while drop MAP_LOG";
         qDebug() << a_query.lastError().text();
    }
*/
