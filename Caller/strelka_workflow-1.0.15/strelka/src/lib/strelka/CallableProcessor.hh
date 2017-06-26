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

#include "blt_util/blt_types.hh"
#include "blt_util/pos_range.hh"
#include "strelka/position_somatic_snv_grid_shared.hh"

#include <iosfwd>
#include <string>


/// manage creation of a callable bed track
struct CallableProcessor
{
    CallableProcessor(
        std::ostream* osptr = NULL) :
        _minQSS(15),
        _minNQSS(15),
        _osptr(osptr),
        _is_range(false)
    {}

    ~CallableProcessor()
    {
        flush();
    }

    void
    add(
        const std::string& chrom,
        const pos_t outputPos,
        const somatic_snv_genotype_grid& sgtg);

    // write out any pending ranges:
    void
    flush();

private:
    const int _minQSS;
    const int _minNQSS;
    std::ostream* _osptr;

    bool _is_range;
    std::string _chrom;
    pos_range _prange;
};
