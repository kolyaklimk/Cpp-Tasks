#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    show_bitset();
}

MainWindow::~MainWindow()
{
    delete ui;
}

inline void MainWindow::show_bitset()
{
    ui->str->setText(b.to_string());
    ui->ull->clear();
    ui->ull->append(QString::number(b.to_ulong()));
}


void MainWindow::on_flip__clicked()
{
    b.flip();
    show_bitset();
}


void MainWindow::on_all__clicked()
{
    QString s = b.all() ? "true" : "false";
    ui->ull_2->clear();
    ui->ull_2->setText(s);
}


void MainWindow::on_any__clicked()
{
    QString s = b.any() ? "true" : "false";
    ui->ull_2->clear();
    ui->ull_2->setText(s);
}


void MainWindow::on_set_1_clicked()
{
    ui->ull_2->clear();
    ui->ull_2->setText(QString::number(b.count()));

}

void MainWindow::on_set_2_clicked()
{
    ui->ull_2->clear();
    ui->ull_2->setText(QString::number(b.none()));
}


void MainWindow::on_set_3_clicked()
{
    ui->ull_2->clear();
    ui->ull_2->setText(QString::number(b.size()));
}


void MainWindow::on_test__clicked()
{
    QString num_s = ui->test_le->text();
    if (num_s.isEmpty())   return;
    size_t pos = num_s.toInt();
    QString s = b.test(pos) ? "true" : "false";
    ui->ull_2->clear();
    ui->ull_2->setText(s);
}


void MainWindow::on_set__clicked()
{
    QString num_s = ui->test_le->text();
    if (num_s.isEmpty())  return;
    size_t pos = num_s.toInt();
    b.set(pos);
    show_bitset();
}


void MainWindow::on_reset__clicked()
{
    QString num_s = ui->test_le->text();
    if (num_s.isEmpty())
        return;
    size_t pos = num_s.toInt();
    b.reset(pos);
    show_bitset();
}

