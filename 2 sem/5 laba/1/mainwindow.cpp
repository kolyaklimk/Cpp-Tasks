#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    t = new task<int>;

    ui->listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::listBox()
{
    ui->listWidget->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    if(!t->empty()){
    for(int a=0; a<t->size();a++){
        ui->listWidget->addItem(QString::number(t->front()));
        if(t->front()== t->min() || t->front()== t->max()) ui->listWidget->item(a)->setBackgroundColor(Qt::red);
        t->push(t->front());
        t->pop();
    }
    ui->lineEdit->setText(QString::number(t->min()));
    ui->lineEdit_2->setText(QString::number(t->max()));
    }
}



void MainWindow::on_pushButton_clicked()
{
    if(t->size()<12) t->push(qrand());
    listBox();
}


void MainWindow::on_pushButton_2_clicked()
{
    if(!t->empty()) t->pop();
    listBox();
}


void MainWindow::on_pushButton_3_clicked()
{
    if(!t->empty()) t->del();
    listBox();
}

