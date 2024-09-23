#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "list.h"
#include "array.h"
#include "tests.h"

int main(int argc, char* argv[]) {

	if (!strcmp(argv[1], "1")) {
		test_changing_n(100);
	}
	else if (!strcmp(argv[1], "2")) {
		test_changing_insert("data/test2_results.csv", &test_list);
	}
	else if (!strcmp(argv[1], "3")) {
		test_changing_insert("data/test3_results.csv", &test_opt_list);
	}
	else if (!strcmp(argv[1], "4")) {
		test_random_insert("data/test4_results.csv", &test_list);
	}
	else if (!strcmp(argv[1], "5")) {
		test_random_insert("data/test5_results.csv", &test_opt_list);
	}
	else {
		test_random_element();
	}

	return 0;
}