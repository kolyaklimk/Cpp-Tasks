//item_square->setFlag(QGraphicsItem::ItemIsMovable); //мышкой перемещать
#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scen();
    ui->lineEdit->setValidator(new QDoubleValidator(0,100,2,this));
    ui->lineEdit->setMaxLength(3);
    ui->lineEdit_2->setValidator(new QDoubleValidator(0,100,2,this));
    ui->lineEdit_2->setMaxLength(3);
    ui->lineEdit_3->setValidator(new QDoubleValidator(0,100,2,this));
    ui->lineEdit_3->setMaxLength(3);
    ui->lineEdit_4->setValidator(new QDoubleValidator(0,100,2,this));
    ui->lineEdit_4->setMaxLength(3);
    ui->lineEdit_5->setValidator(new QDoubleValidator(0,100,2,this));
    ui->lineEdit_5->setMaxLength(1);
    ui->lineEdit_6->setValidator(new QDoubleValidator(0,100,2,this));
    ui->lineEdit_6->setMaxLength(2);

    d = new dot();
    d->setPos(dx,dy);
    scene->addItem(d);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::scen()
{
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(0,0,500,400); // Устанавливаем размер сцены
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

//свой рисунок
void MainWindow::on_radioButton_10_clicked()
{
    if (!check_button){
    delete_figurs(10);
    check_button=1;
    delete scene;
    scene = new custom();       // Инициализируем графическую сцену
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0,0,500,400);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    //периметр, площадь, центр
    ui->textBrowser->setText("-");
    ui->textBrowser_2->setText("-");
    }
}
//пятиугольник
void MainWindow::on_radioButton_8_clicked()
{
    if (!check_button){
    fx=260;
    fy=210;
    this->xx=ui->lineEdit_2->text().toInt();
    delete_figurs(8);
    item_pentagon = new pentagon(xx);
    item_pentagon->setPos(fx,fy);
    scene->addItem(item_pentagon);

    //периметр, площадь, центр
    ui->textBrowser->setText(QString::number(5*xx));
    ui->textBrowser_2->setText(QString::number(5/2*xx*xx/2/sin(3.14/5)));
    }
}
//шестиугольник
void MainWindow::on_radioButton_9_clicked()
{
    if (!check_button){
    fx=260;
    fy=210;
    this->xx=ui->lineEdit_2->text().toInt();
    delete_figurs(9);
    item_hexagon = new hexagon(xx);
    item_hexagon->setPos(fx,fy);
    scene->addItem(item_hexagon);

    //периметр, площадь, центр
    ui->textBrowser->setText(QString::number(6*xx));
    ui->textBrowser_2->setText(QString::number(6/2*xx*xx/2/sin(3.14/6)));
    }
}
//звезда_5
void MainWindow::on_radioButton_5_clicked()
{
    if (!check_button){
    fx=260;
    fy=210;
    this->xx=ui->lineEdit_2->text().toInt();
    delete_figurs(5);
    item_star_5 = new star_5(xx);
    item_star_5->setPos(fx,fy);
    scene->addItem(item_star_5);

    //периметр, площадь, центр
    ui->textBrowser->setText(QString::number(5*xx));
    ui->textBrowser_2->setText(QString::number(5/4*sqrt(50-22*sqrt(5))*qPow(xx/2/sin(3.14/5),2)));
    }
}
//звезда_6
void MainWindow::on_radioButton_6_clicked()
{
    if (!check_button){
    fx=260;
    fy=210;
    this->xx=ui->lineEdit_2->text().toInt();
    delete_figurs(6);
    item_star_6 = new star_6(xx);
    item_star_6->setPos(fx,fy);
    scene->addItem(item_star_6);

    //периметр, площадь, центр
    ui->textBrowser->setText(QString::number(6*xx));
    ui->textBrowser_2->setText(QString::number(5/4*sqrt(50-22*sqrt(5))*qPow(xx/2/sin(3.14/6),2)));
    }
}
//звезда_8
void MainWindow::on_radioButton_7_clicked()
{
    if (!check_button){
    fx=260;
    fy=210;
    this->xx=ui->lineEdit_2->text().toInt();
    delete_figurs(7);
    item_star_8 = new star_8(xx);
    item_star_8->setPos(fx,fy);
    scene->addItem(item_star_8);

    //периметр, площадь, центр
    ui->textBrowser->setText(QString::number(8*xx));
    ui->textBrowser_2->setText(QString::number(5/4*sqrt(50-22*sqrt(5))*qPow(xx/2/sin(3.14/8),2)));
    }
}
//прямоугольник
void MainWindow::on_radioButton_4_clicked()
{
    if (!check_button){
    fx=260;
    fy=210;
    this->xx=ui->lineEdit_2->text().toInt();
    this->yy=ui->lineEdit_3->text().toInt();
    delete_figurs(4);
    item_rectangle = new rectangle(xx,yy);
    item_rectangle->setPos(fx,fy);
    scene->addItem(item_rectangle);

    //периметр, площадь, центр
    ui->textBrowser->setText(QString::number(2*(xx+yy)));
    ui->textBrowser_2->setText(QString::number(xx*yy));
    }
}
//треугольник
void MainWindow::on_radioButton_3_clicked()
{
    if (!check_button){
    fx=260;
    fy=210;
    this->xx=ui->lineEdit_2->text().toInt();
    delete_figurs(3);
    item_triangle = new triangle(xx);
    item_triangle->setPos(fx,fy);
    scene->addItem(item_triangle);

    //периметр, площадь, центр
    ui->textBrowser->setText(QString::number(3*xx));
    ui->textBrowser_2->setText(QString::number(qPow(xx,2)*sqrt(3)/4));
    }
}
//квадрат
void MainWindow::on_radioButton_2_clicked()
{
    if (!check_button){
    fx=260;
    fy=210;
    this->xx=ui->lineEdit_2->text().toInt();
    delete_figurs(2);
    item_square = new square(xx);
    item_square->setPos(fx,fy);
    scene->addItem(item_square);
    buf2x=fx;bufx=fx;
    buf2y=fy;bufy=fy;

    //периметр, площадь, центр
    ui->textBrowser->setText(QString::number(4*xx));
    ui->textBrowser_2->setText(QString::number(qPow(xx,2)));
    }
}
//окружность
void MainWindow::on_radioButton_clicked()
{
    if (!check_button){
    fx=260;
    fy=210;
    this->radius=ui->lineEdit_4->text().toInt();
    delete_figurs(1);
    item_circle = new circle(radius);
    item_circle->setPos(fx,fy);
    scene->addItem(item_circle);

    //периметр, площадь, центр
    ui->textBrowser->setText(QString::number(3.14*2*radius));
    ui->textBrowser_2->setText(QString::number(3.14*qPow(radius,2)));
    }
}
//delete
void MainWindow::delete_figurs(int x)
{
    switch(figur){
    case 1: delete item_circle;break;
    case 2: delete item_square;break;
    case 3: delete item_triangle;break;
    case 4: delete item_rectangle;break;
    case 5: delete item_star_5;break;
    case 6: delete item_star_6;break;
    case 7: delete item_star_8;break;
    case 8: delete item_pentagon;break;
    case 9: delete item_hexagon;break;
    case 10: delete scene; check_button=0;qApp->closeAllWindows();QProcess::startDetached(qApp->applicationFilePath(), QStringList()); break;
    }
    figur = x;
    buf2x=dx;
    buf2y=dy;
    bufx=dx;
    bufy=dy;
    buf3=0;
    buf4=1;
}
///////////////////////МАСШТАБ/////////////////////////////////////////
void MainWindow::on_pushButton_2_clicked()
{
    if (check_button || ui->lineEdit_5->text().toDouble()<=0);
    else{
    check_button=1;
    if((bufx-dx!=0 || bufy-dy!=0) &&buf4!=1 && fx!=dx) trans_re_pushButton_2_clicked();
    else{
    buf5=round(ui->lineEdit_5->text().toDouble()*100)/100;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(pushButton_2_clicked()));
    timer->start(1);
    }
    }
}
void MainWindow::pushButton_2_clicked()
{
    if(int(buf4*100)<int(buf5*100)) buf4+=0.01;
    else buf4-=0.01;
    switch(figur){
    case 1:
        item_circle->setTransformOriginPoint(dx-fx,dy-fy);
        item_circle->setScale(buf4);break;
    case 2:
        item_square->setTransformOriginPoint(dx-fx,dy-fy);
        item_square->setScale(buf4);break;
    case 3:
        item_triangle->setTransformOriginPoint(dx-fx,dy-fy);
        item_triangle->setScale(buf4);break;
    case 4:
        item_rectangle->setTransformOriginPoint(dx-fx,dy-fy);
        item_rectangle->setScale(buf4);break;
    case 5:
        item_star_5->setTransformOriginPoint(dx-fx,dy-fy);
        item_star_5->setScale(buf4);break;
    case 6:
        item_star_6->setTransformOriginPoint(dx-fx,dy-fy);
        item_star_6->setScale(buf4);break;
    case 7:
        item_star_8->setTransformOriginPoint(dx-fx,dy-fy);
        item_star_8->setScale(buf4);break;
    case 8:
        item_pentagon->setTransformOriginPoint(dx-fx,dy-fy);
        item_pentagon->setScale(buf4);break;
    case 9:
        item_hexagon->setTransformOriginPoint(dx-fx,dy-fy);
        item_hexagon->setScale(buf4);break;
    }
    if (int(buf4*100) == int(buf5*100)){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(pushButton_2_clicked()));
        delete timer;
        check_button=0;
        bufx=dx;
        bufy=dy;
    }
}
void MainWindow::trans_re_pushButton_2_clicked(){
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(re_pushButton_2_clicked()));
    timer->start(1);
}
void MainWindow::re_pushButton_2_clicked()
{
    if(int(buf4*100)<100) buf4+=0.01;
    else buf4-=0.01;
    switch(figur){
    case 1:
        item_circle->setTransformOriginPoint(bufx-fx,bufy-fy);
        item_circle->setScale(buf4);break;
    case 2:
        item_square->setTransformOriginPoint(bufx-fx,bufy-fy);
        item_square->setScale(buf4);break;
    case 3:
        item_triangle->setTransformOriginPoint(bufx-fx,bufy-fy);
        item_triangle->setScale(buf4);break;
    case 4:
        item_rectangle->setTransformOriginPoint(bufx-fx,bufy-fy);
        item_rectangle->setScale(buf4);break;
    case 5:
        item_star_5->setTransformOriginPoint(bufx-fx,bufy-fy);
        item_star_5->setScale(buf4);break;
    case 6:
        item_star_6->setTransformOriginPoint(bufx-fx,bufy-fy);
        item_star_6->setScale(buf4);break;
    case 7:
        item_star_8->setTransformOriginPoint(bufx-fx,bufy-fy);
        item_star_8->setScale(buf4);break;
    case 8:
        item_pentagon->setTransformOriginPoint(bufx-fx,bufy-fy);
        item_pentagon->setScale(buf4);break;
    case 9:
        item_hexagon->setTransformOriginPoint(bufx-fx,bufy-fy);
        item_hexagon->setScale(buf4);break;
    }
    if (int(buf4*100) == 100){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(re_pushButton_2_clicked()));
        delete timer;
        buf4=1;
        check_button=0;
        bufx=dx;
        bufy=dy;
        on_pushButton_2_clicked();
    }
}
///////////////////////ВРАЩЕНИЕ/////////////////////////////////////////
void MainWindow::on_pushButton_clicked()
{
    if (check_button || ui->lineEdit->text().toInt()<0);
    else{
    if (ui->lineEdit->text().toInt()>360) ui->lineEdit->setText("360");
    check_button=1;
    if((buf2x-dx!=0 || buf2y-dy!=0) && buf3 && fx!=dx) trans_re_pushButton_clicked();
    else{
    buf=ui->lineEdit->text().toInt();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(pushButton_clicked()));
    timer->start(5);
    }
    }
}
void MainWindow::pushButton_clicked()
{
    if(buf3<buf) buf3++;
    else buf3--;
    switch(figur){
    case 1:
        item_circle->setTransformOriginPoint(dx-fx,dy-fy);
        item_circle->setRotation(buf3);break;
    case 2:
        item_square->setTransformOriginPoint(dx-fx,dy-fy);
        item_square->setRotation(buf3);break;
    case 3:
        item_triangle->setTransformOriginPoint(dx-fx,dy-fy);
        item_triangle->setRotation(buf3);break;
    case 4:
        item_rectangle->setTransformOriginPoint(dx-fx,dy-fy);
        item_rectangle->setRotation(buf3);break;
    case 5:
        item_star_5->setTransformOriginPoint(dx-fx,dy-fy);
        item_star_5->setRotation(buf3);break;
    case 6:
        item_star_6->setTransformOriginPoint(dx-fx,dy-fy);
        item_star_6->setRotation(buf3);break;
    case 7:
        item_star_8->setTransformOriginPoint(dx-fx,dy-fy);
        item_star_8->setRotation(buf3);break;
    case 8:
        item_pentagon->setTransformOriginPoint(dx-fx,dy-fy);
        item_pentagon->setRotation(buf3);break;
    case 9:
        item_hexagon->setTransformOriginPoint(dx-fx,dy-fy);
        item_hexagon->setRotation(buf3);break;
    }
    if (buf3 == buf){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(pushButton_clicked()));
        delete timer;
        check_button=0;
        buf2x=dx;
        buf2y=dy;
    }
}
void MainWindow::trans_re_pushButton_clicked(){
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(re_pushButton_clicked()));
    timer->start(5);
}
void MainWindow::re_pushButton_clicked()
{
    buf3--;
    switch(figur){
    case 1:
        item_circle->setTransformOriginPoint(buf2x-fx,buf2y-fy);
        item_circle->setRotation(buf3);break;
    case 2:
        item_square->setTransformOriginPoint(buf2x-fx,buf2y-fy);
        item_square->setRotation(buf3);break;
    case 3:
        item_triangle->setTransformOriginPoint(buf2x-fx,buf2y-fy);
        item_triangle->setRotation(buf3);break;
    case 4:
        item_rectangle->setTransformOriginPoint(buf2x-fx,buf2y-fy);
        item_rectangle->setRotation(buf3);break;
    case 5:
        item_star_5->setTransformOriginPoint(buf2x-fx,buf2y-fy);
        item_star_5->setRotation(buf3);break;
    case 6:
        item_star_6->setTransformOriginPoint(buf2x-fx,buf2y-fy);
        item_star_6->setRotation(buf3);break;
    case 7:
        item_star_8->setTransformOriginPoint(buf2x-fx,buf2y-fy);
        item_star_8->setRotation(buf3);break;
    case 8:
        item_pentagon->setTransformOriginPoint(buf2x-fx,buf2y-fy);
        item_pentagon->setRotation(buf3);break;
    case 9:
        item_hexagon->setTransformOriginPoint(buf2x-fx,buf2y-fy);
        item_hexagon->setRotation(buf3);break;
    }
    if (buf3 == 0){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(re_pushButton_clicked()));
        delete timer;
        check_button=0;
        buf2x=dx;
        buf2y=dy;
        on_pushButton_clicked();
    }
}
/////////////////////////////////ТОЧКА////////////////////////////////////////////
void MainWindow::on_up_clicked()
{
    if (check_button || ui->lineEdit_6->text().toInt()<=0);
    else{
    check_button=1;
    buf2=dy;
    dy-=ui->lineEdit_6->text().toInt();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(up_clicked()));
    timer->start(5);
    }
}
void MainWindow::on_down_clicked()
{
    if (check_button || ui->lineEdit_6->text().toInt()<=0);
    else{
        check_button=1;
    buf2=dy;
    dy+=ui->lineEdit_6->text().toInt();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(down_clicked()));
    timer->start(5);
    }
}
void MainWindow::on_left_clicked()
{
    if (check_button || ui->lineEdit_6->text().toInt()<=0);
    else{
        check_button=1;
    buf2=dx;
    dx-=ui->lineEdit_6->text().toInt();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(left_clicked()));
    timer->start(5);
    }
}
void MainWindow::on_right_clicked()
{
    if (check_button || ui->lineEdit_6->text().toInt()<=0);
    else{
        check_button=1;
    buf2=dx;
    dx+=ui->lineEdit_6->text().toInt();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(right_clicked()));
    timer->start(5);
    }
}
void MainWindow::on_sbros_clicked()
{
    if (check_button);
    else{
    dx=fx;dy=fy;
    d->setPos(dx,dy);
    }
}


