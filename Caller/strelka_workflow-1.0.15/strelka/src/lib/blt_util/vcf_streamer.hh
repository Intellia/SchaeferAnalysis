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
#ifndef __VCF_STREAMER_HH
#define __VCF_STREAMER_HH

#include "blt_util/bam_util.hh"
#include "blt_util/tabix_util.hh"
#include "blt_util/vcf_record.hh"


struct vcf_streamer {

    // optionally provide a BAM header to validate vcf chromosome names against
    //
    explicit
    vcf_streamer(const char* filename,
                 const char* region = NULL,
                 const bam_header_t* bh = NULL);

    ~vcf_streamer();

    // advance to next vcf record
    //
    // is_indel_only - if set, skip all records except indels
    //
    bool next(const bool is_indel_only=false);

    const vcf_record* get_record_ptr() const {
        if (_is_record_set) return &_vcfrec;
        else               return NULL;
    }

    const char* name() const { return _stream_name.c_str(); }

    unsigned record_no() const { return _record_no; }

    void report_state(std::ostream& os) const;

    //const bam_header_t*
    //get_header() const { return _bfp->header; }

private:
    bool _is_record_set;
    bool _is_stream_end;
    unsigned _record_no;
    std::string _stream_name;

    tabix_t* _tfp;
    ti_iter_t _titer;

    vcf_record _vcfrec;
};


#endif
