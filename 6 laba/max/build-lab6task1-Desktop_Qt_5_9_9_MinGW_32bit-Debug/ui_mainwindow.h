/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *key_le;
    QLineEdit *data_le;
    QPushButton *add;
    QPushButton *delete_2;
    QPushButton *make_balanced;
    QPushButton *show_bykey;
    QTextEdit *textEdit;
    QPushButton *make_balanced_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *add_2;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *make_balanced_3;
    QPushButton *make_balanced_4;
    QPushButton *make_balanced_5;
    QPushButton *make_balanced_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(935, 621);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 360, 121, 51));
        QFont font;
        font.setPointSize(25);
        label->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 410, 261, 51));
        label_2->setFont(font);
        key_le = new QLineEdit(centralwidget);
        key_le->setObjectName(QStringLiteral("key_le"));
        key_le->setGeometry(QRect(150, 380, 113, 28));
        QFont font1;
        font1.setPointSize(15);
        key_le->setFont(font1);
        data_le = new QLineEdit(centralwidget);
        data_le->setObjectName(QStringLiteral("data_le"));
        data_le->setGeometry(QRect(280, 430, 113, 28));
        data_le->setFont(font1);
        data_le->setReadOnly(true);
        add = new QPushButton(centralwidget);
        add->setObjectName(QStringLiteral("add"));
        add->setGeometry(QRect(660, 530, 261, 41));
        add->setFont(font1);
        delete_2 = new QPushButton(centralwidget);
        delete_2->setObjectName(QStringLiteral("delete_2"));
        delete_2->setGeometry(QRect(10, 520, 261, 41));
        delete_2->setFont(font1);
        make_balanced = new QPushButton(centralwidget);
        make_balanced->setObjectName(QStringLiteral("make_balanced"));
        make_balanced->setGeometry(QRect(280, 470, 231, 41));
        make_balanced->setFont(font1);
        show_bykey = new QPushButton(centralwidget);
        show_bykey->setObjectName(QStringLiteral("show_bykey"));
        show_bykey->setGeometry(QRect(10, 470, 261, 41));
        show_bykey->setFont(font1);
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(0, 0, 941, 361));
        make_balanced_2 = new QPushButton(centralwidget);
        make_balanced_2->setObjectName(QStringLiteral("make_balanced_2"));
        make_balanced_2->setGeometry(QRect(280, 520, 231, 41));
        make_balanced_2->setFont(font1);
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(810, 390, 113, 28));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(810, 430, 113, 28));
        add_2 = new QPushButton(centralwidget);
        add_2->setObjectName(QStringLiteral("add_2"));
        add_2->setGeometry(QRect(660, 480, 261, 41));
        add_2->setFont(font1);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(660, 370, 141, 51));
        label_5->setFont(font);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(660, 420, 151, 51));
        label_6->setFont(font);
        make_balanced_3 = new QPushButton(centralwidget);
        make_balanced_3->setObjectName(QStringLiteral("make_balanced_3"));
        make_balanced_3->setGeometry(QRect(510, 400, 141, 41));
        make_balanced_3->setFont(font1);
        make_balanced_4 = new QPushButton(centralwidget);
        make_balanced_4->setObjectName(QStringLiteral("make_balanced_4"));
        make_balanced_4->setGeometry(QRect(510, 440, 141, 41));
        make_balanced_4->setFont(font1);
        make_balanced_5 = new QPushButton(centralwidget);
        make_balanced_5->setObjectName(QStringLiteral("make_balanced_5"));
        make_balanced_5->setGeometry(QRect(510, 480, 141, 41));
        make_balanced_5->setFont(font1);
        make_balanced_6 = new QPushButton(centralwidget);
        make_balanced_6->setObjectName(QStringLiteral("make_balanced_6"));
        make_balanced_6->setGeometry(QRect(510, 520, 141, 41));
        make_balanced_6->setFont(font1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 935, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\320\232\320\273\321\216\321\207:", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217:", Q_NULLPTR));
        key_le->setText(QString());
        data_le->setText(QString());
        add->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\200\320\260\320\275\320\264\320\276\320\274", Q_NULLPTR));
        delete_2->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\277\320\276 \320\272\320\273\321\216\321\207\321\203", Q_NULLPTR));
        make_balanced->setText(QApplication::translate("MainWindow", "\320\241\320\261\320\260\320\273\320\260\320\275\321\201\320\270\321\200\320\276\320\262\320\260\321\202\321\214", Q_NULLPTR));
#ifndef QT_NO_WHATSTHIS
        show_bykey->setWhatsThis(QApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        show_bykey->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\276\320\261\321\200\320\260\320\267\320\270\321\202\321\214 \320\277\320\276 \320\272\320\273\321\216\321\207\321\203", Q_NULLPTR));
        make_balanced_2->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265", Q_NULLPTR));
        add_2->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\320\244.\320\230.\320\236.", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "\320\235\320\236\320\234\320\225\320\240", Q_NULLPTR));
        make_balanced_3->setText(QApplication::translate("MainWindow", "\320\262\321\213\320\262\320\276\320\264", Q_NULLPTR));
        make_balanced_4->setText(QApplication::translate("MainWindow", "\320\277\321\200\321\217\320\274\321\213\320\271", Q_NULLPTR));
        make_balanced_5->setText(QApplication::translate("MainWindow", "\320\276\320\261\321\200\320\260\321\202\320\275\321\213\320\271", Q_NULLPTR));
        make_balanced_6->setText(QApplication::translate("MainWindow", "\320\262\320\276\320\267\321\200\320\260\321\201\321\202\320\260\320\275\320\270\320\265", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
