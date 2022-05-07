#include "mystring.h"
//https://gist.github.com/karthikkondagalla/58658c47871f2d8b7b83476c6942ebe7
MyString::MyString()
{
    data = new char[1];
    sizee = 1;
    data[0] = '\0';
}
MyString::MyString(const MyString& s)
{
    unsigned i, j;
    for (i = 0; s.data[i] != '\0'; i++);
    data = new char[i + 1];
    sizee = i + 1;
    for (j = 0; j < sizee; j++)data[j] = s.data[j];
}
MyString::MyString(const char* cs)
{
    unsigned i, j;
    for (i = 0; cs[i] != '\0'; i++);
    sizee = i + 1;
    data = new char[sizee];
    for (j = 0; j < (sizee - 1); j++)data[j] = cs[j];
    data[i] = '\0';
}

MyString::MyString(const MyString& s, const size_t& pos, const size_t& n)
{
    unsigned i, j;
    data = new char[n + 1];
    sizee = n + 1;
    for (i = pos, j = 0; i < (pos + n); i++, j++)data[j] = s.data[i];
    data[n] = '\0';
}
MyString::MyString(const char* cs, const size_t& n)
{
    unsigned i;
    for (i = 0; cs[i] != '\0'; i++);
    sizee = n + 1;
    data = new char[sizee];
    for (i = 0; i < (sizee - 1) && i < n; i++)data[i] = cs[i];
    data[n] = '\0';
}
MyString::MyString(const size_t& n, const char& c)
{
    unsigned i;
    sizee = n + 1;
    data = new char[sizee];
    for (i = 0; i < n; i++)data[i] = c;
    data[n] = '\0';
}

MyString::~MyString() {
    if (this->data != NULL)
        delete[] this->data;
}


char* MyString::getText() {
    return data;
}

void MyString::setText(char* text) {
    delete[] this->data;

    this->sizee = my_strlen(text);
    this->data = new char[this->sizee];

    my_strncpy(this->data, text, this->sizee);
}

size_t MyString::getLength() const {
    return my_strlen(this->data);
}

void MyString::setLength(size_t sizee) {
    size_t old_length = this->getLength();
    char* old_data = this->data;

    this->sizee = sizee;
    this->data = new char[sizee];

    for (size_t i = 0; i < sizee; i++) {
        if (i < old_length) {
            this->data[i] = old_data[i];
        }
        else {
            this->data[i] = '\0';
        }
    }

    delete[] old_data;

    this->data[sizee] = '\0';
}

void MyString::add(const MyString& text) {
    size_t new_size = this->sizee + text.sizee;
    setLength(new_size);

    size_t length = getLength();
    for (size_t i = length; i < new_size; i++) {
        this->data[i] = text.data[i - length];
    }
}

char MyString::at(size_t pos) const {
    if (pos > getLength()) {
        return '\0';
    }
    return data[pos];
}
bool MyString::compare(const MyString& string) const {
    return my_strcmp(this->data, string.data) == 0;
}

char MyString::operator[](size_t pos) {
    return this->at(pos);
}

MyString operator+(const MyString& string1, const MyString& string2) {
    MyString string = MyString(string1);
    string.add(string2);

    return string;
}

bool operator==(const MyString& string1, const MyString& string2) {
    return string1.compare(string2);
}


bool MyString::empty() {
    if (sizee == 0) return 1;
    return 0;
}
void MyString::clear()
{
    if (this->data != NULL)
        delete[] this->data;
    sizee=0;
}
size_t MyString::capacity()
{
    return sizee;
}

void MyString::resize(size_t sizee, char c = '\0') {
    char* old_data = this->data;
    if (sizee > this->sizee) {
        this->data = new char[sizee];
        my_strcmp(this->data, old_data);
        for (size_t a = this->sizee; a < sizee; a++)
            this->data[a] = c;
    }
    else {
        this->data = new char[sizee];
        for (size_t a = 0; a < sizee; a++)
            this->data[a] = old_data[a];
    }
    this->sizee = sizee;
    delete[] old_data;
}


size_t MyString::max_size() {
    return INT_MAX;
}

size_t MyString::lenght() {
    return this->sizee;
}

size_t MyString::size() {
    return this->sizee;
}

char  MyString::back() const {
    if (this->sizee > 0) {
        return this->data[this->sizee - 1];
    }
}
char  MyString::front() const {
    if (this->sizee > 0) {
        return this->data[0];
    }
}


void MyString::append(MyString& string) {
    char* old_data = this->data;
    this->data = new char[sizee + string.size()+1];
    for (size_t a = 0; a < sizee; a++) this->data[a] = old_data[a];
    for (size_t a = 0; a < string.size(); a++) this->data[a + sizee] = old_data[a];
    this->sizee = sizee + string.size();
    data[sizee + string.size()]='\0';
    delete[] old_data;
}


