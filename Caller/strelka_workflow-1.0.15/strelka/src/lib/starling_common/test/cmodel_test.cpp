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

#include "cmodel.cpp"


BOOST_AUTO_TEST_SUITE( cmodel )



BOOST_AUTO_TEST_CASE( test_cmodel_qscore ) {

    BOOST_CHECK_EQUAL(prior_adjustment(std::log(2./1.),1.),5);
    BOOST_CHECK_EQUAL(prior_adjustment(std::log(1./2.),1.),2);

    BOOST_CHECK_EQUAL(prior_adjustment(std::log(2000./1.),1.),33);
    BOOST_CHECK_EQUAL(prior_adjustment(std::log(1./2000.),1.),0);

//    BOOST_CHECK_EQUAL(prior_adjustment(std::log(1./0.),1.),40);
}


BOOST_AUTO_TEST_SUITE_END()
