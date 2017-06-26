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

#include "blt_util/seq_util.hh"

#include "boost/foreach.hpp"

#include <iosfwd>
#include <string>
#include <vector>


struct vcf_record {

    vcf_record() : pos(0) { clear(); }

    // set record from record string s, return false on error
    bool set(const char* s);

    void clear() {
        chrom="";
        pos=0;
        ref="";
        alt.clear();
    }

    bool
    is_valid() const {
        if (! is_valid_seq(ref.c_str())) return false;
        BOOST_FOREACH(const std::string& alt_allele, alt) {
            if (! is_valid_seq(alt_allele.c_str())) return false;
        }
        return true;
    }

    bool
    is_indel() const {
        if (! is_valid()) return false;
        if ((ref.size()>1) && (alt.size()>0)) return true;
        BOOST_FOREACH(const std::string& alt_allele, alt) {
            if (alt_allele.size()>1) return true;
        }
        return false;
    }

    bool
    is_snv() const {
        if (! is_valid()) return false;
        if (1 != ref.size()) return false;
        BOOST_FOREACH(const std::string& alt_allele, alt) {
            if (1 != alt_allele.size()) return false;
        }
        return true;
    }

    std::string chrom;
    int pos;
    std::string ref;
    std::vector<std::string> alt;
};


std::ostream& operator<<(std::ostream& os, const vcf_record& vcfr);

