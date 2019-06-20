// MIT License
//
// Copyright (c) 2019 Filip Björklund
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

// ========================================================================== //
// Headers
// ========================================================================== //

#include "alflib/allocator.hpp"
#include "alflib/assert.hpp"
#include "alflib/common.hpp"
#include "alflib/math/math.hpp"

// ========================================================================== //
// ArrayList Declaration
// ========================================================================== //

namespace alflib {

/** \class ArrayList
 * \author Filip Björklund
 * \date 07 juni 2019 - 21:32
 * \brief Array-list
 * \details
 * Represents an array-list where each object in the list is layed out linearly
 * in memory.
 */
template<typename T>
class ArrayList
{
public:
  /** Type of the size and index data **/
  using SizeType = u64;
  /** Pointer type **/
  using PointerType = T*;
  /** Reference type **/
  using ReferenceType = T&;

  /** Default array-list capacity **/
  static constexpr SizeType DEFAULT_CAPACITY = 10;
  /** Size of an object in the list **/
  static constexpr SizeType OBJECT_SIZE = sizeof(T);
  /** Factor of resize **/
  static constexpr SizeType RESIZE_FACTOR = 2;

public:
  /** Array-list iterator **/
  class Iterator
  {
  private:
    /** Pointer to data**/
    PointerType mPointer;

  public:
    /** Construct iterator **/
    Iterator(PointerType pointer);

    /** Next element **/
    void operator++();

    /** Previous element **/
    void operator--();

    /** Check inequality **/
    bool operator!=(const Iterator& other);

    /** Retrieve reference **/
    ReferenceType operator*();

    /** Retrieve pointer **/
    PointerType operator->();
  };

private:
  /** Data buffer**/
  T* mBuffer;
  /** Capacity of the buffer **/
  SizeType mCapacity;
  /** Number of elements in the list currently **/
  SizeType mSize;

  /** Allocator **/
  Allocator& mAllocator;

public:
  /** Construct an array-list with the specified capacity and allocator.
   * \brief Construct array-list.
   * \param capacity Initial capacity of the array-list.
   * \param allocator Allocator for allocating data.
   */
  explicit ArrayList(u64 capacity = DEFAULT_CAPACITY,
                     Allocator& allocator = DefaultAllocator::Instance());

  /** Construct an array-list from an initializer list.
   * \brief Construct array-list.
   * \param initializerList Initializer list to initialize the array-list from.
   * \param allocator Allocator for allocating data.
   */
  ArrayList(std::initializer_list<T> initializerList,
            Allocator& allocator = DefaultAllocator::Instance());

  /** Copy-constructor **/
  ArrayList(const ArrayList& other);

  /** Move-constructor **/
  ArrayList(ArrayList&& other);

  /** Destructor **/
  ~ArrayList();

  /** Copy-assignment **/
  ArrayList& operator=(const ArrayList& other);

  /** Move-assignment **/
  ArrayList& operator=(ArrayList&& other);

  /** Append an object to the end of the list.
   * \brief Append object.
   * \param object Object to append.
   */
  void Append(const T& object);

  /** Append an object to the end of the list.
   * \brief Append object.
   * \param object Object to append.
   */
  void Append(T&& object);

  /** Append an object to the end of the list. The object is created in-place in
   * the list from the specified arguments forwarded to its constructor.
   * \brief Append object.
   * \tparam ARGS Types of arguments to object constructor.
   * \param arguments Arguments to object constructor.
   */
  template<typename... ARGS>
  void AppendEmplace(ARGS&&... arguments);

  /** Prepend an object to the beginning of the list.
   * \brief Prepend object.
   * \param object Object to prepend.
   */
  void Prepend(const T& object);

  /** Prepend an object to the beginning of the list.
   * \brief Prepend object.
   * \param object Object to prepend.
   */
  void Prepend(T&& object);

