#ifndef UNORDERED_SET_H
#define UNORDERED_SET_H
#include <iostream>
#include <QString>
#include <forward_list>
#include <vector>

template<typename Key, typename Value, typename Hash = std::hash<Key>, typename EqualTo = std::equal_to<Key>>
class unordered_map {

    typedef std::pair<Key, Value> value_type;

    struct node {
        value_type data;
        size_t cached;
        node(value_type _data, size_t _cached) : data(_data), cached(_cached) {}
        QString key_val() {  return QString::number(data.first) + " " + data.second;
        }
    };

    double load_factor = 0;
    double max_load_factor = 0.5;
    size_t bucket_count = 0, sz = default_sz;
    const size_t default_sz = 60;
    typedef typename std::forward_list<node>::iterator buck;

    std::forward_list<node> elemOfList;
    std::vector<buck> buckets;

public:

    class iterator {
        buck cur;
    public:
        iterator(const iterator& other) : cur(other.cur) {}

        iterator(const buck& other) : cur(other) {}

        iterator& operator++() {
            ++cur;
            return *this;
        }

        iterator& operator--() {
            --cur;
            return *this;
        }

        node& operator*() {  return *cur;  }

        bool operator== (const iterator& other) const noexcept { return cur == other.cur; }

        bool operator!= (const iterator& other) const noexcept { return cur != other.cur; }

        bool operator== (const buck& other) const noexcept { return cur == other; }

        bool operator!= (const buck& other) const noexcept { return cur != other;  }
    };

    buck begin() { return elemOfList.begin(); }

    buck end() { return elemOfList.end(); }

    unordered_map() {  buckets.resize(default_sz, elemOfList.end()); }

    size_t bucket_counter() const noexcept { return bucket_count; }

    size_t size() const noexcept { return sz; }

    double getLoadFactor() noexcept {
        load_factor = bucket_count / sz; return load_factor;
    }

    bool empty() const noexcept { return !sz; }

    void rehash(size_t new_size) {
        if (new_size <= sz) return;

        std::vector<buck> new_buckets(new_size, elemOfList.end());
        for (buck it = elemOfList.begin(); it != elemOfList.end(); ++it) {
        it->cached = Hash{}(it->data.first) % new_size;
        }

        size_t prev_cached = elemOfList.begin()->cached;
        buck it = elemOfList.begin();
        new_buckets[it->cached] = it;

        for (++it; it != elemOfList.end(); it) {
            if (!EqualTo{}(prev_cached, it->cached)) {
                new_buckets[it->cached] = it;
            }

            if (++it != elemOfList.end()) { prev_cached = it->cached; }

        }

        sz = new_size;
        buckets = new_buckets;
    }


    const double getMaxLoadFactor() const noexcept { return max_load_factor; }

    void setMaxLoadFactor(double new_value) noexcept { max_load_factor = new_value; }


    void insert(Key&& _key, Value&& _val = Value()) {

        if (getLoadFactor() >= max_load_factor) rehash(sz * 4);

        size_t cache = Hash{}(_key) % buckets.size();

        if (buckets[cache] != elemOfList.end()) {
            elemOfList.insert_after(buckets[cache], node(std::make_pair(_key, _val), cache));
        }

        else {
        buckets[cache] = elemOfList.insert_after(elemOfList.before_begin(),
                node(std::make_pair(_key, _val), cache));
        }
        ++bucket_count;
    }

    QString print(Key&& _key) {
        QString info = "";
        size_t cached = Hash{}(_key) % buckets.size();
        buck it = buckets[cached];
        for (it; it != elemOfList.end() && it->cached == cached; ++it) {
            info += QString::number(it->data.first) + ": " + QString::number(cached);
            info += "\n";
        }
        return info;
    }

    QString show() {
        QString info = "";
        for (auto& it : elemOfList) {
            info += QString::number((it).data.first)+ ": " + QString::number(Hash{}(it.data.first) % buckets.size());
            info += "\n";
        }
        return info;
    }

    void erase(Key&& _key) {
        if (empty()) return;

        size_t cached = Hash{}(_key) % buckets.size();
        if (buckets[cached] == elemOfList.end()) return;

        buck it = buckets[cached];
        for (it; it->cached == cached; ++it) {
            buck next_next = it;
            ++next_next;
            if (next_next == elemOfList.end() || ++next_next == elemOfList.end()) break;
            if (it->cached != next_next->cached) break;
        }

        if (it == buckets[cached]) {
            buck temp = it;
            if (++temp == elemOfList.end())  buckets[cached] = elemOfList.end();
            else  elemOfList.erase_after(it);
        }

        else elemOfList.erase_after(it);
        --bucket_count;

    }

    bool contains(Key&& _key) {
        size_t cached = Hash{}(_key) % buckets.size();
        return buckets[cached] != elemOfList.end();
    }

    void clear() {
        elemOfList.clear();
        buckets.clear();
        bucket_count = 0;
        buckets.resize(default_sz, elemOfList.end());
    }


    Value operator[] (Key&& _key) const {
        Key unhashed_key = _key;
        size_t cached = Hash{}(_key) % buckets.size();
        if (buckets[cached] == elemOfList.end()) insert(std::move(unhashed_key));

        buck it = buckets[cached];
        for (it; it->cached == cached; ++it) {
            buck temp = it;
            if (++temp == elemOfList.end() || temp->cached != cached) break;
        }

        return it->data.second;
    }

    Value& operator[] (Key&& _key) {
        Key unhashed_key = _key;
        size_t cached = Hash{}(_key) % buckets.size();
        if (buckets[cached] == elemOfList.end()) insert(std::move(unhashed_key));

        buck it = buckets[cached];
        for (it; it->cached == cached; ++it) {
            buck temp = it;
            if (++temp == elemOfList.end() || temp->cached != cached) break;
        }
        return it->data.second;
    }
};

#endif
