#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit->setMaxLength(20);
    ui->key_le->setValidator(new QIntValidator(0, 999999, this));
    ui->lineEdit_2->setValidator(new QIntValidator(0, 999999, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_tree()
{
    if(!tree.empty()){
ui->textEdit->setText(tree.dum());
    }
}


void MainWindow::on_add_clicked()
{
    tree.insert("rand",qrand());
    show_tree();
}


void MainWindow::on_delete_2_clicked()
{
    if(!tree.empty()){
    tree.erase(ui->key_le->text().toInt());
    show_tree();
    }
}


void MainWindow::on_make_balanced_clicked()
{
    if(!tree.empty()){
    tree.make_balanced();
    show_tree();
    }
}


void MainWindow::on_show_bykey_clicked()
{
    if(!tree.empty()){
    ui->data_le->setText(tree.find(ui->key_le->text().toInt()));
    }
}


void MainWindow::on_make_balanced_2_clicked()
{
    if(!tree.empty()){
    ui->data_le->setText(QString::number(tree.count_symbols()));
    }
}


void MainWindow::on_add_2_clicked()
{
    tree.insert(ui->lineEdit->text(),ui->lineEdit_2->text().toInt());
    show_tree();
}


void MainWindow::on_make_balanced_3_clicked()
{
    if(!tree.empty()){
    show_tree();
    }
}


void MainWindow::on_make_balanced_4_clicked()
{
    if(!tree.empty()){
    ui->textEdit->setText(tree.print(3));
    }

}


void MainWindow::on_make_balanced_5_clicked()
{
    if(!tree.empty()){
    ui->textEdit->setText(tree.print(2));
    }
}


void MainWindow::on_make_balanced_6_clicked()
{
    if(!tree.empty()){
    ui->textEdit->setText(tree.print(1));
    }
}