  /** Prepend an object to the beginning of the list. The object is created
   * in-place in the list from the specified arguments forwarded to its
   * constructor.
   * \brief Prepend object.
   * \tparam ARGS Types of arguments to object constructor.
   * \param arguments Arguments to object constructor.
   */
  template<typename... ARGS>
  void PrependEmplace(ARGS&&... arguments);

  /** Remove an object from the list at the specified index.
   * \brief Remove object.
   * \param index Index of object.
   */
  void Remove(SizeType index);

  /** Remove an object from that list that is equal to the specified object.
   * \brief Remove object.
   * \param object Object to search for and remove.
   */
  void Remove(const T& object);

  /** Remove an object from that list that is equal to the specified object.
   * \brief Remove object.
   * \param object Object to search for and remove.
   */
  void Remove(T&& object);

  /** Resize the list to the specified size. This is useful if the user is using
   * the index operator to access objects instead of inserting them.
   * \note If the size is less than the current size then any objects outside
   * the new range (0 - size) will be destructed.
   * \brief Resize list.
   * \param size Size to resize to.
   */
  void Resize(SizeType size);

  /** Reserve capacity in the list for the specified number of objects. If the
   * capacity of the list is already greater than the new capacity then nothing
   * will happen.
   * \brief Reserve capacity.
   * \param capacity Capacity to reserve.
   */
  void Reserve(SizeType capacity);

  /** Shrink the capacity of the list to that specified. If the capacity is
   * already less than the one to shrink to nothing will happen.
   * \brief Shrink capacity.
   * \param capacity Capacity to shrink to.
   */
  void Shrink(SizeType capacity);

  /** Shrink the capacity of the list to exactly fit all the objects currently
   * in the list.
   * \brief Shrink to fit.
   */
  void ShrinkToFit();

  /** Returns whether or not the list contains the specified object.
   * \brief Returns whether object is in list.
   * \param object Object to check if in list.
   * \return True if the list contains the object otherwise false.
   */
  bool Contains(const T& object);

  /** Returns the object at the specified index in the list.
   * \pre Index must not be out of bounds.
   * \brief Returns object at index.
   * \param index Index to return object at.
   * \return Object at index.
   */
  T& At(SizeType index);

  /** Returns the object at the specified index in the list.
   * \pre Index must not be out of bounds.
   * \brief Returns object at index.
   * \param index Index to return object at.
   * \return Object at index.
   */
  const T& At(SizeType index) const;

  /** Returns the object at the specified index in the list.
   * \pre Index must not be out of bounds.
   * \brief Returns object at index.
   * \param index Index to return object at.
   * \return Object at index.
   */
  T& operator[](SizeType index);

  /** Returns the object at the specified index in the list.
   * \pre Index must not be out of bounds.
   * \brief Returns object at index.
   * \param index Index to return object at.
   * \return Object at index.
   */
  const T& operator[](SizeType index) const;

  /** Returns the iterator to the beginning of the list.
   * \brief Returns beginning iterator.
   * \return Begin iterator.
   */
  Iterator Begin() const { return Iterator(mBuffer); }

  /** \copydoc ArrayList::Begin **/
  Iterator begin() const { return Begin(); }

  /** Returns the iterator to the end of the list.
   * \brief Returns ending iterator.
   * \return End iterator.
   */
  Iterator End() const { return Iterator(mBuffer + mSize); }

  /** \copydoc ArrayList::End **/
  Iterator end() const { return End(); }

  /** Returns the capacity of the list.
   * \brief Returns capacity.
   * \return Capacity.
   */
  SizeType GetCapacity() const { return mCapacity; }

