
// Maximum value that can be stored in unsigned: (2^32) - 1
static const unsigned MAX = 4294967295;

// Declarations
typedef struct Node Node;
Node* create_node(unsigned val);
Node* create_nsize_list(unsigned n, Node** tail);
void attach(Node* iter, Node* new_node);
Node* insert(Node* iter, Node* tail, Node* new_node, unsigned pos);
Node* append(Node* tail, Node* new_node);
void destroy(Node* iter);
void print_list(Node* iter);

// Definitions
typedef struct Node {
	int val;
	struct Node* next;
	struct Node* prev;
} Node;

Node* create_node(unsigned val) {
	Node* new_node = (Node*) malloc(sizeof(Node));
	new_node->val = val;
	new_node->prev = NULL;
	new_node->next = NULL;

	return new_node;	
}

Node* create_nsize_list(unsigned n, Node** tail) {
	assert (n < MAX);
	Node* head = create_node(0);
	*tail = head;
	for (int i = 1; i < n; i++) {
		Node* new_node = create_node(i);
		*tail = append(*tail, new_node);
	}

	return head;
}

void attach(Node* iter, Node* new_node) {
	new_node->next = iter;
	new_node->prev = iter->prev;
	iter->prev->next = new_node;
	iter->prev = new_node;
}

Node* insert(Node* iter, Node* tail, Node* new_node, unsigned pos) {
	while (1) {
		if (pos == 0) {
			attach(iter, new_node);
			return tail;
		}

		if (iter->next == NULL) break;
		pos--;
		iter = iter->next;	
	}
	new_node->prev = iter;
	iter->next = new_node;

	if (pos == 1) return new_node;

	return tail;
}

Node* append(Node* tail, Node* new_node) {
	tail->next = new_node;
	new_node->prev = tail;
	return new_node;
}

void destroy(Node* iter) {
	while (iter->next != NULL) {
		iter = iter->next;
		free(iter->prev);
	}
	free(iter);
}

void print_list(Node* iter) {
	while (iter) {
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");
}
