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


#ifndef __STARLING_INDEL_ERROR_PROB_HH
#define __STARLING_INDEL_ERROR_PROB_HH


#include "starling_common/starling_indel_report_info.hh"
#include "starling_common/starling_shared.hh"


//
// "indel_error" is the probability that the read supporting the indel case is an error
// "ref_error" is the probability that the read supporting the ref case is an error
//
void
get_indel_error_prob(const starling_options& client_opt,
                     const starling_indel_report_info& iri,
                     double& indel_error_prob,
                     double& ref_error_prob);

#endif

