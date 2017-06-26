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

#ifndef __STARLING_TYPES_HH
#define __STARLING_TYPES_HH

#include <stdint.h>


typedef uint32_t align_id_t;
typedef int32_t sample_id_t;

// So long as the sample count required by multi-sample applications
// remains small, any typoe of heap allocation is a waste, so we use
// this to create stack arrays:
//
enum { MAX_SAMPLE=2 };

#endif
