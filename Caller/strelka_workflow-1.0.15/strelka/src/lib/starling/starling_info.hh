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

#ifndef __STARLING_INFO_HH
#define __STARLING_INFO_HH

#include "blt_util/prog_info.hh"


struct starling_info : public prog_info {

    static
    const prog_info& get() {
        static const starling_info vci;
        return vci;
    }

private:
    const char* name() const {
        static const char NAME[] = "IsaacVariantCaller";
        return NAME;
    }

    const char* version() const {
        static const char VERSION[] = "${VERSION}";
        return VERSION;
    }

    void usage(const char* xmessage = 0) const;

    void doc() const {};

    starling_info() {}
    virtual ~starling_info() {}
};

#endif
