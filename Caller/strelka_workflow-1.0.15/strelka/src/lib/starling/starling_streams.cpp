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

#include "starling_streams.hh"

#include <iostream>


const sample_info starling_sample_info;



starling_streams::
starling_streams(const starling_options& opt,
                 const prog_info& pinfo,
                 const bam_header_t* const header)
    : base_t(opt,pinfo,starling_sample_info) {

    if (opt.is_bindel_diploid_file) {
        _bindel_diploid_osptr[0].reset(initialize_bindel_file(opt,pinfo,opt.bindel_diploid_filename));
    }

    if (opt.is_gvcf_output()) {
        _gvcf_osptr[0] = initialize_gvcf_file(opt,pinfo,opt.gvcf.out_file,header,_gvcf_osptr_auto[0]);
    }

    if (opt.is_realigned_read_file) {
        _realign_bam_ptr[0].reset(initialize_realign_bam(opt.is_clobber,pinfo,opt.realigned_read_filename,"realigned-read BAM",header));
    }
}
