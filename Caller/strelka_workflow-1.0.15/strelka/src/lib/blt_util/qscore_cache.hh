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

#ifndef __QSCORE_CACHE_HH
#define __QSCORE_CACHE_HH

#include <stdint.h>

#include <cassert>
#include <ciso646>


struct qphred_cache {

    static
    double
    get_error_prob(const int qscore) {
        return qc().get_error_prob_imp(qscore);
    }

    static
    double
    get_ln_comp_error_prob(const int qscore) {
        return qc().get_lncompe_imp(qscore);
    }

    static
    double
    get_ln_error_prob(const int qscore) {
        return qc().get_lne_imp(qscore);
    }

    static
    int
    get_mapped_qscore(const int basecall_qscore,
                      const int mapping_qscore) {
        return qc().get_mapped_qscore_imp(basecall_qscore,mapping_qscore);
    }

    enum { MAX_QSCORE = 70,
           MAX_MAP = 90
         };

    static
    void
    qscore_check(const int qscore,
                 const char* label) {
        if (qscore < 0) invalid_qscore_error(qscore,label);
        if (qscore > MAX_QSCORE) high_qscore_error(qscore,label);
    }

private:
    qphred_cache();

    static
    const qphred_cache&
    qc() {
        static const qphred_cache qc;
        return qc;
    }

    static void invalid_qscore_error(const int qscore, const char* label);
    static void high_qscore_error(const int qscore, const char* label);

    static
    void
    qscore_check_int(const int qscore) {
        static const char* label = "phred";
        qscore_check(qscore,label);
    }

    double
    get_error_prob_imp(const int qscore) const {
        qscore_check_int(qscore);
        return q2p[qscore];
    }

    double
    get_lncompe_imp(const int qscore) const {
        qscore_check_int(qscore);
        return q2lncompe[qscore];
    }

    double
    get_lne_imp(const int qscore) const {
        qscore_check_int(qscore);
        return q2lne[qscore];
    }

    int
    get_mapped_qscore_imp(const int basecall_qscore,
                          int mapping_qscore) const {
        static const char* label = "basecall quality";
        qscore_check(basecall_qscore,label);
        assert(mapping_qscore>=0);
        if (mapping_qscore>MAX_MAP) { mapping_qscore=MAX_MAP; }
        return mappedq[mapping_qscore][basecall_qscore];
    }

    double q2p[MAX_QSCORE+1];
    double q2lncompe[MAX_QSCORE+1];
    double q2lne[MAX_QSCORE+1];
    uint8_t mappedq[MAX_MAP+1][MAX_QSCORE+1];
};


struct qlogodds_cache {

    static
    double
    get_error_prob(const int qscore) {
        static const qlogodds_cache qc;
        return qc.get_error_prob_imp(qscore);
    }

private:
    qlogodds_cache();

    void qscore_error(const int qscore) const;

    double
    get_error_prob_imp(const int qscore) const {
        if ((qscore < MIN_QSCORE) || (qscore > MAX_QSCORE)) qscore_error(qscore);
        return q2p[qscore];
    }

    enum { MIN_QSCORE = -40, MAX_QSCORE = 70 };

    double q2p_base[MAX_QSCORE+1-MIN_QSCORE];
    double* const q2p;
};

#endif

