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

#include "boost/test/unit_test.hpp"

#include "math_util.hh"

#include <cmath>


BOOST_AUTO_TEST_SUITE( math_util )

static
void
single_log_sum_test(const double x1,
                    const double x2) {

    static const double eps(0.00001);

    const double expect(std::log(x1+x2));

    const double lnx1(std::log(x1));
    const double lnx2(std::log(x2));
    const double result(log_sum(lnx1,lnx2));

    BOOST_CHECK_CLOSE(result, expect, eps);
}


BOOST_AUTO_TEST_CASE( test_log_sum ) {

    single_log_sum_test(0.5,0.2);
    single_log_sum_test(0.00001,0.00000001);
    single_log_sum_test(1,1);
}

BOOST_AUTO_TEST_SUITE_END()

