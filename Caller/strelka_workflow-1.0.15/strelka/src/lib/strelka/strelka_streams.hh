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

#include "strelka_sample_type.hh"

#include "starling_common/starling_streams_base.hh"
#include "strelka/strelka_shared.hh"



struct strelka_streams : public starling_streams_base {

    typedef starling_streams_base base_t;

    strelka_streams(const strelka_options& opt,
                    const prog_info& pinfo,
                    const bam_header_t* const bam_header);

    ~strelka_streams();

    std::ostream*
    somatic_snv_osptr() const
    {
        return _somatic_snv_osptr.get();
    }

    std::ostream*
    somatic_indel_osptr() const
    {
        return _somatic_indel_osptr.get();
    }

    std::ostream*
    somatic_callable_osptr() const
    {
        return _somatic_callable_osptr.get();
    }

private:
    std::auto_ptr<std::ostream> _somatic_snv_osptr;
    std::auto_ptr<std::ostream> _somatic_indel_osptr;
    std::auto_ptr<std::ostream> _somatic_callable_osptr;
};
