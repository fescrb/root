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

#include "Vector.h"
#include <boost/test/unit_test.hpp>

using namespace root;

BOOST_AUTO_TEST_SUITE(Root)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Math)
BOOST_AUTO_TEST_SUITE(Vector)


/******************************
*********Float2 Tests**********
*******************************/

BOOST_AUTO_TEST_SUITE(Float2)

BOOST_AUTO_TEST_CASE(Float2Equals){
    float2 vector(2.0f,4.0f);
    BOOST_REQUIRE(vector==vector && vector[0]==2.0f && vector[1]==4.0f);
}

BOOST_AUTO_TEST_CASE(Float2Add){
    float2 lhs(3.0f,4.0f);
    float2 rhs(-1.5f,40.0f);
    BOOST_REQUIRE(lhs+rhs == float2(1.5f,44.0f));
    BOOST_REQUIRE(add(lhs,rhs) == float2(1.5f,44.0f));
}

BOOST_AUTO_TEST_CASE(Float2Minus){
    float2 lhs(3.0f,4.0f);
    float2 rhs(-1.5f,40.0f);
    BOOST_REQUIRE(lhs-rhs == float2(4.5f,-36.0f));
    BOOST_REQUIRE(sub(lhs,rhs) == float2(4.5f,-36.0f));
}

BOOST_AUTO_TEST_CASE(Float2Mul){
    float2 lhs(3.0f,-1.0f);
    F32 rhs(5.0f);
    BOOST_REQUIRE(lhs*rhs == float2(15.0f,-5.0f));
    BOOST_REQUIRE(mul(lhs,rhs) == float2(15.0f,-5.0f));
}

BOOST_AUTO_TEST_CASE(Float2ComponentWiseMul){
    float2 lhs(3.0f,-1.0f);
    float2 rhs(6.0f,-70.0f);
    BOOST_REQUIRE(lhs*rhs == float2(18.0f,70.0f));
    BOOST_REQUIRE(mul(lhs,rhs) == float2(18.0f,70.0f));
}

BOOST_AUTO_TEST_CASE(Float2Div){
    float2 lhs(3.0f,-1.0f);
    F32 rhs(5.0f);
    BOOST_REQUIRE(lhs/rhs == float2(3.0f/rhs,-1.0f/rhs));
    BOOST_REQUIRE(div(lhs,rhs) == float2(3.0f/rhs,-1.0f/rhs));
}

BOOST_AUTO_TEST_CASE(Float2Dot){
    float2 lhs(6.0f,10.0f);
    float2 rhs(7.0f,-2.0f);
    BOOST_REQUIRE(dot(lhs,rhs) == 22.0f);
}

BOOST_AUTO_TEST_CASE(Float2Mag){
    float2 vector(3.0f,4.0f);
    BOOST_REQUIRE(mag(vector) == 5.0f);
}

BOOST_AUTO_TEST_SUITE_END()

/*******************************
*********Double2 Tests**********
********************************/

BOOST_AUTO_TEST_SUITE(Double2)

BOOST_AUTO_TEST_CASE(Double2Equals){
    double2 vector(2.0f,4.0f);
    BOOST_REQUIRE(vector==vector && vector[0]==2.0f && vector[1]==4.0f);
}

BOOST_AUTO_TEST_CASE(Double2Add){
    double2 lhs(3.0f,4.0f);
    double2 rhs(-1.5f,40.0f);
    BOOST_REQUIRE(lhs+rhs == double2(1.5f,44.0f));
    BOOST_REQUIRE(add(lhs,rhs) == double2(1.5f,44.0f));
}

BOOST_AUTO_TEST_CASE(Double2Minus){
    double2 lhs(3.0f,4.0f);
    double2 rhs(-1.5f,40.0f);
    BOOST_REQUIRE(lhs-rhs == double2(4.5f,-36.0f));
    BOOST_REQUIRE(sub(lhs,rhs) == double2(4.5f,-36.0f));
}

BOOST_AUTO_TEST_CASE(Double2Mul){
    double2 lhs(3.0f,-1.0f);
    F64 rhs(5.0f);
    BOOST_REQUIRE(lhs*rhs == double2(15.0f,-5.0f));
    BOOST_REQUIRE(mul(lhs,rhs) == double2(15.0f,-5.0f));
}

