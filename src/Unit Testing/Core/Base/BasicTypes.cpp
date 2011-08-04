/*
 * Copyright (C) 2011  Fernando Escribano Macias
 *
 * This file is part of the Root Engine.
 * 
 * The Root Engine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The Root Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with The Root Engine.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "BasicTypes.h"
#include <boost/test/unit_test.hpp>

using namespace root;

BOOST_AUTO_TEST_SUITE(Root)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Base)
BOOST_AUTO_TEST_SUITE(BasicTypes)

/*******************************
*********Integer Tests**********
*******************************/


BOOST_AUTO_TEST_SUITE(Integers)

BOOST_AUTO_TEST_CASE(I64Size){
    BOOST_REQUIRE(sizeof(I64) == I64_SIZE);
}

BOOST_AUTO_TEST_CASE(I32Size){
    BOOST_REQUIRE(sizeof(I32) == I32_SIZE);
}

BOOST_AUTO_TEST_CASE(I16Size){
    BOOST_REQUIRE(sizeof(I16) == I16_SIZE);
}

BOOST_AUTO_TEST_CASE(I8Size){
    BOOST_REQUIRE(sizeof(I8) == I8_SIZE);
}

BOOST_AUTO_TEST_SUITE_END()


/****************************************
*********Unsigned Integer Tests**********
****************************************/


BOOST_AUTO_TEST_SUITE(UnsignedIntegers)

BOOST_AUTO_TEST_CASE(U64Size){
    BOOST_REQUIRE(sizeof(U64) == U64_SIZE);
}

BOOST_AUTO_TEST_CASE(U32Size){
    BOOST_REQUIRE(sizeof(U32) == U32_SIZE);
}

BOOST_AUTO_TEST_CASE(U16Size){
    BOOST_REQUIRE(sizeof(U16) == U16_SIZE);
}

BOOST_AUTO_TEST_CASE(U8Size){
    BOOST_REQUIRE(sizeof(U8) == U8_SIZE);
}

BOOST_AUTO_TEST_SUITE_END()

/**************************************
*********Floating Point Tests**********
**************************************/

BOOST_AUTO_TEST_SUITE(FloatingPoint)

BOOST_AUTO_TEST_CASE(F64Size){
    BOOST_REQUIRE(sizeof(F64) == 8);
}

BOOST_AUTO_TEST_CASE(F32Size){
    BOOST_REQUIRE(sizeof(F32) == 4);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
