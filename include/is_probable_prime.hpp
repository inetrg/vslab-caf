#pragma once

// Boost includes
CAF_PUSH_WARNINGS
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
CAF_POP_WARNINGS

/// Returns `true` if `x` is probably prime and `false` if
/// it is definitely composite. The probability to declare a
/// composite n as probably prime is at most 0.25^trials.
template <class T>
bool is_probable_prime(const T& x, unsigned trials = 25) {
  // increase 25 to a higher value for higher accuracy
  return boost::multiprecision::miller_rabin_test(x, trials);
}
