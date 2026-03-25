#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <cstddef>
namespace iknk
{
  template<class T>
  struct Vector {
    Vector();
    ~Vector();
    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    private:
      T * data;
      size_t size, capacity;
  };
}

template<class T>
bool iknk::Vector<T>::isEmpty() const noexcept
{
  return !size;
}

template<class T>
size_t iknk::Vector<T>::getSize() const noexcept
{
  return size;
}

template<class T>
iknk::Vector<T>::Vector():
  data(nullptr),
  size(0),
  capacity(0)
{}
template <class T>
iknk::Vector<T>::~Vector()
{
  delete [] data;
}
#endif
