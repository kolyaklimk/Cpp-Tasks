//QThread::sleep(1);


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textBrowser->setTextColor("red");
    ui->textBrowser_2->setTextColor("red");

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(230,10,500,370); // Устанавливаем размер сцены
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    scene2 = new QGraphicsScene(this);
    ui->graphicsView_2->setScene(scene2);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene2->setSceneRect(740,10,500,230); // Устанавливаем размер сцены
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);

    my_unique_ptr<circle> circle_ptr2(new circle());
    circle_ptr.swap(circle_ptr2);
    scene2->addItem(circle_ptr.get());
    circle_ptr.get()->setPos(900,100);
}



MainWindow::~MainWindow()
{
    delete ui;
}


class text{
public:
    text() {qDebug()<<"open";}
    ~text() {qDebug()<<"close\n";}
};

void MainWindow::on_pushButton_clicked()
{
    if(check_button==1){
        check_button=0;
    ui->textBrowser->clear();
    ui->textBrowser->insertPlainText("Кол-во указателей: 0");
    ui->textBrowser->insertPlainText("\nСоздание ук-ля №1");
     my_unique_ptr<text> ptr1(new text());
     {
         ui->textBrowser->insertPlainText("\nСоздание ук-ля №2");
         my_unique_ptr<text> ptr2(ptr1);
         ui->textBrowser->insertPlainText("\nПеремещения ук-ля №1 в №2");
         xx=2;
         ui->textBrowser->insertPlainText("\nУдаление ук-ля №2");
     }

     timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(draw_t()));
     timer->start(1000);
    }
}


void MainWindow::on_pushButton_2_clicked()
{

    if(check_button==1){
        check_button=0;
    ui->textBrowser->clear();
    ui->textBrowser->insertPlainText("Кол-во указателей: 0");
    ui->textBrowser->insertPlainText("\nСоздание указателя №1");
     my_unique_ptr<text> ptr1(new text());
     {
         ui->textBrowser->insertPlainText("\nСоздание ук-ля №2");
         my_unique_ptr<text> ptr2(ptr1);
         ui->textBrowser->insertPlainText("\nПеремещения ук-ля №1 в №2");
         {
             ui->textBrowser->insertPlainText("\nСоздание ук-ля №3");
             my_unique_ptr<text> ptr3(ptr2);
             ui->textBrowser->insertPlainText("\nПеремещения ук-ля №2 в №3");
             xx=3;
             ui->textBrowser->insertPlainText("\nУдаление ук-ля №3");
         }
     }

     timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(draw_t()));
     timer->start(1000);
    }

}



void MainWindow::draw_t()
{
    if(!xxx){
        circlee2=new circle2();
        scene->addItem(circlee2);
        circlee2->setPos(460,10);
    }
        circlee[xxx]=new circle();
        scene->addItem(circlee[xxx]);
        int x = random(300+xxx*100);
        int y = random(100+xxx*38);
        while(x>600)x-=50;
        while(y>270)y-=50;
        circlee[xxx]->setPos(x,y);

        linee[xxx]=new line(x,y);
        scene->addItem(linee[xxx]);
        linee[xxx]->setPos(0,0);

        if(xxx)delete linee[xxx-1];
        xxx++;
        if(xxx==xx){
            disconnect(timer, SIGNAL(timeout()), this, SLOT(draw_t()));
            delete timer;
            xxx--;
            timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(draw_delete()));
            timer->start(1000);
        }
}

void MainWindow::draw_delete()
{
    if(xx) delete linee[--xx];
    xx=0;
    delete circlee[xxx--];
    timer->start(1);
    if(xxx==-1){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(draw_delete()));
        xxx=0;
        delete timer;
        delete circlee2;
        check_button=1;
    }
}

uint MainWindow::random(uint x)
{
    QString secs = QString::number(QDateTime::currentDateTime().toSecsSinceEpoch());
    double buf= secs.mid(secs.length()-2).toInt()  * (secs.mid(secs.length()-1).toInt()+1);
    while(buf<x) buf+=secs.mid(secs.length()-1).toInt()+10;
    return buf;
}

void MainWindow::on_pushButton_3_clicked()
{
    if(check_button==1){
        check_button=3;
    ui->textBrowser_2->clear();
    my_unique_ptr<circle> ptr2(circle_ptr);
    ui->textBrowser_2->insertPlainText("\ncircle_ptr.operator_null(): " + QString::number(circle_ptr.operator_null()));
    ui->textBrowser_2->insertPlainText("\nptr2.operator_null(): " + QString::number(ptr2.operator_null()));
    ptr2.release();
    ui->textBrowser_2->insertPlainText("\nptr2.release()");
    ptr2.reset(new circle());
    ui->textBrowser_2->insertPlainText("\nptr2.reset(new circle()) -> ptr2.operator_null(): "+ QString::number(ptr2.operator_null()));
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    if(check_button==3){
    qApp->closeAllWindows();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    if(check_button==1){
        check_button=3;
    ui->textBrowser_2->clear();
    my_unique_ptr<circle> ptr2(new circle());
    ui->textBrowser_2->insertPlainText("1 - my_shared_ptr<circle> ptr2(new circle())");
    ptr2.swap(circle_ptr);
    ui->textBrowser_2->insertPlainText("\n2 - ptr2.swap(circle_ptr)");
    ui->textBrowser_2->insertPlainText("\nОбъект удалён, значит произошёл swap "
                                       "указателей и ptr2 удалился по завершению функции");
    }

}


void MainWindow::on_pushButton_6_clicked()
{

    if(check_button==1){
        check_button=3;
        circle_ptr.get_deleter();
    }
}

