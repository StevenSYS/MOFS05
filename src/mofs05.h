/*
	MIT License
	
	Copyright (c) 2026 StevenSYS
	
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#ifndef __MOFS05__
#define __MOFS05__

#include "errors.h"
#include "multistruct.h"

/* Macros */
#define MOFS05_NAME "MOFS05"
#define MOFS05_VERSION "1.0pre"

#define MOFS05_MAGIC MOFS05_NAME
#define MOFS05_LENGTH_MAGIC 6
#define MOFS05_LENGTH_NAME 100

#define MOFS05_PREFIX MOFS05_NAME

/* Structs */
typedef struct {
	char name[MOFS05_LENGTH_NAME];
	unsigned int size;
	void *data;
} mofs05File_t;

MULTISTRUCT(mofs05_t, mofs05File_t);

/* Functions */
enum mofs05_errors mofs05_writeFile(
	const char *filename,
	const mofs05_t *mofs05
);

enum mofs05_errors mofs05_readFile(
	const char *filename,
	mofs05_t *mofs05
);

mofs05File_t *mofs05_getFile(
	const mofs05_t *mofs05,
	const char *filename
);

enum mofs05_errors mofs05_extractFile(
	const mofs05File_t *mofs05File
);

enum mofs05_errors mofs05_extract(
	const mofs05_t *mofs05
);

#endif