BOOST_AUTO_TEST_CASE(Double2ComponentWiseMul){
    double2 lhs(3.0f,-1.0f);
    double2 rhs(6.0f,-70.0f);
    BOOST_REQUIRE(lhs*rhs == double2(18.0f,70.0f));
    BOOST_REQUIRE(mul(lhs,rhs) == double2(18.0f,70.0f));
}

BOOST_AUTO_TEST_CASE(Double2Div){
    double2 lhs(3.0f,-1.0f);
    F64 rhs(5.0f);
    BOOST_REQUIRE(lhs/rhs == double2(3.0f/rhs,-1.0f/rhs));
    BOOST_REQUIRE(div(lhs,rhs) == double2(3.0f/rhs,-1.0f/rhs));
}

BOOST_AUTO_TEST_CASE(Double2Dot){
    double2 lhs(6.0f,10.0f);
    double2 rhs(7.0f,-2.0f);
    BOOST_REQUIRE(dot(lhs,rhs) == 22.0f);
}

BOOST_AUTO_TEST_CASE(Double2Mag){
    double2 vector(3.0f,4.0f);
    BOOST_REQUIRE(mag(vector) == 5.0f);
}

BOOST_AUTO_TEST_SUITE_END()

/******************************
*********Float3 Tests**********
*******************************/

BOOST_AUTO_TEST_SUITE(Float3)

BOOST_AUTO_TEST_CASE(Float3Equals){
    float3 vector(2.0f,4.0f,6.0f);
    BOOST_REQUIRE(vector==vector && vector.getX() ==2.0f && vector.getY()==4.0f && vector.getZ()==6.0f);
}

BOOST_AUTO_TEST_CASE(Float3Add){
    float3 lhs(3.0f,4.0f,5.0f);
    float3 rhs(-1.5f,40.0f,9.0f);
    BOOST_REQUIRE(lhs+rhs == float3(1.5f,44.0f,14.0f));
    BOOST_REQUIRE(add(lhs,rhs) == float3(1.5f,44.0f,14.0f));
}

BOOST_AUTO_TEST_CASE(Float3Minus){
    float3 lhs(3.0f,4.0f,5.0f);
    float3 rhs(-1.5f,40.0f,9.0f);
    BOOST_REQUIRE(lhs-rhs == float3(4.5f,-36.0f,-4.0f));
    BOOST_REQUIRE(sub(lhs,rhs) == float3(4.5f,-36.0f,-4.0f));
}

BOOST_AUTO_TEST_CASE(Float3Mul){
    float3 lhs(3.0f,-1.0f,5.0f);
    F32 rhs(5.0f);
    BOOST_REQUIRE(lhs*rhs == float3(15.0f,-5.0f,25.0f));
    BOOST_REQUIRE(mul(lhs,rhs) == float3(15.0f,-5.0f,25.0f));
}

BOOST_AUTO_TEST_CASE(Float3ComponentWiseMul){
    float3 lhs(3.0f,-1.0f,5.0f);
    float3 rhs(6.0f,-70.0f,-0.5);
    BOOST_REQUIRE(lhs*rhs == float3(18.0f,70.0f,-2.5f));
    BOOST_REQUIRE(mul(lhs,rhs) == float3(18.0f,70.0f,-2.5f));
}

BOOST_AUTO_TEST_CASE(Float3Div){
    float3 lhs(3.0f,-1.0f,5.0f);
    F32 rhs(5.0f);
    BOOST_REQUIRE(lhs/rhs == float3(3.0f/rhs,-1.0f/rhs,1.0f));
    BOOST_REQUIRE(div(lhs,rhs) == float3(3.0f/rhs,-1.0f/rhs,1.0f));
}

BOOST_AUTO_TEST_CASE(Float3Dot){
    float3 lhs(6.0f,10.0f,5.0f);
    float3 rhs(7.0f,-2.0f,3.5f);
    BOOST_REQUIRE(dot(lhs,rhs) == 39.5f);
}

BOOST_AUTO_TEST_CASE(Float3Mag){
    float3 vector(3.0f,4.0f,5.0f);
    BOOST_REQUIRE(mag(vector) == F32(sqrt(50.0f)));
}

