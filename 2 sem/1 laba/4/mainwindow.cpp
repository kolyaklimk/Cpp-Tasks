#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //da = new file();

    // Инициализируем второе окно
    sWin = new second();
    // подключаем к слоту запуска главного окна по кнопке во втором окне
    connect(sWin, &second::firstWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writte()
{
    QString buf;
    for(int i=0;i<sizee;i++){
    buf+="№"+QString::number(i)+"\nНазвание проекта: " + name_project[i];
    buf+="Задание в рамках проекта: " + work_of_project[i];
    buf+="ФИО исполнителя: " + name_worker[i];
    buf+="ФИО руководителя: " + name_direct[i];
    buf+="Дата выдачи: " + date_of_issue[i].toString(Qt::SystemLocaleShortDate) + '\n';
    buf+="Срок выполнения: " + deadline[i].toString(Qt::SystemLocaleShortDate) + '\n';
    buf+="Дата сдачи: " + date_delivery[i].toString(Qt::SystemLocaleShortDate) + "\n\n";
    }

    ui->textBrowser->setText(buf);
}


void MainWindow::on_pushButton_clicked()
{
    sWin->show();
    this->close();
}


void MainWindow::on_pushButton_7_clicked()
{
    QString buf,buf2;
    switch (swit) {
    case 1:
        for (int i=0;i<sizee;i++) {
            if(ui->comboBox->currentText() == name_direct[i]){
                buf=name_direct[i];
                for(int q=0;q<sizee;q++)
                    if(name_direct[q]==buf)
                        buf2+=name_project[q];
                        ui->textBrowser->setText(buf2);
                break;
            }
        }
    break;
    case 2:
        for (int i=0;i<sizee;i++) {
            if(ui->comboBox->currentText() == name_worker[i]){
                buf=name_worker[i];
                for(int q=0;q<sizee;q++)
                    if(name_worker[q]==buf)
                        buf2+=work_of_project[q];
                        ui->textBrowser->setText(buf2);
                break;
            }
        }
    break;
    case 3:
        for (int i=0;i<sizee;i++) {
            if(ui->comboBox->currentText() == name_project[i]){
                buf=name_project[i];
                for(int q=0;q<sizee;q++)
                    if(name_project[q]==buf)
                        buf2+=name_worker[q];
                        ui->textBrowser->setText(buf2);
                break;
            }
        }
    break;
    case 4:
        for (int i=0;i<sizee;i++) {
            if(ui->comboBox->currentText() == name_worker[i]){
                ui->textBrowser->setText("Название проекта: " + name_project[i] +
                                         "Задание в рамках проекта: " + work_of_project[i] +
                                         "ФИО исполнителя: " + name_worker[i] +
                                         "ФИО руководителя: " + name_direct[i] +
                                         "Дата выдачи: " + date_of_issue[i].toString(Qt::SystemLocaleShortDate) + '\n' +
                                         "Срок выполнения: " + deadline[i].toString(Qt::SystemLocaleShortDate) + '\n' +
                                         "Дата сдачи: " + date_delivery[i].toString(Qt::SystemLocaleShortDate));
                break;
            }
        }
    break;
    }
}

void MainWindow::on_radioButton_clicked()
{
    swit=1;
    ui->comboBox->clear();
    QVector<QString> buf;
    if(sizee){
        buf.push_back(name_direct[0]);
        for (int i=1;i<sizee;i++){
            bool b=0;
            for(int q=0;q<buf.size();q++){
                if(buf[q]==name_direct[i]) b=1;
            }
            if(!b) buf.push_back(name_direct[i]);
        }
        for(int q=0;q<buf.size();q++){
        ui->comboBox->addItem(buf[q]);
        }
    }
}

void MainWindow::on_radioButton_2_clicked()
{
    swit=2;
    ui->comboBox->clear();
    QVector<QString> buf;
    if(sizee){
        buf.push_back(name_worker[0]);
        for (int i=1;i<sizee;i++){
            bool b=0;
            for(int q=0;q<buf.size();q++){
                if(buf[q]==name_worker[i]) b=1;
            }
            if(!b) buf.push_back(name_worker[i]);
        }
        for(int q=0;q<buf.size();q++){
        ui->comboBox->addItem(buf[q]);
        }
    }
}

void MainWindow::on_radioButton_3_clicked()
{
    swit=3;
    ui->comboBox->clear();
    QVector<QString> buf;
    if(sizee){
        buf.push_back(name_project[0]);
        for (int i=1;i<sizee;i++){
            bool b=0;
            for(int q=0;q<buf.size();q++){
                if(buf[q]==name_project[i]) b=1;
            }
            if(!b) buf.push_back(name_project[i]);
        }
        for(int q=0;q<buf.size();q++){
        ui->comboBox->addItem(buf[q]);
        }
    }
}

void MainWindow::on_radioButton_4_clicked()
{
    swit=4;
    ui->comboBox->clear();
    QVector<QString> buf;
    if(sizee){
        for (int i=1;i<sizee;i++){
            if(date_delivery[i] > deadline[i]) buf.push_back (name_worker[i]);
        }
        for(int q=0;q<buf.size();q++){
        ui->comboBox->addItem(buf[q]);
        }
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    this->close();
}


void MainWindow::on_pushButton_2_clicked()
{
    store();
    if(read()){
    writte();
    }
    else ui->textBrowser->setText("Неверный файл");
}


void MainWindow::on_pushButton_4_clicked()
{
    write();
}


void MainWindow::on_pushButton_3_clicked()
{
    read();
    sort();
    writte();
}


void MainWindow::on_pushButton_5_clicked()
{
    store_save();
    write();
}

