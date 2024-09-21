#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "list.h"
#include "array.h"

/* FUNCTION PROTOTYPES */

double test_list(unsigned n, unsigned insert_idx);
double test_array(unsigned n, unsigned insert_idx);
void test_changing_n(int cycles, unsigned batches_n[], double list_runtimes[], double array_runtimes[]);
void test_changing_insert(double list_runtimes[], double array_runtimes[]);
void save_changing_n_results(int cycles, unsigned batches_n[], double list_runtimes[], double array_runtimes[]);
void save_changing_insert_results(double list_runtimes[], double array_runtimes[]);

int main(int argc, char* argv[]) {
	if (!strcmp(argv[1], "0")) {
		int cycles = 100;
		double array_runtimes[cycles];
		double list_runtimes[cycles];
		unsigned batches_n[cycles];
		// Initialize batches
		batches_n[0] = 1000000;
		for (int i = 1; i < cycles; i++) {
			batches_n[i] = batches_n[i - 1] + 100000;
		}
		test_changing_n(cycles, batches_n, list_runtimes, array_runtimes);
		save_changing_n_results(cycles, batches_n, list_runtimes, array_runtimes);
	}
	else {
		double list_runtimes[1000];
		double array_runtimes[1000];
		test_changing_insert(list_runtimes, array_runtimes);
		save_changing_insert_results(list_runtimes, array_runtimes);
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

void test_changing_n(int cycles, unsigned batches_n[], double list_runtimes[], double array_runtimes[]) {
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
}

void test_changing_insert(double list_runtimes2[], double array_runtimes2[]) {
	double runtime = 0.0;
	
	for (unsigned i = 1; i < 1000; i++) {
		runtime = test_list(100000, i*100 - 1);
		printf("Cycle: %u --- Insertion Index: %u --- Runtimes: %f --- ", i, i*100 - 1, runtime);
		list_runtimes2[i] = runtime;
		
		runtime = test_array(100000, i* 100 - 1);
		printf("%f\n", runtime);
		array_runtimes2[i] = runtime;
	}
}

void save_changing_n_results(int cycles, unsigned batches_n[], double list_runtimes[], double array_runtimes[]) {
	FILE* fp = fopen("data/test1_results.csv", "w");
	char result[20000] = {};

	strcat(result, "Elements,List,Array\n");
	for (int i = 0; i < cycles; i++) {
		char buffer[100] = {};
		sprintf(buffer, "%u,%f,%f\n", batches_n[i], list_runtimes[i], array_runtimes[i]);
		strcat(result, buffer);
	}

	fwrite(result, strlen(result), 1, fp);
	fclose(fp);
}

void save_changing_insert_results(double list_runtimes[], double array_runtimes[]) {
	FILE* fp = fopen("data/test2_results.csv", "w");
	char result[100000] = {};

	strcat(result, "Insertion Index,List,Array\n");
	for (unsigned i = 0; i < 1000; i++) {
		char buffer[100] = {};
		sprintf(buffer, "%u,%f,%f\n", i, list_runtimes[i], array_runtimes[i]);
		strcat(result, buffer);
	}

	fwrite(result, strlen(result), 1, fp);
	fclose(fp);
}