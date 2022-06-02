#ifndef RBTREE_H
#define RBTREE_H
#include <QString>

#include <QTreeWidget>
template<typename Key, typename Value>
class rbTree {
    enum Red_or_Black { black, red };

protected:

    QString tr;

    struct node {

        Red_or_Black color = black;
        node* parent = nullptr, * left = nullptr, * right = nullptr;
        bool exist = true;
        std::pair<const Key, Value> data;
        node(std::pair<const Key, Value> _data,
            node* _parent = nullptr, node* _right = nullptr,
            node* _left = nullptr, Red_or_Black _color = red) :
            data(std::move(_data)), parent(_parent),
            right(_right), left(_left), color(_color) {}

        node(bool _exist, std::pair<const Key, Value> _data) : exist(_exist), data(std::move(_data)) {}
    };

    node* root = nullptr;
    size_t sz = 0;

private:
    void l_rotate(node* parent) {

        node* uncle = parent->right;
        parent->right = uncle->left;

        if (uncle->left)  uncle->left->parent = parent;

        uncle->parent = parent->parent;

        if (!(parent->parent))  root = uncle;

        else {
            if (parent == (parent->parent)->left)  (parent->parent)->left = uncle;
            else  (parent->parent)->right = uncle;
        }

        uncle->left = parent;
        parent->parent = uncle;
    }

    void r_rotate(node* parent) {
        node* uncle = parent->left;
        parent->left = uncle->right;

        if (uncle->right)  uncle->right->parent = parent;

        uncle->parent = parent->parent;

        if (!(parent->parent))  root = uncle;

        else {
            if (parent == (parent->parent)->right)  (parent->parent)->right = uncle;
            else  (parent->parent)->left = uncle;
        }
        uncle->right = parent;
        parent->parent = uncle;
    }

    void _insert(node* new_node) {
        node* cur = root;
        node* parent = nullptr;

        while (cur) {
            parent = cur;
            if (new_node->data.first > cur->data.first)  cur = cur->right;
            else  cur = cur->left;
        }
        new_node->parent = parent;

        if (parent) {
            if (new_node->data.first > parent->data.first)  parent->right = new_node;
            else parent->left = new_node;
        }

        else  root = new_node;
        new_node->color = red;
        insertFixUp(new_node);
    }

    void insertFixUp(node*& new_node) {
        node* parent = new_node->parent;

        while (new_node != root && parent->color == red) {
            node* grandparent = parent->parent;
            if ((grandparent)->left == parent) {
                node* uncle = (grandparent)->right;

                if (uncle && uncle->color == red) {
                    parent->color = black;
                    uncle->color = black;
                    grandparent->color = red;
                    new_node = grandparent;
                    parent = new_node->parent;
                }
                else {
                    if (parent->right == new_node) {
                        l_rotate(parent);
                        std::swap(new_node, parent);
                    }
                    r_rotate(grandparent);
                    grandparent->color = red;
                    parent->color = black;
                    break;
                }
            }

            else {
                node* uncle = grandparent->left;
                if (uncle && uncle->color == red) {
                    grandparent->color = red;
                    parent->color = black;
                    uncle->color = black;
                    new_node = grandparent;
                    parent = new_node->parent;
                }

                else {
                    if (parent->left == new_node) {
                        r_rotate(parent);
                        std::swap(parent, new_node);
                    }
                    l_rotate(grandparent);
                    parent->color = black;
                    grandparent->color = red;
                    break;
                }
            }
        }
        root->color = black;
    }

    void clear(node*& cur) {
        if (cur) {
            clear(cur->left);
            clear(cur->right);
            delete cur;
        }
    }

