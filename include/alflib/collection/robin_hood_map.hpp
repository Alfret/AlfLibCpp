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

// Standard headers
#include <functional>

// Project headers
#include "alflib/memory/allocator.hpp"
#include "alflib/core/assert.hpp"
#include "alflib/math/math.hpp"
#include "alflib/collection/map.hpp"

// ========================================================================== //
// RobinHoodMap Declaration
// ========================================================================== //

namespace alflib {

/** \class RobinHoodMap
 * \author Filip Björklund
 * \date 22 june 2019 - 18:07
 * \brief Hash map with Robin Hood probing
 * \details
 * Class that represent a probing hash map implemented with Robin Hood bucket
 * swapping during probing.
 */
template<typename K, typename V>
class RobinHoodMap
{
private:
  /** Default bucket count **/
  static constexpr u32 DEFAULT_BUCKET_CAPACITY = 32;
  /** Default max load factor limit**/
  static constexpr f32 DEFAULT_MAX_LOAD_FACTOR = 0.8f;

public:
  /** Index type **/
  using IndexType = u32;
  /** Entry type **/
  using EntryType = MapEntry<K, V>;

  /** Single bucket in the map **/
  struct Bucket
  {
    /** Hashed key **/
    u32 hash;
    /** Entry **/
    EntryType entry;
  };

private:
  /** Allocator for allocating the underlying buffer **/
  Allocator& mAllocator;

  /** Buckets **/
  Bucket* mBuckets = nullptr;
  /** Bucket capacity **/
  IndexType mBucketCapacity = 0;
  /** Number of occupied buckets. This differs from 'mSize' because it includes
   * tombstones **/
  IndexType mOccupiedBucketCount = 0;
  /** Current number of stored objects **/
  IndexType mSize = 0;

  /** Maximum load factor before the bucket capacity is increased **/
  f32 mMaxLoadFactor = DEFAULT_MAX_LOAD_FACTOR;

public:
  /** Construct a robin-hood map. A initial bucket count and allocator may be
   * specified.
   * \pre Bucket capacity must be a power of two.
   * \brief Construct robin-hood map.
   * \param bucketCapacity Number of initial buckets allocated.
   * \param allocator Allocator to use for allocating buckets.
   */
  RobinHoodMap(IndexType bucketCapacity = DEFAULT_BUCKET_CAPACITY,
               Allocator& allocator = DefaultAllocator::Instance());

  ~RobinHoodMap();

  bool HasKey(K&& key);

  V& operator[](K&& key);

  /** Returns the number of objects currently stored in the map.
   * \brief Returns number of object in map.
   * \return Number of object in map.
   */
  IndexType GetSize() const { return mSize; }

  /** Returns the current load factor of the map.
   * \brief Returns load factor.
   * \return Load factor.
   */
  f32 GetLoadFactor() const
  {
    return mOccupiedBucketCount / f32(mBucketCapacity);
  }

private:
  bool IsTombstone(Bucket& entry);

  u32 DistanceFromIndex(u32 hash, IndexType index);

  void Resize(IndexType capacity);
};

// -------------------------------------------------------------------------- //
template<typename K, typename V>
RobinHoodMap<K, V>::RobinHoodMap(RobinHoodMap::IndexType bucketCount,
                                 Allocator& allocator)
  : mAllocator(allocator)
  , mBucketCapacity(bucketCount)
{
  // Assert precondition
  AlfAssert(IsPowerOfTwo(bucketCount),
            "Bucket count must be a power of two, however it is {}",
            bucketCount);

  // Allocate buckets
  mBuckets = static_cast<Bucket*>(
    mAllocator.Alloc(sizeof(Bucket) * mBucketCapacity, alignof(Bucket)));
  memset(mBuckets, 0, sizeof(Bucket) * mBucketCapacity);
}

// -------------------------------------------------------------------------- //
template<typename K, typename V>
RobinHoodMap<K, V>::~RobinHoodMap()
{
  for (IndexType i = 0; i < mBucketCapacity; i++) {
    Bucket& bucket = mBuckets[i];
    if (bucket.hash != 0 && !IsTombstone(bucket)) {
      bucket.entry.~EntryType();
    }
  }

  mAllocator.Delete(mBuckets);
}

// -------------------------------------------------------------------------- //

template<typename K, typename V>
bool
RobinHoodMap<K, V>::HasKey(K&& key)
{
  return false;
}

// -------------------------------------------------------------------------- //

template<typename K, typename V>
V& RobinHoodMap<K, V>::operator[](K&& key)
{
  // Enlarge bucket buffer if necessary
  if (GetLoadFactor() >= mMaxLoadFactor) {
    Resize(mBucketCapacity << 1u);
  }

  // Find entry
  u32 hash = std::hash<K>{}(key);
  IndexType index = ModuloPowerOfTwo(hash, mBucketCapacity);
  s64 insertIndex = -1;
  V value;
  u32 distance = 0;
  while (true) {
    Bucket& bucket = mBuckets[index];

    // Same hash:
    if (bucket.hash == hash && bucket.entry.GetKey() == key) {
      return bucket.entry.GetValue();
    }

    // Empty bucket:
    if (bucket.hash == 0) {
      bucket.hash = hash;
      bucket.entry = EntryType{ std::move(key), std::move(value) };
      break;
    }

    // Not empty
    u32 currentDistance = DistanceFromIndex(bucket.hash, index);
    if (currentDistance < distance) {
      // Tombstone bucket:
      if (IsTombstone(bucket)) {
        bucket.hash = hash;
        bucket.entry = EntryType{ std::move(key), std::move(value) };
        break;
      }

      // Swap the bucket content for this content
      {
        std::swap(hash, bucket.hash);
        std::swap(value, bucket.value);
        std::swap(key, bucket.key);
        distance = currentDistance;

        if (insertIndex == -1) {
          insertIndex = index;
        }
      }
    }

    // Update index and distance
    index = ModuloPowerOfTwo(index + 1, mBucketCapacity);
    distance++;
  }

  // Return value at index
  mSize++;
  return mBuckets[insertIndex].entry.GetValue();
}

// -------------------------------------------------------------------------- //

template<typename K, typename V>
bool
RobinHoodMap<K, V>::IsTombstone(Bucket& entry)
{
  return (entry.hash & 0x80000000) != 0;
}

// -------------------------------------------------------------------------- //

template<typename K, typename V>
u32
RobinHoodMap<K, V>::DistanceFromIndex(u32 hash, IndexType index)
{
  u32 _index = ModuloPowerOfTwo(hash, mBucketCapacity);
  return ModuloPowerOfTwo(index + mBucketCapacity - _index, mBucketCapacity);
}

// -------------------------------------------------------------------------- //

template<typename K, typename V>
void
RobinHoodMap<K, V>::Resize(RobinHoodMap::IndexType capacity)
{}

}