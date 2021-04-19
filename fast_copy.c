/*
 * SPDX-License-Identifier: MIT
 *
 * The MIT License (MIT)
 *
 * Copyright (c) <2021> <Stephan Gatzka>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "fast_copy.h"

static inline bool is_aligned(const void *ptr, size_t byte_count)
{
	return ((uintptr_t)(ptr)) % (byte_count) == 0;
}

void *fast_copy(void *restrict dest, const void *restrict src, size_t count)
{
	uint_fast32_t *restrict dest_aligned;
	const uint_fast32_t *restrict src_aligned;

	size_t bc = sizeof(*dest_aligned);

	if (!is_aligned(dest, bc) || !is_aligned(src, bc)) {
		uint8_t *restrict byte_dest = dest;
		const uint8_t *restrict byte_src = src;
		for (size_t i = 0; i < count; i++) {
			byte_dest[i] = byte_src[i];
		}

		return dest;
	}

	size_t main_count = count / sizeof(*dest_aligned);

	uint_fast8_t post_count =
	    (uint_fast8_t)(count - (main_count * sizeof(*dest_aligned)));

	dest_aligned = dest;
	src_aligned = src;

	while (main_count-- > 0) {
		*dest_aligned = *src_aligned;
		dest_aligned++;
		src_aligned++;
	}

	uint8_t *restrict byte_dest = dest;
	const uint8_t *restrict byte_src = src;
	for (size_t i = count - post_count; i < count; i++) {
		byte_dest[i] = byte_src[i];
	}

	return dest;
}
