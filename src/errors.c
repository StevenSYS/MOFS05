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

#include "internal/errors.h"

const char *mofs05_errors(enum mofs05_errors error) {
	switch (error) {
		case MOFS05_ERROR_NONE:			return "No errors";
		case MOFS05_ERROR_EXTERNAL:		return "External error";
		case MOFS05_ERROR_ALLOCATE:		return "Failed to allocate memory for variable";
		case MOFS05_ERROR_FILE_NULL:		return "File is NULL";
		case MOFS05_ERROR_FILE_SMALL:		return "File is too small";
		case MOFS05_ERROR_FILE_IS_DIR:		return "File is a directory";
		case MOFS05_ERROR_FILE_NOT_EXIST:	return "File doesn't exist";
		case MOFS05_ERROR_ARGS_SMALL:		return "Not enough arguments";
		case MOFS05_ERROR_INCORRECT_FORMAT:	return "Incorrect format";
		default:				return "Unknown error";
	}
}