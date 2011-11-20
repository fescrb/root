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

#include "GLXSurface.h"

using namespace root::graphics;

GLXSurface::GLXSurface()
: 	m_pContext(new OpenGLGLXContext){
	initialiseGLX();
}

GLXSurface::GLXSurface(OpenGLGLXContext *context)
:	m_pContext(context){
	initialiseGLX();
}

void GLXSurface::initialiseGLX() {
	int visualInfoNum;
	Display *display = m_pContext->getDisplay();
	GLXFBConfig frameBufferConfig = m_pContext->getFrameBufferConfig();

	m_pVisualInfo = glXGetVisualFromFBConfig(display, frameBufferConfig);

	m_xWindowAttributes.border_pixel = 0;
	m_xWindowAttributes.event_mask = StructureNotifyMask;
	m_xWindowAttributes.colormap = XCreateColormap(display, RootWindow(display, m_pVisualInfo->screen), m_pVisualInfo->visual, AllocNone);

	int valueMask = CWBorderPixel | CWColormap | CWEventMask;

	m_window = XCreateWindow(display, RootWindow(display, m_pVisualInfo->screen), 0, 0, 256, 256, 0, m_pVisualInfo->depth, InputOutput, m_pVisualInfo->visual, valueMask, &m_xWindowAttributes);

	m_glxWindow = glXCreateWindow( display, frameBufferConfig, m_window, NULL );

	XMapWindow( display, m_window );
}

Context* GLXSurface::getContext() {
	return m_pContext;
}

Window GLXSurface::getWindow() {
	return m_window;
}

void GLXSurface::makeContextCurrent() {
	m_pContext->makeCurrent(this);
}

void GLXSurface::swapBuffers() {
	glXSwapBuffers(m_pContext->getDisplay(), m_window);
}

Surface* Surface::create() {
	return new GLXSurface;
}