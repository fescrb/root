/*
 * Copyright (C) 2020  Fernando Escribano Macias 
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

/**
 * @file Just a file to dump any manual tests.
 */ 

#include <root/graphics/instance.h>
#include <root/io/format.h>

#include <iostream>

int main() {
    root::instance::init();
    auto devices = root::instance::get()->physical_devices();

    for(int i = 0; i < devices.size(); i++) {
        std::cout << root::format().to_string(*(devices[i].properties())) << std::endl;

        auto& familyProperties = devices[i].queue_family_properties();
        for(int j = 0; j < familyProperties.size(); j++) {
            std::cout << root::format().to_string(familyProperties[j]) << std::endl;
        }
    }
}