#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    ui->number->setValidator(new QIntValidator(0, 999999, this));
    ui->number_2->setValidator(new QIntValidator(0, 999999, this));
    ui->number_3->setValidator(new QIntValidator(0, 999, this));
    ui->tarrif->setValidator(new QIntValidator(0, 999999, this));
    ui->hours->setValidator(new QIntValidator(0, 999, this));
    ui->fi->setMaxLength(100);
    ui->otc->setMaxLength(100);
    ui->nam->setMaxLength(100);

}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addInfo_Tail_clicked()
{
    if(storage!=nullptr){
        if(ui->number->text().size()>0){
            if(ui->fi->text().size()>0){
                if(ui->nam->text().size()>0){
                    if(ui->otc->text().size()>0){
                        if(ui->tarrif->text().size()>0){
                if(ui->hours->text().size()>0){
                    list.push_back(elem);
                    list[list.size()-1].number =ui->number->text();
                    list[list.size()-1].fi =ui->fi->text();
                    list[list.size()-1].nam = ui->nam->text();
                    list[list.size()-1].otc = ui->otc->text();
                    list[list.size()-1].tarrif = ui->tarrif->text();
                    list[list.size()-1].hours = ui->hours->text();
                     ui->textBrowser->clear();
                     for(int a=0; a<list.size(); a++){
                         ui->textBrowser->append("№" + QString::number(a+1));
                         ui->textBrowser->append("Табельный номер: " + list[a].number);
                         ui->textBrowser->append("Фамилия: " + list[a].fi);
                         ui->textBrowser->append("Имя: " + list[a].nam);
                         ui->textBrowser->append("Отчество: " + list[a].otc);
                         ui->textBrowser->append("Тариф: " + list[a].tarrif);
                         ui->textBrowser->append("Кол-во часов: " + list[a].hours+"\n\n");
                     }
                    }
                else ui->textBrowser->setText("Введите коректно количество проработтаных часов");
                }
                else ui->textBrowser->setText("Введите коректно Тариф");
                }
                        else ui->textBrowser->setText("Введите коректно число Отчество");
                        }
                else ui->textBrowser->setText("Введите коректно Имя");
                }
            else ui->textBrowser->setText("Введите коректно Вамилию");
            }
        else ui->textBrowser->setText("Введите коректно табельный номер");
    }
else ui->textBrowser->setText("Файл не открыт или не создан");
}

void MainWindow::on_addInfo_Head_clicked()
{
    if(storage!=nullptr){
        if(ui->number->text().size()>0){
            if(ui->fi->text().size()>0){
                if(ui->nam->text().size()>0){
                    if(ui->otc->text().size()>0){
                        if(ui->tarrif->text().size()>0){
                if(ui->hours->text().size()>0){
                    list.push_front(elem);
                    list[0].number =ui->number->text();
                    list[0].fi =ui->fi->text();
                    list[0].nam = ui->nam->text();
                    list[0].otc = ui->otc->text();
                    list[0].tarrif = ui->tarrif->text();
                    list[0].hours = ui->hours->text();
                     ui->textBrowser->clear();
                     for(int a=0; a<list.size(); a++){
                         ui->textBrowser->append("№" + QString::number(a+1));
                         ui->textBrowser->append("Табельный номер: " + list[a].number);
                         ui->textBrowser->append("Фамилия: " + list[a].fi);
                         ui->textBrowser->append("Имя: " + list[a].nam);
                         ui->textBrowser->append("Отчество: " + list[a].otc);
                         ui->textBrowser->append("Тариф: " + list[a].tarrif);
                         ui->textBrowser->append("Кол-во часов: " + list[a].hours+"\n\n");
                     }
                    }
                else ui->textBrowser->setText("Введите коректно количество проработтаных часов");
                }
                else ui->textBrowser->setText("Введите коректно Тариф");
                }
                        else ui->textBrowser->setText("Введите коректно число Отчество");
                        }
                else ui->textBrowser->setText("Введите коректно Имя");
                }
            else ui->textBrowser->setText("Введите коректно Вамилию");
            }
        else ui->textBrowser->setText("Введите коректно табельный номер");
    }
else ui->textBrowser->setText("Файл не открыт или не создан");

}


void MainWindow::on_out_clicked()
{
    if(storage!=nullptr){
        ui->textBrowser->clear();
        for(int a=0; a<list.size(); a++){
            ui->textBrowser->append("№" + QString::number(a+1));
            ui->textBrowser->append("Табельный номер: " + list[a].number);
            ui->textBrowser->append("Фамилия: " + list[a].fi);
            ui->textBrowser->append("Имя: " + list[a].nam);
            ui->textBrowser->append("Отчество: " + list[a].otc);
            ui->textBrowser->append("Тариф: " + list[a].tarrif);
            ui->textBrowser->append("Кол-во часов: " + list[a].hours+"\n\n");
        }
    }
else ui->textBrowser->setText("Файл не открыт или не создан");
}



