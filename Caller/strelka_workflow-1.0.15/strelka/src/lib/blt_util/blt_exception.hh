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
#ifndef __BLT_EXCEPTION_HH
#define __BLT_EXCEPTION_HH

#include <exception>
#include <string>

/// \brief a minimal exception class
struct blt_exception : public std::exception {

    blt_exception(const char* s);

    ~blt_exception() throw() {}

    const char* what() const throw() { return message.c_str(); }

    std::string message;
};


#endif

