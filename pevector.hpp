#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <cstddef>
namespace iknk
{
  template<class T>
  struct Vector {
    Vector();
    ~Vector();
    bool isEmpty();
    private:
      T * data;
      size_t size, capacity;
  };
}

template<class T>
iknk::Vector<T>():
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
