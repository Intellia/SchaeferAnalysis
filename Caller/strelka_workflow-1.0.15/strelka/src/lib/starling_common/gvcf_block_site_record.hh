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

#pragma once


#include "blt_util/stream_stat.hh"
#include "starling_common/gvcf_locus_info.hh"



struct gvcf_block_site_record {

    gvcf_block_site_record(const gvcf_options& opt)
        : frac_tol(static_cast<double>(opt.block_percent_tol)/100.)
        , abs_tol(opt.block_abs_tol)
        , count(0)
    {}

    void
    reset() {
        count=0;
        block_gqx.reset();
        block_dpu.reset();
        block_dpf.reset();
    }

    // determine if the site could be joined to this block:
    bool
    test(const site_info& si) const;

    // add record to this block
    void
    join(const site_info& si);

    site_info record;

    const double frac_tol;
    const int abs_tol;
    int count;
    stream_stat block_gqx;
    stream_stat block_dpu;
    stream_stat block_dpf;
    //stream_stat _blockMQ;
};

