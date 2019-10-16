#pragma once

#include "caf/config.hpp"
#include "caf/fwd.hpp"

CAF_PUSH_WARNINGS
#include <boost/multiprecision/cpp_int.hpp>
CAF_POP_WARNINGS

// *not* very good style to open external namespaces,
// but unfortunately necessary here to get ADL working
namespace boost {
namespace multiprecision {
void serialize(caf::serializer& s, int512_t& i512);
void serialize(caf::deserializer& d, int512_t& i512);

// Use this if you want to print numbers with aout.
std::string to_string(int512_t x);
} // namespace multiprecision
} // namespace boost
