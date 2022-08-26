#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTextCursor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont font = QFont("Microsoft YaHei",16,2);
    ui->textEdit->setFont(font);
    //ui->textEdit->setAcceptDrops(false);
    ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
}

MainWindow::~MainWindow()
{
    delete ui;
}




int MainWindow::balanced(const std::string &s)
{
    QStack<char> stack;
    int a=1;
    int pos_op=0;
    int pos_clos=0;
    stroka=1;
    number=0;
        for (char c : s) {
            switch (c) {

            case '(': stack.push(')');
                if(!pos_op) pos_op=a;
                cheak=a; cheakNum=stroka;
                break;
            case '[': stack.push(']');
                if(!pos_op) pos_op=a;
                cheak=a;cheakNum=stroka;
                break;
            case '{': stack.push('}');
                if(!pos_op) pos_op=a;
                cheak=a;cheakNum=stroka;
                break;

            case ')': if(!pos_clos && !pos_op) pos_clos=a;cheakNum=stroka;
            case ']': if(!pos_clos && !pos_op) pos_clos=a;cheakNum=stroka;
            case '}': if(!pos_clos && !pos_op) pos_clos=a;cheakNum=stroka;

                if (stack.empty() || stack.top() != c) {
                    if(pos_op) return pos_op;
                    if(pos_clos) return pos_clos;
                    return a;
                }
                stack.pop();
                if(stack.empty()){
                pos_op=0;
                pos_clos=0;
                }
                break;
            default:
                break;
            }
            if(c=='\n'){
                number=0;
                stroka++;
            }
            number++;
            a++;
        }
        if(pos_op) return pos_op;
        if(pos_clos) return pos_clos;
        if(!stack.empty()) return cheak-1;
        return -1;
}

/*
int MainWindow::balanced(const std::string &s)
{
    QStack<char> stack;
    int a=1;
    stroka=1;
    number=0;
        for (char c : s) {
            switch (c) {

            case '(': stack.push(')');
                cheak=a; cheakNum=stroka;
                break;
            case '[': stack.push(']');
                cheak=a;cheakNum=stroka;
                break;
            case '{': stack.push('}');
                cheak=a;cheakNum=stroka;
                break;

            case ')': cheakNum=stroka;
            case ']': cheakNum=stroka;
            case '}': cheakNum=stroka;

                if (stack.empty() || stack.top() != c) {
                    return a;
                }
                stack.pop();
                break;
            default:
                break;
            }
            if(c=='\n'){
                number=0;
                stroka++;
            }
            number++;
            a++;
        }
        if(!stack.empty()){
            return cheak;
        }
        return -1;
}
*/



int MainWindow::pro1(std::string s){
    qDebug() << 1;
    int counter=0;
    int a=1;
    stroka=1;
    int cheak=1;
    for(char c: s){
        if(c=='('){
            cheakNum=stroka;
            cheak=a;
            counter++;
        }
        else if (c== ')'){
            counter--;
            if(counter<0){
                cheakNum=stroka;
                return a;
            }
    }
        if(c=='\n'){
            stroka++;
        }
        a++;
}
    if (counter) return cheak;
    return -1;
}

int MainWindow::pro2(std::string s){
    qDebug() << 2;
    int counter=0;
    int a=1;
    stroka=1;
    int cheak=1;
    for(char c: s){
        if(c=='['){
            cheakNum=stroka;
            cheak=a;
            counter++;
        }
        else
            if (c== ']'){ counter--;
                if(counter<0){
                    cheakNum=stroka;
                    return a;
                }
    }
        if(c=='\n'){
            stroka++;
        }
        a++;
}
    if (counter) return cheak;
    return -1;
}

int MainWindow::pro3(std::string s){
    qDebug() << 3;
    int counter=0;
    int a=1;
    stroka=1;
    int cheak=1;
    for(char c: s){
        if(c=='{'){
            cheakNum=stroka;
            cheak=a;
            counter++;
        }
        else
            if (c== '}'){ counter--;
                if(counter<0){
                    cheakNum=stroka;
                    return a;
                }
    }
        if(c=='\n'){
            stroka++;
        }
        a++;
}
    if (counter) return cheak;
    return -1;
}




