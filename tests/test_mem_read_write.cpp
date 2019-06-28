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

// ========================================================================== //
// Headers
// ========================================================================== //

#include <doctest/doctest.h>
#include "alflib/collection/array_list.hpp"
#include "alflib/memory/memory_reader.hpp"
#include "alflib/memory/memory_writer.hpp"

// ========================================================================== //
// Functions
// ========================================================================== //

namespace alflib {

struct DataObject
{
  String str;
  f64 num;

  void ToBytes(MemoryWriter& writer) const
  {
    writer.Write(str);
    writer.Write(num);
  }

  static DataObject FromBytes(MemoryReader& reader)
  {
    DataObject obj;
    obj.str = reader.Read<String>();
    obj.num = reader.Read<f64>();
    return obj;
  }
};

// -------------------------------------------------------------------------- //

TEST_CASE("[] - Memory Writer")
{
  // Write some data
  Buffer buffer(10);
  MemoryWriter writer(buffer);
  writer.Write(32);
  writer.Write(3.14f);
  writer.Write("This is a test");
  writer.Write(String{ "Another string" });
  writer.Write(DataObject{ "String", 27.89 });

  ArrayList<s32> list = { 1, 3, 5, 7, 9 };
  writer.Write(list);

  std::unordered_map<String, s32> mapIn;
  mapIn["A key"] = 22;
  mapIn["My other key"] = 138;
  writer.Write(mapIn);

  // Read data back
  MemoryReader reader(writer.GetBuffer());
  CHECK(reader.Read<s32>() == 32);
  CHECK(reader.Read<f32>() == doctest::Approx(3.14f));
  CHECK(reader.Read<String>() == "This is a test");
  CHECK(reader.Read<String>() == "Another string");

  DataObject obj = reader.Read<DataObject>();
  CHECK(obj.str == "String");
  CHECK(obj.num == doctest::Approx(27.89));

  u32 refValues[5] = { 1, 3, 5, 7, 9 };
  ArrayList<s32> _list = reader.ReadArrayList<s32>();
  for (u32 i = 0; i < list.GetSize(); i++) {
    CHECK(list[i] == refValues[i]);
  }

  auto mapOut = reader.ReadStdUnorderedMap<String, s32>();
  CHECK(mapOut.size() == 2);
  CHECK(mapOut["A key"] == 22);
  CHECK(mapOut["My other key"] == 138);
}

}
