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

#ifndef __ALIGN_PATH_BAM_UTIL_HH
#define __ALIGN_PATH_BAM_UTIL_HH

#include "blt_util/bam_util.hh"
#include "starling_common/align_path.hh"


// convert internal BAM cigar representation directly into a path:
//
void
bam_cigar_to_apath(const uint32_t* bam_cigar,
                   const unsigned n_cigar,
                   ALIGNPATH::path_t& apath);

// convert apath to internal BAM cigar representation:
//
// bam_cigar should already be set to apath.size() capacity
//
void
apath_to_bam_cigar(const ALIGNPATH::path_t& apath,
                   uint32_t* bam_cigar);

// convert apath into a CIGAR string and replace CIGAR in BAM record
//
void
edit_bam_cigar(const ALIGNPATH::path_t& apath,
               bam1_t& br);

#endif