void MainWindow::test(const std::string &s)
{
    int a = balanced(s);
/*
    int a;
    a=pro1(s);
    if(a==-1) a=pro2(s);
    if(a==-1) a=pro3(s);
*/


    if(a==-1){
         //QString buf=ui->textEdit->toPlainText();
         //buf.replace(QRegExp("\n"),"<br>");
         //ui->textEdit->setText("<font color = gray><\\font>"+buf);
        ui->textBrowser->setText("Success");
    }
    else {
        /*
        QString buf=ui->textEdit->toPlainText();
        char c = ui->textEdit->toPlainText().toStdString()[a-1];
        buf.replace(a-1,1,"<font color = red><\\font>"+QString(c)+"<font color = gray><\\font>");
        buf.replace(QRegExp("\n"),"<br>");
        ui->textEdit->setText("<font color = gray><\\font>" + buf);
        */
        QTextCursor cur3=ui->textEdit->textCursor();
        cur3.setPosition(a-1);
        ui->textBrowser->setText("Номер: " +QString::number(cur3.columnNumber()+1)+"\nСтрока: " +QString::number(cheakNum));
    }
    ui->textEdit->connect(ui->textEdit,SIGNAL(textChanged()), this, SLOT(on_textEdit_textChanged()));
    ui->textEdit->connect(ui->textEdit,SIGNAL(cursorPositionChanged()), this, SLOT(on_textEdit_cursorPositionChanged()));

}

void MainWindow::on_textEdit_textChanged()
{
    ui->textEdit->disconnect();
    int pos=ui->textEdit->textCursor().position();
    /*
    while (ui->textEdit->toPlainText().length() > 150000) {
        QTextCursor cur2=ui->textEdit->textCursor();
        cur2.setPosition(150000);
        cur2.setPosition(ui->textEdit->toPlainText().length(),QTextCursor::KeepAnchor);
        cur2.removeSelectedText();
        ui->textEdit->setTextCursor(cur2);

    ui->textEdit->textCursor().setPosition(ui->textEdit->toPlainText().length());
    ui->textEdit->connect(ui->textEdit,SIGNAL(textChanged()), this, SLOT(on_textEdit_textChanged()));
    }
    */
    test(ui->textEdit->toPlainText().toStdString());
    cursor = ui->textEdit->textCursor();
    cursor.setPosition(pos);
    ui->textEdit->setTextCursor(cursor);
}

void MainWindow::on_open_clicked()
{
    storage = QFileDialog::getOpenFileName(0,"Выберете файл","","*txt");
    QFile text(storage);
    text.open(QIODevice::ReadOnly);
    ui->textEdit->setText(text.readAll());
    text.close();
}


void MainWindow::on_save_clicked()
{
    if(storage!=nullptr){
    QFile text(storage);
    text.open(QIODevice::WriteOnly );
    QTextStream writeStream(&text);
    writeStream << ui->textEdit->toPlainText();
    text.close();
    }
else ui->textBrowser->setText("Файл не открыт или не создан");
}


void MainWindow::on_save_as_clicked()
{
    storage = QFileDialog::getSaveFileName(0,"Выберете файл","","*.txt");
    QFile text(storage);
    text.open(QIODevice::WriteOnly );
    QTextStream writeStream(&text);
    writeStream << ui->textEdit->toPlainText();
    text.close();
}


void MainWindow::on_textEdit_cursorPositionChanged()
{
    QTextCursor cur3=ui->textEdit->textCursor();
    QString buf=ui->textEdit->toPlainText();
    int buff=ui->textEdit->textCursor().position();
    int b=0;
    int line=1;
    for (QChar c : buf){
        if(b==buff) break;
        if (c=='\n'){
            line++;
        }
        b++;
    }
    ui->textBrowser_2->setText("Номер: " +QString::number(cur3.columnNumber() +1)+"\nСтрока: " + QString::number(line));
}

