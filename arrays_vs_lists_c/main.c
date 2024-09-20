#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "array.h"

double test_list() {
	Node* tail;
	Node* head = create_nsize_list(400000000, &tail);
	
	//print_list(head);

	Node* n_node = create_node(0);

	clock_t cycles = clock();
	tail = insert(head, tail, n_node, 200000000);
	cycles = clock() - cycles;

	//print_list(head);

	destroy(head);

	return (double) cycles / CLOCKS_PER_SEC;
}

double test_array() {
	Array* array = instantiate_array();

    for (int i = 0; i < 400000000; i++) {
        append_a(array, i);
    }

    //print_array(array);

	clock_t cycles = clock();
    insert_a(array, -1, 200000000);
	cycles = clock() - cycles;

    //print_array(array);

    free(array->data);
    free(array);

	return (double) cycles / CLOCKS_PER_SEC;
}

int main() {
	double runtime = 0.0;
	
	runtime = test_list();
	printf("Runtime: %f\n", runtime);

	runtime = test_array();
	printf("Runtime: %f\n", runtime);

	return 0;
}
