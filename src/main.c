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

#include <stdio.h>
#include <string.h>
#include <mofs05.h>
#include <sys/stat.h>

#include "progInfo.h"

#define MAIN_PREFIX "Main"

mofs05_t mofs05;

static void printHelp() {
	printf(
		PROGRAM_NAME " v" PROGRAM_VERSION "\n"
		"lib" MOFS05_NAME " v" MOFS05_VERSION "\n"
		"l - List file contents of a MOFS05 file\n"
		"n - Make a MOFS05 file from other files\n"
		"s - List sizes of all files in a MOFS05 file\n"
		"x - Extract file(s) from a MOFS05 file\n"
		"X - Extract all files from a MOFS05 file\n"
	);
	return;
}

static inline enum mofs05_errors loadArgs(int argc, char *argv[]) {
	int i;
	enum mofs05_errors ret = MOFS05_ERROR_NONE;
	mofs05File_t *mofs05File;
	struct stat fileStat;
	FILE *file;
	
	if (argc < 2) {
		printHelp();
		return MOFS05_ERROR_NONE;
	}
	
	if (strcmp(argv[1], "l") == 0) {
		if (argc < 3) {
			return MOFS05_ERROR_ARGS_SMALL;
		}
		
		ret = mofs05_readFile(
			argv[2],
			&mofs05
		);
		
		MOFS05_PER(
			MOFS05_ERROR_EXTERNAL,
			ret,
			MOFS05_PREFIX
		);
		
		for (i = 0; i < mofs05.count; i++) {
			printf("%s\n", mofs05.i[i].name);
		}
		return MOFS05_ERROR_NONE;
	} else if (strcmp(argv[1], "n") == 0) {
		if (argc < 4) {
			return MOFS05_ERROR_ARGS_SMALL;
		}
		
		mofs05.count = argc - 3;
		MULTISTRUCT_INIT(mofs05File_t, mofs05);
		
		for (i = 0; i < mofs05.count; i++) {
			if (stat(argv[i + 2], &fileStat) < 0) {
				return MOFS05_ERROR_FILE_NULL;
			} else if (S_ISDIR(fileStat.st_mode)) {
				return MOFS05_ERROR_FILE_IS_DIR;
			}
			
			file = fopen(argv[i + 2], "rb");
			if (file == NULL) {
				return MOFS05_ERROR_FILE_NULL;
			}
			
			fseek(file, 0L, SEEK_END);
			mofs05.i[i].size = ftell(file);
			fseek(file, 0L, SEEK_SET);
			
			strncpy(
				mofs05.i[i].name,
				argv[i + 2],
				MOFS05_LENGTH_NAME
			);
			
			mofs05.i[i].data = malloc(mofs05.i[i].size);
			
			fread(
				mofs05.i[i].data,
				sizeof(char),
				mofs05.i[i].size,
				file
			);
		}
		
		ret = mofs05_writeFile(
			argv[argc - 1],
			&mofs05
		);
		
		MOFS05_PER(
			MOFS05_ERROR_EXTERNAL,
			ret,
			MOFS05_PREFIX
		);
		return MOFS05_ERROR_NONE;
	} else if (strcmp(argv[1], "s") == 0) {
		if (argc < 3) {
			return MOFS05_ERROR_ARGS_SMALL;
		}
		
		ret = mofs05_readFile(
			argv[2],
			&mofs05
		);
		
		MOFS05_PER(
			MOFS05_ERROR_EXTERNAL,
			ret,
			MOFS05_PREFIX
		);
		
		for (i = 0; i < mofs05.count; i++) {
			printf("%u\n", mofs05.i[i].size);
		}
		return MOFS05_ERROR_NONE;
	} else if (strcmp(argv[1], "x") == 0) {
		if (argc < 4) {
			return MOFS05_ERROR_ARGS_SMALL;
		}
		
		ret = mofs05_readFile(
			argv[2],
			&mofs05
		);
		
		MOFS05_PER(
			MOFS05_ERROR_EXTERNAL,
			ret,
			MOFS05_PREFIX
		);
		
		for (i = 3; i < argc; i++) {
			mofs05File = mofs05_getFile(&mofs05, argv[i]);
			if (mofs05File == NULL) {
				return MOFS05_ERROR_FILE_NULL;
			}
			
			ret = mofs05_extractFile(mofs05File);
			
			MOFS05_PER(
				MOFS05_ERROR_EXTERNAL,
				ret,
				MOFS05_PREFIX
			);
		}
		return MOFS05_ERROR_NONE;
	} else if (strcmp(argv[1], "X") == 0) {
		if (argc < 3) {
			return MOFS05_ERROR_ARGS_SMALL;
		}
		
		ret = mofs05_readFile(
			argv[2],
			&mofs05
		);
		
		MOFS05_PER(
			MOFS05_ERROR_EXTERNAL,
			ret,
			MOFS05_PREFIX
		);
		
		ret = mofs05_extract(&mofs05);
		
		MOFS05_PER(
			MOFS05_ERROR_EXTERNAL,
			ret,
			MOFS05_PREFIX
		);
		return MOFS05_ERROR_NONE;
	} else {
		printHelp();
	}
	return MOFS05_ERROR_NONE;
}

int main(int argc, char *argv[]) {
	enum mofs05_errors ret = MOFS05_ERROR_NONE;
	
	ret = loadArgs(argc, argv);
	
	MOFS05_PER(
		1,
		ret,
		MAIN_PREFIX
	)
	
	MULTISTRUCT_UNINIT(mofs05);
	return 0;
}