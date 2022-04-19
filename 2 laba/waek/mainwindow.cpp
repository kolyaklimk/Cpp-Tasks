#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel(0,2,this);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList lst;
    lst << "Рандом" << "use_count" << "expired" << "Owner_before" ;
    ui->tableWidget->setHorizontalHeaderLabels(lst);
    l=new int;
    lem.push_back(new int);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::reform(int amount)
{
    for(int a=0; a<amount; a++) ui->tableWidget->removeRow(0);
    for(int aa=1; aa<=amount; aa++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(qrand() % 100)));
        if(ui->tableWidget->rowCount()>1){
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,
        new QTableWidgetItem(QString::number(lem[lem.size()-2].owner_before(lem[lem.size()-1]))));
        }
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(lem[lem.size()-1].use_count())));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(QString::number(lem[lem.size()-1].expired())));
    }
}

void MainWindow::on_add_clicked()
{
    if(ui->tableWidget->rowCount()<10){
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    lem.push_back(lem[0]);
    lem[lem.size()-1]=lem[0];
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(qrand() % 100)));
    if(ui->tableWidget->rowCount()>1){
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,
    new QTableWidgetItem(QString::number(lem[lem.size()-2].owner_before(lem[lem.size()-1]))));
    }
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(lem[lem.size()-1].use_count())));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(QString::number(lem[lem.size()-1].expired())));
    }
    reform(ui->tableWidget->rowCount());
}


void MainWindow::on_delete_2_clicked()
{
    if(ui->tableWidget->rowCount()>0){
    lem.pop_back();
    ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
    //reform(ui->tableWidget->rowCount());
    }
}

void MainWindow::on_add_2_clicked()
{
 if(!shared.size()){
     my_shared_ptr<int> buf(new int(4));
     shared.push_back(buf);
     //reform(ui->tableWidget->rowCount());
 }
 else{
    shared.push_back(shared[0]);
    //reform(ui->tableWidget->rowCount());

 }
 lem[0] = shared[0];
}


void MainWindow::on_delete_3_clicked()
{
    if(shared.size()>0){
        shared.pop_back();
        //reform(ui->tableWidget->rowCount());
    }
}


/*void MainWindow::on_reset_clicked()
{
lem[ui->tableWidget->rowCount()-1].reset();
if(ui->tableWidget->rowCount()>1){
ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,
new QTableWidgetItem(QString::number(lem[lem.size()-2].owner_before(lem[lem.size()-1]))));
}
ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(lem[lem.size()-1].use_count())));
ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(QString::number(lem[lem.size()-1].expired())));
}
*/

