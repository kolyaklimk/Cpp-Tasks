#pragma once

template<class T> 
class Vector {
public:
	Vector();

	explicit Vector(int s);

	Vector(const Vector& arg);

	Vector<T>& operator=(const Vector<T>& arg);

	~Vector();







	class iterator
	{
	public:
		iterator(T* p) :_curr(p) {}

		T& operator+(int n) 
		{
			return *(_curr+n);
		}

		T& operator-(int n)
		{
			return *(_curr - n);
		}

		T& operator++()
		{
			return *++_curr;
		}

		T& operator--()
		{
			return *--_curr;
		}


		T& operator*()
		{
			return *_curr;
		}

		bool operator==(const iterator& b) const
		{
			return _curr == b._curr;
		}

		bool operator!=(const iterator& b) const
		{
			return _curr != b._curr;
		}

	private:
		T* _curr;
	};

	iterator begin()
	{
		return Vector<T>::iterator(&_elements[0]);
	}

	iterator end()
	{
		return Vector<T>::iterator(&_elements[_size]);
	}

	const iterator cbegin() const
	{
		return Vector<T>::iterator(&_elements[0]);
	}

	const iterator cend() const
	{
		return Vector<T>::iterator(&_elements[_size]);
	}

	iterator rbegin()
	{
		return Vector<T>::iterator(&_elements[_size]);
	}

	iterator rend()
	{
		return Vector<T>::iterator(&_elements[0]);
	}

	const iterator crbegin() const
	{
		return Vector<T>::iterator(&_elements[_size]);
	}

	const iterator crend() const
	{
		return Vector<T>::iterator(&_elements[0]);
	}





	bool empty() const;

	int capacity() const;

	void reserve(int newmalloc);

	void resize(int newsize, T val = T());

	int size() const;

	void clear();

	void push_back(const T& d);

	void emplace(int size, const T& d);

	void erase(int size1, int size2);

	void insert(int size1, const T& d);
	void insert(int size1, const Vector<T>& v);

	void emplace_back(const T& d);

	void pop_back();

	void swap(Vector& other) {
		std::swap(_size, other._size);
		std::swap(_space, other._space);
		std::swap(_elements, other._elements);
	}

	T& operator[](int i);

	const T& operator[](int i) const;

	T& front();

	void assign(int count, const T& value);

	const T& front() const;

	T& back();

	const T& back() const;

	T* data();

	const T* data() const;

	T& at(int);

private:
	int	_size;
	T* _elements;	
	int	_space;
						
};





template<class T>
Vector<T>::Vector() :_size(0), _elements(0), _space(0)
{}

template<class T>
inline Vector<T>::Vector(int s) : _size(s), _elements(new T[s]), _space(s)
{
	for (int index = 0; index < _size; ++index)
		_elements[index] = T();
}

template<class T>
inline Vector<T>::Vector(const Vector& arg) :_size(arg._size), _elements(new T[arg._size])
{
	for (int index = 0; index < arg._size; ++index)
		_elements[index] = arg._elements[index];
}

template<class T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& a)
{
	if (this == &a) return *this;

	if (a._size <= _space)
	{
		for (int index = 0; index < a._size; ++index)
		{
			_elements[index] = a._elements[index];
			_size = a._size;
			return *this;
		}
	}

	T* p = new T[a._size];

	for (int index = 0; index < a._size; ++index)
		p[index] = a._elements[index];

	delete[] _elements;
	_size = a._size;
	_space = a._size;
	_elements = p;
	return *this;
}

template<class T>
Vector<T>::~Vector()
{
	delete[] _elements;
}

template<class T>
inline bool Vector<T>::empty() const
{
	return (_size == 0);
}

template<class T>
inline int Vector<T>::capacity() const
{
	return _space;
}

template<class T>
inline void Vector<T>::reserve(int newalloc)
{
	if (newalloc <= _space) return;

	T* p = new T[newalloc];

	for (int i = 0; i < _size; ++i)
		p[i] = _elements[i];

	delete[] _elements;

	_elements = p;

	_space = newalloc;

}

template<class T>
inline void Vector<T>::resize(int newsize, T val)
{
	reserve(newsize);

	for (int index = _size; index < newsize; ++index)
		_elements[index] = T();

	_size = newsize;
}

template<class T>
inline int Vector<T>::size() const
{
	return _size;
}


template<class T>
inline void Vector<T>::assign(int count, const T& value)
{
	delete[] _elements;
	_elements = new T[count];
	for (int a = 0; a < count; a++)
		_elements[a] = value;
}



template<class T>
inline void Vector<T>::push_back(const T& d)
{
	if (_space == 0)
		reserve(8);
	else if (_size == _space)
		reserve(2 * _space);

	_elements[_size] = d;

	++_size;
}

template<class T>
inline T& Vector<T>::operator[](int i)
{
	return _elements[i];
}

template<class T>
inline const T& Vector<T>::operator[](int i) const
{
	return _elements[i];
}

template<class T>
inline T& Vector<T>::front()
{
	return _elements[0];
}

template<class T>
inline const T& Vector<T>::front() const
{
	return _elements[0];
}

template<class T>
inline T& Vector<T>::back()
{
	return _elements[_size - 1];
}

template<class T>
inline const T& Vector<T>::back() const
{
	return _elements[_size - 1];
}

template<class T>
inline T* Vector<T>::data()
{
	return _elements;
}

template<class T>
inline const T* Vector<T>::data() const
{
	return _elements;
}

template<class T>
T& Vector<T>::at(int v) {
	return T[v];
}


template<class T>
void Vector<T>::emplace(int size, const T& d) {
	T* q = _elements;
	_elements = new T[++_size];
	for (int a = 0; a < size; a++)
		_elements[a] = q[a];
	_elements[size] = d;
	for (int a = size+1; a < _size; a++)
		_elements[a] = q[a];
	delete[] q;
	_space = _size;
}

template<class T>
void Vector<T>::emplace_back(const T& d) {
	T* q = _elements;
	_elements = new T[_size+1];
	for (int a = 0; a < _size; a++)
		_elements[a] = q[a];
	_elements[_size++] = d;
	delete[] q;
	_space = _size;
}

template<class T>
void Vector<T>::erase(int size1, int size2) {
	T* q = _elements;
	_elements = new T[_size - size2];
	for (int a = 0; a < size1; a++)
		_elements[a] = q[a];

	for (int a = size1+size2; a < _size - size2; a++)
		_elements[a-size2] = q[a];
	delete[] q;
	_size -= size2;
	_space = _size;
}

template<class T>
void Vector<T>::insert(int size1, const T& d) {
	T* q = _elements;
	_elements = new T[++_size];
	for (int a = 0; a < size1; a++)
		_elements[a] = q[a];
	_elements[size1] = d;
	for (int a = size1 + 1; a < _size; a++)
		_elements[a] = q[a];
	delete[] q;
	_space = _size;
}

template<class T>
void Vector<T>::insert(int size1, const Vector<T>& v) {
	T* q = _elements;
	_elements = new T[_size + v.size()];
	for (int a = 0; a < v.size1; a++)
		_elements[a] = q[a];
	for (int a = size1; a < size1 + v.size(); a++)
		_elements[a] = v[a - size1];

	for (int a = size1 + v.size(); a < _size + v.size(); a++)
		_elements[a] = q[a - v.size()];
	delete[] q;
	_size += v.size();
	_space = _size;
}