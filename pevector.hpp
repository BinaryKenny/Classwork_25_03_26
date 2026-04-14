#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <stdexcept>
#include <utility>
#include <vector>

namespace iknk
{
  template< class T >
  struct Iterator;

  template< class T>
  struct CIterator;

  template< class T >
  struct Vector {
    Vector();
    ~Vector();
    Vector(size_t size, const T & value);
    Iterator< T > begin();
    Iterator< T > end();
    Iterator< T > iterator(size_t i);
    CIterator< T > cbegin();
    CIterator< T > cend();
    CIterator< T > citerator(size_t i);

    void insert(size_t id, const T & t);
    void insert(size_t id, const Vector<T> & rhs, size_t beg, size_t end);

    void insert(Iterator<T> pos, const T & value);
    void insert(Iterator<T> pos, CIterator<T> begin, CIterator<T> end);
    void insert(Iterator< T > pos, const T & value, size_t k);

    void erase(size_t id);
    void erase(size_t beg, size_t end);

    void erase(Iterator< T > pos);
    void erase(Iterator< T > begin, Iterator< T > end);
    void erase(Iterator< T > begin, size_t k);
 
//ДОМАШНЯЯ РАБОТА
//Реализовать итераторы вектора(random access), const and non-const (их не тестировать)
//Еще придумать по 3 insert/erase с итераторами
    Vector(const Vector<T> & rhs);
    Vector(Vector<T> && rhs) noexcept;
    Vector<T> & operator=(const Vector<T> & rhs);
    Vector<T> & operator=(Vector<T> && rhs) noexcept;
    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;
      
    void swap(Vector<T> & rhs) noexcept;
    
    void pushBack(const T &);
    void popBack();
    void pushFront(const T &);

    T & operator[](size_t id) noexcept;
    const T & operator[](size_t id) const noexcept;
    T & at(size_t id);
    const T & at(size_t id) const;
    bool operator==(const Vector<T> & rhs) const noexcept;

    private:
      explicit Vector(size_t size);
      T * data;
      size_t size_, capacity;
  };

  template<class T>
  struct Iterator {
    Iterator(Vector< T > &, size_t);
    ~Iterator() = default;
    Iterator< T > operator+(size_t i);
    Iterator< T > operator-(size_t i);
    void write(Iterator< T > & it, const T & value);
    void cut(Iterator< T > & it);

    Vector<T> & vector;
    size_t id;
  };

  template< class T >
  struct CIterator {
    CIterator(Vector< T > &, size_t);
    ~CIterator() = default;
    CIterator< T > operator+(size_t i);
    CIterator< T > operator-(size_t i);
    T read(CIterator< T > & it);

    Vector< T > vector;
    size_t id;
  };
}

template<class T>
iknk::Vector<T>::Vector():
  data(nullptr),
  size_(0),
  capacity(0)
{}

template <class T>
iknk::Vector<T>::~Vector()
{
  delete [] data;
}

template<class T>
iknk::Vector<T>::Vector(size_t size):
  data(size ? new T[size * 2] : nullptr),
  size_(size),
  capacity(size * 2)
{}

template<class T>
iknk::Iterator<T>::Iterator(Vector<T> & v, size_t i):
vector(v),
id(i)
{}

template<class T>
iknk::Iterator<T> iknk::Iterator<T>::operator+(size_t i) {
  if (id + i > vector.getSize() - 1) {
    throw std::out_of_range("Iterator is out of bound");
  }
  return Iterator<T>(vector, id + i);
}

template<class T>
iknk::Iterator< T > iknk::Iterator<T>::operator-(size_t i) {
  if (id + 1 - i <= 0) {
    throw std::out_of_range("Iterator is out of bound");
  }
  return Iterator< T >(vector, id - i);
}

template<class T>
void iknk::Iterator<T>::write(Iterator<T> &it, const T &value) {
  it.vector[id] = value;
}

template<class T>
void iknk::Iterator<T>::cut(Iterator<T> &it) {
  vector.erase(it.id);
}


template<class T>
iknk::CIterator<T>::CIterator(Vector<T> & v, size_t i):
vector(v),
id(i)
{}

template<class T>
iknk::CIterator<T> iknk::CIterator<T>::operator+(size_t i) {
  if (id + i > vector.getSize() - 1) {
    throw std::out_of_range("Const Iterator is out of bound");
  }
  return CIterator<T>(vector, id + i);
}

