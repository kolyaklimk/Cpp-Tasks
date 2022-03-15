#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    da = new Date();
    model = new QStandardItemModel(0,3,this);
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //запрет на изменения таблицы
    model->setHeaderData(0,Qt::Horizontal, "Дата");
    model->setHeaderData(1,Qt::Horizontal, "След. день");
    model->setHeaderData(2,Qt::Horizontal, "Разница(дни)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::table(){
    delete model;
    model = new QStandardItemModel(da->strok,3,this);
    ui->tableView->setModel(model);

    QModelIndex index;
    for(int col=0;col<da->strok;col++){
    index = model->index(col,0);
    model->setData(index,da->dat[col]);
    }
    for(int col=0;col<da->strok;col++){
    index = model->index(col,1);
    model->setData(index,da->NextDay(da->dat[col]));
    }
    for(int col=0;col<da->strok-1;col++){
    index = model->index(col,2);
    model->setData(index,da->raznica(da->dat[col],da->dat[col+1]));
    }
}
bool Date::data()//загрузка из файла
{
    QString buf,line;
    bool v=1;
    QDate day;
    QFile file(storage);
    file.open(QIODevice::ReadOnly);
    //buf=file.readLine();
    //if(buf.toInt()==12345){
      //  dat.clear();
        //strok=0;
    while (!file.atEnd()) {
        buf=file.readLine();
        buf.remove(10,2);
        day = QDate::fromString(buf,"dd.MM.yyyy");
        if(!day.isValid()) return 0;
        dat.push_back(buf);
        strok++;
    //}
    }
    //else v=0;
    file.close();
    return v;
}

void Date::store()
{
//if (QFileDialog::getOpenFileName(0,"Выберете файл","","*txt") == "") return;
storage = QFileDialog::getOpenFileName(0,"Выберете файл","","*txt");
}

QString Date::NextDay(QString day){
    QDate dat = QDate::fromString(day,"dd.MM.yyyy");
    return dat.addDays(1).toString(Qt::SystemLocaleShortDate);
}

int Date::raznica(QString day1,QString day2){
    QDate d1 = QDate::fromString(day1,"dd.MM.yyyy");
    QDate d2 = QDate::fromString(day2,"dd.MM.yyyy");
    return fabs(d1.daysTo(d2));
}

QString Date::PreviousDay(QString day)
{
    QDate dat = QDate::fromString(day,"dd.MM.yyyy");
    return dat.addDays(-1).toString(Qt::SystemLocaleShortDate);
}

bool Date::IsLeap(QString day){
    day.remove(0,6);
    return QDate::isLeapYear(day.toInt());
}

short Date::WeekNumber(QString day){
    QString buf=day;
    buf.remove(0,6);
    buf="01.01."+buf;
    QDate d1 = QDate::fromString(day,"dd.MM.yyyy");
    QDate d2 = QDate::fromString(buf,"dd.MM.yyyy");
    return fabs(d1.daysTo(d2))/7;
}

int Date::DaysTillYourBithday(QString day){
    this->bithdaydate=day;
    QString d2s=QDate::currentDate().toString(Qt::SystemLocaleShortDate);
    day.remove(6,4);
    d2s.remove(0,6);
    day +=d2s;
    QDate d1 = QDate::fromString(day,"dd.MM.yyyy");
    QDate d2 = QDate::currentDate();
    if(d1>d2) return d2.daysTo(d1);
    else return d2.daysTo(d1.addYears(1));
}

int Date::Duration(QString day)
{
    QDate d1 = QDate::fromString(day,"dd.MM.yyyy");
    QDate d2 = QDate::currentDate();
    return fabs(d2.daysTo(d1));

}

void MainWindow::on_tomorrow_clicked()
{
    if(ui->lineEdit->text().toInt()<da->strok+1 && ui->lineEdit->text().toInt()>0){
        ui->textBrowser->setText("Выбрано: " + da->dat[ui->lineEdit->text().toInt()-1]
                + "\nСледующий день: " +da->NextDay(da->dat[ui->lineEdit->text().toInt()-1]));
    }
    else ui->textBrowser->setText("Неверное значение");
}

void MainWindow::on_yesterday_clicked()
{
    if(ui->lineEdit->text().toInt()<da->strok+1 && ui->lineEdit->text().toInt()>0){
        ui->textBrowser->setText("Выбрано: " + da->dat[ui->lineEdit->text().toInt()-1]
                + "\nПредыдущий день: " +da->PreviousDay(da->dat[ui->lineEdit->text().toInt()-1]));
    }
    else ui->textBrowser->setText("Неверное значение");
}


void MainWindow::on_higher_year_clicked()
{
    if(ui->lineEdit->text().toInt()<da->strok+1 && ui->lineEdit->text().toInt()>0){
        QString dda;
        if(da->IsLeap(da->dat[ui->lineEdit->text().toInt()-1])) dda="Да";
        else dda="Нет";
        ui->textBrowser->setText("Выбрано: " + da->dat[ui->lineEdit->text().toInt()-1]
                + "\nВисокосный: " + dda);
    }
    else ui->textBrowser->setText("Неверное значение");
}


