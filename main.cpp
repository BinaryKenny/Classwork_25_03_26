#include "pevector.hpp"
#include <iostream>
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

int main()
{
  size_t failed = 0;
  using test_t = bool(*)(const char **);
  using case_t = std::pair<test_t, const char *>;
  case_t tests[] = {
    {testConstractAndDecstruct, "Vector must be default constructable"},
    {testDefaultVectorIsEmpty, "Default constructed Vector must be empty"},
    {testSizeOfEmptyVector, "Size of empty Vector must be zero"},
    {testSizeOfNonEmptyVector, "Size of non-empty vector must be greater than zero"},
    {testCapacityOfVector, "Capacity of non-empty vector must be greater than zero"},
    {testPushBackOfVector, "PushBack is wrong"}
  };
  size_t count = sizeof(tests) / sizeof(case_t);
  for (size_t i = 0; i < count; i++)
  {
    const char * testName = nullptr;
    bool r = tests[i].first(&testName);
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
