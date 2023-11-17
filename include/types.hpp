#pragma once

#include <vector>

#include <caf/all.hpp>

CAF_PUSH_WARNINGS
#include <boost/multiprecision/cpp_int.hpp>
CAF_POP_WARNINGS

CAF_BEGIN_TYPE_ID_BLOCK(vslab, first_custom_type_id)

  // -- types ------------------------------------------------------------------

  CAF_ADD_TYPE_ID(vslab, (boost::multiprecision::int512_t))
  CAF_ADD_TYPE_ID(vslab, (std::vector<boost::multiprecision::int512_t>) )

  // -- atoms ------------------------------------------------------------------

  CAF_ADD_ATOM(vslab, calc_atom)

CAF_END_TYPE_ID_BLOCK(vslab)
