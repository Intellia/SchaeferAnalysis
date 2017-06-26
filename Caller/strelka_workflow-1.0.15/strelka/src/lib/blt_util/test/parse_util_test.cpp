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

#include "parse_util.hh"

#include <string>

BOOST_AUTO_TEST_SUITE( parse_util )

using namespace illumina::blt_util;

BOOST_AUTO_TEST_CASE( test_parse_int ) {
    const char* two = "2";
    const int val(parse_int(two));
    BOOST_CHECK_EQUAL(val, 2);
}

BOOST_AUTO_TEST_CASE( test_parse_int_str ) {
    static const char two[] = "2";
    const int val(parse_int_str(std::string(two)));
    BOOST_CHECK_EQUAL(val, 2);
}

BOOST_AUTO_TEST_CASE( test_parse_int_str_bad_input ) {
    static const std::string junk("ABCD");
    BOOST_CHECK_THROW(parse_int_str(junk), std::exception);
}

BOOST_AUTO_TEST_SUITE_END()

