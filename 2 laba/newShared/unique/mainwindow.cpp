#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel(0,2,this);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList lst;
    lst << "Рандом" << "operator_null";
    ui->tableWidget->setHorizontalHeaderLabels(lst);
    my_unique_ptr<int> temp(new int(404));
    uniq = temp;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_clicked()
{
    if(ui->tableWidget->rowCount()<10){
        if(!ui->tableWidget->rowCount()){
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(qrand() % 100)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(uniq.operator_null())));
        }
        else{
        my_unique_ptr<int> temp(uniq);
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(qrand() % 100)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(temp.operator_null())));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-2,1,new QTableWidgetItem(QString::number(uniq.operator_null())));
        uniq.swap(temp);
        }
    }
}

void MainWindow::on_delete_2_clicked()
{
    if(ui->tableWidget->rowCount()>0){
        ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(uniq.operator_null())));

    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(ui->tableWidget->rowCount()){
        uniq.get_deleter();
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(uniq.operator_null())));
        uniq.reset(new int(404));
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if(ui->tableWidget->rowCount()){
        my_unique_ptr<int> temp(uniq.release());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(uniq.operator_null())));
        uniq.reset(new int(404));
        uniq.swap(temp);
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    if(ui->tableWidget->rowCount()){
        uniq.reset(new int(404));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(uniq.operator_null())));
    }

}

