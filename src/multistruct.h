#ifndef __MULTISTRUCT__
#define __MULTISTRUCT__

#include "multistructConfig.h"

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