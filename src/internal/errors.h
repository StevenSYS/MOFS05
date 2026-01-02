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

#ifndef __MOFS05_ERRORS__
#define __MOFS05_ERRORS__

#ifdef __cplusplus
extern "C" {
#endif

/* Macros */
#define MOFS05_PER(_ret, _error, _prefix) \
	if (_error) { \
		if (_error != MOFS05_ERROR_EXTERNAL) { \
			fprintf( \
				stderr, \
				"ERROR: " _prefix ": %s\n", \
				mofs05_errors(_error) \
			); \
		} \
		return _ret; \
	}

#define MOFS05_PE(_error, _prefix) \
	if (_error) { \
		if (_error != MOFS05_ERROR_EXTERNAL) { \
			fprintf( \
				stderr, \
				"ERROR: " _prefix ": %s\n", \
				mofs05_errors(_error) \
			); \
		} \
	}

/* Enums */
enum mofs05_errors {
	MOFS05_ERROR_NONE,
	MOFS05_ERROR_EXTERNAL,
	MOFS05_ERROR_ALLOCATE,
	MOFS05_ERROR_FILE_NULL,
	MOFS05_ERROR_FILE_SMALL,
	MOFS05_ERROR_FILE_IS_DIR,
	MOFS05_ERROR_FILE_NOT_EXIST,
	MOFS05_ERROR_ARGS_SMALL,
	MOFS05_ERROR_INCORRECT_FORMAT,
	MOFS05_ERROR_UNKNOWN
};

/* Functions */
const char *mofs05_errors(enum mofs05_errors error);

#ifdef __cplusplus
};
#endif

#endif