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

#include "starling_common/pos_basecall_buffer.hh"

#include <iostream>



// debug dumpers:
void
pos_basecall_buffer::
dump(std::ostream& os) const {

    pciter i(_pdata.begin()), i_end(_pdata.end());
    for (; i!=i_end; ++i) {
        os << "pc_buff pos: " << i->first << "\n";
    }
}

void
pos_basecall_buffer::update_ranksums(char refpos, const pos_t pos,const base_call& bc, const uint8_t mapq, const int cycle) {
    const bool is_reference(refpos==id_to_base(bc.base_id));

    _pdata[pos].baseq_ranksum.add_observation(is_reference,static_cast<int>(bc.get_qscore()));
    _pdata[pos].mq_ranksum.add_observation(is_reference,static_cast<int>(mapq));
    _pdata[pos].read_pos_ranksum.add_observation(is_reference,cycle);
}