template<class T>
iknk::CIterator<T> iknk::CIterator<T>::operator-(size_t i) {
  if (id + 1 - i <= 0) {
    throw std::out_of_range("Const Iterator is out of bound");
  }
  return CIterator<T>(vector, id - i);
}

template<class T>
T iknk::CIterator<T>::read(CIterator<T> &it) {
  return it.vector[id];
}


template<class T>
iknk::Vector<T>::Vector(const Vector<T> & rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); i++)
  {
    data[i] = rhs.data[i];
  }
}

template<class T>
iknk::Vector<T> & iknk::Vector<T>::operator=(const Vector<T> & rhs)
{
  if (this == std::addressof(rhs))   //для взятия именно адреса
  {
    return *this;
  }
  Vector<T> cpy(rhs);
  swap(cpy);
  return *this;
}

template<class T>
iknk::Vector<T>::Vector(Vector<T> && rhs) noexcept:
data(rhs.data),
size_(rhs.size_),
capacity(rhs.capacity)
{
  rhs.data = nullptr;
}
template<class T>
iknk::Vector<T> & iknk::Vector<T>::operator=(Vector<T> && rhs) noexcept
{
  if (this == &rhs)
  {
    return *this;
  }
  Vector<T> cpy(std::move(rhs));
  swap(cpy);
  return *this;
}
template<class T>
void iknk::Vector<T>::pushFront(const T & t)
{
  Vector<T> v(getSize() + 1);
  v[0] = t;
  {
    for (size_t i = 1; i < v.getSize(); ++i)
    {
      v[i] = (*this)[i - 1];
    }
  }
  swap(v);
}

template<class T>
void iknk::Vector<T>::swap(Vector & rhs) noexcept
{
  std::swap(data, rhs.data);
  std::swap(size_, rhs.size_);
  std::swap(capacity, rhs.capacity);
}

template<class T>
T & iknk::Vector<T>::at(size_t id)
{
  const Vector<T> * cthis = this;
  const T & cr = cthis->at(id);
  T & r = const_cast< T & >(cr);
  return r;
}

template<class T>
bool iknk::Vector<T>::isEmpty() const noexcept
{
  return !size_;
}

template<class T>
const T & iknk::Vector<T>::at(size_t id) const
{
  if (id < getSize())
  {
      return (*this)[id];
  }
  throw std::out_of_range("id out of bound");
}

template<class T>
T & iknk::Vector<T>::operator[](size_t id) noexcept
{
  return data[id];
}

template<class T>
const T & iknk::Vector<T>::operator[](size_t id) const noexcept
{
  return data[id];
}

template<class T>
size_t iknk::Vector<T>::getSize() const noexcept
{
  return size_;
}

template<class T>
iknk::Vector<T>::Vector(size_t size, const T & value):
  Vector(size)
{
  for (size_t i = 0; i < size; i++)
  {
    data[i] = value;
  }
}

template<class T>
iknk::Iterator<T> iknk::Vector<T>::begin() {
  return Iterator< T >(*this, 0);
}

template<class T>
iknk::Iterator<T> iknk::Vector<T>::end() {
  return Iterator< T >(*this, size_ - 1);
}

template<class T>
iknk::Iterator<T> iknk::Vector<T>::iterator(size_t i) {
  return Iterator< T >(*this, i);
}

template<class T>
iknk::CIterator<T> iknk::Vector<T>::cbegin() {
  return CIterator< T >(*this, 0);
}

template< class T>
iknk::CIterator< T > iknk::Vector< T >::cend() {
  return CIterator< T >(*this, size_ - 1);
}

template<class T>
iknk::CIterator<T> iknk::Vector<T>::citerator(size_t i) {
  return CIterator< T >(*this, i);
}

template<class T>
void iknk::Vector<T>::insert(size_t id, const T &t) {
  T * new_data = nullptr;
  size_t new_capacity = size_ + 1 > capacity ? capacity * 2 + 1 : capacity;
  try {
    new_data = new T[new_capacity];
  }
  catch (...) {
    throw std::bad_alloc();
  }
  capacity = new_capacity;
  for (size_t i = 0; i < size_ + 1; i++) {
    try {
      if (i != id) {
        new_data[i] = data[i];
      }
      else {
        new_data[i] = t;
      }
    } catch (...) {
      delete new_data;
      throw std::logic_error("Some problems with inserting");
    }
  }
  size_++;
  delete [] data;
  data = new_data;
}

