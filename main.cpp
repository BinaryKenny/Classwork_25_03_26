#include "pevector.hpp"
#include <iostream>
#include <cstring>
using iknk::Vector;

bool testConstractAndDecstruct(const char ** pname)
{
  *pname = __func__;
  iknk::Vector<int> v;
  return true;
}

bool testDefaultVectorIsEmpty(const char ** pname)
{
  *pname = __func__;
  Vector<int> v;
  return v.isEmpty();
}

bool testSizeOfEmptyVector(const char ** pname)
{
  *pname = __func__;
  Vector<int> v;
  return !v.getSize();
}

bool testSizeOfNonEmptyVector(const char ** pname)
{
  *pname = __func__;
  constexpr size_t size = 2ull;
  try
  {
    Vector<int> v(size, 10);
    return v.getSize() == size;
  }
  catch(...)
  {
    throw;
  }
}

bool testCapacityOfVector(const char ** pname)
{
  *pname = __func__;
  constexpr size_t size = 2ull;
  try
  {
    Vector<int> v(size, 10);
    return v.getCapacity() == size;
  }
  catch(...)
  {
    throw;
  }
}

bool testPushBackOfVector(const char ** pname)
{
  *pname = __func__;
  try
  {
    Vector<int> v(2, 10);
    v.pushBack(7);
    return v[v.getSize() - 1] == 7;
  }
  catch (...)
  {
    throw;
  }
}

bool testPopBackOfVector(const char ** pname)
{
  *pname = __func__;
  try
  {
    Vector<int> v(2, 10);
    v.popBack();
    return v.getSize() == 1;
  }
  catch (...)
  {
    throw;
  }
}

bool testElementCheckedAccess(const char ** pname)
{
  *pname = __func__;
  Vector< int > v;
  v.pushBack(2);
  try
  {
    int & r = v.at(0);
    return r == 2;
  }
  catch(...)
  {
    return false;
  }
}

bool testElementCheckedConstAccess(const char ** pname)
{
  *pname = __func__;
  Vector< int > v;
  v.pushBack(2);
  const Vector< int > & rv = v;
  try
  {
    const int & r = rv.at(0);
    return r == 2;
  }
  catch(...)
  {
    return false;
  }
}

bool testElementCheckedOutOfBoundAccess(const char ** pname)
{
  *pname = __func__;
  Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch (const std::out_of_range & e)
  {
    const char * text = e.what();
    return !std::strcmp("id out of bound", text);
  }
  catch(...)
  {
    return false;
  }
}

bool testElementCheckedOutOfBoundConstAccess(const char ** pname)
{
  *pname = __func__;
  const Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch (const std::out_of_range & e)
  {
    const char * text = e.what();
    return !std::strcmp("id out of bound", text);
  }
  catch(...)
  {
    return false;
  }
}

bool testCopyConstructor(const char ** pname)
{
  *pname = __func__;
  Vector< int > v(10, 2);
  v.pushBack(1);
  v.pushBack(2);
  Vector< int > yav = v;
  if (v.isEmpty() || yav.isEmpty())
  {
    throw std::out_of_range("id out of bound");
  }
  bool isEqual = yav.getSize() == v.getSize();
  for (size_t i = 0; isEqual && i < v.getSize(); i++)
  {
    try
    {
      isEqual = v.at(i) == yav.at(i);
    }
    catch(...)
    {
      return false;
    }
  }
  return isEqual;
}

int main()
{
  size_t failed = 0;
  using test_t = bool(*)(const char **);
  using case_t = std::pair<test_t, const char *>;
    case_t tests[] = {
        {testConstractAndDecstruct, "Vector must be default"
            " constructable"},
        {testDefaultVectorIsEmpty, "Default constructed"
            " Vector must be empty"},
        {testSizeOfEmptyVector, "Size of empty"
            " Vector must be zero"},
        {testSizeOfNonEmptyVector, "Size of non-empty"
            " vector must be greater than zero"},
        {testCapacityOfVector, "Capacity of non-empty"
            " vector must be greater than zero"},
        {testPushBackOfVector, "PushBack is wrong"},
        {testPopBackOfVector, "PopBack is wrong: size of"
            " vector is not the same the expected"},
        {testElementCheckedAccess, "Inbound access must"
            " return lvalue reference"},
        {testElementCheckedOutOfBoundAccess, "Out of bound access"
            " must generate exception"},
        {testCopyConstructor, "Copied vector must be"
            " equal to original"},
        {testElementCheckedConstAccess, "Inbound const access must"
            " return lvalue reference"},
        {testElementCheckedOutOfBoundConstAccess, "Out of bound const"
            " access must generate exception"}
  };
  size_t count = sizeof(tests) / sizeof(case_t);
  for (size_t i = 0; i < count; i++)
  {
    const char * testName = nullptr;
    bool r = false;
    try
    {
      r = tests[i].first(&testName);
    }
    catch(const std::logic_error & e)
    {
      std::cout << "[NOT RUN] " << testName << "\n";
      std::cout << "\t" << "Reason: " << e.what() << "\n";
      failed++;
      continue;
    }
    if (!r)
    {
      failed++;
      std::cout << "[Fail] " << testName << "\n";
      std::cout << "\t" << tests[i].second << "\n";
    }
  }
  std::cout << "Summary:\n" << "\t" << (count - failed) << " passed\n";
  std::cout << "\t" << count << " total\n";
}