    void remove(node*& deleted) {
        node* child, * parent;
        Red_or_Black color;

        if (deleted->left && deleted->right) {
            node* replace = deleted;
            replace = deleted->right;

            while (replace->left)   replace = replace->left;

            if (deleted->parent) {
                if (deleted->parent->left == deleted)  deleted->parent->left = replace;
                else  deleted->parent->right = replace;
            }

            else  root = replace;

            child = replace->right;
            parent = replace->parent;
            color = replace->color;

            if (parent == deleted)  parent = replace;

            else {
                if (child)   child->parent = parent;
                parent->left = child;
                replace->right = deleted->right;
                deleted->right->parent = replace;
            }

            replace->parent = deleted->parent;
            replace->color = deleted->color;
            replace->left = deleted->left;
            deleted->left->parent = replace;
            if (color == black)  removeFixUp(child, parent);
            delete deleted;
            return;
        }

        if (deleted->left)  child = deleted->left;
        else   child = deleted->right;

        parent = deleted->parent;
        color = deleted->color;

        if (child)  child->parent = parent;

        if (parent) {
            if (deleted == parent->left)  parent->left = child;
            else parent->right = child;
        }
        else root = child;
        if (color == black)   removeFixUp(child, parent);
        delete deleted;
    }

    void removeFixUp(node*& child, node*& parent) {
        node* othernode;
        while ((!child) || child->color == black && child != root) {
            if (parent->left == child) {
                othernode = parent->right;
                if (othernode->color == red) {
                    othernode->color = black;
                    parent->color = red;
                    l_rotate(parent);
                    othernode = parent->right;
                }

                else {
                    if (!(othernode->right) || othernode->right->color == black) {
                        othernode->left->color = black;
                        othernode->color = red;
                        r_rotate(othernode);
                        othernode = parent->right;
                    }
                    othernode->color = parent->color;
                    parent->color = black;
                    othernode->right->color = black;
                    l_rotate(parent);
                    child = root;
                    break;
                }
            }

            else {
                othernode = parent->left;
                if (othernode->color == red) {
                    othernode->color = black;
                    parent->color = red;
                    r_rotate(parent);
                    othernode = parent->left;
                }

                if ((!othernode->left || othernode->left->color == black) &&
                    (!othernode->right || othernode->right->color == black)) {
                    othernode->color = red;
                    child = parent;
                    parent = child->parent;
                }

                else {
                    if (!(othernode->left) || othernode->left->color == black) {
                        othernode->right->color = black;
                        othernode->color = red;
                        l_rotate(othernode);
                        othernode = parent->left;
                    }
                    othernode->color = parent->color;
                    parent->color = black;
                    othernode->left->color = black;
                    r_rotate(parent);
                    child = root;
                    break;
                }
            }
        }
        if (child)  child->color = black;
    }

protected:

    node* search(node* cur, const Key& _key) {
        if (!cur)   return new node(false, std::make_pair(_key, Value()));

        if (cur->data.first == _key) return cur;
        else
            if (_key > cur->data.first)  return search(cur->right, _key);
            else return search(cur->left, _key);
    }

public:

    rbTree() : root(nullptr) {}

    ~rbTree() {  clear(root); }

    node* min() {
        node* cur = root;
        while (cur->left) { cur = cur->left; }
        return cur;
    }


    node* max(node* parent) {
        node* cur = root;
        while (cur->right->parent) {
            cur = parent->right;
        }
        return cur;
    }


    node* insert(const std::pair<const Key, Value>&& data) {
        node* new_node = new node(std::move(data));
        _insert(new_node);
        ++sz;
        return new_node;
    }

    void remove(const Key& _key) {
        node* deletenode = search(root, _key);
        if (deletenode->exist) {
            remove(deletenode);
            --sz;
        }
    }

    const size_t size() const noexcept {  return sz;   }

    bool empty() const noexcept { return !root; }

    Value& search(const Key& _key) {
        node* temp = search(root, _key);
        if (temp->exist)
            return temp->data.second;
        else {
            temp->exist = true;
            _insert(temp);
            return temp->data.second;
        }
    }

    void allprintTree(QTreeWidget* tree) {
        QTreeWidgetItem* itm = new QTreeWidgetItem(tree, QStringList(QString("TREE")));
        printTree(root, tree, itm);
    }

    void printTree(node* node, QTreeWidget* tree, QTreeWidgetItem* vec) {
        if (node == nullptr) return;
        QTreeWidgetItem* itm = new QTreeWidgetItem(vec, QStringList(QString::number(node->data.first)));
        printTree(node->right, tree, itm);
        printTree(node->left, tree, itm);
    }
};

#endif // RBTREE_H
