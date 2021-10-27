#include "int512_serialization.hpp"

#include <sstream>

#include "caf/deserializer.hpp"
#include "caf/serializer.hpp"

namespace boost {
namespace multiprecision {

std::string to_string(int512_t x) {
  std::stringstream s;
  s << x;
  return s.str();
}

} // namespace multiprecision
} // namespace boost
