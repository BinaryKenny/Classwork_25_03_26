#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <cstddef>
namespace iknk
{
  template<class T>
  struct Vector {
    Vector();
    ~Vector();
    Vector(size_t size, const T & value);
    Vector(const Vector<T> & rhs) = delete;
    Vector<T> & operator=(const Vector<T> & rhs) = delete;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;

    void pushBack(const T &); // написать pushBack()
    void popBack(); // написать

    private:
      T * data;
      size_t size_, capacity;
  };
}

template<class T>
bool iknk::Vector<T>::isEmpty() const noexcept
{
  return !size_;
}

template<class T>
size_t iknk::Vector<T>::getSize() const noexcept
{
  return size_;
}

template<class T>
iknk::Vector<T>::Vector(size_t size, const T & value):
  data(size ? new T[size] : nullptr),
  size_(size),
  capacity(size)
{
  for (size_t i = 0; i < size; i++)
  {
    try
    {
      data[i] = value;
    }
    catch(...)
    {
      delete [] data;
      throw;
    }
  }
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
#endif