template<class T>
void iknk::Vector<T>::insert(size_t id, const Vector<T> &rhs, size_t beg, size_t end) {
  size_t sizeOfSegment = end - beg;
  T * segment = new T[sizeOfSegment]();
  T * new_data = nullptr;
  try {
    if (rhs == *this) {
      for (size_t i = 0; i < sizeOfSegment; i++) {
        segment[i] = data[beg + i];
      }
    }
    else {
      for (size_t i = 0; i < sizeOfSegment; i++) {
        segment[i] = rhs.data[beg + i];
      }
    }
    size_t new_capacity = capacity;
    if (size_ + sizeOfSegment > capacity) {
      new_capacity = capacity * 2;
    }
    try {
      new_data = new T[new_capacity];
      capacity *= 2;
    }
    catch (...) {
      throw std::bad_alloc();
    }
    for (size_t i = 0; i < id; i++) {
      new_data[i] = data[i];
    }
    for (size_t i = id; i < end + id - beg; i++) {
      new_data[i] = segment[i - id];
    }
    for (size_t i = end + id - beg; i < size_ + sizeOfSegment; i++) {
      new_data[i] = data[i - end + beg];
    }
  }
  catch (...) {
    throw std::logic_error("Some problems with coping (it isn't method's exception)");
  }
  delete [] data;
  data = new_data;
  size_ = size_ + sizeOfSegment;
}

template<class T>
void iknk::Vector<T>::insert(Iterator<T> pos, const T & value) {
  pos.vector.insert(pos.id, value);
}

template<class T>
void iknk::Vector<T>::insert(Iterator<T> pos, CIterator<T> begin, CIterator<T> end) {
  pos.vector.insert(pos.id, begin.vector, begin.id, end.id);
}

template<class T>
void iknk::Vector<T>::insert(Iterator<T> pos, const T & value, size_t k) {
  T * new_data = nullptr;
  size_t new_capacity = capacity;
  if (k + size_ > capacity) {
    new_capacity = capacity * 2;
  }
  try {
    new_data = new T[new_capacity];
    capacity *= 2;
  }
  catch (...) {
    throw std::bad_alloc();
  }
  for (size_t i = 0; i < pos.id; i++) {
    new_data[i] = data[i];
  }
  for (size_t i = pos.id; i < pos.id + k; i++) {
    new_data[i] = value;
  }
  for (size_t i = pos.id + k; i < size_ + k; i++) {
    new_data[i] = data[i - k];
  }
  size_ += k;
  delete [] data;
  data = new_data;
}

template<class T>
void iknk::Vector<T>::erase(size_t id) {
  T * new_data = new T[capacity];
  for (size_t i = 0; i < size_; i++) {
    if (i == id) {
      continue;
    }
    new_data[i] = data[i];
  }
  delete [] data;
  data = new_data;
  size_--;
}

template<class T>
void iknk::Vector<T>::erase(size_t beg, size_t end) {
  T * new_data = new T[capacity];
  size_t id = 0;
  for (size_t i = 0; i < size_; i++) {
    if (i < beg || i >= end) {
      new_data[id] = data[i];
      id++;
    }
  }
  delete [] data;
  data = new_data;
  size_ = size_ - (end - beg);
}

template<class T>
size_t iknk::Vector<T>::getCapacity() const noexcept
{
  return capacity;
}

template<class T>
void iknk::Vector<T>::pushBack(const T & value)
{
  if (size_ == capacity)
  {
    T * new_data = nullptr;
    try
    {
      new_data = new T[capacity * 2 + 1];
      capacity = capacity * 2 + 1;
      for (size_t i = 0; i < size_; i++)
      {
        new_data[i] = data[i];
      }
      delete [] data;
      data = new_data;
    }
    catch (...)
    {
      delete new_data;
      throw;
    }
  }
  data[size_++] = value;
}

template<class T>
void iknk::Vector<T>::popBack()
{
  if (size_ == 0)
  {
    throw std::logic_error("Logic error: vector is empty");
  }
  size_--;
}

template<class T>
bool iknk::Vector<T>::operator==(const Vector<T> & rhs) const noexcept
{
  if (getSize() != rhs.getSize()) {
    return false;
  }
  for (size_t i = 0; i < getSize(); i++) {
    if (data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}
#endif
