// -*- mode: c++; indent-tabs-mode: nil; -*-
//
// Copyright (c) 2009-2016 Illumina, Inc.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

/// \file

/// \author Chris Saunders
///
#ifndef __MATH_UTIL_HH
#define __MATH_UTIL_HH

#include "boost/math/special_functions/log1p.hpp"

#include <cmath>

#include <algorithm>


/// returns log(1+x), switches to special libc function when abs(x) is small
///
template <typename FloatType>
FloatType
log1p_switch(const FloatType x) {

    // better number??
    static const FloatType smallx_thresh(0.01);

    if (std::abs(x)<smallx_thresh) {
        return boost::math::log1p(x);
    } else {
        return std::log(1+x);
    }
}


/// returns equiv of log(exp(x1)+exp(x2))
///
template <typename FloatType>
FloatType
log_sum(FloatType x1, FloatType x2) {
    if (x1<x2) std::swap(x1,x2);
    return x1 + log1p_switch(std::exp(x2-x1));
}

#endif