void MainWindow::up_clicked()
{
    d->setPos(dx,--buf2);
    if (buf2==dy){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(up_clicked()));
        delete timer;
        check_button=0;
    }
}
void MainWindow::down_clicked()
{
    d->setPos(dx,++buf2);
    if (buf2==dy){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(down_clicked()));
        delete timer;
        check_button=0;
    }
}
void MainWindow::left_clicked()
{
    d->setPos(--buf2,dy);
    if (buf2==dx){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(left_clicked()));
        delete timer;
        check_button=0;
    }
}
void MainWindow::right_clicked()
{
    d->setPos(++buf2,dy);
    if (buf2==dx){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(right_clicked()));
        delete timer;
        check_button=0;
    }
}
/////////////////////////////////ОБЪЕКТ/////////////////////////////////////////
void MainWindow::on_up_2_clicked()
{
    if (check_button || ui->lineEdit_6->text().toInt()<=0);
    else{
    check_button=1;
    buf=fy;
    buf2=dy;
    fy-=ui->lineEdit_6->text().toInt();
    dy-=ui->lineEdit_6->text().toInt();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(up_2_clicked()));
    timer->start(5);
    }
}
void MainWindow::on_down_2_clicked()
{
    if (check_button || ui->lineEdit_6->text().toInt()<=0);
    else{
        check_button=1;
    buf=fy;
    buf2=dy;
    fy+=ui->lineEdit_6->text().toInt();
    dy+=ui->lineEdit_6->text().toInt();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(down_2_clicked()));
    timer->start(5);
    }
}
void MainWindow::on_left_2_clicked()
{
    if (check_button || ui->lineEdit_6->text().toInt()<=0);
    else{
        check_button=1;
    buf=fx;
    buf2=dx;
    fx-=ui->lineEdit_6->text().toInt();
    dx-=ui->lineEdit_6->text().toInt();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(left_2_clicked()));
    timer->start(5);
    }
}
void MainWindow::on_right_2_clicked()
{
    if (check_button || ui->lineEdit_6->text().toInt()<=0);
    else{
        check_button=1;
    buf=fx;
    buf2=dx;
    fx+=ui->lineEdit_6->text().toInt();
    dx+=ui->lineEdit_6->text().toInt();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(right_2_clicked()));
    timer->start(5);
    }
}
void MainWindow::on_sbros_2_clicked()
{
    if (check_button);
    else{
    dx=260;dy=210;
    d->setPos(dx,dy);
    switch(figur){
    case 1: on_radioButton_clicked();break;
    case 2: on_radioButton_2_clicked();break;
    case 3: on_radioButton_3_clicked();break;
    case 4: on_radioButton_4_clicked();break;
    case 5: on_radioButton_5_clicked();break;
    case 6: on_radioButton_6_clicked();break;
    case 7: on_radioButton_7_clicked();break;
    case 8: on_radioButton_8_clicked();break;
    case 9: on_radioButton_9_clicked();break;
    }
    buf2x=dx;
    buf2y=dy;
    bufx=dx;
    bufy=dy;
    buf3=0;
    buf4=1;
    }
}


