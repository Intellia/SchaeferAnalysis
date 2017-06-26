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
///
/// \author Chris Saunders
///
/// note coding convention for all ranges '_pos fields' is:
/// XXX_begin_pos is zero-indexed position at the beginning of the range
/// XXX_end_pos is zero-index position 1 step after the end of the range
///

#pragma once


namespace INDEL_ALIGN_TYPE {
enum index_t {
    GENOME_TIER1_READ,
    GENOME_TIER2_READ,
    GENOME_SUBMAP_READ,
    CONTIG,
    CONTIG_READ
};

inline
const char*
label(const index_t i) {
    switch (i) {
    case GENOME_TIER1_READ : return "genome_tier1";
    case GENOME_TIER2_READ : return "genome_tier2";
    case GENOME_SUBMAP_READ : return "genome_submap";
    case CONTIG : return "contig";
    case CONTIG_READ : return "contig_read";
    default: return "unknown";
    }
}
}