BOOST_AUTO_TEST_CASE(Float3Cross){
    float3 lhs(6.0f,10.0f,5.0f);
    float3 rhs(7.0f,-2.0f,3.5f);
    float3 crossProduct = cross(lhs,rhs);
    BOOST_REQUIRE(crossProduct == float3(45,14,-82));
    // Check that it's perpendicular.
    BOOST_REQUIRE(!dot(crossProduct,lhs));
    BOOST_REQUIRE(!dot(crossProduct,rhs));
}

BOOST_AUTO_TEST_SUITE_END()

/*******************************
*********Double3 Tests**********
********************************/

BOOST_AUTO_TEST_SUITE(Double3)

BOOST_AUTO_TEST_CASE(Double3Equals){
    double3 vector(2.0f,4.0f,6.0f);
    BOOST_REQUIRE(vector==vector && vector[0]==2.0f && vector[1]==4.0f && vector[2]==6.0f);
}

BOOST_AUTO_TEST_CASE(Double3Add){
    double3 lhs(3.0f,4.0f,5.0f);
    double3 rhs(-1.5f,40.0f,9.0f);
    BOOST_REQUIRE(lhs+rhs == double3(1.5f,44.0f,14.0f));
    BOOST_REQUIRE(add(lhs,rhs) == double3(1.5f,44.0f,14.0f));
}

BOOST_AUTO_TEST_CASE(Double3Minus){
    double3 lhs(3.0f,4.0f,5.0f);
    double3 rhs(-1.5f,40.0f,9.0f);
    BOOST_REQUIRE(lhs-rhs == double3(4.5f,-36.0f,-4.0f));
    BOOST_REQUIRE(sub(lhs,rhs) == double3(4.5f,-36.0f,-4.0f));
}

BOOST_AUTO_TEST_CASE(Double3Mul){
    double3 lhs(3.0f,-1.0f,5.0f);
    F64 rhs(5.0f);
    BOOST_REQUIRE(lhs*rhs == double3(15.0f,-5.0f,25.0f));
    BOOST_REQUIRE(mul(lhs,rhs) == double3(15.0f,-5.0f,25.0f));
}

BOOST_AUTO_TEST_CASE(Double3ComponentWiseMul){
    double3 lhs(3.0f,-1.0f,5.0f);
    double3 rhs(6.0f,-70.0f,-0.5);
    BOOST_REQUIRE(lhs*rhs == double3(18.0f,70.0f,-2.5f));
    BOOST_REQUIRE(mul(lhs,rhs) == double3(18.0f,70.0f,-2.5f));
}

BOOST_AUTO_TEST_CASE(Double3Div){
    double3 lhs(3.0f,-1.0f,5.0f);
    F64 rhs(5.0f);
    BOOST_REQUIRE(lhs/rhs == double3(3.0f/rhs,-1.0f/rhs,1.0f));
    BOOST_REQUIRE(div(lhs,rhs) == double3(3.0f/rhs,-1.0f/rhs,1.0f));
}

BOOST_AUTO_TEST_CASE(Double3Dot){
    double3 lhs(6.0f,10.0f,5.0f);
    double3 rhs(7.0f,-2.0f,3.5f);
    BOOST_REQUIRE(dot(lhs,rhs) == 39.5f);
}

BOOST_AUTO_TEST_CASE(Double3Mag){
    double3 vector(3.0f,4.0f,5.0f);
    BOOST_REQUIRE(mag(vector) == F64(sqrt(50.0f)));
}

BOOST_AUTO_TEST_CASE(Double3Cross){
    double3 lhs(6.0f,10.0f,5.0f);
    double3 rhs(7.0f,-2.0f,3.5f);
    double3 crossProduct = cross(lhs,rhs);
    BOOST_REQUIRE(crossProduct == double3(45,14,-82));
    // Check that it's perpendicular.
    BOOST_REQUIRE(!dot(crossProduct,lhs));
    BOOST_REQUIRE(!dot(crossProduct,rhs));
}

BOOST_AUTO_TEST_SUITE_END()

/******************************
*********Float4 Tests**********
*******************************/

