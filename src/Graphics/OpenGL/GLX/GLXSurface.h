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

#ifndef ROOT_GRAPHICS_GLX_SURFACE_H
#define ROOT_GRAPHICS_GLX_SURFACE_H

#include "Surface.h"

#include "GLXContext.h"

namespace root {

	namespace graphics {

		class GLXSurface
		: 	public Surface {
			public:
				explicit 					 GLXSurface();
				explicit 					 GLXSurface(OpenGLGLXContext *context);

				virtual Context				*getContext();
				Window						 getWindow();

				virtual void				 swapBuffers();
				void						 makeContextCurrent();

			private:
				void						 initialiseGLX();

				OpenGLGLXContext			*m_pContext;

				Window						 m_window;
				XSetWindowAttributes		 m_xWindowAttributes;
				GLXWindow					 m_glxWindow;

				XVisualInfo					*m_pVisualInfo;
		};

	}

}

#endif //ROOT_GRAPHICS_GLX_SURFACE_H
