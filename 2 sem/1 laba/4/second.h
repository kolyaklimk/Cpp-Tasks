#ifndef SECOND_H
#define SECOND_H

#include <QMainWindow>
#include <file.h>
#include <QDebug>

namespace Ui {
class second;
}

class second : public QMainWindow, public file
{
    Q_OBJECT

public:
    explicit second(QWidget *parent = nullptr);
    ~second();
    void writet();

signals:
    void firstWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::second *ui;
    //file *da;
};

#endif // SECOND_H
