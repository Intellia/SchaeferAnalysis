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

#include "ranksum.hh"

#include <iostream>


BOOST_AUTO_TEST_SUITE( test_ranksum )


BOOST_AUTO_TEST_CASE( test_ranksum )
{
    ranksum r('A');
    r.add_observation('A',44);
    r.add_observation('A',45); //check tie both
    r.add_observation('N',45);
    r.add_observation('N',50);
    r.add_observation('A',52);
    r.add_observation('A',53);
    r.add_observation('A',56);
    r.add_observation('A',58); //check tie single
    r.add_observation('A',58);
    r.add_observation('N',61);
    r.add_observation('N',63);
    r.add_observation('A',65);
    r.add_observation('N',75);
    r.add_observation('A',79);
    r.add_observation('N',85);
    r.add_observation('N',93);

    BOOST_REQUIRE( (r.get_u_stat() < 0.00001));
}


BOOST_AUTO_TEST_SUITE_END()

