#ifndef MANOVECTOR_H
#define MANOVECTOR_H

// -- after comment designates completed sections of code

#include <limits>

template <class valueType>
class ManoVector 
{

private:
	valueType* _element;
	int _size, _capacity;

public:
    using size_type = std::size_t;
    using value_type = valueType;
    using iterator = valueType*;
    using const_iterator = const valueType*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

// CONSTRUCTOR --
    ManoVector() : _element(new valueType[0]), _size(), _capacity() {}
    explicit ManoVector(int size);
    ManoVector(int size, int val);
    ManoVector(const std::initializer_list<valueType>& vec);
    ManoVector(const ManoVector<valueType>& vec);
    template<class InputIterator> ManoVector(InputIterator first, InputIterator last);
// DESTRUCTOR --
    ~ManoVector() {
        delete[] _element;
    }

// OPERATOR= --
    ManoVector& operator=(ManoVector&& vect);
    ManoVector& operator=(const ManoVector<valueType>& vect);
    
// ITERATOR --

    // begin, cbegin --
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    // end, cend --
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    // rbegin, rend --
    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;

    // crbegin, crend --
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

// CAPACITY --

    // size --
    int size() const { return _size; }
    // max_size --
    size_t max_size() const;
    // resize --
    void resize(int new_size);
    // capacity --
    int capacity() const { return _capacity; }
    // empty --
    bool empty() const;
    // reserve --
    void reserve(int new_size);
    // shrink_to_fit --
    void shrink_to_fit();
    
// ELEMENT ACCESS --

    //operator[] --
    valueType& operator[](int i) { return _element[i]; }
    //at --
    valueType& at(int pos);
    //front --
    valueType& front();
    //back --
    valueType& back();
    //data --
    valueType* data();

// MODIFIERS

    //push_back --
    void push_back(const valueType& value);
    //pop_back --
    void pop_back();
    //insert --
    iterator insert(iterator ndx, const valueType& val);
    //erase --
    iterator erase(iterator ndx);
    iterator erase(iterator first, iterator last);
    //swap --
    void swap(ManoVector& vect);
    //clear --
    void clear();
    //emplace_back --
    template <typename ... Args> valueType& emplace_back(Args&& ... args);
    //emplace --
    template <typename ... Args> iterator emplace(const_iterator pos, Args&& ... args);
    void move_elem(valueType* dest, valueType* from, size_type n);
// Non-member function overloads

    // swap --
    void swap(valueType& x, valueType& y);

// Relational operators

    // operator== --
    bool operator==(const ManoVector<valueType>& vect) const;
    // operator >= --
    bool operator>=(const ManoVector<valueType>& vect) const;
    // operator <= --
    bool operator<=(const ManoVector<valueType>& vect) const;
    // operator != --
    bool operator!=(const ManoVector<valueType>& vect) const;
    // operator > --
    bool operator>(const ManoVector<valueType>& vect) const;
    // operator < --
    bool operator<(const ManoVector<valueType>& vect) const;
};

template<class valueType>
ManoVector<valueType>::ManoVector(int size) : _size(size), _capacity(size) 
{
    _element = new valueType[size];
}

template<class valueType >
ManoVector<valueType>::ManoVector(int size, int val) : _size(size), _capacity(size) 
{
    _element = new valueType[_size];

    for (int i = 0; i < _size; i++)
        _element[i] = val;
}

template<class valueType>
ManoVector<valueType>::ManoVector(const ManoVector<valueType>& vect) : _size(vect.size()), _capacity(vect.capacity()) 
{
    _element = new valueType[_capacity];

    for (int i = 0; i < _size; i++)
        _element[i] = vect._element[i];
}

template<class valueType>
ManoVector<valueType>::ManoVector(const std::initializer_list<valueType>& vect) : _size(vect.size()), _capacity(vect.size()) 
{
    _element = new valueType[vect.size()];

    for (int i = 0; i < vect.size(); i++)
        _element[i] = *(vect.begin() + i);
}

template<class valueType>
template<class InputIterator>
ManoVector<valueType>::ManoVector(InputIterator first, InputIterator last)
{
    size_type count = 0;
    for (InputIterator curr = first; curr != last; ++curr) ++count;
    _size = count;
    _capacity = count + count / 2 + 1;
    _element = new valueType[_capacity];
    for (size_type i = 0; i < count; i++)
        _element[i] = *first++;
}

template <class valueType>
ManoVector<valueType>& ManoVector<valueType>::operator=(ManoVector&& vec) 
{
    if (&vec == this)
        return *this;
    _element = vec._element;
    _size = vec._size;
    _capacity = vec._capacity;
    vec._element = nullptr;
    vec._size = 0;
    vec._capacity = 0;
    return *this;
}

