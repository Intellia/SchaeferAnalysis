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

/*
 * Codonphaser.hh
 *
 *  Test for codon-phasing.
 *
 *  Created on: Aug 10, 2013
 *  Author: Morten Kallberg
 */

#ifndef CODONPHASER_HH_
#define CODONPHASER_HH_

//#include "starling_common/gvcf_block_site_record.hh"
#include "starling_common/gvcf_locus_info.hh"

class Codon_phaser {
public:
    Codon_phaser();
    virtual ~Codon_phaser();

public:

    bool add_site(site_info& si);  // Add site to buffer
    void clear_buffer(void);       // clear site buffer
    site_info make_record(void);   // make phased record
    void write_out_buffer();       // debugging feature, print current buffer to std
    bool is_in_block;              // Are we currently in a phasing block
    std::vector<site_info> buffer;
private:
    int block_end;                 // position of last added het site to block
    int range;
    int het_count;

};

#endif /* CODONPHASER_HH_ */
