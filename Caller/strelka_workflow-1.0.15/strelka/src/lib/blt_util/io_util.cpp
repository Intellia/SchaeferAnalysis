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
#include "blt_util/log.hh"

#include <cstdlib>

#include <fstream>
#include <iostream>



void
open_ifstream(std::ifstream& ifs,
              const char* filename) {

    ifs.open(filename);
    if (! ifs) {
        log_os << "ERROR: Can't open file: " << filename << "\n";
        exit(EXIT_FAILURE);
    }
}
