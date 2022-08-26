#pragma once

#ifndef MAP_H
#define MAP_H

#include <QString>
#include "rbTree.h"

template <typename Key, typename Value>
class Set : public rbTree<Key, Value> {

public:

    class iterator {

    private:
        typename rbTree<Key, Value>::node* cur, *par = nullptr, *root;

    public:
        iterator() : cur(nullptr), root(nullptr) {}

        iterator(typename rbTree<Key, Value>::node* _iter, typename rbTree<Key, Value>::node* _root = nullptr) :  cur(_iter), root(_root) {}

        iterator(const iterator& other) : cur(other.cur), root(other.root) {}

        std::pair<Key, Value> operator*() { return cur->data;  }

        iterator& operator++() {
            if (!cur) {
                cur = root;
                while (cur->left)
                    cur = cur->left;
            }

            else
                if (cur->right) {
                    cur = cur->right;
                    while (cur->left)
                        cur = cur->left;
                }
                else {
                    par = cur->parent;
                    while (par && cur == par->right) {
                        cur = par;
                        par = par->parent;
                    }
                    cur = par;
                }

            return *this;

        }

        bool operator== (const iterator& other) const {
            return cur == other.cur;
        }

        bool operator!= (const iterator& other) const {
            return cur != other.cur;
        }
    };

    iterator find(const Key&& _key) {
            auto temp =  rbTree<Key, Value>::search(rbTree<Key, Value>::root, std::move(_key));

            if (temp->exist) return temp;
            else  return nullptr;
        }

    iterator begin() { return iterator(rbTree<Key, Value>::min(), rbTree<Key, Value>::root); }

    iterator end() { return iterator(nullptr); }

};

#endif // MAP_H
