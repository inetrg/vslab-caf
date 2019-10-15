#pragma once

// Boost includes
CAF_PUSH_WARNINGS
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
CAF_POP_WARNINGS

/// Returns `true` if `x` is probably prime and `false` if
/// it is definitely composite. The probability to declare a
/// composite n as probably prime is at most 0.25^trials.
inline bool is_probable_prime(const boost::multiprecision::int512_t& x,
                              unsigned trials = 25) {
  using namespace boost::multiprecision;
  // Increase 25 to a higher value for higher accuracy.
  return miller_rabin_test(static_cast<uint512_t>(x), trials);
}
