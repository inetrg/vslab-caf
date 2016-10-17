#ifndef INT512_SERIALIZATION
#define INT512_SERIALIZATION

#include "caf/serializer.hpp"
#include "caf/deserializer.hpp"

CAF_PUSH_WARNINGS
#include <boost/multiprecision/cpp_int.hpp>
CAF_POP_WARNINGS

// *not* very good style to open external namespaces,
// but unfortunately necessary here to get ADL working
namespace boost { namespace multiprecision {
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
} } // namespace boost::multiprecision

#endif // INT512_SERIALIZATION
