#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "mofs05.h"

#define ITR(_condission, _ret) \
	if (_condission) { \
		return _ret; \
	}

enum mofs05_errors mofs05_writeFile(
	const char *filename,
	const mofs05_t *mofs05
) {
	char byte;
	unsigned int i, j;
	
	struct stat fileStat;
	
	FILE *file = fopen(filename, "wb");
	
	ITR(stat(filename, &fileStat) < 0, MOFS05_ERROR_FILE_NOT_EXIST)
	else ITR(S_ISDIR(fileStat.st_mode), MOFS05_ERROR_FILE_IS_DIR);
	
	ITR(file == NULL, MOFS05_ERROR_FILE_NULL);
	
	fwrite(
		MOFS05_MAGIC,
		sizeof(char),
		MOFS05_LENGTH_MAGIC,
		file
	);
	
	fwrite(
		&mofs05->count,
		sizeof(int),
		1,
		file
	);
	
	for (i = 0; i < mofs05->count; i++) {
		fwrite(
			&mofs05->i[i],
			sizeof(char),
			MOFS05_LENGTH_NAME +
			sizeof(int),
			file
		);
		
		for (j = 0; j < mofs05->i[i].size; j++) {
			byte = ((char *)mofs05->i[i].data)[j] + j;
			fwrite(
				&byte,
				sizeof(char),
				1,
				file
			);
		}
	}
	fclose(file);
	return MOFS05_ERROR_NONE;
}

enum mofs05_errors mofs05_readFile(
	const char *filename,
	mofs05_t *mofs05
) {
	char magic[MOFS05_LENGTH_MAGIC];
	unsigned int i, j;
	
	struct stat fileStat;
	
	FILE *file = fopen(filename, "rb");
	
	ITR(stat(filename, &fileStat) < 0, MOFS05_ERROR_FILE_NOT_EXIST)
	else ITR(S_ISDIR(fileStat.st_mode), MOFS05_ERROR_FILE_IS_DIR);
	
	ITR(file == NULL, MOFS05_ERROR_FILE_NULL);
	
	fread(
		magic,
		sizeof(char),
		MOFS05_LENGTH_MAGIC,
		file
	);
	
	if (strcmp(magic, MOFS05_MAGIC) != 0) {
		return MOFS05_ERROR_INCORRECT_FORMAT;
	}
	
	fread(
		&mofs05->count,
		sizeof(int),
		1,
		file
	);
	ITR(!mofs05->count, MOFS05_ERROR_FILE_SMALL);
	MULTISTRUCT_INIT(mofs05File_t, (*mofs05));
	
	for (i = 0; i < mofs05->count; i++) {
		fread(
			mofs05->i[i].name,
			sizeof(char),
			MOFS05_LENGTH_NAME,
			file
		);
		fread(
			&mofs05->i[i].size,
			sizeof(int),
			1,
			file
		);
		
		mofs05->i[i].data = malloc(
			mofs05->i[i].size
		);
		
		fread(
			mofs05->i[i].data,
			sizeof(char),
			mofs05->i[i].size,
			file
		);
		
		for (j = 0; j < mofs05->i[i].size; j++) {
			((char *)mofs05->i[i].data)[j] -= j;
		}
	}
	fclose(file);
	return MOFS05_ERROR_NONE;
}

mofs05File_t *mofs05_getFile(
	const mofs05_t *mofs05,
	const char *filename
) {
	unsigned int i;
	
	for (i = 0; i < mofs05->count; i++) {
		if (strcmp(mofs05->i[i].name, filename) == 0) {
			return &mofs05->i[i];
		}
	}
	return NULL;
}

enum mofs05_errors mofs05_extractFile(
	const mofs05File_t *mofs05File
) {
	char buffer[MOFS05_LENGTH_NAME + 1] = { 0 };
	FILE *file;
	
	strncpy(
		buffer,
		mofs05File->name,
		MOFS05_LENGTH_NAME
	);
	file = fopen(buffer, "wb");
	ITR(file == NULL, MOFS05_ERROR_FILE_NULL);
	
	fwrite(
		mofs05File->data,
		sizeof(char),
		mofs05File->size,
		file
	);
	
	fclose(file);
	return MOFS05_ERROR_NONE;
}

enum mofs05_errors mofs05_extract(
	const mofs05_t *mofs05
) {
	unsigned int i;
	
	for (i = 0; i < mofs05->count; i++) {
		mofs05_extractFile(&mofs05->i[i]);
	}
	return MOFS05_ERROR_NONE;
}