void MyString::push_back(char q) {

    char* old_data = this->data;
    this->data = new char[sizee + 2];
    for (size_t a = 0; a < sizee; a++) this->data[a] = old_data[a];
    this->data[sizee] = q;
    this->data[sizee+1] = '\0';
    this->sizee = sizee + 1;
    delete[] old_data;
}

MyString& MyString::assign(const char* cs, const size_t& n)
{
    unsigned i;
    this->sizee = n + 1;
    this->data = new char[n + 1];
    for (i = 0; i < (this->sizee - 1); i++)
        this->data[i] = cs[i];
    this->data[this->sizee - 1] = '\0';
    return *this;
}

MyString& MyString::insert(const size_t& pos, const MyString& s)
{
    MyString str(data);
    unsigned i, j;
    sizee = s.sizee + str.sizee - 1;
    delete[] data;
    data = new char[sizee];
    for (i = 0; i < pos; i++)
        data[i] = str.data[i];
    for (i = pos, j = 0; j < (s.sizee - 1); i++, j++)
        data[i] = s.data[j];
    for (i = s.sizee + pos - 1, j = pos; i < sizee; i++, j++)
        data[i] = str.data[j];
    return *this;
}

size_t MyString::rfind(const char* s2)
{
    const size_t ln1 = my_strlen(data);
    const size_t ln2 = my_strlen(s2);

    if (ln1 < ln2)
        return size_t(-1);

    for (auto* it = data + ln1 - ln2, *end = data - 1; it != end; --it)
        if (my_strncmp(it, s2, ln2) == 0)
            return size_t(it - data);

    return size_t(-1);
}

int MyString::find(MyString textForFind)
{

    int j = 0;
    for (int i = 0; i < size(); i++) {
        if (data[i] == textForFind[j])
            j++;
        else if (j == textForFind.size())
            return j;
        else
            j = 0;
    }
    return -1;
}
MyString& MyString::erase(const size_t& pos, const size_t& n)
{
    unsigned i, j;
    MyString str(data);
    sizee = str.sizee - n;
    delete[] data;
    data = new char[sizee];
    for (i = 0; i < pos; i++)
        data[i] = str.data[i];
    for (i = pos, j = pos + n; j < str.sizee; i++, j++)data[i] = str.data[j];
    return *this;
    std::string as;
    as.find_first_of("1232");
}

MyString& MyString::replace(const size_t& pos, const size_t& n, const MyString& s)
{
    MyString str(data);
    unsigned i;
    str.erase(pos, n);
    str.insert(pos, s);
    sizee = str.sizee;
    delete[] data;
    data = new char[sizee];
    for (i = 0; i < sizee; i++)
        data[i] = str.data[i];
    return *this;
}

void MyString::swap(MyString& s)
{
    char* str = new char[sizee];
    size_t i = this->copy(str, sizee - 1, 0);
    str[i] = 0;
    *this = s;
    s = str;
    delete[] str;
}

size_t MyString::copy(char* cs, const size_t& n, const size_t& pos) const
{
    size_t i, j;
    for (j = pos, i = 0; i < n; i++, j++)
        cs[i] = data[j];
    return i;
}


void MyString::pop_back() {
    if(sizee>0){
    char* old_data = this->data;
    this->data = new char[sizee];
    for (size_t a = 0; a < sizee-1; a++) this->data[a] = old_data[a];
    data[sizee-1]='\0';
    this->sizee = sizee - 1;
    delete[] old_data;
    }
}


int MyString::find_first_of(MyString textForFind) {
    for (size_t a = 0; a < sizee; a++)
        for (size_t aa = 0; aa < textForFind.sizee; aa++)
            if (data[a] == textForFind[aa]) return a;
    return 0;
}

int MyString::find_last_of(MyString textForFind) {
    for (size_t a = sizee-1; a >=0; a--)
        for (size_t aa = 0; aa < textForFind.sizee; aa++)
            if (data[a] == textForFind[aa]) return a;
    return 0;
}


int MyString::find_first_not_of(MyString textForFind) {
    for (size_t a = 0; a < sizee; a++)
        for (size_t aa = 0; aa < textForFind.sizee; aa++)
            if (data[a] != textForFind[aa]) return a;
    return 0;
}

int MyString::find_last_not_of(MyString textForFind) {
    for (size_t a = sizee - 1; a >= 0; a--)
        for (size_t aa = 0; aa < textForFind.sizee; aa++)
            if (data[a] != textForFind[aa]) return a;
    return 0;
}
