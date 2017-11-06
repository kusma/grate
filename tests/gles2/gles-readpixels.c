/*
 * Copyright (c) 2012, 2013 Erik Faye-Lund
 * Copyright (c) 2013 Avionic Design GmbH
 * Copyright (c) 2013 Thierry Reding
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "common.h"

static void draw(struct window *window)
{
	static const char *vertex_source =
		"precision highp float;\n"
		"attribute vec4 position;\n"
		"attribute vec4 color;\n"
		"\n"
		"varying vec4 vcolor;\n"
		"\n"
		"void main()\n"
		"{\n"
		"  gl_Position = position;\n"
		"  vcolor = color;\n"
		"}\n";

	static const char *fragment_source =
		"precision mediump float;\n"
		"varying vec4 vcolor;\n"
		"\n"
		"void main()\n"
		"{\n"
		"  gl_FragColor = vcolor;\n"
		"}\n";

	static GLfloat vertices[] = {
		 0.0f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
	};

	static GLfloat colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
	};

	GLuint vertex = glsl_shader_load(GL_VERTEX_SHADER, &vertex_source, 1);
	GLuint fragment = glsl_shader_load(GL_FRAGMENT_SHADER, &fragment_source, 1);
	GLuint program = glsl_program_create(vertex, fragment);
	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "color");
	glsl_program_link(program);

	glUseProgram(program);
	glViewport(0, 0, window->width, window->height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, colors);
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glFinish();

	GLubyte pixel[4];
	glReadPixels(window->width / 2, window->height / 2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
	for (int i = 0; i < 4; ++i)
		printf("%02x ", pixel[i]);
	printf("\n");

	eglSwapBuffers(window->egl.display, window->egl.surface);
}

int main(int argc, char *argv[])
{
	const unsigned int width = 640;
	const unsigned int height = 480;
	struct window *window;

	window = window_create(0, 0, width, height);
	if (!window) {
		fprintf(stderr, "failed to create window\n");
		return 1;
	}

	window_show(window);

	while (true) {
		if (!window_event_loop(window))
			break;

		draw(window);
	}



	window_close(window);
	return 0;
}
