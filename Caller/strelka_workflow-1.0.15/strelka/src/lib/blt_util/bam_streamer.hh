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

#include "blt_util/bam_record.hh"

#include <string>


struct bam_streamer {

    explicit
    bam_streamer(const char* filename,
                 const char* region = NULL);

    ~bam_streamer();

    /// set new or first region for same filename:
    void
    set_new_region(const char* region);

    void
    set_new_region(int reg, int beg, int end);

    bool next();

    const bam_record* get_record_ptr() const {
        if (_is_record_set) return &_brec;
        else               return NULL;
    }

    const char* name() const {
        return _stream_name.c_str();
    }

    unsigned record_no() const {
        return _record_no;
    }

    void report_state(std::ostream& os) const;

    const char*
    target_id_to_name(const int32_t tid) const;

    int32_t
    target_name_to_id(const char* seq_name) const;

    const bam_header_t*
    get_header() const {
        return _bfp->header;
    }

private:
    void _load_index();

    bool _is_record_set;
    samfile_t* _bfp;
    bam_index_t* _bidx;
    bam_iter_t _biter;
    bam_record _brec;

    // track for debug only:
    unsigned _record_no;
    std::string _stream_name;
    bool _is_region;
    std::string _region;
};

