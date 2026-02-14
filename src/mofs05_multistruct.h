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

#ifndef __MULTISTRUCT__
#define __MULTISTRUCT__

#include "mofs05_multistructConfig.h"

/* Macros */
#define MULTISTRUCT(_name, _type) \
	typedef struct { \
		_type *i; \
		unsigned int count; \
	} _name;

#define MULTISTRUCT_INIT(_type, _var) \
	if (_var.count) { \
		_var.i = (_type *)MULTISTRUCT_MALLOC( \
			sizeof(_type[_var.count]) \
		); \
		if (_var.i == NULL) { \
			return MOFS05_ERROR_ALLOCATE; \
		} \
	}

#define MULTISTRUCT_UNINIT(_var) \
	if (_var.i != NULL) { \
		MULTISTRUCT_FREE(_var.i); \
		_var.i = NULL; \
	} \
	_var.count = 0;

#endif