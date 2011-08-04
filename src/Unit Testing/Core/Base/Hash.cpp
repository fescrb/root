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

#include "Hash.h"

#include "DefaultAllocator.h" // We need to allocate space for the test message, so we use the default allocator.

#include <boost/test/unit_test.hpp>

using namespace root;

BOOST_AUTO_TEST_SUITE(Root)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Base)
BOOST_AUTO_TEST_SUITE(Hash)

/***************************
 * Test hashing algorithms *
 ***************************/

const I8* message = "7RaP831sUYzHx9cIY6Bo8NV6Bistqnw6IXV9kJfp7r7fEttzO3cMequkyg5fIPYfh2YNQSmfELlBTF36ppLsRhvodRk" \
					"DLxEJ3VdQIigghXebjwcDbPY3GOKmeLF7lbmh38i7Zy0nvXNxpY2aezs4z7S02LZuRgrtz9hj2XeQaqTIbjuP9WdfT9" \
					"vOusOTNlwBfgb996SE" ;
					  
struct HashTestFixture {
					 HashTestFixture() {
		messageLength = strlen(message);
		testMessage = (U8*)DefaultAllocator::getStandardAllocator()->allocate(messageLength * U8_SIZE);
		memcpy(testMessage,message,messageLength*U8_SIZE);
	}
	
					~HashTestFixture() {
		DefaultAllocator::getStandardAllocator()->free<U8>(testMessage);
	}
	
	U8				*testMessage;
	
	U32				 messageLength;
	
	//! Checksum value calculated by posix cksum program.
	static const U32 crc32ChecksumValue = 2761070660;
	
	//! CRC-32-IEEE 802.3 Polynomial key. 
	static const U32 crc32PolynomialKey = 0x82608EDB;
};

#include <stdio.h>

BOOST_FIXTURE_TEST_CASE(CRC32Checksum,HashTestFixture){
	printf("%u\n",crc32(testMessage, messageLength,crc32PolynomialKey));
    BOOST_REQUIRE(crc32ChecksumValue == crc32(testMessage, messageLength,crc32PolynomialKey));
}




BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()