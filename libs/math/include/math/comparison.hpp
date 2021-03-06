#pragma once
//------------------------------------------------------------------------------
//
//   Copyright 2018-2019 Fetch.AI Limited
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//
//------------------------------------------------------------------------------

#include "math/meta/math_type_traits.hpp"
#include <cassert>

namespace fetch {
namespace math {

/**
 * Max function for two values
 * @tparam T
 * @param datum1
 * @param datum2
 * @return
 */
template <typename T>
T Max(T const &datum1, T const &datum2, T &ret)
{
  ret = std::max(datum1, datum2);
  return ret;
}
template <typename T>
T Max(T const &datum1, T const &datum2)
{
  T ret{};
  ret = Max(datum1, datum2, ret);
  return ret;
}

/**
 * Min function for two values
 * @tparam T
 * @param datum1
 * @param datum2
 * @return
 */
template <typename T>
inline void Min(T const &datum1, T const &datum2, T &ret)
{
  ret = std::min(datum1, datum2);
}
template <typename T>
inline T Min(T const &datum1, T const &datum2)
{
  T ret = std::min(datum1, datum2);
  return ret;
}

}  // namespace math
}  // namespace fetch