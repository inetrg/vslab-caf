#include "int512_serialization.hpp"

#include <sstream>

#include "caf/deserializer.hpp"
#include "caf/serializer.hpp"

namespace boost {
namespace multiprecision {

void serialize(caf::serializer& s, int512_t& i512) {
  auto& x = i512.backend();
  s << x.sign() << static_cast<uint32_t>(x.size());
  s.apply_raw(x.size() * sizeof(limb_type), x.limbs());
}

void serialize(caf::deserializer& d, int512_t& i512) {
  auto& x = i512.backend();
  bool is_signed;
  uint32_t limbs;
  d >> is_signed >> limbs;
  x.resize(limbs, limbs);
  d.apply_raw(limbs * sizeof(limb_type), x.limbs());
  if (is_signed != x.sign())
    x.negate();
}

std::string to_string(int512_t x) {
  std::stringstream s;
  s << x;
  return s.str();
}

} // namespace multiprecision
} // namespace boost
