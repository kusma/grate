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

#include <GLES2/gl2.h>

#include "common.h"

static const GLchar *vertex_shader[] = {
	"attribute vec4 position;\n",
	"attribute vec4 color;\n",
	"varying vec4 vcolor;\n",
	"\n",
	"void main()\n",
	"{\n",
	"    gl_Position = position;\n",
	"    vcolor = color;\n",
	"}"
};

static const GLchar *fragment_shader[] = {
	"precision mediump float;\n",
	"varying vec4 vcolor;\n",
	"uniform vec4 u0, u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11, u12;\n",
	"\n",
	"void main()\n",
	"{\n",
	"    gl_FragColor = u0 + u1 + u2 + u3 + u4 + u5 + u6 + u7 + u8 + u9 + u10 + u11 + u12;\n",
	"}"
};

void pbuffer_draw(struct pbuffer *pbuffer)
{
	static const GLfloat vertices[] = {
		 0.0f,  0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f,
	};
	static const GLfloat colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
	};
	static const GLushort indices[] = {
		0, 1, 2,
	};
	GLuint vs, fs, program;
	GLint position, color, uniform;

	printf("=== compiling shaders\n");
	vs = glsl_shader_load(GL_VERTEX_SHADER, vertex_shader,
			      ARRAY_SIZE(vertex_shader));
	fs = glsl_shader_load(GL_FRAGMENT_SHADER, fragment_shader,
			      ARRAY_SIZE(fragment_shader));
	glFlush();
	printf("=== linking program\n");
	program = glsl_program_create(vs, fs);
	glsl_program_link(program);
	glFlush();
	printf("=== using program\n");
	glUseProgram(program);
	glFlush();

	position = glGetAttribLocation(program, "position");
	color = glGetAttribLocation(program, "color");
	uniform = glGetUniformLocation(program, "u0");

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glVertexAttribPointer(position, 4, GL_FLOAT, GL_FALSE,
			      4 * sizeof(GLfloat), vertices);
	glEnableVertexAttribArray(position);

	glVertexAttribPointer(color, 4, GL_FLOAT, GL_FALSE,
			      4 * sizeof(GLfloat), colors);
	glEnableVertexAttribArray(color);

	glUniform4f(uniform, 0.75f, 0.25f, 0.75f, 1.0f);

	glDrawElements(GL_TRIANGLES, ARRAY_SIZE(indices), GL_UNSIGNED_SHORT,
		       indices);
	glFlush();
	printf("=== done\n");
}

int main(int argc, char *argv[])
{
	struct gles_options options;
	struct pbuffer *pbuffer;
	int err;

	memset(&options, 0, sizeof(options));
	options.width = 32;
	options.height = 32;

	err = gles_parse_command_line(&options, argc, argv);
	if (err < 0)
		return 1;

	pbuffer = pbuffer_create(options.width, options.height);
	if (!pbuffer) {
		fprintf(stderr, "pbuffer_create() failed\n");
		return 1;
	}

	pbuffer_draw(pbuffer);
	pbuffer_save(pbuffer, "test.png");
	pbuffer_free(pbuffer);

	return 0;
}
