#include "errors.h"

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