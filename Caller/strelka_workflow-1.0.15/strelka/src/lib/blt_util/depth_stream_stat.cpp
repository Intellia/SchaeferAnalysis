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
#include "blt_util/depth_stream_stat.hh"

#include <iostream>



std::ostream&
operator<<(std::ostream& os,const depth_stream_stat& ss) {

    os << "sample_size: " << ss.sample_size() << " nonzero: " << ss.nonzero() << " min: " << ss.min() << " max: " << ss.max()
       << " mean: " << ss.mean() << " sd: " << ss.sd();

    return os;
}
