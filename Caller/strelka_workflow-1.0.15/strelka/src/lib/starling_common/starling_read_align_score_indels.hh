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

#ifndef __STARLING_READ_ALIGN_SCORE_INDELS_HH
#define __STARLING_READ_ALIGN_SCORE_INDELS_HH


#include "candidate_alignment.hh"

#include "starling_common/indel_synchronizer.hh"
#include "starling_common/starling_read_segment.hh"
#include "starling_common/starling_shared.hh"

#include <set>
#include <vector>


typedef indel_buffer::iterator iiter;
typedef indel_buffer::const_iterator ciiter;

typedef std::map<indel_key,bool> indel_status_map_t;


// use the most likely alignment for each indel state for every indel
// in indel_status_map to generate data needed in indel calling:
//
void
score_indels(const starling_options& opt,
             const starling_deriv_options& dopt,
             const starling_sample_options& sample_opt,
             const read_segment& rseg,
             indel_synchronizer& isync,
             const std::set<candidate_alignment>& cal_set,
             const bool is_incomplete_search,
             const std::vector<double>& cal_set_path_lnp,
             double max_path_lnp,
             const candidate_alignment* max_cal_ptr);

#endif