template <class valueType>
ManoVector<valueType>& ManoVector<valueType>::operator=(const ManoVector<valueType>& vec) 
{
    if (&vec == this)
        return *this;
    valueType* newCont = new valueType[vec._size];
    for (int i = 0; i != vec._size; ++i)  
        newCont[i] = vec._element[i];
    delete[] _element;  
    _element = newCont;       
    _size = vec._size;
    _capacity = vec._capacity;
    return *this;
}

template<class valueType>
typename ManoVector<valueType>::iterator ManoVector<valueType>::begin() 
{
    return _element;
}

template<class valueType>
typename ManoVector<valueType>::const_iterator ManoVector<valueType>::begin() const 
{
    return _element;
}

template<class valueType>
typename ManoVector<valueType>::const_iterator ManoVector<valueType>::cbegin() const 
{
    return begin();
}

template<class valueType>
typename ManoVector<valueType>::iterator ManoVector<valueType>::end() 
{
    return _element + _size;
}

template<class valueType>
typename ManoVector<valueType>::const_iterator ManoVector<valueType>::end() const 
{
    return _element + _size;
}

template<class valueType>
typename ManoVector<valueType>::const_iterator ManoVector<valueType>::cend() const 
{
    return end();
}

template<class valueType>
typename ManoVector<valueType>::reverse_iterator ManoVector<valueType>::rbegin() 
{
    return reverse_iterator(_element + _size);
}

template<class valueType>
typename ManoVector<valueType>::reverse_iterator ManoVector<valueType>::rend()
{
    return reverse_iterator(_element);
}

template<class valueType>
typename ManoVector<valueType>::const_reverse_iterator ManoVector<valueType>::rbegin() const
{
    return reverse_iterator(_element + _size);
}

template<class valueType>
typename ManoVector<valueType>::const_reverse_iterator ManoVector<valueType>::rend() const
{
    return reverse_iterator(_element);
}

template<class valueType>
typename ManoVector<valueType>::const_reverse_iterator ManoVector<valueType>::crbegin() const
{
    return rbegin();
}

template<class valueType>
typename ManoVector<valueType>::const_reverse_iterator ManoVector<valueType>::crend() const
{
    return rend();
}

template <class valueType>
size_t ManoVector<valueType>::max_size() const 
{
    return std::numeric_limits<size_type>::max();
}

template<class valueType>
void ManoVector<valueType>::resize(int new_size) 
{
    if (new_size < 0)
        throw std::exception();
    if (new_size < _size)
        _size = new_size;
    if (new_size > _capacity)
    {
        valueType* temp = new valueType[new_size];

        for (int i = 0; i < _size; i++)
            temp[i] = _element[i];

        delete[] _element;
        _element = temp;
        _capacity = new_size;
    }
}

template <class valueType>
bool ManoVector<valueType>::empty() const 
{
    return (_size == 0);
}

template<class valueType>
void ManoVector<valueType>::reserve(int amt) 
{
    if (_capacity < amt)
        resize(amt);
}

template<class valueType>
void ManoVector<valueType>::shrink_to_fit() 
{
    valueType* temp = new valueType[_size];

    for (int i = 0; i < _size; i++)
        temp[i] = _element[i];

    delete[] _element;
    _element = temp;
    _capacity = _size;
}

template <class valueType>
valueType& ManoVector<valueType>::at(int pos) 
{
    if (pos >= _size)
        throw std::out_of_range("Index was out of range.");
    return _element[pos];
}

template <class valueType>
valueType& ManoVector<valueType>::front()
{
    return _element[0];
}

template <class valueType>
valueType& ManoVector<valueType>::back()
{
    return _element[_size - 1];
}

template <class valueType>
valueType* ManoVector<valueType>::data()
{
    return _element;
}

template<class valueType>
void ManoVector<valueType>::push_back(const valueType& value)
{
    if (_size == _capacity)
        reserve(2 * _capacity + 1);
    _element[_size++] = value;
}

template<class valueType>
void ManoVector<valueType>::pop_back() 
{
    if (_size > 0)
        _size--;
}

template<class valueType>
typename ManoVector<valueType>::iterator ManoVector<valueType>::insert(iterator iter, const valueType& val)
{
    int i = 0;

    if (_capacity > _size) 
    {
        for (iterator it(_element + _size); it != iter; it--, i++)
            _element[_size - i] = _element[_size - i - 1];
        *iter = val;
        _size++;
    }
    else 
    {
        valueType* temp = new valueType[_size + 1];
        for (iterator it(_element); it != iter; it++, i++)
            temp[i] = _element[i];
        temp[i] = val;
        i++;

        for (iterator it(_element + i + 1); it != _element + _size + 2; it++, i++)
            temp[i] = _element[i - 1];
        delete[] _element;
        _element = temp;
        _size++;
        _capacity = _size;
    }
    return iter;
}

