#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Graphic setup
    ui->setupUi(this);
    myPicture   = new MyGraphicView();
    ui->graphicLayout->addWidget(myPicture);

    //Link buttons from UI

    //Button will create new map. Creating new map also call Snake().
    connect(ui->mapParamRedraw,SIGNAL(clicked()),myPicture,SLOT(slotRedrawMap()));

    //Button will create new Snakes in existing map.
    connect(ui->buttonSnakeGen, SIGNAL(clicked()), myPicture, SLOT(slotGenNewSnake()));

    //Button will change Snakes color. First change body, second head.
    connect(ui->buttonSnakeBodyColor, SIGNAL(clicked()), myPicture, SLOT(slotChangeBodyColor()));
    connect(ui->buttonSnakeHeadColor, SIGNAL(clicked()), myPicture, SLOT(slotChangeHeadColor()));

    //Link textEdit element from UI

    //This field will determine how many steps Snake will take if it stuck.
    connect(ui->stepBackSnake, SIGNAL(textEdited(const QString)), myPicture, SLOT(slotRecStepBack(const QString )));

    //This field will determine what snake will recieve signals from buttons.
    connect(ui->snakeAtID, SIGNAL(textEdited(const QString)), myPicture, SLOT(slotSnakeAtID(const QString )));


}

MainWindow::~MainWindow()
{
    delete ui->gridLayout;
    delete ui;
}
/*

    //Debug function.
    //connect(ui->setGameSpeed, SIGNAL(textEdited(const QString)), myPicture, SLOT(slotNewGameSpeed(const QString )));

    void slotChangeHeadColor1();
    void slotChangeHeadColor2();
    void slotGenNewSnake();

    void slotSetStepBack1();buttonSnake1ReverseStep
    void slotSetStepBack2();buttonSnake2ReverseStep
    void slotRecStepBack1(const QString &text);
    void slotRecStepBack2(const QString &text);

    void slotNewGameSpeed(const QString &text);
*/
