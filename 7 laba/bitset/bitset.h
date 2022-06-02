#ifndef BITSET_H
#define BITSET_H
#define bit (8 * sizeof(int))
#include <QString>

template<size_t Bits>
class bitset {

public:

    bitset() { for (size_t i = 0; i < Bits; ++i) reset(i); }

    bool none() { return !any();   }

    bool all() {   return count() == size(); }

    bool any() {
        for (size_t i = 0; i <= Bits; ++i)
            if (get_bit(i))  return true;
        return false;
    }

    void set(size_t bitN) {
        if ( bitN >= Bits)   return;
         bitN = Bits -  bitN;
        -- bitN;
        bits[ bitN / bit] |= (1 << ( bitN % bit));
    }

    void reset(size_t bitN) {
        if ( bitN >= Bits)  return;
         bitN = Bits - bitN;
        -- bitN;
        bits[ bitN / bit] &= ~(1 << ( bitN % bit));
    }

    void reset() {
        for (size_t i = 0; i < Bits; ++i) reset(i);
    }

    bool test(size_t bitN) {
        if ( bitN >= Bits)  return false;
         bitN = Bits - bitN;
        -- bitN;
        return (bits[ bitN / bit] & (1 << ( bitN % bit)));
    }

    void flip(size_t  bitN) {
        if ( bitN >= Bits) return;
         bitN = Bits -  bitN;
        -- bitN;
        bits[ bitN / bit] ^= (1 << ( bitN % bit));
    }

    void flip() {
        for (int i = 0; i < Bits; ++i) {
            if (get_bit(i)) _reset(i);
            else  _set(i);
        }
    }

    size_t size() noexcept {  return Bits;  }

    size_t count() {
        int counter = 0;
        for (int i = 0; i < Bits; ++i)
            if (get_bit(i))   ++counter;
        return counter;
    }

    QString to_string() {
        QString s_bits;
        for (int i = 0; i < Bits; i++) {
            s_bits.push_back(get_bit(i) ? '1' : '0');
        }
        return s_bits;
    }

    unsigned to_ulong() {
        unsigned num = 0;
        for (int i = 0; i < Bits; ++i)  num += get_bit(i) * pow(2, Bits - 1 - i);
        return num;
    }

    unsigned to_ullong() {
        unsigned num = 0;
        for (int i = 0; i < Bits; ++i)  num += get_bit(i) * pow(2, Bits - 1 - i);
        return num;
    }

    bool operator[] (int bitN) {

        if ( bitN >= Bits) return false;
         bitN = Bits - bitN;
        -- bitN;
        return ((bits[ bitN / bit] & (1 << (bitN % bit))));
    }

private:
    int bits[Bits / 32 + 1];

    void _reset(size_t  bitN) {
        bits[ bitN / bit] &= ~(1 << ( bitN % bit));
    }

    void _set(size_t  bitN) {
        bits[ bitN / bit] |= (1 << ( bitN % bit));
    }
    bool get_bit(size_t  bitN) {
        return ((bits[ bitN / bit] & (1 << ( bitN % bit))));
    }
};

#endif // BITSET_H
