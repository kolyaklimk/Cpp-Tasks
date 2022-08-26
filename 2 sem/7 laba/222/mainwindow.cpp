#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_pushButton_clicked()
{
}


void MainWindow::on_deploy_clicked()
{
    QString depl_key = ui->key_le->text();

    if (depl_key.isEmpty())
        return;


    int key = depl_key.toInt();

    ui->show_list->setText(s.print(std::move(key)));

}

void MainWindow::show_set()
{
    ui->show_list->clear();

    ui->show_list->setText(s.show());
}


void MainWindow::on_add_clicked()
{

    QString add_key = ui->key_le->text();

    if (add_key.isEmpty())
        return;

    int key = add_key.toInt();

    s.insert(std::move(key));

    show_set();
}


void MainWindow::on_deploy_2_clicked()
{
    show_set();
}


void MainWindow::on_deploy_4_clicked()
{
    ui->show_list->setText(QString::number(s.contains(ui->key_le->text().toInt())));
}


void MainWindow::on_deploy_3_clicked()
{
    s.clear();
    show_set();
}

