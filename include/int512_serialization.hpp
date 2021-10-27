#pragma once

#include "caf/config.hpp"
#include "caf/fwd.hpp"
#include "caf/byte.hpp"
#include "caf/span.hpp"

CAF_PUSH_WARNINGS
#include <boost/multiprecision/cpp_int.hpp>
CAF_POP_WARNINGS

// *not* very good style to open external namespaces,
// but unfortunately necessary here to get ADL working
namespace boost {
namespace multiprecision {

// Use this if you want to print numbers with aout.
std::string to_string(int512_t x);

template <class Inspector>
bool inspect(Inspector& f, int512_t& i512) {
  auto& x = i512.backend();
  auto get_sign = [&x] { return x.sign(); };
  auto set_sign = [&x](bool is_signed) {
    if (is_signed != x.sign())
        x.negate();
    return true;
  };
  auto get_limbs = [&x] {
    std::cout << "original size " << x.size() << " * " << sizeof(limb_type) << std::endl;
    auto num_bytes = x.size() * sizeof(limb_type);
    std::vector<caf::byte> s(num_bytes);
    auto ptr = reinterpret_cast<caf::byte*>(x.limbs());
    std::copy(ptr, ptr + num_bytes, s.data());
    return s;
  };
  auto set_limbs = [&x](const std::vector<caf::byte>& val) {
    uint32_t size = val.size() / sizeof(limb_type);
    std::cout << "resizing from " << x.size() << " to " << size << std::endl;
    x.resize(size, size);
    std::copy(val.data(), val.data() + val.size(), reinterpret_cast<caf::byte*>(x.limbs()));
    return true;
  };
  return f.object(x).fields(f.field("limbs", get_limbs, set_limbs), f.field("sign", get_sign, set_sign));
}

} // namespace multiprecision
} // namespace boost
