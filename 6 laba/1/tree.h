#ifndef Elem_H
#define Elem_H
#include <QString>
#include <QDebug>
#include <iostream>
#include <memory>
#include <QTreeWidget>
#include <QVector>
#include <QDebug>
struct Elem{
    QString name;
    int key;
    Elem* left,*right;
};

class tree
{
private:
    Elem* Head;

    void insert(QString s,int key, Elem *buf){
        if(key < buf->key){
            if(buf->left != NULL) insert(s,key, buf->left);
            else
            {
                buf->left = new Elem;
                buf->left->key = key;
                buf->left->name = s;
                buf->left->left = NULL;
                buf->left->right = NULL;
            }
        }
        else
            if(key > buf->key)
            {
            if(buf->right != NULL) insert(s,key, buf->right);
            else
            {
                buf->right = new Elem;
                buf->right->key = key;
                buf->right->name = s;
                buf->right->right = NULL;
                buf->right->left = NULL;
            }
        }
    }

    Elem* search(int key, Elem *buf){
        if(buf != NULL){
            if(key == buf->key) return buf;
            if(key < buf->key) return search(key, buf->left);
            else return search(key, buf->right);
        }
        return NULL;
    }

    void destroy_Elem(Elem *buf){
        if(buf != NULL){
            destroy_Elem(buf->left);
            destroy_Elem(buf->right);
            delete buf;
            buf=NULL;
        }
    }
public:
    QString printOrd(int a){
        QString str="";
        switch(a){
        case 1: preOrder(Head,str); break;
        case 2: inOrder(Head,str); break;
        case 3: postOrder(Head,str); break;
        }
        return str;
    }
    void postOrder(Elem* node,QString& str){
        if (node == nullptr) return ;
        preOrder(node->left,str);
        preOrder(node->right,str);
        str+=QString::number(node->key) + ' ';
    }
    void inOrder(Elem* node,QString& str){
        if (node == nullptr) return ;
        preOrder(node->left,str);
        str+=QString::number(node->key) + ' ';
        preOrder(node->right,str);
    }
    void preOrder(Elem* node,QString& str){
        if (node == nullptr) return ;
        str+=QString::number(node->key) + ' ';
        preOrder(node->left,str);
        preOrder(node->right,str);
    }
    tree(): Head(nullptr){};
    ~tree(){
        destroy_Elem(Head);
    }
    void insert(QString s,int key){
        if(Head != NULL){
            insert(s, key, Head);
        }
        else{
            Head = new Elem;
            Head->key = key;
            Head->name = s;
            Head->left = NULL;
            Head->right = NULL;
        }
    }

QString Creat(){
    QString str;
    if(Head){
        str+= Head->name + ", " + QString::number(Head->key)+'\n';
        printSubtree(Head,str);
    }
    return str;
}
bool empty(){
    return Head==nullptr;
}

    void creatString(Elem const * node, QString& strr,bool high = true, std::vector<std::string> const & lpref = std::vector<std::string>(), std::vector<std::string> const & cpref = std::vector<std::string>(), std::vector<std::string> const & rpref = std::vector<std::string>(), bool root = true, bool left = true, std::shared_ptr<std::vector<std::vector<std::string>>> lines = nullptr) {
        if (!node) return;
        typedef std::vector<std::string> VS;
        auto VSCat = [](VS const & a, VS const & b){ auto r = a; r.insert(r.end(), b.begin(), b.end()); return r; };
        if (root) lines = std::make_shared<std::vector<VS>>();

        if (node->left)
            creatString(node->left, strr,high,VSCat(lpref, high ? VS({" ", " "}) : VS({" "})), VSCat(lpref, high ? VS({"/", "|"}) : VS({"/"})), VSCat(lpref, high ? VS({"-", " "}) : VS({"-"})), false, true, lines);
        auto sval = std::to_string(node->key);
        size_t sm = left || sval.empty() ? sval.size() / 2 : ((sval.size() + 1) / 2 - 1);
        for (size_t i = 0; i < sval.size(); ++i)
            lines->push_back(VSCat(i < sm ? lpref : i == sm ? cpref : rpref, {std::string(1, sval[i])}));
        if (node->right)
            creatString(node->right, strr,high, VSCat(rpref, high ? VS({"-", " "}) : VS({"-"})), VSCat(rpref, high ? VS({"\\", "|"}) : VS({"\\"})), VSCat(rpref, high ? VS({" ", " "}) : VS({" "})), false, false, lines);
        if (root) {
            VS out;
            for (size_t l = 0;;++l) {
                bool last = true;
                std::string line;
                for (size_t i = 0; i < lines->size(); ++i)
                    if (l < (*lines).at(i).size()) {
                        line += lines->at(i)[l];
                        last = false;
                    } else line += " ";
                if (last) break;
                out.push_back(line);
            }
            for (size_t i = 0; i < out.size(); ++i)
                strr+= QString::fromStdString(out[i]) + '\n';
        }
    }

