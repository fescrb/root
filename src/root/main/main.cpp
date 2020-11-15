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

#include <root/root.h>

#include <root/graphics/graphics.h>

#if !defined(ROOT_ANDROID)
int main(int argc, char** argv) {
    root::graphics::init();
    int res = root_main(argc, argv);
    root::graphics::deinit();
    return res;
}
#else 

#include "platform/android/looper.h"

void android_main(struct android_app* state) {
    root::main::loop(state);
}
#endif