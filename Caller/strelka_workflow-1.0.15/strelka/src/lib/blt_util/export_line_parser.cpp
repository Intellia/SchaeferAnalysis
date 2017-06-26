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
#include "blt_util/blt_exception.hh"
#include "blt_util/export_line_parser.hh"

#include <cassert>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <sstream>



void
export_line_parser::
set_export_line(char* line) {
    static const char sep('\t');

    assert(line);

    char* p(line);

    _entry[0]=p;
    unsigned i(1);
    while ((*p != '\n') && (*p != '\0')) {
        if (*p == sep) {
            if (i == MAX_ENTRY) break;
            *p = '\0';
            _entry[i++] = p+1;
        }
        ++p;
    }

    *p = '\0';
    _is_set=true;

    if (i < SIZE) {
        _entry[i] = 0;
        std::ostringstream oss;
        oss << "ERROR:: Detected only " <<  i << " fields in export line where at least " << SIZE << " fields were expected.\n"
            << "\texport line: ";
        write_export_line(oss);
        oss << "\n";
        _is_set=false;
        throw blt_exception(oss.str().c_str());
    }
    _entry_count=i;
}



void
export_line_parser::
write_export_line(std::ostream& os) const {

    for (unsigned i(0); i<SIZE; ++i) {
        if (_entry[i]==0) break;
        if (i) os << '\t';
        os << _entry[i];
    }
}



void
export_line_parser::
str2i_die(const char* s,
          const char* type) const {
    std::ostringstream oss;
    oss << "ERROR:: export_line_parser failed to parse: '" << s << "' as type " << type << " in export line:\n\n";
    write_export_line(oss);
    oss << "\n";
    throw blt_exception(oss.str().c_str());
}



export_single_line_parser::
export_single_line_parser(const char* line) {
    assert(line);
    const unsigned line_size(strlen(line));
    assert(line_size<_line_buf_size);
    strncpy(_line_buf,line,_line_buf_size-1);
    set_export_line(_line_buf);
}
