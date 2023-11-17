#pragma once

#include <cstddef>

#include "caf/byte.hpp"
#include "caf/config.hpp"
#include "caf/fwd.hpp"
#include "caf/span.hpp"

CAF_PUSH_WARNINGS
#include <boost/multiprecision/cpp_int.hpp>
CAF_POP_WARNINGS

// *not* very good style to open external namespaces,
// but unfortunately necessary here to get ADL working
namespace boost {
namespace multiprecision {

constexpr auto bytes_in_int512 = 512 / 8;
// Format:
// 1 byte: size in bytes (1 <= n <= 64)
// 1 byte: sign (true: positive, false: negative)
// 64 bytes for the number itself
constexpr auto serialization_size = bytes_in_int512 + 2;

// Use this if you want to print numbers with aout.
std::string to_string(int512_t x);

template <class Inspector>
bool inspect(Inspector& f, int512_t& i512) {
  auto& x = i512.backend();
  auto getter = [&] {
    std::array<std::byte, serialization_size> data;
    auto write_ptr = data.data();
    // serialize size
    std::byte size = static_cast<std::byte>(x.size());
    *write_ptr = size;
    ++write_ptr;
    // serialize sign
    std::byte sign = static_cast<std::byte>(static_cast<uint8_t>(x.sign()));
    *write_ptr = sign;
    ++write_ptr;
    // serialize data
    uint32_t bytes_to_copy = x.size() * sizeof(limb_type);
    auto ptr = reinterpret_cast<std::byte*>(x.limbs());
    std::copy(ptr, ptr + bytes_to_copy, write_ptr);
    return data;
  };
  auto setter = [&](const std::array<std::byte, serialization_size>& data) {
    auto read_ptr = data.data();
    // deserialize size
    uint32_t size = static_cast<uint32_t>(*read_ptr);
    ++read_ptr;
    // deserialize sign
    bool sign = static_cast<bool>(*read_ptr);
    ++read_ptr;
    x.resize(size, size);
    // deserialize data
    uint32_t bytes_to_copy = x.size() * sizeof(limb_type);
    std::copy(read_ptr, read_ptr + bytes_to_copy,
              reinterpret_cast<std::byte*>(x.limbs()));
    // apply sign
    if (sign != x.sign())
      x.negate();
    return true;
  };
  return f.object(x).fields(f.field("data", getter, setter));
}

} // namespace multiprecision
} // namespace boost