BOOST_AUTO_TEST_SUITE(Float4)

BOOST_AUTO_TEST_CASE(Float4Equals){
    float4 vector(2.0f,4.0f,6.0f,8.0f);
    BOOST_REQUIRE(vector==vector && vector.getX()==2.0f && vector.getY()==4.0f && vector.getZ() && vector.getW()==8.0f);
}

BOOST_AUTO_TEST_CASE(Float4Add){
    float4 lhs(3.0f,4.0f,5.0f,0.0f);
    float4 rhs(-1.5f,40.0f,9.0f,3.5f);
    BOOST_REQUIRE(lhs+rhs == float4(1.5f,44.0f,14.0f,3.5f));
    BOOST_REQUIRE(add(lhs,rhs) == float4(1.5f,44.0f,14.0f,3.5f));
}

BOOST_AUTO_TEST_CASE(Float4Minus){
    float4 lhs(3.0f,4.0f,5.0f,0.0f);
    float4 rhs(-1.5f,40.0f,9.0f,3.5f);
    BOOST_REQUIRE(lhs-rhs == float4(4.5f,-36.0f,-4.0f,-3.5f));
    BOOST_REQUIRE(sub(lhs,rhs) == float4(4.5f,-36.0f,-4.0f,-3.5f));
}

BOOST_AUTO_TEST_CASE(Float4Mul){
    float4 lhs(3.0f,-1.0f,5.0f,4.5f);
    F32 rhs(5.0f);
    BOOST_REQUIRE(lhs*rhs == float4(15.0f,-5.0f,25.0f,22.5f));
    BOOST_REQUIRE(mul(lhs,rhs) == float4(15.0f,-5.0f,25.0f,22.5f));
}

BOOST_AUTO_TEST_CASE(Float4ComponentWiseMul){
    float4 lhs(3.0f,-1.0f,5.0f,4.5f);
    float4 rhs(6.0f,-70.0f,-0.5,6.0f);
    BOOST_REQUIRE(lhs*rhs == float4(18.0f,70.0f,-2.5f,27.0f));
    BOOST_REQUIRE(mul(lhs,rhs) == float4(18.0f,70.0f,-2.5f,27.0f));
}

BOOST_AUTO_TEST_CASE(Float4Div){
    float4 lhs(3.0f,-1.0f,5.0f,4.5f);
    F32 rhs(5.0f);
    BOOST_REQUIRE(lhs/rhs == float4(3.0f/rhs,-1.0f/rhs,1.0f,4.5f/rhs));
    BOOST_REQUIRE(div(lhs,rhs) == float4(3.0f/rhs,-1.0f/rhs,1.0f,4.5f/rhs));
}

BOOST_AUTO_TEST_CASE(Float4Sum){
    float4 vector(6.0f,10.0f,5.0f,-2.0f);
    BOOST_REQUIRE(sum(vector) == 19.0f);
}

BOOST_AUTO_TEST_CASE(Float4Dot){
    float4 lhs(6.0f,10.0f,5.0f,-2.0f);
    float4 rhs(7.0f,-2.0f,3.5f,4.5f);
    BOOST_REQUIRE(dot(lhs,rhs) == 30.5f);
}

BOOST_AUTO_TEST_CASE(Float4Mag){
    float4 vector(3.0f,4.0f,5.0f,6.0f);
    BOOST_REQUIRE(mag(vector) == F32(sqrt(86.0f)));
}

BOOST_AUTO_TEST_CASE(Float4Cross){
    float4 lhs(6.0f,10.0f,5.0f,1.0f);
    float4 rhs(7.0f,-2.0f,3.5f,0.0f);
    float4 crossProduct = cross(lhs,rhs);
    BOOST_REQUIRE(crossProduct == float4(45.0f,14.0f,-82.0f,0.0f));
    // Check that it's perpendicular.
    BOOST_REQUIRE(!dot(crossProduct,lhs));
    BOOST_REQUIRE(!dot(crossProduct,rhs));
}

BOOST_AUTO_TEST_CASE(Float4Normalize){
    float4 vector(6.0f,9.0f,5.0f,1.0f);
    float4 vector2(54.343f,-100.99f,7.4510f,8816.0f);
	
	vector.normalize();
	
	BOOST_REQUIRE(1.0f == mag(vector));
    BOOST_REQUIRE(1.0f == mag(normalized(vector2)));
}

