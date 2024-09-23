# ifndef LIST_H
# define LIST_H

// Maximum value that can be stored in unsigned: (2^32) - 1
static const unsigned MAX = 4294967295;

/* FUNCTION PROTOTYPES */
typedef struct Node Node;
Node* create_node(unsigned val);
Node* create_nsize_list(unsigned n, Node** tail);
void attach(Node** head, Node** tail, Node* iter, Node* new_node);
void insert(Node** head, Node** tail, Node* new_node, unsigned pos);
void insert_ls(Node** head, Node** tail, Node* new_node, unsigned element);
Node* insert_optimized(Node** head, Node** tail, Node* new_node, unsigned pos, unsigned n);
Node* append(Node* tail, Node* new_node);
void destroy(Node* iter);
void print_list(Node* iter);

/* FUNCTION DEFINITIONS */
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

void attach(Node** head, Node** tail, Node* iter, Node* new_node) {
	if (iter == *tail) {
		iter->next = new_node;
		new_node->prev = iter;
		*tail = new_node;
		return;
	}
	else if (iter == *head) {
		*head = new_node;
		iter->prev = new_node;
		new_node->next = iter;
		return;
	}
	else {
		new_node->next = iter;
		new_node->prev = iter->prev;
		iter->prev->next = new_node;
		iter->prev = new_node;
	}
	
}

void insert(Node** head, Node** tail, Node* new_node, unsigned pos) {
	Node* iter = *head;
	unsigned i = 0;
	for (; i < pos; i++) {
		if (iter->next == NULL) break;
		iter = iter->next;
	}
	attach(head, tail, iter, new_node);
}

void insert_ls(Node** head, Node** tail, Node* new_node, unsigned element) {
	Node* iter = *head;
	while (iter) {
		if (element <= iter->val) break;
		iter = iter->next;
	}
	attach(head, tail, iter, new_node);
}

Node* insert_optimized(Node** head, Node** tail, Node* new_node, unsigned pos, unsigned n) {
	if (pos < (int) n / 2) {
		insert(head, tail, new_node, pos);
	}
	else {
		Node* iter = *tail;
		unsigned i = n - 1;
		for (; i > pos; i--) {
			if (iter->prev == NULL) break;
			iter = iter->prev;
		}
		attach(head, tail, iter, new_node);
	}
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

# endif
