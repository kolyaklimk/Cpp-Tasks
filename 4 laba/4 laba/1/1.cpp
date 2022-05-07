//https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.3/a02030.html
#include <iostream>
#include <vector>
#include <string>

/// pair holds two objects of arbitrary type.
template<class A, class B>
struct pair
{
    A first;
    B second;

    pair() : first(), second() { }

    pair(const A& a, const B& b) : first(a), second(b) { }

    template<class AA, class BB>
    pair(const pair<AA, BB>& p) : first(p.first), second(p.second) { }

    pair& operator =(const pair& p)
    {
        first = std::move(p.first);
        second = std::move(p.second);
        return *this;
    }

    template<class AA, class BB>
    pair& operator =(const pair<AA, BB>& p)
    {
        first = std::move(p.first);
        second = std::move(p.second);
        return *this;
    }

    void swap(pair& p)
    {
        std::swap(first, p.first);
        std::swap(second, p.second);
    }

    template<class AA, class BB>
    void swap(pair<AA, BB>& p)
    {
        first = std::move(p.first);
        second = std::move(p.second);
    }


    void make_pair(A x, B y)
    {
        first = x;
        second = y;
    }
};

int main()
{
    pair<int, double> a1(2432, 423);
    pair<int, double> a2(54, 23);
    
    std::cout << a1.first << "   " << a1.second << '\n';
    a1.make_pair(231, 432);
    std::cout << a1.first << "   " << a1.second << '\n';
    a1.swap(a2);
    std::cout << a1.first << "   " << a1.second << '\n';
    a1 = a2;
    std::cout << a1.first << "   " << a1.second << '\n';
    a1.first = 43;
    a1.second = 43;
    std::cout << a1.first << "   " << a1.second << '\n';
    
    pair<pair<int, double>, pair<int, double>> dub(a1,a2);
    pair<pair<int, double>, pair<int, double>> dub2(pair<int, double>(324, 523), pair<int, double>(824, 423));
    std::cout << dub.first.first << "   " << dub.first.second << "   " << dub.second.first << "   " << dub.second.second << '\n';
    dub.swap(dub2);

    std::cout << dub.first.first << "   " << dub.first.second << "   " << dub.second.first << "   " << dub.second.second;
}