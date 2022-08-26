#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QSyntaxHighlighter>
#include <QFileDialog>
#include <QFile>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_textEdit_textChanged();

    void on_open_clicked();

    void on_save_clicked();

    void on_save_as_clicked();

    void on_textEdit_cursorPositionChanged();

private:
    QTextCursor cursor;
    int balanced(const std::string &s);
    void test(const std::string& s);
    Ui::MainWindow *ui;
    int stroka;
    int number;
    int cheakNum;
    QString storage=nullptr;
    int cheak;

    int pro1(std::string s);
    int pro2(std::string s);
    int pro3(std::string s);
};
#endif // MAINWINDOW_H
