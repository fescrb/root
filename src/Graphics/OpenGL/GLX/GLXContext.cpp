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

#include "GLXContext.h"

using namespace root;
using namespace graphics;

int testAttributes[] = {
    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
    GLX_RENDER_TYPE,   GLX_RGBA_BIT,
    GLX_DOUBLEBUFFER,  True,
    GLX_RED_SIZE,      1,
    GLX_GREEN_SIZE,    1,
    GLX_BLUE_SIZE,     1,
    None
};


OpenGLGLXContext::OpenGLGLXContext() {
	m_pRawAttributes = testAttributes;

    m_pDisplay = XOpenDisplay(NULL);
    if (!m_pDisplay) {
		// No display opened
    }

    int numberOfAttributes;
    GLXFBConfig* frameBufferConfigs = glXChooseFBConfig(m_pDisplay, DefaultScreen(m_pDisplay), m_pRawAttributes, &numberOfAttributes);
                                   
	if (!frameBufferConfigs) {
      // No such configuration available
	}

	m_pFrameBufferConfig = frameBufferConfigs[0];

    /* Create a GLX context for OpenGL rendering */
    m_context = glXCreateNewContext(m_pDisplay, m_pFrameBufferConfig, GLX_RGBA_TYPE, NULL, True);
}

GLXContext OpenGLGLXContext::getGLXContext() {
	return m_context;
}

Display* OpenGLGLXContext::getDisplay() {
	return m_pDisplay;
}

GLXFBConfig OpenGLGLXContext::getFrameBufferConfig() {
	return m_pFrameBufferConfig;
}

int* OpenGLGLXContext::getRawAttributes() {
	return m_pRawAttributes;
}
