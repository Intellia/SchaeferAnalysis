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

#include "blt_util/bam_record.hh"
#include "blt_util/blt_exception.hh"

#include <sstream>



unsigned
bam_record::
alt_map_qual(const char* tag) const {
    uint8_t* alt_ptr(bam_aux_get(_bp,tag));
    if ((NULL != alt_ptr) && is_int_code(alt_ptr[0])) {
        const int alt_map(bam_aux2i(alt_ptr));
        if (alt_map<0) {
            std::ostringstream oss;
            oss << "ERROR: Unexpected negative value in optional BAM tag: '" << std::string(tag,2) << "'\n"
                << "\tRemove the --eland-compatability flag to stop using this tag.\n";
            throw blt_exception(oss.str().c_str());
        }
        return static_cast<unsigned>(alt_map);
    } else {
        return map_qual();
    }
}



const char*
bam_record::
get_string_tag(const char* tag) const {

    // retrieve the BAM tag
    uint8_t* pTag = bam_aux_get(_bp, tag);
    if (!pTag) return NULL;

    // skip tags that are not encoded as a null-terminated string
    if (pTag[0] != 'Z') return NULL;
    ++pTag;

    return (const char*)pTag;
}



bool
bam_record::
get_num_tag(const char* tag, int32_t& num) const {

    // retrieve the BAM tag
    uint8_t* pTag = bam_aux_get(_bp, tag);
    if (!pTag) return false;

    // skip tags that are not encoded as integers
    if (!is_int_code(pTag[0])) return false;
    num = bam_aux2i(pTag);

    return true;
}
