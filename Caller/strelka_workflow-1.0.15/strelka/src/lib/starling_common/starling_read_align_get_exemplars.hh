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

///
/// \author Chris Saunders
///

#pragma once

#include "starling_common/alignment.hh"
#include "starling_common/starling_read_segment.hh"
#include "starling_common/starling_shared.hh"

#include <vector>


/// for a read segment, expand into a set of starting alignments (exemplars)
/// for alignment search based on read mapper and grouper proposals
///
void
get_exemplar_alignments(const starling_options& opt,
                        const read_segment& rseg,
                        std::vector<alignment>& exal);

