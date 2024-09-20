#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

double test_list() {
	Node* tail;
	Node* head = create_nsize_list(400000000, &tail);
	
	//print_list(head);

	Node* n_node = create_node(0);

	clock_t time_elapsed = clock();
	tail = insert(head, tail, n_node, 200000000);
	time_elapsed = clock() - time_elapsed;

	//print_list(head);

	destroy(head);

	return (double) time_elapsed / CLOCKS_PER_SEC;
}

double test_array() {}

int main() {
	double runtime = test_list();
	printf("Runtime: %f\n", runtime);

	// runtime = test_array();
	// printf("Runtime: %f\n", runtime);

	return 0;
}
