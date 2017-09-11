#include "libstring.h"


String get_string(char *str) {
	char *tmp;
	tmp = (char *)malloc(strlen(str) * sizeof(char));
	memcpy((void *)tmp, (void *)str, strlen(str));
	String result;
	result.p = tmp;
	result.size = strlen(str);
	return result;
}

void free_string(String str) {
	free(str.p);
}

uint32_t str_len(String str) {
	return str.size;
}

int32_t str_cmd(String str1, String str2) {
	return strcmp(str1.p, str2.p);
}

