#ifndef H_LIBSTRING
#define H_LIBSTRING

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "memory.h"
#include "string.h"


struct String {
	uint32_t size;
	char *p;
};

typedef struct String String;


String get_string(char *str);
uint32_t str_len(String str);
int32_t str_cmp(String str1, String str2);


#endif