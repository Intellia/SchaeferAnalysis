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

/// variation on the original strowman snv caller -- implements a
/// compile-time specified grid in allele frequency space and requires
/// similar frequency as definition of non-somatic.
///

/// \author Chris Saunders
///

#pragma once


struct somatic_snv_genotype_grid {

    somatic_snv_genotype_grid()
        : is_forced_output(false) {}

    typedef bool tier_t;

    struct result_set {
        result_set()
            : snv_qphred(0)
            , snv_from_ntype_qphred(0)
            , nonsomatic_qphred(0)
        {}

        unsigned ntype;
        unsigned max_gt;
        int snv_qphred;
        int snv_from_ntype_qphred;
        int nonsomatic_qphred;
    };

    bool
    is_snv() const {
        return (0 != rs.snv_qphred);
    }

    bool
    is_output() const {
        return (is_snv() || is_forced_output);
    }

    tier_t snv_tier;
    tier_t snv_from_ntype_tier;
    unsigned ref_gt;
    result_set rs;
    bool is_forced_output;
};