void MainWindow::on_insert_clicked()
{

    if(storage!=nullptr){
        if(ui->number->text().size()>0){
            if(ui->fi->text().size()>0){
                if(ui->nam->text().size()>0){
                    if(ui->otc->text().size()>0){
                        if(ui->tarrif->text().size()>0){
                            if(ui->hours->text().size()>0){
                                if (ui->insertNumber->text().toInt()>0 && ui->insertNumber->text().toInt()<=list.size()+1){
                    int aa = ui->insertNumber->text().toInt()-1;
                    list.push_insert(aa,elem);
                    qDebug() << aa;
                    list[aa].number =ui->number->text();
                    list[aa].fi =ui->fi->text();
                    list[aa].nam = ui->nam->text();
                    list[aa].otc = ui->otc->text();
                    list[aa].tarrif = ui->tarrif->text();
                    list[aa].hours = ui->hours->text();
                     ui->textBrowser->clear();
                     for(int a=0; a<list.size(); a++){
                         ui->textBrowser->append("№" + QString::number(a+1));
                         ui->textBrowser->append("Табельный номер: " + list[a].number);
                         ui->textBrowser->append("Фамилия: " + list[a].fi);
                         ui->textBrowser->append("Имя: " + list[a].nam);
                         ui->textBrowser->append("Отчество: " + list[a].otc);
                         ui->textBrowser->append("Тариф: " + list[a].tarrif);
                         ui->textBrowser->append("Кол-во часов: " + list[a].hours+"\n\n");
                     }
                            }
                            else ui->textBrowser->setText("Неверное значение");
                    }
                else ui->textBrowser->setText("Введите коректно количество проработтаных часов");
                }
                else ui->textBrowser->setText("Введите коректно Тариф");
                }
                        else ui->textBrowser->setText("Введите коректно число Отчество");
                        }
                else ui->textBrowser->setText("Введите коректно Имя");
                }
            else ui->textBrowser->setText("Введите коректно Вамилию");
            }
        else ui->textBrowser->setText("Введите коректно табельный номер");
    }
else ui->textBrowser->setText("Файл не открыт или не создан");
}


void MainWindow::on_deleteAll_clicked()
{
    if(storage!=nullptr){
    while(list.size()!=0){
        list.deleteNum(0,elem);
    }
    ui->textBrowser->clear();
    }
else ui->textBrowser->setText("Файл не открыт или не создан");
}

void MainWindow::on_deletenumber_clicked()
{
    if(storage!=nullptr){
    if(ui->deleteNumber->text().toInt()>0 && ui->deleteNumber->text().toInt()<=list.size()){
            list.deleteNum(ui->deleteNumber->text().toInt(),elem);
            ui->textBrowser->clear();
            for(int a=0; a<list.size(); a++){
                ui->textBrowser->append("№" + QString::number(a+1));
                ui->textBrowser->append("Табельный номер: " + list[a].number);
                ui->textBrowser->append("Фамилия: " + list[a].fi);
                ui->textBrowser->append("Имя: " + list[a].nam);
                ui->textBrowser->append("Отчество: " + list[a].otc);
                ui->textBrowser->append("Тариф: " + list[a].tarrif);
                ui->textBrowser->append("Кол-во часов: " + list[a].hours+"\n\n");
            }
    }
    else ui->textBrowser->setText("Введите коректно № удаления");
    }
else ui->textBrowser->setText("Файл не открыт или не создан");
}



void MainWindow::on_pushButton_clicked()
{
    if(storage!=nullptr){
        ui->textBrowser->clear();
        for(int a=0;a<list.size();a++){
            if(list[a].tarrif.toUInt()<=ui->number_2->text().toUInt()){
                ui->textBrowser->append("Фамилия: " + list[a].fi);
                ui->textBrowser->append("Имя: " + list[a].nam);
                ui->textBrowser->append("Отчество: " + list[a].otc);
                ui->textBrowser->append("Тариф: " + list[a].tarrif+"\n\n");
            }
        }
    if(ui->textBrowser->toPlainText().size()<5) ui->textBrowser->setText("Введите коректные данные поиска");
    }
else ui->textBrowser->setText("Файл не открыт или не создан");
}


void MainWindow::on_pushButton_3_clicked()
{
    if(storage!=nullptr){
        ui->textBrowser->clear();
        for(int a=0;a<list.size();a++){
            if(list[a].hours.toUInt()>=ui->number_3->text().toUInt()){
                ui->textBrowser->append("Фамилия: " + list[a].fi);
                ui->textBrowser->append("Имя: " + list[a].nam);
                ui->textBrowser->append("Отчество: " + list[a].otc);
                ui->textBrowser->append("Кол-во часов: " + list[a].hours+"\n\n");
            }
        }
    if(ui->textBrowser->toPlainText().size()<5) ui->textBrowser->setText("Введите коректные данные поиска");
    }
else ui->textBrowser->setText("Файл не открыт или не создан");
}

