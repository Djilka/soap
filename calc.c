#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define D_USER 0

// #include "optim.h"

#include "auto.h"
#if D_USER
#include "user.h"
#endif

void help()
{
	print_iol();
}

int main(int argc, char *argv[])
{
	oil_auto_init();
	if (argc == 1) {
		#if D_USER
		user();
		#endif
	} else {
		if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h"))
			help();
		else
			auto_range(argc - 1, &argv[1]);
	}

	oil_clear();
	return 0;
}