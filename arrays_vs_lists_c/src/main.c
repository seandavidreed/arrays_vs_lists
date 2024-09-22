#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "list.h"
#include "array.h"

/* FUNCTION PROTOTYPES */

double test_list(unsigned n, unsigned insert_idx);
double test_opt_list(unsigned n, unsigned insert_idx);
double test_array(unsigned n, unsigned insert_idx);
void test_changing_n(int cycles);
void test_changing_insert(bool with_optimization);

int main(int argc, char* argv[]) {

	if (!strcmp(argv[1], "1")) {
		test_changing_n(100);
	}
	else if (!strcmp(argv[1], "2")) {
		test_changing_insert(false);
	}
	else if (!strcmp(argv[1], "3")) {
		test_changing_insert(true);
	}

	return 0;
}

/* FUNCTION DEFINITIONS */

double test_list(unsigned n, unsigned insert_idx) {
	Node* tail;
	Node* head = create_nsize_list(n, &tail);
	
	Node* n_node = create_node(0);

	clock_t cycles = clock();
	tail = insert(head, tail, n_node, insert_idx);
	cycles = clock() - cycles;

	destroy(head);

	return (double) cycles / CLOCKS_PER_SEC;
}

double test_opt_list(unsigned n, unsigned insert_idx) {
	Node* tail;
	Node* head = create_nsize_list(n, &tail);
	
	Node* n_node = create_node(0);

	clock_t cycles = clock();
	tail = insert_optimized(head, tail, n_node, insert_idx, n);
	cycles = clock() - cycles;

	destroy(head);

	return (double) cycles / CLOCKS_PER_SEC;
}

double test_array(unsigned n, unsigned insert_idx) {
	Array* array = instantiate_array();

    for (int i = 0; i < n; i++) {
        append_a(array, i);
    }

	clock_t cycles = clock();
    insert_a(array, -1, insert_idx);
	cycles = clock() - cycles;

    free(array->data);
    free(array);

	return (double) cycles / CLOCKS_PER_SEC;
}

void test_changing_n(int cycles) {

	// Declare variables
	double array_runtimes[cycles];
	double list_runtimes[cycles];
	unsigned batches_n[cycles];

	// Initialize batches
	batches_n[0] = 1000000;
	for (int i = 1; i < cycles; i++) {
		batches_n[i] = batches_n[i - 1] + 100000;
	}

	// Run cycles and collect runtimes
	double runtime = 0.0;
	for (int i = 0; i < cycles; i++) {
		unsigned insert_idx = (unsigned) batches_n[i] / 2;		/* Change me */
		runtime = test_list(batches_n[i], insert_idx);
		printf("Cycle: %d --- Elements: %d --- Runtimes: %f --- ", i, batches_n[i], runtime);
		list_runtimes[i] = runtime;

		runtime = test_array(batches_n[i], insert_idx);
		printf("%f\n", runtime);
		array_runtimes[i] = runtime;
	}

	// Format results into one string
	char result[4000] = {"Elements,List,Array\n"};
	for (int i = 0; i < cycles; i++) {
		char buffer[40] = {};
		sprintf(buffer, "%u,%f,%f\n", batches_n[i], list_runtimes[i], array_runtimes[i]);
		strncat(result, buffer, 27);
	}

	// Save to file
	FILE* fp = fopen("data/test1_results.csv", "w");
	if (fp == NULL) {
		printf("Failed to open file.\n%s.\nExiting...\n", strerror(errno));
		exit(1);
	}
	fwrite(result, strlen(result), 1, fp);
	fclose(fp);
}

void test_changing_insert(bool with_optimization) {

	// Declare variables
	int samples = 1000;
	double runtime = 0.0;
	double list_runtimes[samples];
	double array_runtimes[samples];
	char output_file[23];
	
	// Run cycles and collect runtimes
	if (!with_optimization) {
		// No list insert optimization
		strcpy(output_file, "data/test2_results.csv");
		for (unsigned i = 1; i < samples; i++) {
			runtime = test_list(100000, i*100 - 1);
			printf("Cycle: %u --- Insertion Index: %u --- Runtimes: %f --- ", i, i*100 - 1, runtime);
			list_runtimes[i] = runtime;
			
			runtime = test_array(100000, i* 100 - 1);
			printf("%f\n", runtime);
			array_runtimes[i] = runtime;
		}
	}
	else {
		// With list insert optimization
		strcpy(output_file, "data/test3_results.csv");
		for (unsigned i = 1; i < samples; i++) {
			runtime = test_opt_list(100000, i*100 - 1);
			printf("Cycle: %u --- Insertion Index: %u --- Runtimes: %f --- ", i, i*100 - 1, runtime);
			list_runtimes[i] = runtime;
			
			runtime = test_array(100000, i* 100 - 1);
			printf("%f\n", runtime);
			array_runtimes[i] = runtime;
		}	
	}

	// Format results into one string
	char result[30000] = {"Insertion Index,List,Array\n"};
	for (unsigned i = 0; i < samples; i++) {
		char buffer[40] = {};
		sprintf(buffer, "%u,%f,%f\n", i*100, list_runtimes[i], array_runtimes[i]);
		strncat(result, buffer, 30);
	}

	// Save to file
	FILE* fp = fopen(output_file, "w");
	if (fp == NULL) {
		printf("Failed to open file: %s\n%s.\nExiting...\n", output_file, strerror(errno));
		exit(1);
	}
	fwrite(result, strlen(result), 1, fp);
	fclose(fp);
}