// Created mostly to aid with SIMD vectors, as I have little experience.
BOOST_AUTO_TEST_CASE(Float4Set){
    float4 vector(6.0f,10.0f,5.0f,1.0f);
    vector.setX(2.0f);
	BOOST_REQUIRE(vector == float4(2.0f,10.0f,5.0f,1.0f));
	vector.setY(12.0f);
	BOOST_REQUIRE(vector == float4(2.0f,12.0f,5.0f,1.0f));
	vector.setZ(9.0f);
	BOOST_REQUIRE(vector == float4(2.0f,12.0f,9.0f,1.0f));
	vector.setW(1.5f);
	BOOST_REQUIRE(vector == float4(2.0f,12.0f,9.0f,1.5f));
}

BOOST_AUTO_TEST_SUITE_END()

/*******************************
*********Double4 Tests**********
********************************/

BOOST_AUTO_TEST_SUITE(Double4)

BOOST_AUTO_TEST_CASE(Double4Equals){
    double4 vector(2.0f,4.0f,6.0f,8.0f);
    BOOST_REQUIRE(vector==vector && vector[0]==2.0f && vector[1]==4.0f && vector[2]==6.0f && vector[3]==8.0f);
}

BOOST_AUTO_TEST_CASE(Double4Add){
    double4 lhs(3.0f,4.0f,5.0f,0.0f);
    double4 rhs(-1.5f,40.0f,9.0f,3.5f);
    BOOST_REQUIRE(lhs+rhs == double4(1.5f,44.0f,14.0f,3.5f));
    BOOST_REQUIRE(add(lhs,rhs) == double4(1.5f,44.0f,14.0f,3.5f));
}

BOOST_AUTO_TEST_CASE(Double4Minus){
    double4 lhs(3.0f,4.0f,5.0f,0.0f);
    double4 rhs(-1.5f,40.0f,9.0f,3.5f);
    BOOST_REQUIRE(lhs-rhs == double4(4.5f,-36.0f,-4.0f,-3.5f));
    BOOST_REQUIRE(sub(lhs,rhs) == double4(4.5f,-36.0f,-4.0f,-3.5f));
}

BOOST_AUTO_TEST_CASE(Double4Mul){
    double4 lhs(3.0f,-1.0f,5.0f,4.5f);
    F64 rhs(5.0f);
    BOOST_REQUIRE(lhs*rhs == double4(15.0f,-5.0f,25.0f,22.5f));
    BOOST_REQUIRE(mul(lhs,rhs) == double4(15.0f,-5.0f,25.0f,22.5f));
}

BOOST_AUTO_TEST_CASE(Double4ComponentWiseMul){
    double4 lhs(3.0f,-1.0f,5.0f,4.5f);
    double4 rhs(6.0f,-70.0f,-0.5,6.0f);
    BOOST_REQUIRE(lhs*rhs == double4(18.0f,70.0f,-2.5f,27.0f));
    BOOST_REQUIRE(mul(lhs,rhs) == double4(18.0f,70.0f,-2.5f,27.0f));
}

BOOST_AUTO_TEST_CASE(Double4Div){
    double4 lhs(3.0f,-1.0f,5.0f,4.5f);
    F64 rhs(5.0f);
    BOOST_REQUIRE(lhs/rhs == double4(3.0f/rhs,-1.0f/rhs,1.0f,4.5f/rhs));
    BOOST_REQUIRE(div(lhs,rhs) == double4(3.0f/rhs,-1.0f/rhs,1.0f,4.5f/rhs));
}

BOOST_AUTO_TEST_CASE(Double4Dot){
    double4 lhs(6.0f,10.0f,5.0f,-2.0f);
    double4 rhs(7.0f,-2.0f,3.5f,4.5f);
    BOOST_REQUIRE(dot(lhs,rhs) == 30.5f);
}

BOOST_AUTO_TEST_CASE(Double4Mag){
    double4 vector(3.0f,4.0f,5.0f,6.0f);
    BOOST_REQUIRE(mag(vector) == F64(sqrt(86.0f)));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
