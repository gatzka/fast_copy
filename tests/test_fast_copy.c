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

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "fast_copy.h"
#include "fff.h"
#include "unity.h"

static const unsigned int BUFFER_SIZE = 100;

DEFINE_FFF_GLOBALS

void setUp(void)
{
	FFF_RESET_HISTORY();
}

void tearDown(void)
{
}

static void test_different_sizes_aligned(void)
{
	uint8_t dst_buffer[BUFFER_SIZE];
	uint8_t src_buffer[BUFFER_SIZE];

	for (size_t i = 1; i < sizeof(src_buffer); i++) {
		memset(src_buffer, 'A', i);
		fast_copy(dst_buffer, src_buffer, i);
		TEST_ASSERT_EQUAL_CHAR_ARRAY(src_buffer, dst_buffer, i);
	}
}

static void test_different_sizes_unaligned_destination(void)
{
	uint8_t dst_buffer[BUFFER_SIZE];
	uint8_t src_buffer[BUFFER_SIZE];

	for (size_t i = 1; i < sizeof(src_buffer) - 1; i++) {
		memset(src_buffer, 'A', i);
		fast_copy(dst_buffer + 1, src_buffer, i);
		TEST_ASSERT_EQUAL_CHAR_ARRAY(src_buffer, dst_buffer + 1, i);
	}
}

static void test_different_sizes_unaligned_source(void)
{
	uint8_t dst_buffer[BUFFER_SIZE];
	uint8_t src_buffer[BUFFER_SIZE];

	for (size_t i = 1; i < sizeof(src_buffer) - 1; i++) {
		memset(src_buffer + 1, 'A', i);
		fast_copy(dst_buffer, src_buffer + 1, i);
		TEST_ASSERT_EQUAL_CHAR_ARRAY(src_buffer + 1, dst_buffer, i);
	}
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_different_sizes_aligned);
	RUN_TEST(test_different_sizes_unaligned_destination);
	RUN_TEST(test_different_sizes_unaligned_source);
	return UNITY_END();
}
