#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel(0,2,this);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->setValidator(new QIntValidator(1,10,this));
    ui->lineEdit_2->setValidator(new QIntValidator(1,10,this));
    ui->lineEdit_3->setValidator(new QIntValidator(1,10,this));

    QStringList lst;
    lst << "Рандом" << "get_count" << "Unique" << "Owner_before"  << "operator_null";
    ui->tableWidget->setHorizontalHeaderLabels(lst);
    l=new elem;
    lem.push_back(*l);
    lem[0].a = new elem;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_add_clicked()
{
    if(ui->tableWidget->rowCount()<10){
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(QString::number(lem[lem.size()-1].a.unique())));
    lem.push_back(*l);
    lem[lem.size()-1].a=lem[0].a;
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(qrand() % 100)));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(lem[0].a.get_count()-1)));
    if(ui->tableWidget->rowCount()>1){
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,
    new QTableWidgetItem(QString::number(lem[lem.size()-2].a.owner_before(lem[lem.size()-1].a))));
    }
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(QString::number(lem[lem.size()-1].a.operator_null())));
    }
}


void MainWindow::on_delete_2_clicked()
{
    if(ui->tableWidget->rowCount()>0){
    if(ui->tableWidget->item(ui->tableWidget->rowCount()-1,4)->text().toInt()) lem[ui->tableWidget->rowCount()-1].a = lem[0].a;
    lem.pop_back();
    ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
    }
}


void MainWindow::on_pushButton_clicked()
{
    if(ui->lineEdit->text().toInt()>0 && ui->lineEdit->text().toInt()<lem[0].a.get_count()){
        if(ui->lineEdit_2->text().toInt()>0 && ui->lineEdit_2->text().toInt()<lem[0].a.get_count()){
            if(ui->lineEdit->text().toInt()!=ui->lineEdit_2->text().toInt()){
                my_shared_ptr<int> a(new int()), b(new int());
                ui->textBrowser->clear();
                *a = ui->tableWidget->item(ui->lineEdit->text().toInt()-1,0)->text().toInt();
                *b = ui->tableWidget->item(ui->lineEdit_2->text().toInt()-1,0)->text().toInt();
                ui->textBrowser->insertPlainText("a = " + QString::number(*a) + " b = " + QString::number(*b));
                ui->textBrowser->insertPlainText("\na.swap(b)");
                a.swap(b);
                ui->tableWidget->item(ui->lineEdit->text().toInt()-1,0)->setText(QString::number(*a));
                ui->tableWidget->item(ui->lineEdit_2->text().toInt()-1,0)->setText(QString::number(*b));
                ui->textBrowser->insertPlainText("\na = " + QString::number(*a) + " b = " + QString::number(*b));
                return;
            }
        }
    }
    ui->textBrowser->setText("Неправильный ввод");
}

void MainWindow::reform(int amount)
{
    for(int a=0; a<amount; a++) ui->tableWidget->removeRow(0);
    for(int aa=1; aa<=amount; aa++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(QString::number(lem[aa].a.unique())));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(qrand() % 100)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(QString::number(lem[0].a.get_count()-1)));
        if(ui->tableWidget->rowCount()>1){
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,
        new QTableWidgetItem(QString::number(lem[aa-1].a.owner_before(lem[aa].a))));
        }
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(QString::number(lem[aa].a.operator_null())));
    }
}




void MainWindow::on_pushButton_2_clicked()
{
    if(ui->lineEdit_3->text().toInt()>0 && ui->lineEdit_3->text().toInt()<lem[0].a.get_count()){
        if(!lem[ui->lineEdit_3->text().toInt()].a.operator_null()){
            lem[ui->lineEdit_3->text().toInt()].a.reset();
            reform(ui->tableWidget->rowCount());
        }
    }
    else ui->textBrowser->setText("Неправильный ввод");
}

