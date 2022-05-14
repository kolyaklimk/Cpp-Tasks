#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    t=new tree();

    ui->textBrowser->setLineWrapMode(QTextEdit::NoWrap);
    ui->lineEdit->setMaxLength(20);
    ui->lineEdit_2->setValidator(new QIntValidator(0, 999999, this));
    ui->lineEdit_5->setValidator(new QIntValidator(0, 999999, this));
    ui->lineEdit_7->setValidator(new QIntValidator(0, 999999, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setWidget()
{
    if(!t->empty()){
    ui->treeWidget->clear();
    ui->textBrowser->setText( t->Creat());
    ui->lineEdit_3->setText(QString::number(t->Min_Key()));
    ui->lineEdit_4->setText(QString::number(t->Max_Key()));
    t->allprintTree(ui->treeWidget);
    }
}

void MainWindow::on_pushButton_clicked()
{
    t->insert(ui->lineEdit->text(),ui->lineEdit_2->text().toInt());
    setWidget();
}

void MainWindow::on_pushButton_2_clicked()
{
    t->insert("Random",qrand());
    setWidget();
}

void MainWindow::on_pushButton_3_clicked()
{
    if(!t->empty()){
    ui->lineEdit_6->setText(t->search(ui->lineEdit_5->text().toInt()));
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    if(!t->empty()){
    t->Del(ui->lineEdit_7->text().toInt());
    setWidget();
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    if(!t->empty()){
    t->make_balance();
    setWidget();
}
}


void MainWindow::on_pushButton_6_clicked()
{
    if(!t->empty()){
    ui->textBrowser->setText(t->printOrd(1));
}
}


void MainWindow::on_pushButton_8_clicked()
{
    if(!t->empty()){
    ui->textBrowser->setText(t->printOrd(2));
}
}


void MainWindow::on_pushButton_7_clicked()
{
    if(!t->empty()){
    ui->textBrowser->setText(t->printOrd(3));
}
}


void MainWindow::on_pushButton_9_clicked()
{
    if(!t->empty()){
        setWidget();
}

}

