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

#ifndef __BLT_ARG_VALIDATE_HH
#define __BLT_ARG_VALIDATE_HH


#include "blt_common/blt_shared.hh"
#include "blt_util/prog_info.hh"


extern const double MAX_MONOPLOID_THETA;
extern const double MAX_DIPLOID_THETA;


void
check_option_arg_range(const prog_info& pinfo,
                       const double val,
                       const char* label,
                       const double min,
                       const double max);


void
validate_blt_opt(const prog_info& pinfo,
                 const blt_options& client_opt);

#endif
