#include "libstring.h"
#include "stdio.h"
#include "stdint.h"



uint32_t main(void) {

	String tmp;
	tmp = get_string("kdjfksdjf");

	printf("%d\t%s\n", tmp.size, tmp.p);

	// if(tmp == NULL) {
	// 	printf("tmp is NULL\n");
	// }


	free_string(tmp);

	return 0;
}
