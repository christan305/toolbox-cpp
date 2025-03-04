// The Reactive C++ Toolbox.
// Copyright (C) 2013-2019 Swirly Cloud Limited
// Copyright (C) 2022 Reactive Markets Limited
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef TOOLBOX_NET_ENDIAN_HPP
#define TOOLBOX_NET_ENDIAN_HPP

#include <toolbox/Config.h>

#include <bit>
#include <concepts>
#include <cstdint>
#include <type_traits>

namespace toolbox {
inline namespace net {

constexpr std::uint16_t bswap(std::uint16_t n) noexcept
{
    return (n << 8) | (n >> 8);
}

constexpr std::int16_t bswap(std::int16_t n) noexcept
{
    return bswap(static_cast<std::uint16_t>(n));
}

constexpr std::uint32_t bswap(std::uint32_t n) noexcept
{
    return (n >> 24) | ((n >> 8) & 0xff00) | ((n << 8) & 0xff0000) | (n << 24);
}

constexpr std::int32_t bswap(std::int32_t n) noexcept
{
    return bswap(static_cast<std::uint32_t>(n));
}

constexpr std::uint64_t bswap(std::uint64_t n) noexcept
{
    const auto hi = std::uint64_t{bswap(static_cast<std::uint32_t>(n))} << 32;
    return hi | bswap(static_cast<std::uint32_t>(n >> 32));
}

constexpr std::int64_t bswap(std::int64_t n) noexcept
{
    return bswap(static_cast<std::uint64_t>(n));
}

template <typename ValueT>
requires std::integral<ValueT>
constexpr ValueT ntoh(ValueT n) noexcept
{
    if constexpr (std::endian::native == std::endian::little) {
        return bswap(n);
    } else {
        return n;
    }
}

template <typename ValueT>
requires std::integral<ValueT>
constexpr ValueT hton(ValueT n) noexcept
{
    if constexpr (std::endian::native == std::endian::little) {
        return bswap(n);
    } else {
        return n;
    }
}

template <typename ValueT>
requires std::integral<ValueT>
constexpr ValueT ltoh(ValueT n) noexcept
{
    if constexpr (std::endian::native == std::endian::little) {
        return n;
    } else {
        return bswap(n);
    }
}

template <typename ValueT>
requires std::integral<ValueT>
constexpr ValueT htol(ValueT n) noexcept
{
    if constexpr (std::endian::native == std::endian::little) {
        return n;
    } else {
        return bswap(n);
    }
}
// Prevent corner case if mixed platform would use htol of big endian
static_assert(std::endian::native == std::endian::little || std::endian::native == std::endian::big,
              "Mixed endianness platforms are not supported");

} // namespace net
} // namespace toolbox

#endif // TOOLBOX_NET_ENDIAN_HPP
