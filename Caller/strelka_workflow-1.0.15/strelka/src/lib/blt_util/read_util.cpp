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


#include "blt_util/read_util.hh"

#include <cstring>



void
get_read_align_strand_end_skip(const char* const read,
                               const unsigned read_size,
                               unsigned& end_skip) {

    unsigned read_end(read_size);

    while (read_end>0) {
        if (read[read_end-1]=='N') read_end--;
        else break;
    }

    end_skip=read_size-read_end;
}



void
get_read_fwd_strand_skip(const char* const read,
                         const unsigned read_size,
                         const bool is_fwd_strand,
                         unsigned& begin_skip,
                         unsigned& end_skip) {

    begin_skip=0;
    if (is_fwd_strand) {
        get_read_align_strand_end_skip(read,read_size,end_skip);
    } else {
        end_skip=0;
        while (begin_skip<read_size) {
            if (read[begin_skip]=='N') begin_skip++;
            else break;
        }
    }
}



static
void
get_read_align_strand_end_skip(const bam_seq& bseq,
                               unsigned& end_skip) {

    unsigned read_end(bseq.size());

    while (read_end>0) {
        if (bseq.get_char(read_end-1)=='N') read_end--;
        else break;
    }

    end_skip=bseq.size()-read_end;
}



void
get_read_fwd_strand_skip(const bam_seq& bseq,
                         const bool is_fwd_strand,
                         unsigned& begin_skip,
                         unsigned& end_skip) {

    begin_skip=0;
    if (is_fwd_strand) {
        get_read_align_strand_end_skip(bseq,end_skip);
    } else {
        end_skip=0;
        const unsigned bsize(bseq.size());
        while (begin_skip<bsize) {
            if (bseq.get_char(begin_skip)=='N') begin_skip++;
            else break;
        }
    }
}
