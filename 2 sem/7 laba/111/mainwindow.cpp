#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeWidget>
#include <QtDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int y=0;y<20;y++){
    v.push_back(qrand());
    }
    for (auto num : v)
        m.insert(std::make_pair(num, QString::number(num)));

    showw();

    ui->key_le_2->setValidator(new QIntValidator(1, 99999, this));
    ui->key_le->setValidator(new QIntValidator(1, 99999, this));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_find_clicked()
{
    QString key = ui->key_le->text();

    if (key.isEmpty())
        return;

    int key_ = key.toInt();
    auto val =  m.find(std::move(key_));
    ui->iterators->clear();
    if(val!=nullptr) ui->iterators->setText((*val).second);
}

void MainWindow::showw()
{
    ui->treeWidget->clear();
    m.allprintTree(ui->treeWidget);
    QString str;
    for (Set<int, QString>::iterator it = m.begin(); it != m.end(); ++it) {

        str += QString::number((*it).first) + "  ";
    }
    ui->iterators->setText(str);
}


void MainWindow::on_find_2_clicked()
{

    bool cheak=1;
    for (Set<int, QString>::iterator it = m.begin(); it != m.end(); ++it) {
        if((*it).first ==ui->key_le_2->text().toInt()) cheak=0;
    }
    if(cheak){
    m.insert(std::make_pair(ui->key_le_2->text().toInt(), ui->key_le_2->text()));
    }
    showw();
}


void MainWindow::on_find_3_clicked()
{
    showw();
}


void MainWindow::on_find_4_clicked()
{
    m.remove(ui->key_le_2->text().toInt());
    showw();
}

