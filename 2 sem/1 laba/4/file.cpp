#include "file.h"

file::file()
{

}

void file::store()
{
//if (QFileDialog::getOpenFileName(0,"Выберете файл","","*txt") == "") return;
storage = QFileDialog::getOpenFileName(0,"Выберете файл","","*txt");
}
void file::store_save()
{
//if (QFileDialog::getOpenFileName(0,"Выберете файл","","*txt") == "") return;
storage = QFileDialog::getSaveFileName(0,"Выберете файл","","*.txt");
}

bool file::read()
{
    QString buf;
    bool v=1;
QFile text(storage);
text.open(QIODevice::ReadOnly);
name_project.clear();
work_of_project.clear();
name_worker.clear();
name_direct.clear();
date_of_issue.clear();
deadline.clear();
date_delivery.clear();
sizee=0;
/*
buf = text.readLine();
if(buf.toInt() == 1234){
    */
while (!text.atEnd()){
    buf=text.readLine();
    if(buf.size()>100 || buf == "\r\n") return 0;
name_project.push_back(buf);
buf=text.readLine();
if(buf.size()>100 || buf == "\r\n") return 0;
work_of_project.push_back(buf);
buf=text.readLine();
if(buf.size()>100 || buf == "\r\n") return 0;
name_worker.push_back(buf);
buf=text.readLine();
if(buf.size()>100 || buf == "\r\n") return 0;
name_direct.push_back(buf);
buf=text.readLine();
buf.remove(10,2);
date_of_issue.push_back(QDate::fromString(buf,"dd.MM.yyyy"));
if(!date_of_issue[date_of_issue.size()-1].isValid()) return 0;
buf=text.readLine();
buf.remove(10,2);
deadline.push_back(QDate::fromString(buf,"dd.MM.yyyy"));
if(!deadline[deadline.size()-1].isValid()) return 0;
buf=text.readLine();
buf.remove(10,2);
date_delivery.push_back(QDate::fromString(buf,"dd.MM.yyyy"));
if(!date_delivery[date_delivery.size()-1].isValid()) return 0;
sizee++;
text.readLine();
//}
}
//else v=0;
text.close();
return v;
}

void file::write()
{
    QFile text(storage);
    text.open(QIODevice::WriteOnly );
    QTextStream writeStream(&text);
    //writeStream << "1234\r\n";
    for (int i=0;i<sizee;i++){
        writeStream << name_project[i];
        writeStream << work_of_project[i];
        writeStream << name_worker[i];
        writeStream << name_direct[i];
        writeStream << date_of_issue[i].toString(Qt::SystemLocaleShortDate)+"\r\n";
        writeStream << deadline[i].toString(Qt::SystemLocaleShortDate)+"\r\n";
        writeStream << date_delivery[i].toString(Qt::SystemLocaleShortDate)+"\r\n";
        writeStream << '\n';
    }
    text.close();
}

void file::sort()
{
    int k = name_direct.size()-2;
    bool is_swap = false;
    QString str;
       for (int i = 0; i <= k; ++i) {
          is_swap = false;
          for (int j = k; j >= i; --j) {
             if (name_project[j] > name_project[j + 1]) {
                 std::swap(name_project[j + 1], name_project[j]);
                 std::swap(work_of_project[j + 1], work_of_project[j]);
                 std::swap(name_worker[j + 1], name_worker[j]);
                 std::swap(name_direct[j + 1], name_direct[j]);
                 std::swap(date_of_issue[j + 1], date_of_issue[j]);
                 std::swap(deadline[j + 1], deadline[j]);
                 std::swap(date_delivery[j + 1], date_delivery[j]);

                is_swap = true;
             }
          }
          if (!is_swap) break;
       }
}

void file::delet(int s)
{
for(int i=s;i<sizee-1;i++){
    name_project[i]=name_project[i+1];
    work_of_project[i]=work_of_project[i+1];
    name_worker[i]=name_worker[i+1];
    name_direct[i]=name_direct[i+1];
    date_of_issue[i]=date_of_issue[i+1];
    deadline[i]=deadline[i+1];
    date_delivery[i]=date_delivery[i+1];
}
name_project.pop_back();
work_of_project.pop_back();
name_worker.pop_back();
name_direct.pop_back();
date_of_issue.pop_back();
deadline.pop_back();
date_delivery.pop_back();
sizee--;
}
