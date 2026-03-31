#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <cstddef>
#include <stdexcept>
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
    size_t getCapacity() const noexcept;

    T & operator[](size_t index);
    void pushBack(const T &);
    void popBack();
    private:
      explicit Vector(size_t size);
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
  Vector(size)
{
  for (size_t i = 0; i < size; i++)
  {
    data[i] = value;
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

template<class T>
iknk::Vector<T>::Vector(size_t size):
  data(size ? new T[size] : nullptr),
  size_(size),
  capacity(size)
{}

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
      new_data = new T[capacity * 2];
      capacity *= 2;
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
T & iknk::Vector<T>::operator[](size_t index)
{
  return data[index];
}
#endif
