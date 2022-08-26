#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    t = new task;
    creatTable();
    ui->lineEdit_4->setValidator(new QIntValidator(0, 999999, this));
    ui->lineEdit_5->setValidator(new QIntValidator(0, 999999, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::creatTable()
{
    t->print(ui->textBrowser);
    ui->lineEdit->setText(QString::number(t->Size()));
    ui->lineEdit_2->setText(QString::number(t->count()));
    ui->lineEdit_3->setText(QString::number(t->empty()));
}


void MainWindow::on_pushButton_clicked()
{
    t->push(qrand());
    creatTable();
}

void MainWindow::on_pushButton_2_clicked()
{
    t->erase(ui->lineEdit_4->text().toInt());
    creatTable();
    //sleep(1);
}

void MainWindow::on_pushButton_4_clicked()
{
    creatTable();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->textBrowser->setText(t->at(ui->lineEdit_5->text().toInt()));
}


void MainWindow::on_pushButton_5_clicked()
{
    t->clear();
    creatTable();
}


void MainWindow::on_pushButton_6_clicked()
{
    for(int a=0;a<15;){
        int q=rand() % 109 + (-37);
        if(q<=10 && q>=-10){
            a++;
            t->push(q);
        }
    }
    creatTable();
}


void MainWindow::on_pushButton_7_clicked()
{
        t->deleteMinus();
        creatTable();
}

