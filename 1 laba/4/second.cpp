#include "second.h"
#include "ui_second.h"

second::second(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::second)
{
    ui->setupUi(this);
    //da = new file();
    ui->lineEdit->setMaxLength(100);
    ui->lineEdit_2->setMaxLength(100);
    ui->lineEdit_3->setMaxLength(100);
    ui->lineEdit_4->setMaxLength(100);
    ui->lineEdit_5->setMaxLength(100);
    ui->lineEdit_6->setMaxLength(100);
    ui->lineEdit_7->setMaxLength(100);
    ui->lineEdit_8->setMaxLength(100);
}



second::~second()
{
    delete ui;
}

void second::writet()
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

    ui->text->setText(buf);
}


void second::on_pushButton_2_clicked()
{
    this->close();
    emit firstWindow();
}


void second::on_pushButton_clicked()
{
if(ui->lineEdit->text().size()>0){
    if(ui->lineEdit_2->text().size()>0){
        if(ui->lineEdit_3->text().size()>0){
            if(ui->lineEdit_4->text().size()>0){
                QDate day(QDate::fromString(ui->lineEdit_5->text(),"dd.MM.yyyy"));
                 if(day.isValid()){
                     QDate day2(QDate::fromString(ui->lineEdit_6->text(),"dd.MM.yyyy"));
                      if(day2.isValid()){
                          QDate day3(QDate::fromString(ui->lineEdit_7->text(),"dd.MM.yyyy"));
                           if(day3.isValid()){
                               if(storage.size()>2){
                               name_project.push_back(ui->lineEdit->text()+"\r\n");
                               work_of_project.push_back(ui->lineEdit_2->text()+"\r\n");
                               name_worker.push_back(ui->lineEdit_3->text()+"\r\n");
                               name_direct.push_back(ui->lineEdit_4->text()+"\r\n");
                               date_of_issue.push_back(QDate::fromString(ui->lineEdit_5->text(),"dd.MM.yyyy"));
                               deadline.push_back(QDate::fromString(ui->lineEdit_6->text(),"dd.MM.yyyy"));
                               date_delivery.push_back(QDate::fromString(ui->lineEdit_7->text(),"dd.MM.yyyy"));
                               sizee++;
                               write();
                               writet();
                               }
                               else ui->text->setText("Файл не выбран");
                           }
                           else ui->text->setText("Введите корректно \"Дата сдачи\"");
                      }
                      else ui->text->setText("Введите корректно \"Срок выполнения\"");
                 }
                 else ui->text->setText("Введите корректно \"Дата выдачи\"");
            }
            else ui->text->setText("Введите \"ФИО руководителя\"");
        }
        else ui->text->setText("Введите \"ФИО исполнителя\"");
    }
    else ui->text->setText("Введите \"Задание в рамках проекта\"");
}
else ui->text->setText("Введите \"Название проекта\"");
}

void second::on_pushButton_3_clicked()
{
    if(storage.size()>2){
    if(ui->lineEdit_8->text().toInt()>0 && ui->lineEdit_8->text().toInt()<sizee){
    delet(ui->lineEdit_8->text().toInt());
    }
    write();
    writet();
    }
    else ui->text->setText("Файл не выбран");
}


void second::on_pushButton_4_clicked()
{
    store();
    if(read()) writet();
    else ui->text->setText("Неверный файл");
}