  /** Returns the size of the list.
   * \brief Returns size.
   * \return Size.
   */
  SizeType GetSize() const { return mSize; }

private:
  /** Check that the capacity is enough to add an object. If it's not then
   * resize **/
  void CheckCapacityToAdd();
};

// -------------------------------------------------------------------------- //

template<typename T>
ArrayList<T>::Iterator::Iterator(PointerType pointer)
  : mPointer(pointer)
{}

// -------------------------------------------------------------------------- //

template<typename T>
void
ArrayList<T>::Iterator::operator++()
{
  ++mPointer;
}

// -------------------------------------------------------------------------- //

template<typename T>
void
ArrayList<T>::Iterator::operator--()
{
  --mPointer;
}

// -------------------------------------------------------------------------- //

template<typename T>
bool
ArrayList<T>::Iterator::operator!=(const Iterator& other)
{
  return mPointer != other.mPointer;
}

// -------------------------------------------------------------------------- //

template<typename T>
typename ArrayList<T>::ReferenceType ArrayList<T>::Iterator::operator*()
{
  return *mPointer;
}

// -------------------------------------------------------------------------- //

template<typename T>
typename ArrayList<T>::PointerType ArrayList<T>::Iterator::operator->()
{
  return mPointer;
}

// -------------------------------------------------------------------------- //

template<typename T>
ArrayList<T>::ArrayList(u64 capacity, Allocator& allocator)
  : mBuffer(nullptr)
  , mCapacity(capacity)
  , mSize(0)
  , mAllocator(allocator)
{
  mBuffer =
    static_cast<T*>(mAllocator.Alloc(mCapacity * OBJECT_SIZE, alignof(T)));
}

// -------------------------------------------------------------------------- //

template<typename T>
ArrayList<T>::ArrayList(std::initializer_list<T> initializerList,
                        Allocator& allocator)
  : mCapacity(initializerList.size())
  , mSize(0)
  , mAllocator(allocator)
{
  mBuffer =
    static_cast<T*>(mAllocator.Alloc(mCapacity * OBJECT_SIZE, alignof(T)));
  for (const T& element : initializerList) {
    new (mBuffer + (mSize++)) T{ element };
  }
}

// -------------------------------------------------------------------------- //

template<typename T>
ArrayList<T>::ArrayList(const ArrayList& other)
  : mCapacity(other.mCapacity)
  , mSize(other.mSize)
  , mAllocator(other.mAllocator)
{
  mBuffer =
    static_cast<T*>(mAllocator.Alloc(mCapacity * OBJECT_SIZE, alignof(T)));
  for (SizeType i = 0; i < mSize; ++i) {
    new (mBuffer + i) T{ other.mBuffer[i] };
  }
}

// -------------------------------------------------------------------------- //

template<typename T>
ArrayList<T>::ArrayList(ArrayList&& other)
  : mBuffer(other.mBuffer)
  , mCapacity(other.mCapacity)
  , mSize(other.mSize)
  , mAllocator(other.mAllocator)
{
  other.mBuffer = nullptr;
  other.mCapacity = 0;
  other.mSize = 0;
}

// -------------------------------------------------------------------------- //

template<typename T>
ArrayList<T>::~ArrayList()
{
  for (SizeType i = 0; i < mSize; ++i) {
    mBuffer[i].~T();
  }
  mAllocator.Free(mBuffer);
}

// -------------------------------------------------------------------------- //

template<typename T>
ArrayList<T>&
ArrayList<T>::operator=(const ArrayList& other)
{
  if (this != &other) {
    mCapacity = other.mCapacity;
    mSize = other.mSize;
    mAllocator = other.mAllocator;
    mBuffer =
      static_cast<T*>(mAllocator.Alloc(mCapacity * OBJECT_SIZE, alignof(T)));
    for (SizeType i = 0; i < mSize; ++i) {
      new (mBuffer + i) T{ other.mBuffer[i] };
    }
  }
  return *this;
}

// -------------------------------------------------------------------------- //

template<typename T>
ArrayList<T>&
ArrayList<T>::operator=(ArrayList&& other)
{
  if (this != &other) {
    mBuffer = other.mBuffer;
    mCapacity = other.mCapacity;
    mSize = other.mSize;
    mAllocator = other.mAllocator;
    other.mBuffer = nullptr;
    other.mCapacity = 0;
    other.mSize = 0;
  }
  return *this;
}

// -------------------------------------------------------------------------- //

template<typename T>
void
ArrayList<T>::Append(const T& object)
{
  CheckCapacityToAdd();
  new (mBuffer + (mSize++)) T{ object };
}

// -------------------------------------------------------------------------- //

template<typename T>
void
ArrayList<T>::Append(T&& object)
{
  CheckCapacityToAdd();
  new (mBuffer + (mSize++)) T{ std::move(object) };
}

// -------------------------------------------------------------------------- //

template<typename T>
template<typename... ARGS>
void
ArrayList<T>::AppendEmplace(ARGS&&... arguments)
{
  CheckCapacityToAdd();
  new (mBuffer + (mSize++)) T{ std::forward<ARGS>(arguments)... };
}

// -------------------------------------------------------------------------- //

template<typename T>
void
ArrayList<T>::Prepend(const T& object)
{
  CheckCapacityToAdd();
  for (SizeType i = mSize - 1; i > 0; ++i) {
    mBuffer[i] = std::move(mBuffer[i - 1]);
    mBuffer[i - 1].~T();
  }
  new (mBuffer) T{ object };
  ++mSize;
}

// -------------------------------------------------------------------------- //

template<typename T>
void
ArrayList<T>::Prepend(T&& object)
{
  CheckCapacityToAdd();
  for (SizeType i = mSize - 1; i > 0; ++i) {
    mBuffer[i] = std::move(mBuffer[i - 1]);
    mBuffer[i - 1].~T();
  }
  new (mBuffer) T{ std::move(object) };
  ++mSize;
}

// -------------------------------------------------------------------------- //

template<typename T>
template<typename... ARGS>
void
ArrayList<T>::PrependEmplace(ARGS&&... arguments)
{
  CheckCapacityToAdd();
  for (SizeType i = mSize - 1; i > 0; ++i) {
    mBuffer[i] = std::move(mBuffer[i - 1]);
    mBuffer[i - 1].~T();
  }
  new (mBuffer) T{ std::forward<ARGS>(arguments)... };
  ++mSize;
}

// -------------------------------------------------------------------------- //

template<typename T>
void
ArrayList<T>::Remove(SizeType index)
{
  // Assert preconditions
  AlfAssert(index >= 0 && index < mSize,
            "ArrayList Remove index out of bounds");

  // Destruct object and move other into spots
  mBuffer[index].~T();
  for (SizeType i = index; i < mSize - 1; ++i) {
    new (mBuffer + i) T{ std::move(mBuffer[i + 1]) };
    mBuffer[i + 1].~T();
  }
  mSize--;
}

// -------------------------------------------------------------------------- //

template<typename T>
void
ArrayList<T>::Remove(const T& object)
{
  for (SizeType i = 0; i < mSize; ++i) {
    if (this[i] == object) {
      mBuffer[i].~T();
      for (SizeType j = i; j < mSize - 1; ++j) {
        new (mBuffer + j) T{ std::move(mBuffer[j + 1]) };
        mBuffer[j + 1].~T();
      }
      mSize--;
      return;
    }
  }
}

// -------------------------------------------------------------------------- //

template<typename T>
void
ArrayList<T>::Remove(T&& object)
{
  for (SizeType i = 0; i < mSize; ++i) {
    if (this[i] == object) {
      mBuffer[i].~T();
      for (SizeType j = i; j < mSize - 1; ++j) {
        new (mBuffer + j) T{ std::move(mBuffer[j + 1]) };
        mBuffer[j + 1].~T();
      }
      mSize--;
      return;
    }
  }
}

// -------------------------------------------------------------------------- //

template<typename T>
void
ArrayList<T>::Resize(SizeType size)
{
  if (size < mCapacity) {
    // Destruct objects if new size is lesser
    for (SizeType i = size; i < mSize; ++i) {
      mBuffer[i].~T();
    }
    // Default construct objects if new size is greater
    for (SizeType i = mSize; i < size; ++i) {
      new (mBuffer + i) T{};
    }
    mSize = size;
  } else {
    // Allocate new buffer and move all objects
    T* newBuffer =
      static_cast<T*>(mAllocator.Alloc(size * OBJECT_SIZE, alignof(T)));
    for (SizeType i = 0; i < Min(mSize, size); ++i) {
      new (newBuffer + i) T{ std::move(mBuffer[i]) };
      mBuffer[i].~T();
    }
    for (SizeType i = mSize; i < size; ++i) {
      new (newBuffer + i) T{};
    }
    mAllocator.Free(mBuffer);
    mBuffer = newBuffer;
    mSize = size;
  }
}

// -------------------------------------------------------------------------- //

template<typename T>
void
ArrayList<T>::Reserve(SizeType capacity)
{
  // Only do something if new capacity is greater than old
  if (capacity > mCapacity) {
    T* newBuffer =
      static_cast<T*>(mAllocator.Alloc(capacity * OBJECT_SIZE, alignof(T)));
    for (SizeType i = 0; i < mSize; ++i) {
      new (newBuffer + i) T{ std::move(mBuffer[i]) };
      mBuffer[i].~T();
    }
    mAllocator.Free(mBuffer);
    mBuffer = newBuffer;
    mCapacity = capacity;
  }
}

// -------------------------------------------------------------------------- //

template<typename T>
void
ArrayList<T>::Shrink(SizeType capacity)
{
  // Only shrink if new capacity is less than old
  if (capacity < mCapacity) {
    T* newBuffer =
      static_cast<T*>(mAllocator.Alloc(capacity * OBJECT_SIZE, alignof(T)));
    for (SizeType i = 0; i < Min(mSize, capacity); ++i) {
      new (newBuffer + i) T{ std::move(mBuffer[i]) };
    }
    for (SizeType i = capacity; i < mSize; ++i) {
      mBuffer[i].~T();
    }
    mAllocator.Free(mBuffer);
    mBuffer = newBuffer;
    mCapacity = capacity;
    mSize = Min(mSize, capacity);
  }
}

// -------------------------------------------------------------------------- //

template<typename T>
void
ArrayList<T>::ShrinkToFit()
{
  Shrink(mSize);
}

// -------------------------------------------------------------------------- //

template<typename T>
bool
ArrayList<T>::Contains(const T& object)
{
  for (SizeType i = 0; i < mSize; ++i) {
    if (At(i) == object) {
      return true;
    }
  }
  return false;
}

// -------------------------------------------------------------------------- //

template<typename T>
T&
ArrayList<T>::At(SizeType index)
{
  // Assert precondition
  AlfAssert(index >= 0 && index < mSize,
            "ArrayList access index out of bounds");
  return mBuffer[index];
}

// -------------------------------------------------------------------------- //

template<typename T>
const T&
ArrayList<T>::At(SizeType index) const
{
  // Assert precondition
  AlfAssert(index >= 0 && index < mSize,
            "ArrayList access index out of bounds");
  return mBuffer[index];
}

// -------------------------------------------------------------------------- //

template<typename T>
T& ArrayList<T>::operator[](SizeType index)
{
  return At(index);
}

// -------------------------------------------------------------------------- //

template<typename T>
const T& ArrayList<T>::operator[](SizeType index) const
{
  return At(index);
}

// -------------------------------------------------------------------------- //

template<typename T>
void
ArrayList<T>::CheckCapacityToAdd()
{
  if (mSize >= mCapacity) {
    Reserve(mCapacity ? mCapacity * RESIZE_FACTOR : DEFAULT_CAPACITY);
  }
}

}
