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

///
/// note coding convention for all ranges '_pos fields' is:
/// XXX_begin_pos is zero-indexed position at the begining of the range
/// XXX_end_pos is zero-index position 1 step after the end of the range
///

#ifndef __STARLING_POS_PROCESSOR_H
#define __STARLING_POS_PROCESSOR_H

#include "starling_common/starling_pos_processor_base.hh"



///
///
struct starling_pos_processor : public starling_pos_processor_base {

    typedef starling_pos_processor_base base_t;

    starling_pos_processor(const starling_options& client_opt,
                           const starling_deriv_options& client_dopt,
                           const reference_contig_segment& ref,
                           const starling_streams_base& client_io)
        : base_t(client_opt,client_dopt,ref,client_io,1) {}

private:
    void
    process_pos_variants(const pos_t pos) {
        process_pos_indel_single_sample(pos,0);
        process_pos_snp_single_sample(pos,0);
    }

    void
    write_counts(const pos_range& output_report_range) const;
};


#endif
