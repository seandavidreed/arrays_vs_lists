# ifndef TESTS_H
# define TESTS_H

/* FUNCTION PROTOTYPES */
double test_list(unsigned n, unsigned insert_idx);
double test_list_ls(unsigned n, unsigned element);
double test_opt_list(unsigned n, unsigned insert_idx);
double test_array(unsigned n, unsigned insert_idx);
double test_array_bs(unsigned n, unsigned element);
void test_changing_n();
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
void test_changing_n() {
	// Declare variables
    const unsigned CYCLES = 100;
    char result[4000] = {"Elements,List,Array\n"};

	// Run cycles and collect runtimes
	for (int i = 0; i < CYCLES; i++) {
        unsigned batch_size = 1000000 + (100000 * i);
		unsigned insert_idx = batch_size / 2;

		double list_runtime = test_list(batch_size, insert_idx);
		printf("Cycle: %d --- Elements: %d --- List RT: %f --- ", i, batch_size, list_runtime);

		double array_runtime = test_array(batch_size, insert_idx);
		printf("Array RT: %f\n", array_runtime);

        char buffer[40] = {};
		sprintf(buffer, "%u,%f,%f\n", batch_size, list_runtime, array_runtime);
		strncat(result, buffer, 27);
	}

	// Save to file
	save_to_file(result, "data/test1_results.csv");
}

/* TESTS 2 and 3 */
void test_changing_insert(char output_file[], double (*func)(unsigned, unsigned)) {
	// Declare variables
    const unsigned N = 100000;
	unsigned samples = N / 100;
    char result[30000] = {"Insertion Index,List,Array\n"};
	
	// Run cycles; collect and format runtimes
	for (unsigned i = 0; i < samples; i++) {
        unsigned idx = i * (N / samples);

		double list_runtime = func(N, idx);
		printf("Cycle: %u --- Insert Idx: %u --- List RT: %f --- ", i, idx, list_runtime);
		
		double array_runtime = test_array(N, idx);
		printf("Array RT: %f\n", array_runtime);

        char buffer[40] = {};
		sprintf(buffer, "%u,%f,%f\n", idx, list_runtime, array_runtime);
		strncat(result, buffer, 30);
	}

	// Save to file
	save_to_file(result, output_file);
}

/* TESTS 4 and 5 */
void test_random_insert(char output_file[], double (*func)(unsigned, unsigned)) {
	// Declare variables
    const unsigned N = 100000;
	unsigned samples = N / 1000;
    char result[30000] = {"Sample,List,Array\n"};

	// Initialize random number generator
	srand(time(0));
	
	// Run cycles and collect runtimes
	for (unsigned i = 0; i < samples; i++) {
		unsigned insert_idx = rand() % N;
		double list_runtime = func(N, insert_idx);
		printf("Cycle: %u --- Insertion Index: %u --- List RT: %f --- ", i, insert_idx, list_runtime);
		
		double array_runtime = test_array(N, insert_idx);
		printf("Array RT: %f\n", array_runtime);

		char buffer[40] = {};
		sprintf(buffer, "%u,%f,%f\n", i, list_runtime, array_runtime);
		strncat(result, buffer, 30);
	}

	// Save to file
	save_to_file(result, output_file);
}

/* TEST 6 */
void test_random_element() {
	
	// Declare variables
    const unsigned N = 100000;
	unsigned samples = N / 1000;
    char result[30000] = {"Sample,List,Array\n"};

	// Initialize random number generator
	srand(time(0));
	
	// Run cycles and collect runtimes
	for (unsigned i = 0; i < samples; i++) {
		unsigned element = rand() % N;
		double list_runtime = test_list_ls(N, element);
		printf("Cycle: %u --- Element: %u --- List RT: %f --- ", i, element, list_runtime);

		double array_runtime = test_array_bs(N, element);
		printf("Array RT: %f\n", array_runtime);

		char buffer[40] = {};
		sprintf(buffer, "%u,%f,%f\n", i, list_runtime, array_runtime);
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