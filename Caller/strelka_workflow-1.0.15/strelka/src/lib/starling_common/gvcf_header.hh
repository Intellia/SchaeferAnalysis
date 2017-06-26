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

#ifndef __GVCF_HEADER
#define __GVCF_HEADER

#include "blt_common/blt_shared.hh"
#include "starling_common/chrom_depth_map.hh"

#include <iosfwd>


void
finish_gvcf_header(const gvcf_options& opt,
                   const gvcf_deriv_options& dopt,
                   const cdmap_t& chrom_depth,
                   const std::string& bam_header_data,
                   std::ostream& os);

#endif
