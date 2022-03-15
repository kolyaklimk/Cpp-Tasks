//QThread::sleep(1);


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    text() {}
    ~text() {}
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
         ui->textBrowser->insertPlainText("\n   Кол-во указателей: " + QString:: number(ptr2.get_count()));
         ui->textBrowser->insertPlainText("\n   Создание weak_ptr к №2: ");
         xx=ptr2.get_count();
         ui->textBrowser->insertPlainText("\n\nУдаление указателя: " + QString:: number(ptr1.get_count()));
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
    circlee2[0]=new circle2();
    scene->addItem(circlee2[0]);
    circlee2[0]->setPos(460,10);
}
else{
    circlee2[1]=new circle2();
    scene->addItem(circlee2[1]);
    circlee2[1]->setPos(640,185);
    circlee2[1]->setScale(0.5);
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

        if(xxx){
            linee[xxx+1]=new line(x-150,y-150);
            scene->addItem(linee[xxx+1]);
            linee[xxx+1]->setPos(150,150);
        }

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
    if(xx) {
        delete circlee2[1];
        delete linee[2];
    }
    xx=0;
    delete linee[xxx];
    delete circlee[xxx--];
    timer->start(500);
    if(xxx==-1){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(draw_delete()));
        xxx=0;
        delete timer;
        delete circlee2[0];
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
    circle_ptr.get()->setPos(950,100);
    my_shared_ptr<circle> ptr2(circle_ptr);
    my_weak_ptr<circle> ptr3(ptr2);
    ui->textBrowser_2->insertPlainText("\nmy_shared_ptr<circle> ptr2(circle_ptr) \nmy_weak_ptr<circle> ptr3(ptr2)");
    ui->textBrowser_2->insertPlainText("\nptr3.use_count(): " + QString::number(ptr3.use_count()));
    ptr2.reset();
    ptr3=ptr2;
    ui->textBrowser_2->insertPlainText("\nptr2.reset(); \nОбъект удалён");
    ui->textBrowser_2->insertPlainText("\nptr3.expired(): " + QString::number(ptr3.expired()));
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
    my_weak_ptr<circle> ptr2(circle_ptr);
    ui->textBrowser_2->insertPlainText("1 - my_weak_ptr<circle> ptr2(circle_ptr)");
    ptr2.lock().swap(circle_ptr);
    circle_ptr.reset();
    ui->textBrowser_2->insertPlainText("\n2 - ptr2.lock().swap(circle_ptr)");
    ui->textBrowser_2->insertPlainText("\nОбъект удалён, значит произошёл swap "
                                       "указателей и ptr2 удалился по завершению функции");
    }

}

void MainWindow::on_pushButton_6_clicked()
{
    my_weak_ptr<circle> ptr2(circle_ptr);
    my_weak_ptr<circle> ptr3(circle_ptr);
    ui->textBrowser_2->insertPlainText("\nmy_weak_ptr<circle> ptr2(circle_ptr) \nmy_weak_ptr<circle> ptr3(circle_ptr)");
    ui->textBrowser_2->insertPlainText("\nptr3.owner_before(ptr2): " + QString::number(ptr3.owner_before(ptr2)));
    ui->textBrowser_2->insertPlainText("\nptr3.use_count(): " + QString::number(ptr3.use_count()));
    ptr3.reset();
    ui->textBrowser_2->insertPlainText("\nptr3.reset() -> ptr3.use_count(): " + QString::number(ptr3.use_count()));
}

