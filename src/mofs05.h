#ifndef __MOFS05__
#define __MOFS05__

#include "errors.h"
#include "multistruct.h"

/* Macros */
#define MOFS05_NAME "MOFS05"
#define MOFS05_MAGIC MOFS05_NAME
#define MOFS05_PREFIX MOFS05_NAME

#define MOFS05_LENGTH_MAGIC 6
#define MOFS05_LENGTH_NAME 100

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