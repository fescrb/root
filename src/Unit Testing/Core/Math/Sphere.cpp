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


#include "Sphere.h"
#include <boost/test/unit_test.hpp>

using namespace root;

BOOST_AUTO_TEST_SUITE(Root)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Math)
BOOST_AUTO_TEST_SUITE(Sphere)

BOOST_AUTO_TEST_CASE(SpherePointIntersection){
	sphere sph(3.0f, 2.0f, -1.0f, 10.0f); 
    float4 inPoint(3.0f , 4.0f, 5.0f, 1.0f);
	float4 outPoint(-5.0f , 16.0f, 4.0f, 1.0f);
    BOOST_REQUIRE( sph.intersects(inPoint));
	BOOST_REQUIRE(!sph.intersects(outPoint));
}

BOOST_AUTO_TEST_CASE(SphereSphereIntersection){
	sphere sph(3.0f, 2.0f, -1.0f, 10.0f); 
    sphere intersectingSphere(10.0f , 4.0f, 5.0f, 10.0f);
	sphere nonIntersectingSphere(-15.0f , 16.0f, 4.0f, 10.0f);
    BOOST_REQUIRE( sph.intersects(intersectingSphere));
	BOOST_REQUIRE(!sph.intersects(nonIntersectingSphere));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()