void MainWindow::on_Weeks_clicked()
{
    if(ui->lineEdit->text().toInt()<da->strok+1 && ui->lineEdit->text().toInt()>0){
        ui->textBrowser->setText("Выбрано: " + da->dat[ui->lineEdit->text().toInt()-1]
                + "\nКоличество недель в году для текущей даты: " + QString::number(da->WeekNumber(da->dat[ui->lineEdit->text().toInt()-1])));
    }
    else ui->textBrowser->setText("Неверное значение");
}


void MainWindow::on_days_to_birsd_clicked()
{
 QDate day(QDate::fromString(ui->lineEdit_2->text(),"dd.MM.yyyy"));
 if(!day.isValid() || day>QDate::currentDate()) ui->textBrowser->setText("Неверное значение");
 else ui->textBrowser->setText("Дата рождения: " + ui->lineEdit_2->text()+
                               "\nДней до дня рождения: " + QString::number(da->DaysTillYourBithday(ui->lineEdit_2->text())));
}


void MainWindow::on_pushButton_clicked()
{
    if(ui->lineEdit->text().toInt()<da->strok+1 && ui->lineEdit->text().toInt()>0){
        ui->textBrowser->setText("Выбрано: " + da->dat[ui->lineEdit->text().toInt()-1]
                + "\nСегодняшняя дата: " + QDate::currentDate().toString(Qt::SystemLocaleShortDate)
                + "\nКоличество дней между текущей и данной датой: " + QString::number(da->Duration(da->dat[ui->lineEdit->text().toInt()-1])));
    }
    else ui->textBrowser->setText("Неверное значение");
}


void MainWindow::on_change_clicked()
{
    if(ui->lineEdit->text().toInt()<da->strok+1 && ui->lineEdit->text().toInt()>0){
        QDate day(QDate::fromString(ui->lineEdit_3->text(),"dd.MM.yyyy"));
        if(!day.isValid()) ui->textBrowser->setText("Неверное значение");
        else{
            da->dat[ui->lineEdit->text().toInt()-1] = ui->lineEdit_3->text();

            QFile file(da->storage);
            file.open(QIODevice::WriteOnly);
            QTextStream writeStream(&file);
            //writeStream << "12345\r\n";
            for (int i=0;i<da->strok;i++){
                writeStream << da->dat[i];
                if(i!=da->strok-1) writeStream << "\n";
            }
            file.close();
            table();
        }
    }
    else ui->textBrowser->setText("Неверное значение");
}


void MainWindow::on_delete_2_clicked()
{
    if(ui->lineEdit->text().toInt()<da->strok+1 && ui->lineEdit->text().toInt()>0){
        QFile file(da->storage);
        if (ui->lineEdit->text().toInt()==da->strok+6) file.open(QIODevice::Append | QIODevice::Text);
        else file.open(QIODevice::WriteOnly);
        for(int i=ui->lineEdit->text().toInt()-1;i<da->strok-1;i++){
        da->dat[i+1]=da->dat[i];
        }
        da->dat.pop_back();
        da->strok--;
        QTextStream writeStream(&file);
        //writeStream << "12345\r\n";
        for (int i=0;i<da->strok;i++){
            writeStream << da->dat[i];
            if(i!=da->strok-1) writeStream << "\n";
        }
        file.close();
        model->removeRows(ui->lineEdit->text().toInt()-1,1);
    }
    else ui->textBrowser->setText("Неверное значение");
}


void MainWindow::on_change_2_clicked()
{
    if(ui->lineEdit_5->text().toInt()<da->strok+2 && ui->lineEdit_5->text().toInt()>0){
        QDate day(QDate::fromString(ui->lineEdit_4->text(),"dd.MM.yyyy"));
        if(!day.isValid()) ui->textBrowser->setText("Неверное значение");
        else{
            da->dat.push_back("");
            for(int i=++da->strok-1;i>ui->lineEdit_5->text().toInt()-1;i--){
                da->dat[i]=da->dat[i-1];
            }
            da->dat[ui->lineEdit_5->text().toInt()-1]=ui->lineEdit_4->text();
            QFile file(da->storage);
            file.open(QIODevice::WriteOnly);
            QTextStream writeStream(&file);
            //writeStream << "12345\r\n";
            for (int i=0;i<da->strok;i++){
                writeStream << da->dat[i];
                if(i!=da->strok-1) writeStream << "\n";
            }
            file.close();
            model->insertRow(1);
            table();
        }
    }
    else ui->textBrowser->setText("Неверное значение");
}


void MainWindow::on_days_to_birsd_2_clicked()
{
    da->store();
if(!da->data()) ui->textBrowser->setText("Файл либо повреждён, либо не соответсвует требованиям");
else table();
}

