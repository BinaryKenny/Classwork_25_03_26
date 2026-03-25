#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <cstddef>
namespace iknk
{
  template<class T>
  struct Vector {
    Vector();
    ~Vector();
    private:
      T * data;
      size_t size, capacity;
  };
}

#endif
