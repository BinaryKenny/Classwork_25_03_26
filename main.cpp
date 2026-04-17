#include "pevector.hpp"
#include <iostream>
#include <cstring>
#include <math.h>
using iknk::Vector;
using iknk::Iterator;
using iknk::CIterator;

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
  return false;
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
    if (v[3] == 10 && v[v.getSize() - 1] == 67) {
      return true;
    }
  }
  catch (...) {
    throw std::logic_error("Exception of inserting");
  }
  return false;
}

bool testErrorSingleInsert(const char ** pname) {
  *pname = __func__;
  Vector< int > v(5, 0);
  try {
    v.insert(10, 67);
    return false;
  }
  catch (std::out_of_range & e) {
    const char * text = e.what();
    return !std::strcmp("id out of bound", text);
  }
  catch (...) {
    return false;
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

bool testErrorSegmentInsert(const char ** pname) {
  *pname = __func__;
  Vector< int > v(10, 0);
  try {
    v.insert(11, v, 5, 10);
    return false;
  }
  catch (const std::out_of_range & e) {
    const char * text = e.what();
    return !std::strcmp("id out of bound", text);
  }
  catch (...) {
    return false;
  }
}

bool testSingleErase(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(9);
  v.pushBack(72);
  v.pushBack(67);
  v.pushBack(76);
  v.erase(2);
  if (v[2] == 67) {
    return false;
  }
  if (v.getSize() == 3) {
    return true;
  }
  return false;
}

bool testErrorSingleErase(const char ** pname) {
  *pname = __func__;
  Vector< int > v(4, 0);
  try {
    v.erase(4);
    return false;
  }
  catch (const std::out_of_range & e) {
    const char * text = e.what();
    return !std::strcmp("id out of bound", text);
  }
  catch (...) {
    return false;
  }
}

bool testSegmentErase(const char ** pname) {
  *pname = __func__;
  Vector < int > v(10,0);
  int expected[] = {0, 1, 2, 3, 4, 8, 9};
  for (size_t i = 1; i < v.getSize(); i++) {
    v[i] = i;
  }
  size_t beg = 5;
  size_t end = 8;
  v.erase(beg, end);
  for (size_t i = 0; i < v.getSize(); i++) {
    if (v[i] != expected[i]) {
      return false;
    }
  }
  return true;
}

bool testErrorSegmentErase(const char ** pname) {
  *pname = __func__;
  Vector< int > v(10, 0);
  size_t beg = 5;
  size_t end = 11;
  try {
    v.erase(beg, end);
    return false;
  }
  catch (const std::out_of_range & e) {
    const char * text = e.what();
    return !std::strcmp("id is out of bound", text);
  }
  catch (...) {
    return false;
  }
}

bool testSingleIteratorInsert(const char ** pname) {
  *pname = __func__;
  Vector< int > v(7, 2);
  Iterator< int > pos = v.iterator(5);
  pos.vector.insert(pos, 34);
  if (v[pos.id] == 34 && v.getSize() == 8) {
    return true;
  }
  return false;
}

bool testSegmentIteratorInsert(const char ** pname) {
  *pname = __func__;
  Vector< int > v(12, 2);
  Vector< int > yav;
  yav.pushBack(34);
  yav.pushBack(67);
  yav.pushBack(76);
  yav.pushBack(43);
  Iterator< int > pos = v.iterator(4);
  CIterator< int > beg = yav.citerator(1);
  CIterator< int > end = yav.citerator(3);
  v.insert(pos, beg, end);
  if (v.getSize() == 14 && v[4] == 67 && v[5] == 76) {
    return true;
  }
  return false;
}

bool testRepetitiveInsert(const char ** pname) {
  *pname = __func__;
  Vector< int > v(7, 2);
  Iterator< int > pos = v.iterator(5);
  v.insert(pos, 34, 4);
  if (v[pos.id] == 34 && v.getSize() == 11) {
    return true;
  }
  return false;
}

bool testSingleIteratorErase(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  int expected[] = {67, 76, 43};
  v.pushBack(34);
  v.pushBack(67);
  v.pushBack(76);
  v.pushBack(43);
  auto iter = v.begin();
  v.erase(iter);
  for (size_t i = 0; i < v.getSize() - 1; i++) {
    if (expected[i] != v[i]) {
      return false;
    }
  }
  return true;
}

bool testSegmentIteratorErase(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  int expected[] = {34, 67, 69};
  v.pushBack(34);
  v.pushBack(67);
  v.pushBack(76);
  v.pushBack(43);
  v.pushBack(100);
  v.pushBack(69);
  auto beg = v.iterator(2);
  auto end = v.iterator(5);
  v.erase(beg, end);
  for (size_t i = 0; i < v.getSize() - 1; i++) {
    if (expected[i] != v[i]) {
      return false;
    }
  }
  return true;
}

bool testCountIteratorErase(const char ** pname) {
  *pname = __func__;
  Vector< int > vector;
  vector.pushBack(76);
  vector.pushBack(43);
  vector.pushBack(67);
  vector.pushBack(100);
  vector.pushBack(69);
  auto pos = vector.citerator(3);
  vector.erase(pos, 2);
  if (vector[vector.getSize() - 1] == 67 && vector.getSize() == 3) {
    return true;
  }
  return false;
}

bool testErrorCountIteratorErase(const char ** pname) {
  *pname = __func__;
  Vector< int > vector(10, 20);
  auto iter = vector.citerator(8);
  try {
    vector.erase(iter,3);
    return false;
  }
  catch (const std::out_of_range & e) {
    const char * text = e.what();
    return !strcmp("Too many element must be deleted", text);
  }
  catch (...) {
    return false;
  }
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
    {testErrorSingleInsert, "If ID > size it must throw the exception"},
    {testSegmentInsert, "Inserted value under the id must be equal to the added value"},
    {testErrorSegmentInsert, "If ID > size it must throw the exception"},
    {testSingleErase, "Erase must delete a value under the id and decrease vector size "},
    {testErrorSingleErase, "If ID bigger than size it must throw the exception"},
    {testSegmentErase, "Erase must delete a segment of vector"},
    {testErrorSegmentErase, "If ID > size it must throw the exception"},
    {testSingleIteratorInsert, "Unbound iterator must have the added value"},
    {testSegmentIteratorInsert, "Unbound iterator must have the added values and bigger size then before"},
    {testRepetitiveInsert, "Unbound iterator must have the added value and vector must be bigger then before"},
    {testSingleIteratorErase, "Erase must delete a value that indicated by iterator"},
    {testSegmentIteratorErase, "Erase must delete the segment that indicated by iterators"},
    {testCountIteratorErase, "Count erase must delete some element from vector"},
    {testErrorCountIteratorErase, "If too many element must be deleted it should throw the exception"}
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
