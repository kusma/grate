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

#ifndef GRATE_GR2D_H
#define GRATE_GR2D_H 1

#include "nvhost.h"

struct nvhost_gr2d {
	struct nvhost_client client;
	struct nvmap_handle *buffer;
	struct nvmap_handle *scratch;
	int fd;
};

struct nvhost_gr2d *nvhost_gr2d_open(struct nvmap *nvmap,
				     struct nvhost_ctrl *ctrl,
				     struct nvhost_fence *fence);
void nvhost_gr2d_close(struct nvhost_gr2d *gr2d);
int nvhost_gr2d_clear(struct nvhost_gr2d *gr2d, struct nvmap_framebuffer *fb,
		      struct nvhost_fence *fence,
		      float red, float green, float blue, float alpha,
		      int x, int y, int width, int height);

#endif
