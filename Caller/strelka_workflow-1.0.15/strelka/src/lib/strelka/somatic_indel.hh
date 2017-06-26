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

#if 0

#include "somatic_indel_call.hh"

#include "starling_common/starling_indel_call_pprob_digt.hh"
#include "strelka/strelka_shared.hh"

#include "boost/utility.hpp"


namespace DDIINDEL {

enum index_t { SIZE = STAR_DIINDEL::SIZE*STAR_DIINDEL::SIZE };

inline
unsigned
get_state(const unsigned normal_gt,
          const unsigned tumor_gt) {
    return normal_gt+STAR_DIINDEL::SIZE*tumor_gt;
}

inline
void
get_digt_states(const unsigned dgt,
                unsigned& normal_gt,
                unsigned& tumor_gt) {
    normal_gt = (dgt%STAR_DIINDEL::SIZE);
    tumor_gt = (dgt/STAR_DIINDEL::SIZE);
}
}

std::ostream& operator<<(std::ostream& os,const DDIINDEL::index_t dgt);



// object used to pre-compute priors:
struct somatic_indel_caller : private boost::noncopyable {

    somatic_indel_caller(const strelka_options& opt,
                         const indel_digt_caller& in_caller);

    void
    get_somatic_indel(const strelka_options& opt,
                      const strelka_deriv_options& dopt,
                      const double indel_error_prob,
                      const double ref_error_prob,
                      const indel_key& ik,
                      const indel_data& normal_id,
                      const indel_data& tumor_id,
                      const bool is_use_alt_indel,
                      somatic_indel_call& sindel) const;

private:
    const double*
    normal_lnprior() const {
        return _in_caller.lnprior();
    }

    // struct prior_set {
    //     double normal[STAR_DIINDEL::SIZE];
    // };

    const indel_digt_caller& _in_caller;
    //    prior_set _lnprior;
    double _ln_som_match;
    double _ln_som_mismatch;
};

// file output -- data only
//
void
write_somatic_indel_file(const somatic_indel_call& dgt,
                         const starling_indel_report_info& iri,
                         const starling_indel_sample_report_info& normal_isri,
                         const starling_indel_sample_report_info& tumor_isri,
                         std::ostream& os);

#endif