    void printSubtree(Elem* root, QString& str, QString prefix="")
    {
            if (root == NULL)
            {
                    return;
            }

            bool hasLeft = (root->left != NULL);
            bool hasRight = (root->right != NULL);

            if (!hasLeft && !hasRight)
            {
                    return;
            }

            str+= prefix + ((hasLeft  && hasRight) ? "├── " : "") + ((!hasLeft && hasRight) ? "└── " : "");

            if (hasRight)
            {
                    bool printStrand = (hasLeft && hasRight && (root->right->right != NULL || root->right->left != NULL));
                    QString newPrefix = prefix + (printStrand ? "│   " : "    ");
                    str+=root->right->name + ", " +QString::number(root->right->key) + '\n';
                    printSubtree(root->right,str, newPrefix);
            }

            if (hasLeft)
            {
                    str+=(hasRight ? prefix : "") + "└── " + root->left->name + ", " + QString::number(root->left->key) +'\n';
                    printSubtree(root->left,str, prefix + "    ");
            }
    }

    QString search(int key){
        Elem* buf = search(key, Head);
        if(buf)return buf->name + ", " + QString::number(buf->key);
        return "error";
    }


    void Del(int key) {
   Elem *Del, *Prev_Del, *R, *Prev_R, *root = Head;
   // Del, Prev_Del – удаляемый узел и его предыдущий (предок);
   // R, Prev_R – элемент, на который заменяется удаленный, и его предок;
   if(key==Head->key){
       if(Head->left==nullptr && Head->right==nullptr){
           delete Head;
           Head=nullptr;
       }
       return;
   }
   Del = root;
   Prev_Del = NULL;
   //-------- Поиск удаляемого элемента и его предка по ключу key ---------
   while (Del != NULL && Del -> key != key) {
   Prev_Del = Del;
   if (Del->key > key) Del = Del->left;
   else Del = Del->right;
   }
   if (Del == NULL) return;
   //-------------------- Поиск элемента R для замены --------------------------------
   if (Del -> right == NULL) R = Del->left;
   else
   if (Del -> left == NULL) R = Del->right;
   else {
   //---------------- Ищем самый правый узел в левом поддереве -----------------
   Prev_R = Del;
   R = Del->left;
   while (R->right != NULL) {
   Prev_R = R;
   R = R->right;
   }
   //----------- Нашли элемент для замены R и его предка Prev_R -------------
   if( Prev_R == Del) R->right = Del->right;
   else {
   R->right = Del->right;
   Prev_R->right = R->left;
   R->left = Prev_R;
   }
   }
   if (Del== root) root = R; // Удаляя корень, заменяем его на R
   else
   //------- Поддерево R присоединяем к предку удаляемого узла -----------
   if (Del->key < Prev_Del->key)
   Prev_Del->left = R; // На левую ветвь
   else Prev_Del->right = R; // На правую ветвь
   delete Del;
   }

    int Min_Key() {
        Elem* p = Head;
        while (p->left != NULL) p = p->left;
        return p->key;
   }

    int Max_Key() {
        Elem* p = Head;
        while (p->right != NULL) p = p->right;
        return p->key;
   }

    void Balans(Elem **p, int n, int k, QVector<int>& a,QVector<QString>& str) {

   if (n == k) {
       *p = NULL;
   return;
   }
   else {
   int m=(n+k)/2;
   *p = new Elem;
   (*p)->key = a[m];
   (*p)->name=str[m];
   Balans( &(*p)->left, n, m, a,str);
   Balans( &(*p)->right, m+1, k, a,str);
   }
   }

    void countOfKeys(Elem* node,QVector<int>& v,QVector<QString>& str){
      if (node == nullptr) return;
      v.push_back(node->key);
      str.push_back(node->name);
      countOfKeys(node->left,v,str);
      countOfKeys(node->right,v,str);
    }

    void make_balance(){
        QVector<int> v;
        QVector<QString> str;
        countOfKeys(Head,v,str);
        Balans(&Head,0,v.size(),v,str);
    }

    void allprintTree(QTreeWidget* tree){
        QTreeWidgetItem *itm = new QTreeWidgetItem(tree, QStringList(QString("TREE")));
        printTree(Head,tree,itm);
    }

    void printTree(Elem* node, QTreeWidget* tree, QTreeWidgetItem* vec){
        if (node == nullptr) return;
        QTreeWidgetItem *itm = new QTreeWidgetItem(vec, QStringList(node->name + ", " + QString::number(node->key)));
        printTree(node->right,tree,itm);
        printTree(node->left,tree,itm);
    }
};

#endif // Elem_H
