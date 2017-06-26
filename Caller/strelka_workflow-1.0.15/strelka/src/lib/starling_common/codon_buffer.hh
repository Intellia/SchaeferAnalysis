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
 * codon_buffer.hh
 *
 *  Created on: Sep 13, 2013
 *      Author: mkallberg
 */

#ifndef CODON_BUFFER_HH_
#define CODON_BUFFER_HH_
#include "starling_common/starling_pos_processor_base.hh"

class Codon_buffer {
public:
    Codon_buffer();
    virtual ~Codon_buffer();
//    void set_sample(starling_pos_processor::sample_info* si);

private:
    int mysample;
//    sample_info* mysample;
};

#endif /* CODON_BUFFER_HH_ */
