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

#ifndef __SCAN_STRING_HH
#define __SCAN_STRING_HH

#include "boost/static_assert.hpp"


template <typename T>
const char*
scan_string() {
    // no scan_string available for type:
    BOOST_STATIC_ASSERT(sizeof(T)==0);
    return NULL;
}


template <>
inline
const char*
scan_string<int>() { return "%d"; }

template <>
inline
const char*
scan_string<long>() { return "%ld"; }


#endif
