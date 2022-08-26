#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    char* c=new char[ui->lineEdit->text().size()+1];
    for(int a=0;a<ui->lineEdit->text().size();a++){
        c[a]=ui->lineEdit->text().at(a).toLatin1();
    }
    c[ui->lineEdit->text().size()] = '\0';
    str.setText(c);
    ui->textBrowser->setText(str.getText());
    delete[] c;
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->textBrowser_2->setText(QString::number(str.getLength()));
}


void MainWindow::on_pushButton_4_clicked()
{
    if(ui->lineEdit->text().size()<7){
    str.setLength(ui->lineEdit->text().toInt());
    ui->textBrowser->setText(str.getText());
    }
    else ui->textBrowser_2->setText("error");
}


void MainWindow::on_pushButton_5_clicked()
{
    char* c=new char[ui->lineEdit->text().size()+1];
    for(int a=0;a<ui->lineEdit->text().size();a++){
        c[a]=ui->lineEdit->text().at(a).toLatin1();
    }
    c[ui->lineEdit->text().size()] = '\0';
    MyString buf;
    buf.setText(c);
    str.add(buf);
    ui->textBrowser->setText(str.getText());
    delete[] c;
}


void MainWindow::on_pushButton_clicked()
{
    if(ui->lineEdit->text().toUInt()-1<str.size() && ui->lineEdit->text().toInt()-1>=0){
        ui->textBrowser_2->setText(QChar(str.at(ui->lineEdit->text().toUInt()-1)));
    }
    else ui->textBrowser_2->setText("error");
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->textBrowser_2->setText(QChar(str.back()));
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->textBrowser_2->setText(QChar(str.front()));

}


void MainWindow::on_pushButton_8_clicked()
{
    char* c=new char[ui->lineEdit->text().size()+1];
    for(int a=0;a<ui->lineEdit->text().size();a++){
        c[a]=ui->lineEdit->text().at(a).toLatin1();
    }
    c[ui->lineEdit->text().size()] = '\0';
    MyString buf;
    buf.setText(c);
    ui->textBrowser_2->setText(QVariant(str.compare(buf)).toString());
    delete[] c;
}


void MainWindow::on_pushButton_9_clicked()
{
    char* c=new char[ui->lineEdit->text().size()+1];
    for(int a=0;a<ui->lineEdit->text().size();a++){
        c[a]=ui->lineEdit->text().at(a).toLatin1();
    }
    c[ui->lineEdit->text().size()] = '\0';
    MyString buf;
    buf.setText(c);
    str.append(buf);
    ui->textBrowser->setText(str.getText());
    delete[] c;
}


void MainWindow::on_pushButton_10_clicked()
{
    str.clear();
    ui->textBrowser->setText(str.getText());
    ui->textBrowser->clear();
}


void MainWindow::on_pushButton_11_clicked()
{
    str.push_back(ui->lineEdit->text().at(0).toLatin1());
    ui->textBrowser->setText(str.getText());
}


void MainWindow::on_pushButton_12_clicked()
{
    str.pop_back();
    ui->textBrowser->setText(str.getText());

}


void MainWindow::on_pushButton_13_clicked()
{
    ui->textBrowser_2->setText(QString::number(str.capacity()));
}


void MainWindow::on_pushButton_14_clicked()
{
    ui->textBrowser_2->setText(QString::number(str.size()));
}


void MainWindow::on_pushButton_15_clicked()
{
    if(ui->lineEdit->text().size()<7){
    str.resize(ui->lineEdit->text().toInt(),'\0');
    ui->textBrowser->setText(str.getText());
    }
    else ui->textBrowser_2->setText("error");

}

