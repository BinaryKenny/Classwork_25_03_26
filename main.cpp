#include "pevector.hpp"
#include <iostream>
#include <cstring>
#include <math.h>
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
    return v.getCapacity() == size * 2;
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

bool testOperatorCopy(const char ** pname) {
  *pname = __func__;
  Vector< int > v1(10, 2);
  Vector < int > v2(9, 5);
  try {
    v1 = v2;
    if (v1 == v2) {
      return true;
    }
  }
  catch (...) {
    return false;
  }
}

bool testMovementConstructor(const char ** pname) {
  *pname = __func__;
  Vector < int > v (Vector< int >(10, 2));
  Vector < int > copy_v(10, 2);
  return v == copy_v;
}

bool testMovementOperator(const char ** pname) {
  *pname = __func__;
  Vector< int > v (Vector< int >(10, 2));
  v = Vector< int >(9, 8);
  Vector< int > copy_v(9, 8);
  return v == copy_v;
}

bool testPushFront(const char ** pname) {
  *pname = __func__;
  Vector< int > v(10, 2);
  int value = 1000;
  int check_value = 67;
  v.pushBack(check_value);
  v.pushFront(value);
  if (v[v.getSize() - 1] != check_value) {
    return false;
  }
  return v[0] == value;
}

bool testSwapVector(const char ** pname) {
  *pname = __func__;
  try {
    Vector< int > v1(10, 2);
    Vector< int > v2(6, 7);
    Vector< int > yav1(v1);
    Vector< int > yav2(v2);
    v1.swap(v2);
    return yav1 == v2 && yav2 == v1;
  }
  catch (...) {
    throw std::logic_error("Bad allocation of member");
  }
}

bool testSingleInsert(const char ** pname) {
  *pname = __func__;
  try {
    Vector< int > v(10, 2);
    v.pushBack(67);
    v.insert(3, 10);
    if (v[3] == 10 && v[v.getSize() - 1] != 67) {
      return true;
    }
  }
  catch (...) {
    throw std::logic_error("Exception of inserting");
  }
}

bool testSegmentInsert(const char ** pname) {
  *pname = __func__;
  int expected[] = {0,1,2,5,6,7,8,9,3,4,5,6,7,8,9};
  Vector< int > v(10, 0);
  for (size_t i = 1; i < 10; i++) {
    v[i] = i;
  }
  v.insert(3, v, 5, 10);
  if (v.getSize() != 15) {
    return false;
  }
  for (size_t i = 0; i < v.getSize(); i++) {
    if (expected[i] != v[i]) {
      return false;
    }
  }
  return true;
}

bool testSingleErase(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  try {
    v.pushBack(9);
    v.pushBack(72);
    v.pushBack(67);
    v.pushBack(76);
    v.erase(2);
  }
  catch (...) {
    throw std::logic_error("Exception of pushBack (bad alloc)");
  }
  if (v[2] == 67) {
    return false;
  }
  if (v.getSize() == 3) {
    return true;
  }
  return false;
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
          " access must generate exception"},
    {testOperatorCopy, "Copied vector must be equal to original"},
    {testMovementConstructor, "Moved vector must be equal to original"},
    {testMovementOperator, "Moved vector must be equal to original"},
    {testPushFront, "First value must be equal to added value. Also, "
          " the rest of vector should be the same to vector before changing"},
    {testSwapVector, "Swaped vector must be equal to copy of its original"},
    {testSingleInsert, "Inserted value under the id must be equal to the added value"},
    {testSegmentInsert, "Inserted value under the id must be equal to the added value"},
    {testSingleErase, "Erase must delete a value under the id and decrease vector size "}
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
