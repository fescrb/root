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

#include <root/root.h>
#include <root/graphics/window.h>
#include <root/graphics/surface.h>
#include <root/graphics/device.h>
#include <root/graphics/swapchain.h>
#include <root/graphics/shader_module.h>
#include <root/graphics/vertex_input.h>
#include <root/graphics/input_assembly.h>
#include <root/graphics/pipeline_layout.h>
#include <root/graphics/raster.h>
#include <root/graphics/renderpass.h>
#include <root/graphics/pipeline.h>
#include <root/graphics/framebuffer.h>
#include <root/graphics/command_pool.h>
#include <root/graphics/command_buffer.h>

#if !defined(ROOT_ANDROID)
#include <GLFW/glfw3.h>
#endif

int root_main(int arg_c, char** arg_v) {
    auto& devices = root::graphics::instance::get()->physical_devices();

    root::graphics::device* device = nullptr;

    root::log::d("", "Found {} devices", devices.size());

    for(int i = 0; i < devices.size(); i++) {
        root::log::d("", "Device {}: {}", i, devices[i].properties());

        auto extension_properties = devices[i].extensions();

        for(int j = 0; j < extension_properties.size(); j++) {
            root::log::d("", "Extension {}:{}", j, extension_properties[j]);
        }

        auto family_properties = devices[i].queue_family_properties();
        
        root::log::d("", "Device {} has {} queues", i, family_properties.size());
        for(int j = 0; j < family_properties.size(); j++) {
            root::log::d("", "Queue {}:{}", j, family_properties[j]);
        }

        if(devices[i].has_graphics_queue() && devices[i].has_present_queue(root::graphics::surface::get_default())) {
            root::log::d("", "Device {} has both a present and a graphics queue", i);
            device = new root::graphics::device(devices[i], root::graphics::surface::get_default());
        } else {
            root::log::d("", "Device {} does not have both a present and a graphics queue", i);
        }
    }

    if(!device) {
        root::log::e("", "No suitable device found");
        abort();
    }

    root::graphics::swapchain swapchain(root::graphics::surface::get_default(), *device);

    root::log::d("", "swapchain created viewport {} scissor {}", swapchain.viewport(), swapchain.scissor());

    root::graphics::shader_module vert(*device, "vert.spv");
    root::graphics::shader_module frag(*device, "frag.spv");

    root::graphics::shader shaders[2] = {
        root::graphics::shader(vert, VK_SHADER_STAGE_VERTEX_BIT, "main"), 
        root::graphics::shader(frag, VK_SHADER_STAGE_FRAGMENT_BIT, "main")
    };

    root::graphics::vertex_input vertex_input;
    root::graphics::input_assembly input_assembly(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);

    root::graphics::pipeline_layout pipeline_layout(*device, swapchain);
    root::graphics::raster raster;

    root::graphics::attachment attachment(swapchain);
    root::graphics::renderpass renderpass(*device, attachment);

    root::graphics::pipeline pipeline(*device, shaders, vertex_input, input_assembly, pipeline_layout, raster, renderpass);

    root::array<root::graphics::framebuffer> framebuffers(swapchain.swapchain_images.size());

    for(root::u32 i = 0; i < framebuffers.size(); i++) {
        framebuffers[i] = std::move(
            root::graphics::framebuffer(
                *device, 
                renderpass, 
                swapchain.swapchain_images.range(i, i+1),
                swapchain.extent
            )
        );
        root::log::d("", "Framebuffer[{}] extent {} ", i, framebuffers[i].entent());
    }

    root::graphics::command_pool command_pool(*device);

    root::graphics::semaphore acquire_s(*device);
    root::graphics::semaphore present_s(*device);

    while(!glfwWindowShouldClose(root::graphics::window::get_default()->handle())){
        glfwPollEvents();
        root::graphics::command_buffer buffer(command_pool);
        root::u32 image = swapchain.acquire(acquire_s);


        buffer.begin();
        buffer.start_render_pass(renderpass, framebuffers[image]);
        buffer.bind_pipeline(pipeline);
        buffer.draw(3, 1, 0, 0);
        buffer.end_render_pass();
        buffer.end();

        VkSubmitInfo submit_info;
        submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit_info.pNext = nullptr;
        submit_info.waitSemaphoreCount = 1;
        submit_info.pWaitSemaphores = &(acquire_s.handle());
        VkPipelineStageFlags wait_stages[] = {VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT};
        submit_info.pWaitDstStageMask = wait_stages;
        submit_info.commandBufferCount = 1;
        submit_info.pCommandBuffers = &(buffer.handle());
        submit_info.signalSemaphoreCount = 1;
        submit_info.pSignalSemaphores = &(present_s.handle());
        VkResult submit_result = vkQueueSubmit(device->get_graphics_queue(), 1, &submit_info, VK_NULL_HANDLE);
        if (submit_result != VK_SUCCESS) {
            root::log::e("simple_window_app", "vkQueueSubmit failed with {}", submit_result);
            abort();
        }
        swapchain.present(root::array_slice<root::graphics::semaphore>(&present_s, 1), image);
    }

    return 0;
}