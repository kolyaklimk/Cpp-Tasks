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

    circle_ptr=new circle();
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
    ui->textBrowser->insertPlainText("   Кол-во указателей: 0");
     my_shared_ptr<text> ptr1(new text());
     ui->textBrowser->insertPlainText("\n   Кол-во указателей: " + QString:: number(ptr1.get_count()));
     {
         my_shared_ptr<text> ptr2(ptr1);
         xx=ptr2.get_count();
         ui->textBrowser->insertPlainText("\n   Кол-во указателей: " + QString:: number(ptr2.get_count()));
         ui->textBrowser->insertPlainText("\n\nУдаление указателя: " + QString:: number(ptr1.get_count()));
     }
     ui->textBrowser->insertPlainText("\n   Кол-во указателей: " + QString:: number(ptr1.get_count()));
     ui->textBrowser->insertPlainText("\nУдаление указателя: " + QString:: number(ptr1.get_count()));

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
    ui->textBrowser->insertPlainText("   Кол-во указателей: 0");
     my_shared_ptr<text> ptr1(new text());
     ui->textBrowser->insertPlainText("\n   Кол-во указателей: " + QString:: number(ptr1.get_count()));
     {
         my_shared_ptr<text> ptr2(ptr1);
         ui->textBrowser->insertPlainText("\n   Кол-во указателей: " + QString:: number(ptr2.get_count()));
         {
             my_shared_ptr<text> ptr3(ptr2);
             xx=ptr3.get_count();
             ui->textBrowser->insertPlainText("\n   Кол-во указателей: " + QString:: number(ptr3.get_count()));
             ui->textBrowser->insertPlainText("\n\nУдаление указателя: " + QString:: number(ptr3.get_count()));
         }
         ui->textBrowser->insertPlainText("\n   Кол-во указателей: " + QString:: number(ptr2.get_count()));
         ui->textBrowser->insertPlainText("\nУдаление указателя: " + QString:: number(ptr1.get_count()));
     }
     ui->textBrowser->insertPlainText("\n   Кол-во указателей: " + QString:: number(ptr1.get_count()));
     ui->textBrowser->insertPlainText("\nУдаление указателя: " + QString:: number(ptr1.get_count()));

     timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()), this, SLOT(draw_t()));
     timer->start(1000);
    }
}



void MainWindow::draw_t()
{
if(!xxx) {
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

        xxx++;
        if(xxx==xx){
            disconnect(timer, SIGNAL(timeout()), this, SLOT(draw_t()));
            delete timer;
            xxx--;
            timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(draw_delete()));
            timer->start(500);
        }
}

void MainWindow::draw_delete()
{
    delete linee[xxx];
    delete circlee[xxx--];
    if(xxx==-1){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(draw_delete()));
        xx=0;
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
    my_shared_ptr<circle> ptr2(circle_ptr);
    ui->textBrowser_2->insertPlainText("ptr2.get_count(): " + QString::number(ptr2.get_count()));
    ui->textBrowser_2->insertPlainText("\nptr2.owner_before(circle_ptr): " + QString::number(ptr2.owner_before(circle_ptr)));
    ui->textBrowser_2->insertPlainText("\ncircle_ptr.owner_before(ptr2): " + QString::number(circle_ptr.owner_before(ptr2)));
    ui->textBrowser_2->insertPlainText("\nptr2.operator_null(): " + QString::number(ptr2.operator_null()));
    ui->textBrowser_2->insertPlainText("\nptr2.unique(): " + QString::number(ptr2.unique()));
    ptr2.reset();
    ui->textBrowser_2->insertPlainText("\nptr2.reset() -> circle_ptr.get_count():"+ QString::number(circle_ptr.get_count()));
    ui->textBrowser_2->insertPlainText("\nptr2.operator_null(): " + QString::number(ptr2.operator_null()));
    ptr2 = new circle();
    circle_ptr.get()->setPos(1000,100);
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
    my_shared_ptr<circle> ptr2(new circle());
    ui->textBrowser_2->insertPlainText("1 - my_shared_ptr<circle> ptr2(new circle())");
    ptr2.swap(circle_ptr);
    ui->textBrowser_2->insertPlainText("\n2 - ptr2.swap(circle_ptr)");
    ui->textBrowser_2->insertPlainText("\nОбъект удалён, значит произошёл swap "
                                       "указателей и ptr2 удалился по завершению функции");


    }

}

