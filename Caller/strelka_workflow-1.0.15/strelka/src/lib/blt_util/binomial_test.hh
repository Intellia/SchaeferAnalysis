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
#ifndef __BINOMIAL_TEST_HH
#define __BINOMIAL_TEST_HH

#include <ciso646>


bool
is_reject_binomial_p_exact(const double alpha,
                           const double p,
                           const unsigned n_success,
                           const unsigned n_failure);

bool
is_reject_binomial_p_chi_sqr(const double alpha,
                             const double p,
                             const unsigned n_success,
                             const unsigned n_failure);

/// \brief test to reject a binomial with p='p' at FPR<='alpha'
///
/// chooses the testing method to strike a reasonable compromise
/// between efficiency and accuracy
///
bool
is_reject_binomial_p(const double alpha,
                     const double p,
                     const unsigned n_success,
                     const unsigned n_failure);

#endif
