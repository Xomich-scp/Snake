#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H
#include <QtSql>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include "snake.h"
#include "map.h"
#include <QRandomGenerator>

#define RANDOM QRandomGenerator::global()->generate()
// Расширяем класс QGraphicsView
class MyGraphicView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MyGraphicView(QWidget *parent = 0);
    ~MyGraphicView();

    MapObject           *gameMap;
    QTimer              *timerMove;
    int                 tempNumberOfSQ=100;

signals:



public slots:
    void slotRedrawMap();                       /* slot for redraw signal */
    void slotMove();                            /* timer slot for moving*/
    void slotNewSizeMap(const QString &text);   /* slot for new size signal   */
    void slotChangeHeadColor();
    void slotChangeBodyColor();

    void slotGenNewSnake();
    void slotRecStepBack(const QString &text);
    void slotSnakeAtID(const QString &text);

    void slotNewGameSpeed(const QString &text);


private:
    QGraphicsScene      *scene;
    QGraphicsItemGroup  *group_1;
    QVector<Snake>      snakeVector;
    QTimer              *timerDraw;
    QSqlDatabase dbase;

    int gameSpeed = 100;
    int snakeChangerId=0;



    int setRandomMap();
    void saveMapSQL();
    void saveSnakeSQL();
    void refreshScreen();
    void deleteItemsFromGroup(QGraphicsItemGroup *group_1);
};


#endif // MYGRAPHICVIEW_H