void MainWindow::on_pushButton_2_clicked()
{
    if(storage!=nullptr){
        ui->textBrowser->clear();
        for(int a=0;a<list.size();a++){
            if(list[a].hours.toUInt()>=144){
                ui->textBrowser->append("Фамилия: " + list[a].fi);
                ui->textBrowser->append("Имя: " + list[a].nam);
                ui->textBrowser->append("Отчество: " + list[a].otc);
                ui->textBrowser->append("Кол-во часов: " + list[a].hours+"\n\n");
            }
        }
    }
else ui->textBrowser->setText("Файл не открыт или не создан");

}


void MainWindow::on_open_clicked()
{
    while(list.size()!=0){
        list.deleteNum(0,elem);
    }
    QString buf[6];
    storage = QFileDialog::getOpenFileName(0,"Выберете файл","","*txt");
    QFile text(storage);
    text.open(QIODevice::ReadOnly);
    while (!text.atEnd()){
        buf[0]=text.readLine();
        if(buf[0][buf[0].size()-1]=='\n') buf[0].remove(buf[0].size()-1,1);
        if(buf[0].size()>7 || buf[0] == "\r\n"){
            ui->textBrowser->setText("Неверный файл");
            while(list.size()!=0){
                list.deleteNum(0,elem);
            }
            return;
        }

        buf[1]=text.readLine();
        if(buf[1][buf[1].size()-1]=='\n') buf[1].remove(buf[1].size()-1,1);
        if(buf[1].size()>100 || buf[1] == "\r\n"){
            ui->textBrowser->setText("Неверный файл");
            while(list.size()!=0){
                list.deleteNum(0,elem);
            }
            return;
        }


        buf[2]=text.readLine();
        if(buf[2][buf[2].size()-1]=='\n') buf[2].remove(buf[2].size()-1,1);
        if(buf[2].size()>100 || buf[2] == "\r\n"){
            ui->textBrowser->setText("Неверный файл");
            while(list.size()!=0){
                list.deleteNum(0,elem);
            }
            return;
        }


        buf[3]=text.readLine();
        if(buf[3][buf[3].size()-1]=='\n') buf[3].remove(buf[3].size()-1,1);
        if(buf[3].size()>100 || buf[0] == "\r\n"){
            ui->textBrowser->setText("Неверный файл");
            while(list.size()!=0){
                list.deleteNum(0,elem);
            }
            return;
        }


        buf[4]=text.readLine();
        if(buf[4][buf[4].size()-1]=='\n') buf[4].remove(buf[4].size()-1,1);
        if(buf[4].size()>7 || buf[4] == "\r\n"){
            ui->textBrowser->setText("Неверный файл");
            while(list.size()!=0){
                list.deleteNum(0,elem);
            }
            return;
        }

        buf[5]=text.readLine();
        if(buf[5][buf[5].size()-1]=='\n') buf[5].remove(buf[5].size()-1,1);
        if(buf[5].size()>4 || buf[5] == "\r\n"){
            ui->textBrowser->setText("Неверный файл");
            while(list.size()!=0){
                list.deleteNum(0,elem);
            }
            return;
        }
        text.readLine();
        list.push_back(elem);
        list[list.size()-1].number =buf[0];
        list[list.size()-1].fi =buf[1];
        list[list.size()-1].nam = buf[2];
        list[list.size()-1].otc = buf[3];
        list[list.size()-1].tarrif = buf[4];
        list[list.size()-1].hours = buf[5];
        qDebug() << list[list.size()-1].hours;
    }
    text.close();
    ui->textBrowser->setText("Файл открыт");
}

void MainWindow::on_create_clicked()
{
    storage = QFileDialog::getSaveFileName(0,"Выберете файл","","*.txt");
    QFile text(storage);
    text.open(QIODevice::WriteOnly );
    QTextStream writeStream(&text);
    for(int a=0;a<list.size();a++){
        writeStream << list[a].number +
                       '\n' +list[a].fi +
                       '\n' +list[a].nam +
                       '\n' +list[a].otc +
                       '\n' +list[a].tarrif +
                       '\n' +list[a].hours + "\n\n";
    }
    text.close();
}

void MainWindow::on_save_clicked()
{
    if(storage!=nullptr){
    QFile text(storage);
    text.open(QIODevice::WriteOnly );
    QTextStream writeStream(&text);
    for(int a=0;a<list.size();a++){
        writeStream << list[a].number +
                       '\n' +list[a].fi +
                       '\n' +list[a].nam +
                       '\n' +list[a].otc +
                       '\n' +list[a].tarrif +
                       '\n' +list[a].hours + "\n\n";
    }
    text.close();
    }
else ui->textBrowser->setText("Файл не открыт или не создан");
}


