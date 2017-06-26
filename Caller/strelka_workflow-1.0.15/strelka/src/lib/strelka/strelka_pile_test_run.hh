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
/// XXX_begin_pos is zero-indexed position at the begining of the range
/// XXX_end_pos is zero-index position 1 step after the end of the range
///

#pragma once

#include "blt_common/snp_pos_info.hh"
#include "strelka/strelka_shared.hh"

#include <iosfwd>
#include <memory>


struct strelka_pile_caller {

    strelka_pile_caller(
        strelka_options& opt,
        std::ostream& os);

    void
    call(
        const bool is_somatic_gvcf,
        const unsigned pos,
        snp_pos_info& norm_pi,
        snp_pos_info& tumor_pi);

private:
    strelka_options& _opt;
    std::auto_ptr<strelka_deriv_options> _dopt_ptr;
    std::ostream& _os;
};
