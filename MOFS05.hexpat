#pragma author StevenSYS
#pragma description MOFS05
#pragma magic [ 4D 4F 46 53 30 35 31 ] @ 0x00

#pragma endian little

/*
	I hate ImHex's pattern editor,
	I hate that you have to use "fn" to make functions,
	and I hate that you have to put a semicolon at the end of the bracket for a function
*/

import type.magic;
import type.size;

struct file_t {
	char name[100];
	type::Size<u32> size;
	u8 data[size];
};

struct mofs05_t {
	type::Magic<"MOFS05"> magic;
	u32 count;
	file_t file[count];
};

mofs05_t mofs05 @ 0x00;