void MainWindow::up_2_clicked()
{
    d->setPos(dx,--buf2);
    switch(figur){
    case 1: item_circle->setPos(fx,--buf);break;
    case 2: item_square->setPos(fx,--buf);break;
    case 3: item_triangle->setPos(fx,--buf);break;
    case 4: item_rectangle->setPos(fx,--buf);break;
    case 5: item_star_5->setPos(fx,--buf);break;
    case 6: item_star_6->setPos(fx,--buf);break;
    case 7: item_star_8->setPos(fx,--buf);break;
    case 8: item_pentagon->setPos(fx,--buf);break;
    case 9: item_hexagon->setPos(fx,--buf);break;
    }
    if (buf==fy){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(up_2_clicked()));
        delete timer;
        check_button=0;
        buf2x=dx;
        buf2y=dy;
        bufx=dx;
        bufy=dy;
    }
}
void MainWindow::down_2_clicked()
{
    d->setPos(dx,++buf2);
    switch(figur){
    case 1: item_circle->setPos(fx,++buf);break;
    case 2: item_square->setPos(fx,++buf);break;
    case 3: item_triangle->setPos(fx,++buf);break;
    case 4: item_rectangle->setPos(fx,++buf);break;
    case 5: item_star_5->setPos(fx,++buf);break;
    case 6: item_star_6->setPos(fx,++buf);break;
    case 7: item_star_8->setPos(fx,++buf);break;
    case 8: item_pentagon->setPos(fx,++buf);break;
    case 9: item_hexagon->setPos(fx,++buf);break;
    }
    if (buf==fy){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(down_2_clicked()));
        delete timer;
        check_button=0;
        buf2x=dx;
        buf2y=dy;
        bufx=dx;
        bufy=dy;
    }
}
void MainWindow::left_2_clicked()
{
    d->setPos(--buf2,dy);
    switch(figur){
    case 1: item_circle->setPos(--buf,fy);break;
    case 2: item_square->setPos(--buf,fy);break;
    case 3: item_triangle->setPos(--buf,fy);break;
    case 4: item_rectangle->setPos(--buf,fy);break;
    case 5: item_star_5->setPos(--buf,fy);break;
    case 6: item_star_6->setPos(--buf,fy);break;
    case 7: item_star_8->setPos(--buf,fy);break;
    case 8: item_pentagon->setPos(--buf,fy);break;
    case 9: item_hexagon->setPos(--buf,fy);break;
    }
    if (buf==fx){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(left_2_clicked()));
        delete timer;
        check_button=0;
        buf2x=dx;
        buf2y=dy;
        bufx=dx;
        bufy=dy;
    }
}
void MainWindow::right_2_clicked()
{
    d->setPos(++buf2,dy);
    switch(figur){
    case 1: item_circle->setPos(++buf,fy);break;
    case 2: item_square->setPos(++buf,fy);break;
    case 3: item_triangle->setPos(++buf,fy);break;
    case 4: item_rectangle->setPos(++buf,fy);break;
    case 5: item_star_5->setPos(++buf,fy);break;
    case 6: item_star_6->setPos(++buf,fy);break;
    case 7: item_star_8->setPos(++buf,fy);break;
    case 8: item_pentagon->setPos(++buf,fy);break;
    case 9: item_hexagon->setPos(++buf,fy);break;
    }
    if (buf==fx){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(right_2_clicked()));
        delete timer;
        check_button=0;
        buf2x=dx;
        buf2y=dy;
        bufx=dx;
        bufy=dy;
    }
}

