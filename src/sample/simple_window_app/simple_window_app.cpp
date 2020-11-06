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
#include <root/io/log.h>

#include <root/graphics/window.h>
#include <root/graphics/surface.h>
#include <root/graphics/device.h>
#include <root/graphics/swapchain.h>
#include <root/graphics/shader.h>

int main() {
    root::instance::init();

    root::window window(640u, 480u, "Test");

    root::surface surface(window);

    auto devices = root::instance::get()->physical_devices();

    root::device* device = nullptr;

    for(int i = 0; i < devices.size(); i++) {
        root::log::d("", "Device {}: {}", i, *(devices[i].properties()));

        auto& familyProperties = devices[i].queue_family_properties();
        for(int j = 0; j < familyProperties.size(); j++) {
            root::log::d("", "Queue {}:{}", j, familyProperties[j]);
        }

        if(devices[i].has_graphics_queue() && devices[i].has_present_queue(surface)) {

            device = new root::device(devices[i], surface);
        }
    }

    if(!device) {
        root::log::e("", "No suitable device found");
        abort();
    }

    root::swapchain swapchain(surface, *device);

    root::shader vert(*device, "vert.spv");
    root::shader frag(*device, "frag.spv");

    while(true){}
}