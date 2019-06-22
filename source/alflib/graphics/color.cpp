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

#include "alflib/graphics/color.hpp"

// ========================================================================== //
// Headers
// ========================================================================== //

#include "alflib/math/limits.hpp"
#include "alflib/math/math.hpp"

// ========================================================================== //
// Color Implementation
// ========================================================================== //

namespace alflib {

Color Color::BLACK = Color(0.0f, 0.0f, 0.0f);

// -------------------------------------------------------------------------- //

Color Color::WHITE = Color(1.0f, 1.0f, 1.0f);

// -------------------------------------------------------------------------- //

Color Color::RED = Color(1.0f, 0.0f, 0.0f);

// -------------------------------------------------------------------------- //

Color Color::GREEN = Color(1.0f, 0.0f, 0.0f);

// -------------------------------------------------------------------------- //

Color Color::BLUE = Color(1.0f, 0.0f, 0.0f);

// -------------------------------------------------------------------------- //

Color Color::CYAN = Color(0.0f, 1.0f, 1.0f);

// -------------------------------------------------------------------------- //

Color Color::MAGENTA = Color(1.0f, 0.0f, 1.0f);

// -------------------------------------------------------------------------- //

Color Color::YELLOW = Color(1.0f, 1.0f, 0.0f);

// -------------------------------------------------------------------------- //

Color Color::CORNFLOWER_BLUE = Color(0.392f, 0.584f, 0.929f);

// -------------------------------------------------------------------------- //

Color::Color(u8 red, u8 green, u8 blue, u8 alpha)
  : mRed(red / f32(U8_MAX))
  , mGreen(green / f32(U8_MAX))
  , mBlue(blue / f32(U8_MAX))
  , mAlpha(alpha / f32(U8_MAX))
{}

// -------------------------------------------------------------------------- //

Color::Color(s32 red, s32 green, s32 blue, s32 alpha)
  : mRed(red / f32(U8_MAX))
  , mGreen(green / f32(U8_MAX))
  , mBlue(blue / f32(U8_MAX))
  , mAlpha(alpha / f32(U8_MAX))
{}

// -------------------------------------------------------------------------- //

Color::Color(u32 red, u32 green, u32 blue, u32 alpha)
  : mRed(red / f32(U8_MAX))
  , mGreen(green / f32(U8_MAX))
  , mBlue(blue / f32(U8_MAX))
  , mAlpha(alpha / f32(U8_MAX))
{}

// -------------------------------------------------------------------------- //

Color::Color(f32 red, f32 green, f32 blue, f32 alpha)
  : mRed(red)
  , mGreen(green)
  , mBlue(blue)
  , mAlpha(alpha)
{}

// -------------------------------------------------------------------------- //

Color::Color(u32 combined)
  : Color((combined >> 24u) & 0xFFu,
          (combined >> 16u) & 0xFFu,
          (combined >> 8u) & 0xFFu,
          (combined >> 0u) & 0xFFu)
{}

// -------------------------------------------------------------------------- //

Color
Color::ToLinear()
{
  return Color{
    mRed <= 0.04045f ? mRed / 12.92f : Power((mRed + 0.055f) / 1.055f, 2.4f),
    mGreen <= 0.04045f ? mGreen / 12.92f
                       : Power((mGreen + 0.055f) / 1.055f, 2.4f),
    mBlue <= 0.04045f ? mBlue / 12.92f : Power((mBlue + 0.055f) / 1.055f, 2.4f),
    mAlpha
  };
}

// -------------------------------------------------------------------------- //

Color
Color::ToGamma()
{
  return Color{
    mRed <= 0.0031308f ? 12.92f * mRed : 1.055f * Power(mRed, 1.0f / 2.4f),
    mGreen <= 0.0031308f ? 12.92f * mGreen
                         : 1.055f * Power(mGreen, 1.0f / 2.4f),
    mBlue <= 0.0031308f ? 12.92f * mBlue : 1.055f * Power(mBlue, 1.0f / 2.4f),
    mAlpha
  };
}

// -------------------------------------------------------------------------- //

Color
Color::ToGrayscale()
{
  const f32 gray = mRed * 0.2126f + mGreen * 0.7152f + mBlue * 0.0722f;
  return Color{ gray, gray, gray };
}

// -------------------------------------------------------------------------- //

u32
Color::GetCombined()
{
  u32 combined = 0;
  combined &= (u32(mRed * U8_MAX) << 24u);
  combined &= (u32(mGreen * U8_MAX) << 16u);
  combined &= (u32(mBlue * U8_MAX) << 8u);
  combined &= (u32(mAlpha * U8_MAX) << 0u);
  return combined;
}

// -------------------------------------------------------------------------- //

bool
operator==(const Color& lhs, const Color& rhs)
{
  return FloatEqual(lhs.mRed, rhs.mRed) && FloatEqual(lhs.mGreen, rhs.mGreen) &&
         FloatEqual(lhs.mBlue, rhs.mBlue) && FloatEqual(lhs.mAlpha, rhs.mAlpha);
}

// -------------------------------------------------------------------------- //

bool
operator!=(const Color& lhs, const Color& rhs)
{
  return !FloatEqual(lhs.mRed, rhs.mRed) ||
         !FloatEqual(lhs.mGreen, rhs.mGreen) ||
         !FloatEqual(lhs.mBlue, rhs.mBlue) ||
         !FloatEqual(lhs.mAlpha, rhs.mAlpha);
}

// -------------------------------------------------------------------------- //

std::ostream&
operator<<(std::ostream& os, const Color& color)
{
  os << "Color {" << color.mRed << ", " << color.mGreen << ", " << color.mBlue
     << ", " << color.mAlpha << "}";
  return os;
}

}