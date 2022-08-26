#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(600,600);
    this->setFixedSize(600,600);

        scene = new QGraphicsScene(this);
        ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
        ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scene->setSceneRect(0,0,600,500); // Устанавливаем размер сцены
        ui->graphicsView->setRenderHint(QPainter::Antialiasing);

        item_samosval = new samosval();
        item_samosval->setPos(100,200);
        scene->addItem(item_samosval);

        item_kuzov = new kuzov();
        item_kuzov->setPos(100,200);
        scene->addItem(item_kuzov);
        item_kuzov->setTransformOriginPoint(20,40);

        item_wheel[0] = new wheel();
        item_wheel[0]->setPos(149,260);
        scene->addItem(item_wheel[0]);
        item_wheel[0]->setScale(0.68);
        item_wheel[0]->setRotation(93);

        item_wheel[1] = new wheel();
        item_wheel[1]->setPos(200,260);
        scene->addItem(item_wheel[1]);
        item_wheel[1]->setScale(0.68);
        item_wheel[1]->setRotation(30);

        item_wheel[2] = new wheel();
        item_wheel[2]->setPos(278,260);
        scene->addItem(item_wheel[2]);
        item_wheel[2]->setScale(0.68);
        item_wheel[2]->setRotation(63);

        timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(moving()));
        timer->start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::moving(){
    if(GetAsyncKeyState(VK_LEFT)){
        if(x1>-20){
        item_samosval->setPos(--x1,200);
        item_kuzov->setPos(--x2,200);
        item_wheel[0]->setPos(--x3,260);
        item_wheel[1]->setPos(--x4,260);
        item_wheel[2]->setPos(--x5,260);
        item_wheel[0]->setRotation(----rotate_wheel1);
        item_wheel[1]->setRotation(----rotate_wheel2);
        item_wheel[2]->setRotation(----rotate_wheel3);
        }
    }
    if(GetAsyncKeyState(VK_RIGHT)){
        if(x1<380){
        item_samosval->setPos(++x1,200);
        item_kuzov->setPos(++x2,200);
        item_wheel[0]->setPos(++x3,260);
        item_wheel[1]->setPos(++x4,260);
        item_wheel[2]->setPos(++x5,260);
        item_wheel[0]->setRotation(++++rotate_wheel1);
        item_wheel[1]->setRotation(++++rotate_wheel2);
        item_wheel[2]->setRotation(++++rotate_wheel3);
        }
    }
    if(GetAsyncKeyState(VK_UP)){
        if(rotate>-50)rotate-=0.3;
        item_kuzov->setRotation(rotate);
    }
    if(GetAsyncKeyState(VK_DOWN)){
        if(rotate<0)rotate+=0.3;
        item_kuzov->setRotation(rotate);
    }
}
