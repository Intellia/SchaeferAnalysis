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

#include "blt_util/bam_record.hh"
#include "blt_util/bam_streamer.hh"
#include "blt_util/vcf_record.hh"
#include "starling_common/starling_pos_processor_base.hh"


/// format the bam region string from the program options and
/// 'influence zones' defined by sppr.
///
std::string
get_starling_bam_region_string(const starling_options& opt,
                               const starling_deriv_options& dopt);


// handles genomic read alignments -- reads are parsed, their indels
// are extracted and buffered, and the reads themselves are buffered
//
void
process_genomic_read(const starling_options& client_opt,
                     const reference_contig_segment&, // ref,
                     const bam_streamer& read_stream,
                     const bam_record& read,
                     const pos_t base_pos,
                     const pos_t,// report_begin_pos,
                     starling_read_counts&, // brc,
                     starling_pos_processor_base& sppr,
                     const unsigned sample_no = 0);

/// insert a candidate indel into sppr
///
/// \param is_forced_output - the results of the genotype type must be output for this indel, no matter how unlikely the variant is:
void
process_candidate_indel(
    const unsigned max_indel_size,
    const vcf_record& vcf_indel,
    starling_pos_processor_base& sppr,
    const unsigned sample_no = 0,
    const bool is_forced_output = false);
