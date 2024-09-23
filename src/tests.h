# ifndef TESTS_H
# define TESTS_H

/* FUNCTION PROTOTYPES */
double test_list(unsigned n, unsigned insert_idx);
double test_list_ls(unsigned n, unsigned element);
double test_opt_list(unsigned n, unsigned insert_idx);
double test_array(unsigned n, unsigned insert_idx);
double test_array_bs(unsigned n, unsigned element);
void test_changing_n(int cycles);
void test_changing_insert(char output_file[], double (*func)(unsigned, unsigned));
void test_random_insert(char output_file[], double (*func)(unsigned, unsigned));
void test_random_element();
void save_to_file(char result[], char output_file[]);

/* FUNCTION DEFINITIONS */
double test_list(unsigned n, unsigned insert_idx) {
	Node* tail;
	Node* head = create_nsize_list(n, &tail);
	
	Node* n_node = create_node(0);

	clock_t cycles = clock();
	insert(&head, &tail, n_node, insert_idx);
	cycles = clock() - cycles;

	destroy(head);

	return (double) cycles / CLOCKS_PER_SEC;
}

double test_list_ls(unsigned n, unsigned element) {
	Node* tail;
	Node* head = create_nsize_list(n, &tail);
	
	Node* n_node = create_node(0);

	clock_t cycles = clock();
	insert_ls(&head, &tail, n_node, element);
	cycles = clock() - cycles;

	destroy(head);

	return (double) cycles / CLOCKS_PER_SEC;
}

double test_opt_list(unsigned n, unsigned insert_idx) {
	Node* tail;
	Node* head = create_nsize_list(n, &tail);
	
	Node* n_node = create_node(0);

	clock_t cycles = clock();
	tail = insert_optimized(&head, &tail, n_node, insert_idx, n);
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

double test_array_bs(unsigned n, unsigned element) {
	Array* array = instantiate_array();

    for (int i = 0; i < n; i++) {
        append_a(array, i);
    }

	clock_t cycles = clock();
    insert_bs(array, element);
	cycles = clock() - cycles;

    free(array->data);
    free(array);

	return (double) cycles / CLOCKS_PER_SEC;
}

/* TEST 1 */
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
	save_to_file(result, "data/test1_results.csv");
}

/* TESTS 2 and 3 */
void test_changing_insert(char output_file[], double (*func)(unsigned, unsigned)) {

	// Declare variables
	int samples = 1000;
	double runtime = 0.0;
	double list_runtimes[samples];
	double array_runtimes[samples];
	
	// Run cycles and collect runtimes
	for (unsigned i = 0; i < samples; i++) {
		runtime = func(100000, i*100);
		printf("Cycle: %u --- Insertion Index: %u --- Runtimes: %f --- ", i, i*100, runtime);
		list_runtimes[i] = runtime;
		
		runtime = test_array(100000, i* 100 - 1);
		printf("%f\n", runtime);
		array_runtimes[i] = runtime;
	}

	// Format results into one string
	char result[30000] = {"Insertion Index,List,Array\n"};
	for (unsigned i = 0; i < samples; i++) {
		char buffer[40] = {};
		sprintf(buffer, "%u,%f,%f\n", i*100, list_runtimes[i], array_runtimes[i]);
		strncat(result, buffer, 30);
	}

	// Save to file
	save_to_file(result, output_file);
}

/* TESTS 4 and 5 */
void test_random_insert(char output_file[], double (*func)(unsigned, unsigned)) {

	// Declare variables
	int samples = 100;
	double runtime = 0.0;
	double list_runtimes[samples];
	double array_runtimes[samples];

	// Initialize random number generator
	srand(time(0));
	
	// Run cycles and collect runtimes
	for (unsigned i = 0; i < samples; i++) {
		unsigned insert_idx = rand() % 100000;
		runtime = func(100000, insert_idx);
		printf("Cycle: %u --- Insertion Index: %u --- Runtimes: %f --- ", i, insert_idx, runtime);
		list_runtimes[i] = runtime;
		
		runtime = test_array(100000, insert_idx);
		printf("%f\n", runtime);
		array_runtimes[i] = runtime;
	}

	// Format results into one string
	char result[30000] = {"Sample,List,Array\n"};
	for (unsigned i = 0; i < samples; i++) {
		char buffer[40] = {};
		sprintf(buffer, "%u,%f,%f\n", i, list_runtimes[i], array_runtimes[i]);
		strncat(result, buffer, 30);
	}

	// Save to file
	save_to_file(result, output_file);
}

/* TEST 6 */
void test_random_element() {
	
	// Declare variables
	int samples = 100;
	double runtime = 0.0;
	double list_runtimes[samples];
	double array_runtimes[samples];

	// Initialize random number generator
	srand(time(0));
	
	// Run cycles and collect runtimes
	for (unsigned i = 0; i < samples; i++) {
		unsigned element = rand() % 100000;
		runtime = test_list_ls(100000, element);
		printf("Cycle: %u --- Element: %u --- Runtimes: %f --- ", i, element, runtime);
		list_runtimes[i] = runtime;

		runtime = test_array_bs(100000, element);
		printf("%f\n", runtime);
		array_runtimes[i] = runtime;
	}

	// Format results into one string
	char result[30000] = {"Sample,List,Array\n"};
	for (unsigned i = 0; i < samples; i++) {
		char buffer[40] = {};
		sprintf(buffer, "%u,%f,%f\n", i, list_runtimes[i], array_runtimes[i]);
		strncat(result, buffer, 30);
	}

	// Save to file
	save_to_file(result, "data/test6_results.csv");
}

void save_to_file(char result[], char output_file[]) {
	FILE* fp = fopen(output_file, "w");
	if (fp == NULL) {
		printf("Failed to open file: %s\n%s.\nExiting...\n", output_file, strerror(errno));
		exit(1);
	}
	fwrite(result, strlen(result), 1, fp);
	fclose(fp);
}

# endif