template<class valueType>
typename ManoVector<valueType>::iterator ManoVector<valueType>::erase(iterator ndx) 
{
    int i = 0;
    auto it = (*this).begin();
    for (it; it != ndx; it++, i++);
    for (auto it = ndx + 1; it != (*this).end(); it++, i++)
        _element[i] = _element[i + 1];
    _size--;
    return ndx;
}

template<class valueType>
typename ManoVector<valueType>::iterator ManoVector<valueType>::erase(iterator first, iterator last) 
{
    int i = 0;
    int temp = 0;
    auto it = (*this).begin();
    for (it; it != first; it++, i++);
    for (it = first; it != last; it++, temp++, i++);
    for (auto it = last; it != (*this).end(); it++, i++)
        _element[i - temp] = _element[i];
    _size -= temp;
    return last;
}

template<class valueType>
void ManoVector<valueType>::swap(ManoVector& vect) 
{
    std::swap(_element, vect._element);
    std::swap(_size, vect._size);
    std::swap(_capacity, vect._capacity);
}

template <class valueType>
void ManoVector<valueType>::clear() 
{
    _capacity = 0;
    _size = 0;
    delete[] _element;
}

template <class valueType>
template <typename ... Args> 
valueType& ManoVector<valueType>::emplace_back(Args&& ... args)
{
    if (_size == _capacity)
    {
        reserve(_capacity + _capacity / 2 + 1);
    }
    return _element[_size++] = std::move(valueType(std::forward<Args>(args) ...));
}

template<typename valueType>
template<typename ...Args>
typename ManoVector<valueType>::iterator ManoVector<valueType>::emplace(const_iterator iter, Args && ...args)
{
    size_type pos = iter - _element;
    iterator _iter = &_element[pos]; 

    if (_size == _capacity)
    {
        reserve(_capacity + _capacity / 2 + 1);
    }
    _iter = &_element[pos];
    move_elem(_iter + 1, _iter, _size - (_iter - _element));
    ++_size;
    *_iter = std::move(valueType(std::forward<Args>(args) ...));
    return _iter;
}

template<typename valueType>
void ManoVector<valueType>::move_elem(valueType* dest, valueType* from, size_type n)
{
    if (dest < from)
    {
        valueType* _dest = dest, * _from = from;
        for (size_t i = 0; i < n; i++)
            *_dest++ = std::move(*_from++);
    }
    else if (dest > from)
    {
        valueType* _dest = dest + n - 1, * _from = from + n - 1;
        for (size_t i = n; i > 0; i--)
            *_dest-- = std::move(*_from--);
    }
    else
        return;
}

template <class valueType>
void ManoVector<valueType>::swap(valueType& x, valueType& y) 
{
    valueType temp = x;
    x = y;
    y = temp;
}

template<class valueType>
bool ManoVector<valueType>::operator==(const ManoVector<valueType>& vect) const 
{
    if (_size == vect._size && _capacity == vect._capacity) 
    {
        for (int i = 0; i < _size; i++)
            if (_element[i] != vect._element[i])
                return false;
        return true;
    }
    return false;
}

template<class valueType>
bool ManoVector<valueType>::operator>=(const ManoVector<valueType>& vect) const
{
    if (_size == vect._size && _capacity == vect._capacity)
    {
        for (int i = 0; i < _size; i++)
            if (_element[i] <= vect._element[i])
                return false;
        return true;
    }
    else return (_size >= vect._size && _capacity >= vect._capacity);
}

template<class valueType>
bool ManoVector<valueType>::operator<=(const ManoVector<valueType>& vect) const
{
    if (_size == vect._size && _capacity == vect._capacity)
    {
        for (int i = 0; i < _size; i++)
            if (_element[i] >= vect._element[i])
                return false;
        return true;
    }
    else return (_size <= vect._size && _capacity <= vect._capacity);
}

template<class valueType>
bool ManoVector<valueType>::operator!=(const ManoVector<valueType>& vect) const
{
    return !operator==(vect);
}

template<class valueType>
bool ManoVector<valueType>::operator>(const ManoVector<valueType>& vect) const
{
    if (_size == vect._size && _capacity == vect._capacity)
    {
        for (int i = 0; i < _size; i++)
            if (_element[i] < vect._element[i])
                return false;
        return true;
    }
    else return (_size > vect._size && _capacity > vect._capacity);
}

template<class valueType>
bool ManoVector<valueType>::operator<(const ManoVector<valueType>& vect) const
{
    if (_size == vect._size && _capacity == vect._capacity)
    {
        for (int i = 0; i < _size; i++)
            if (_element[i] > vect._element[i])
                return false;
        return true;
    }
    else return (_size < vect._size && _capacity < vect._capacity);
}

#endif