/*
 * Copyright (c) 2017 Dmitry Osipenko
 * Copyright (c) 2017 Erik Faye-Lund
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

#ifndef GRATE_3D_CTX_H
#define GRATE_3D_CTX_H 1

#include "host1x.h"

struct grate;
struct grate_program;
struct grate_texture;
struct grate_3d_ctx;
struct mat4;

enum grate_3d_ctx_cull_face
{
	GRATE_3D_CTX_CULL_FACE_NONE		= 0xA001,
	GRATE_3D_CTX_CULL_FACE_FRONT		= 0xA002,
	GRATE_3D_CTX_CULL_FACE_BACK		= 0xA003,
	GRATE_3D_CTX_CULL_FACE_BOTH		= 0xA004,
};

enum grate_3d_ctx_depth_function {
	GRATE_3D_CTX_DEPTH_FUNC_NEVER		= 0xB001,
	GRATE_3D_CTX_DEPTH_FUNC_LESS		= 0xB002,
	GRATE_3D_CTX_DEPTH_FUNC_EQUAL		= 0xB003,
	GRATE_3D_CTX_DEPTH_FUNC_LEQUAL		= 0xB004,
	GRATE_3D_CTX_DEPTH_FUNC_GREATER		= 0xB005,
	GRATE_3D_CTX_DEPTH_FUNC_NOTEQUAL	= 0xB006,
	GRATE_3D_CTX_DEPTH_FUNC_GEQUAL		= 0xB007,
	GRATE_3D_CTX_DEPTH_FUNC_ALWAYS		= 0xB008,
};

enum grate_3d_ctx_stencil_test_face {
	GRATE_3D_CTX_STENCIL_TEST_FRONT		= 0xC001,
	GRATE_3D_CTX_STENCIL_TEST_BACK		= 0xC002,
	GRATE_3D_CTX_STENCIL_TEST_BOTH		= 0xC003,
};

enum grate_3d_ctx_stencil_test_func {
	GRATE_3D_CTX_STENCIL_TEST_NEVER		= 0xD001,
	GRATE_3D_CTX_STENCIL_TEST_ALWAYS	= 0xD002,
	GRATE_3D_CTX_STENCIL_TEST_EQUAL		= 0xD003,
	GRATE_3D_CTX_STENCIL_TEST_NOTEQUAL	= 0xD004,
	GRATE_3D_CTX_STENCIL_TEST_LEQUAL	= 0xD005,
	GRATE_3D_CTX_STENCIL_TEST_GEQUAL	= 0xD006,
	GRATE_3D_CTX_STENCIL_TEST_GREATER	= 0xD007,
	GRATE_3D_CTX_STENCIL_TEST_LESS		= 0xD008,
};

enum grate_3d_ctx_stencil_operation {
	GRATE_3D_CTX_STENCIL_OP_ZERO		= 0xE001,
	GRATE_3D_CTX_STENCIL_OP_KEEP		= 0xE002,
	GRATE_3D_CTX_STENCIL_OP_INVERT		= 0xE003,
	GRATE_3D_CTX_STENCIL_OP_REPLACE		= 0xE004,
	GRATE_3D_CTX_STENCIL_OP_INCR		= 0xE005,
	GRATE_3D_CTX_STENCIL_OP_DECR		= 0xE006,
	GRATE_3D_CTX_STENCIL_OP_INCR_WRAP	= 0xE007,
	GRATE_3D_CTX_STENCIL_OP_DECR_WRAP	= 0xE008,
};

struct grate_3d_ctx * grate_3d_alloc_ctx(struct grate *grate);

int grate_3d_ctx_vertex_attrib_pointer(struct grate_3d_ctx *ctx,
				       unsigned location, unsigned size,
				       unsigned type, unsigned stride,
				       struct host1x_bo *data_bo);

#define grate_3d_ctx_vertex_attrib_float_pointer(ctx, location, size, bo)\
	grate_3d_ctx_vertex_attrib_pointer(ctx, location, size,		\
					   TGR3D_ATTRIB_TYPE_FLOAT32,	\
				           size * sizeof(float), bo)	\

int grate_3d_ctx_enable_vertex_attrib_array(struct grate_3d_ctx *ctx,
					    unsigned target);

int grate_3d_ctx_disable_vertex_attrib_array(struct grate_3d_ctx *ctx,
					     unsigned target);

int grate_3d_ctx_bind_render_target(struct grate_3d_ctx *ctx,
				    unsigned target,
				    struct host1x_pixelbuffer *pixbuf);

int grate_3d_ctx_set_render_target_dither(struct grate_3d_ctx *ctx,
					  unsigned target,
					  bool enable);

int grate_3d_ctx_enable_render_target(struct grate_3d_ctx *ctx,
				      unsigned target);

int grate_3d_ctx_disable_render_target(struct grate_3d_ctx *ctx,
				       unsigned target);

int grate_3d_ctx_bind_program(struct grate_3d_ctx *ctx,
			      struct grate_program *program);

int grate_3d_ctx_set_vertex_uniform(struct grate_3d_ctx *ctx,
				    unsigned location, unsigned nb,
				    float *values);

int grate_3d_ctx_set_vertex_mat4_uniform(struct grate_3d_ctx *ctx,
					 unsigned location, struct mat4 *mat);

int grate_3d_ctx_set_fragment_uniform(struct grate_3d_ctx *ctx,
				      unsigned location, unsigned nb,
				      float *value);

int grate_3d_ctx_set_fragment_float_uniform(struct grate_3d_ctx *ctx,
					    unsigned location, float value);

void grate_3d_ctx_set_depth_range(struct grate_3d_ctx *ctx,
				  float near, float far);

void grate_3d_ctx_set_dither(struct grate_3d_ctx *ctx, uint32_t unk);

void grate_3d_ctx_set_viewport_bias(struct grate_3d_ctx *ctx,
				    float x, float y, float z);

void grate_3d_ctx_set_viewport_scale(struct grate_3d_ctx *ctx,
				     float width, float height, float depth);

void grate_3d_ctx_set_point_params(struct grate_3d_ctx *ctx, uint32_t params);

void grate_3d_ctx_set_point_size(struct grate_3d_ctx *ctx, float size);

void grate_3d_ctx_set_line_params(struct grate_3d_ctx *ctx, uint32_t params);

void grate_3d_ctx_set_line_width(struct grate_3d_ctx *ctx, float width);

void grate_3d_ctx_use_guardband(struct grate_3d_ctx *ctx, bool enabled);

void grate_3d_ctx_set_front_direction_is_cw(struct grate_3d_ctx *ctx,
					    bool front_cw);

void grate_3d_ctx_set_cull_face(struct grate_3d_ctx *ctx,
				enum grate_3d_ctx_cull_face cull_face);

void grate_3d_ctx_set_scissor(struct grate_3d_ctx *ctx,
			      unsigned x, unsigned width,
			      unsigned y, unsigned height);

void grate_3d_ctx_set_point_coord_range(struct grate_3d_ctx *ctx,
					float min_s, float max_s,
					float min_t, float max_t);

void grate_3d_ctx_set_polygon_offset(struct grate_3d_ctx *ctx,
				     float units, float factor);

void grate_3d_ctx_set_provoking_vtx_last(struct grate_3d_ctx *ctx, bool last);

int grate_3d_ctx_bind_texture(struct grate_3d_ctx *ctx,
			      unsigned location,
			      struct grate_texture *tex);

void grate_3d_ctx_set_depth_func(struct grate_3d_ctx *ctx,
				 enum grate_3d_ctx_depth_function func);

void grate_3d_ctx_perform_depth_test(struct grate_3d_ctx *ctx, bool enable);

void grate_3d_ctx_perform_depth_write(struct grate_3d_ctx *ctx, bool enable);

int grate_3d_ctx_bind_depth_buffer(struct grate_3d_ctx *ctx,
				   struct host1x_pixelbuffer *pixbuf);

void grate_3d_ctx_perform_stencil_test(struct grate_3d_ctx *ctx, bool enable);

void grate_3d_ctx_set_stencil_func(struct grate_3d_ctx *ctx,
				   enum grate_3d_ctx_stencil_test_face face,
				   enum grate_3d_ctx_stencil_test_func func,
				   unsigned ref, unsigned mask);

void grate_3d_ctx_set_stencil_ops(struct grate_3d_ctx *ctx,
				enum grate_3d_ctx_stencil_test_face face,
				enum grate_3d_ctx_stencil_operation fail_op,
				enum grate_3d_ctx_stencil_operation zfail_op,
				enum grate_3d_ctx_stencil_operation zpass_op);

int grate_3d_ctx_bind_stencil_buffer(struct grate_3d_ctx *ctx,
				     struct host1x_pixelbuffer *pixbuf);

#endif
