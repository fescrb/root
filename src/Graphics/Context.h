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

#ifndef ROOT_GRAPHICS_CONTEXT_H
#define ROOT_GRAPHICS_CONTEXT_H

namespace root {

	namespace graphics {

		class Surface;

		class Context {
			public:
				/**
				 * @return true iff success.
				 */
				virtual bool 		 makeCurrent(Surface *surface) = 0;
		};

	}

}

#endif //ROOT_GRAPHICS_CONTEXT_H
