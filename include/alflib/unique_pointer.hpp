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
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
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
// UniquePointer Declaration
// ========================================================================== //

namespace alflib {

/** \class UniquePointer
 * \author Filip Björklund
 * \date 10 juni 2019 - 09:41
 * \brief Unique pointer.
 * \details
 * Represents a smart pointer that manages a unique instance of a pointer.
 */
template<typename T>
class UniquePointer
{
private:
  /** Pointer **/
  T* mPointer = nullptr;

public:
  /** Construct a unique pointer from an existing raw pointer.
   * \brief Construct from raw pointer.
   * \param pointer Pointer to construct from.
   */
  UniquePointer(T* pointer);

  /** Deleted copy constructor **/
  UniquePointer(const UniquePointer&) = delete;

  /** Move constructor **/
  UniquePointer(UniquePointer&& other);

  /** Destructs the unique pointer and deletes the managed pointer aswell.
   * \brief Destruct pointer.
   */
  ~UniquePointer();

  /** Deleted copy assignment **/
  UniquePointer& operator=(const UniquePointer&) = delete;

  /** Move assignment **/
  UniquePointer& operator=(UniquePointer&& other);

  /** Assign a new pointer to be managed. The previous pointer is deleted before
   * the new one is assigned. If the pointer is the one already being managed 
   * then this call does nothing.
   * \brief Reassign pointer.
   * \param pointer Pointer to assign.
   * \return Reference to this.
   */
  UniquePointer& operator=(T* pointer);

  /** Returns a reference to the managed object.
   * \brief Returns reference to object.
   * \return Object reference.
   */
  T& operator*() { return *mPointer; }

  /** Returns a pointer to the managed object.
   * \brief Returns pointer to object.
   * \return Object pointer.
   */
  T* operator->() { return mPointer; }

public:
  /** Make a unique pointer by forwarding the specified arguments to the 
   * constructor of the managed object.
   * \brief Make unique pointer.
   * \tparam ARGS Types of arguments to constructor.
   * \param arguments Arguments to object constructor.
   * \return Pointer.
   */
  template<typename ... ARGS>
  static UniquePointer Make(ARGS&& ... arguments);

};

// -------------------------------------------------------------------------- //

template<typename T>
UniquePointer<T>::UniquePointer(T* pointer)
  :	mPointer(pointer)
{}

// -------------------------------------------------------------------------- //

template<typename T>
UniquePointer<T>::UniquePointer(UniquePointer&& other)
{
  mPointer = other.mPointer;
  other.mPointer = nullptr;
}

// -------------------------------------------------------------------------- //

template<typename T>
UniquePointer<T>::~UniquePointer()
{
  delete mPointer;
}

// -------------------------------------------------------------------------- //

template<typename T>
UniquePointer<T>&
UniquePointer<T>::operator=(UniquePointer&& other)
{
  if (this != &other) {
    mPointer = other.mPointer;
    other.mPointer = nullptr;
  }
  return *this;
}

template<typename T>
UniquePointer<T>&
UniquePointer<T>::operator=(T* pointer)
{
  if (pointer != mPointer) {
    delete mPointer;
    mPointer = pointer;
  }
  return *this;
}

// -------------------------------------------------------------------------- //

template<typename T>
template<typename ... ARGS>
UniquePointer<T>
UniquePointer<T>::Make(ARGS&&... arguments)
{
  T* pointer = new T{ std::forward<ARGS>(arguments)... };
  return UniquePointer<T>(pointer);
}

}
