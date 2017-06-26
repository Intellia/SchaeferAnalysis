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

#include "position_somatic_snv.hh"
#include "position_somatic_snv_grid.hh"
#include "position_somatic_snv_strand_grid.hh"
#include "somatic_indel.hh"
#include "somatic_indel_grid.hh"

#include "strelka/strelka_shared.hh"



strelka_deriv_options::
strelka_deriv_options(const strelka_options& opt,
                      const reference_contig_segment& ref)
    : base_t(opt,ref)
    , _sscaller_strand_grid(new somatic_snv_caller_strand_grid(opt,pdcaller()))
    , _sicaller_grid(new somatic_indel_caller_grid(opt,incaller()))
{}



strelka_deriv_options::
~strelka_deriv_options() {}
