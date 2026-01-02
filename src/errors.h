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