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

#ifndef __GROUPER_CONTIG_HH
#define __GROUPER_CONTIG_HH

#include "starling_common/alignment.hh"


struct grouper_contig : public alignment {

    grouper_contig() :
        is_usable(true) {}

    void
    clear() {
        alignment::clear();
        id.clear();
        chrom.clear();
        seq.clear();
        is_usable=true;
    }

    std::string id;
    std::string chrom;
    std::string seq;
    bool is_usable;  // < mark contig as usable if it exceeds MAX_CONTIG_SIZE
};


//debugging output:
std::ostream& operator<<(std::ostream& os, const grouper_contig& ctg);

#endif
