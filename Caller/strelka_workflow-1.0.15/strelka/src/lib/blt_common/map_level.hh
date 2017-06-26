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
#ifndef __MAP_LEVEL_HH
#define __MAP_LEVEL_HH

#include <cassert>


namespace MAPLEVEL {
enum index_t {
    UNKNOWN,
    UNKNOWN_MAPPED,
    TIER1_MAPPED,
    TIER2_MAPPED,
    SUB_MAPPED,
    UNMAPPED
};

inline
const char*
get_label(const index_t i) {
    switch (i) {
    case UNKNOWN: return "unknown";
    case UNKNOWN_MAPPED: return "unknown-mapped";
    case TIER1_MAPPED: return "tier1-mapped";
    case TIER2_MAPPED: return "tier2-mapped";
    case SUB_MAPPED: return "sub-mapped";
    case UNMAPPED: return "unmapped";
    default:
        assert(0);
        return "none";
    }
}
}


#endif
