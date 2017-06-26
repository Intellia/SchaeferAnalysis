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

#pragma once

#include "boost/utility.hpp"


struct somatic_indel_call {

    somatic_indel_call()
        : is_forced_output(false)
    {}

    typedef bool tier_t;

    struct result_set {

        result_set()
            : sindel_qphred(0),
              is_overlap(false)
        {}

        unsigned ntype;
        unsigned max_gt;
        int sindel_qphred;
        int sindel_from_ntype_qphred;
        bool is_overlap;
    };

    bool
    is_indel() const {
        return (rs.sindel_qphred != 0);
    }

    // should this indel be written out?
    bool
    is_output() const {
        return (is_indel() || is_forced_output);
    }

    tier_t sindel_tier;
    tier_t sindel_from_ntype_tier;
    result_set rs;
    bool is_forced_output;
};
