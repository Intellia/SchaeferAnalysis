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
/// XXX_begin_pos is zero-indexed position at the beginning of the range
/// XXX_end_pos is zero-index position 1 step after the end of the range
///

#pragma once

#include "strelka_sample_type.hh"
#include "strelka_streams.hh"

#include "starling_common/starling_pos_processor_base.hh"
#include "strelka/CallableProcessor.hh"
#include "strelka/strelka_shared.hh"


///
///
struct strelka_pos_processor : public starling_pos_processor_base {

    typedef starling_pos_processor_base base_t;

    strelka_pos_processor(const strelka_options& opt,
                          const strelka_deriv_options& dopt,
                          const reference_contig_segment& ref,
                          const strelka_streams& client_io);

    ~strelka_pos_processor();

private:
    void
    process_pos_variants(const pos_t pos) {
        process_pos_indel_single_sample(pos,STRELKA_SAMPLE_TYPE::NORMAL);
        process_pos_indel_single_sample(pos,STRELKA_SAMPLE_TYPE::TUMOR);

        process_pos_snp_single_sample(pos,STRELKA_SAMPLE_TYPE::NORMAL);
        process_pos_snp_single_sample(pos,STRELKA_SAMPLE_TYPE::TUMOR);

        process_pos_snp_somatic(pos);
        process_pos_indel_somatic(pos);
    }

    void
    process_pos_snp_somatic(const pos_t pos);

    void
    process_pos_indel_somatic(const pos_t pos);

    void
    write_counts(const pos_range& output_report_range) const;

    /////////////////////////////

    // keep some of the original strelka classes handy so we don't
    // have to down-cast:
    const strelka_options& _opt;
    const strelka_deriv_options& _dopt;
    const strelka_streams& _client_io;

    extra_position_data _tier2_epd[MAX_SAMPLE];

    CallableProcessor _callProcessor;
};
