#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "list.h"
#include "array.h"

double test_list(unsigned n) {
	Node* tail;
	Node* head = create_nsize_list(n, &tail);
	
	//print_list(head);

	Node* n_node = create_node(0);

	clock_t cycles = clock();
	tail = insert(head, tail, n_node, (unsigned) n / 2);
	cycles = clock() - cycles;

	//print_list(head);

	destroy(head);

	return (double) cycles / CLOCKS_PER_SEC;
}

double test_array(unsigned n) {
	Array* array = instantiate_array();

    for (int i = 0; i < n; i++) {
        append_a(array, i);
    }

    //print_array(array);

	clock_t cycles = clock();
    insert_a(array, -1, (unsigned) n / 2);
	cycles = clock() - cycles;

    //print_array(array);

    free(array->data);
    free(array);

	return (double) cycles / CLOCKS_PER_SEC;
}

int main() {
	double file_buffer[20];
	double runtime = 0.0;
	unsigned start = 4000000;
	unsigned n = start;
	
	for (int i = 0; i < 10; i++) {
		runtime = test_list(n);
		printf("Runtime: %f\n", runtime);
		file_buffer[i] = runtime;

		runtime = test_array(n);
		printf("Runtime: %f\n", runtime);
		file_buffer[i+10] = runtime;

		n += start;
	}

	FILE* fp = fopen("results.txt", "w");
	char result[202] = {};

	strcat(result, "List, Array\n");
	for (int i = 0; i < 10; i++) {
		char buffer[20] = {};
		sprintf(buffer, "%f, %f\n", file_buffer[i], file_buffer[i + 10]);
		strcat(result, buffer);
	}

	fwrite(result, 202, 1, fp);
	fclose(fp);

	return 0;
}
