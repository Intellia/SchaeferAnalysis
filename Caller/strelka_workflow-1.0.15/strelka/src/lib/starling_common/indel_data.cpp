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

#include "blt_util/blt_exception.hh"
#include "starling_common/indel_data.hh"

#include <iostream>
#include <sstream>



std::ostream&
operator<<(std::ostream& os,
           const indel_observation_data& obs) {

    os << "is_noise: " << obs.is_noise << "\n";
    os << "is_external: " << obs.is_external_candidate << "\n";
    os << "is_forced_output: " << obs.is_forced_output << "\n";
    os << "type: " << INDEL_ALIGN_TYPE::label(obs.iat) << "\n";
    os << "align_id: " << obs.id << "\n";
    os << "insert_seq: " << obs.insert_seq << "\n";
    return os;
}

static
void
report_indel_evidence_set(const indel_data::evidence_t& e,
                          const char* label,
                          std::ostream& os) {
    typedef indel_data::evidence_t::const_iterator viter;
    viter i(e.begin()),i_end(e.end());
    for (unsigned n(0); i!=i_end; ++i) {
        os << label << " no: " << ++n << " id: " << *i << "\n";
    }
}



std::ostream&
operator<<(std::ostream& os,
           const read_path_scores& rps) {

    os << "ref: " << rps.ref
       << " indel: " << rps.indel
       << " nsite: " << rps.nsite;

#if 0
    if (rps.is_alt) {
        os << " alt: " << rps.alt;
    }
#else
    typedef read_path_scores::alt_indel_t::const_iterator aiter;
    aiter i(rps.alt_indel.begin()), i_end(rps.alt_indel.end());
    for (; i!=i_end; ++i) {
        const indel_key& ik(i->first);
        os << " alt-" << ik.pos << "-" << INDEL::get_index_label(ik.type) << ik.length << ": " << i->second;
    }
#endif

    os << " ist1?: " << rps.is_tier1_read;

    return os;
}


void
insert_seq_manager::
_exception(const char* msg) const {
    std::ostringstream oss;
    oss << "Exception in insert_seq_manager: " << msg;
    throw blt_exception(oss.str().c_str());
}


void
insert_seq_manager::
_finalize() {
    unsigned count(0);
    std::string& candidate(_consensus_seq);

    BOOST_FOREACH(const obs_t::value_type& val, _obs)
    {
        if (val.first.size() < candidate.size()) continue;
        if (val.first.size() == candidate.size())
        {
            if (val.second <= count) continue;
        }
        candidate = val.first;
        count = val.second;
    }
    _consensus_seq = candidate;
    _obs.clear();
    _is_consensus=true;
}



std::ostream&
operator<<(std::ostream& os,
           const indel_data& id) {
    os << "seq: " << id.get_insert_seq() << "\n";

    report_indel_evidence_set(id.all_read_ids,"all_read",os);
    report_indel_evidence_set(id.contig_ids,"contig",os);
    //    report_indel_evidence_set(id.tier1_map_read_ids,"tier1_map_read",os);
    report_indel_evidence_set(id.tier2_map_read_ids,"tier2_map_read",os);
    report_indel_evidence_set(id.submap_read_ids,"submap_read",os);
    report_indel_evidence_set(id.noise_read_ids,"noise_read",os);

    {
        typedef indel_data::score_t::const_iterator siter;
        siter i(id.read_path_lnp.begin()), i_end(id.read_path_lnp.end());
        for (unsigned n(0); i!=i_end; ++i) {
            os << "read_path_lnp no: " << ++n
               << " id: " << i->first
               << " " << i->second
               << "\n";
        }
    }

    report_indel_evidence_set(id.suboverlap_tier1_read_ids,"suboverlap_tier1_read",os);
    report_indel_evidence_set(id.suboverlap_tier2_read_ids,"suboverlap_tier2_read",os);

    os << "is_external_candidate: " << id.is_external_candidate << "\n";

    return os;
}

