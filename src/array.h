# ifndef ARRAY_H
# define ARRAY_H

typedef struct Array {
    unsigned* data;
    unsigned index;
    unsigned capacity;
} Array;

Array* instantiate_array() {
    Array* array = (Array*) malloc(sizeof(Array));
    array->data = (unsigned*) malloc(sizeof(unsigned) * 4);
    array->index = 0;
    array->capacity = 4;
    
    return array;
}

void append_a(Array* arr, unsigned element) {
    if (arr->index > arr->capacity) {
        arr->capacity *= 2;
        unsigned* ptr = (unsigned*)realloc(arr->data, sizeof(unsigned) * arr->capacity);
        arr->data = ptr;
    }
    arr->data[arr->index] = element;
    arr->index++;
}

int insert_a(Array* arr, unsigned element, unsigned index) {
    if (index > arr->capacity - 1) {
        return -1;
    }

    if (arr->index > arr->capacity) {
        arr->capacity *= 2;
        unsigned* ptr = (unsigned*)realloc(arr->data, sizeof(unsigned) * arr->capacity);
        arr->data = ptr;
    }

    unsigned i = arr->index;
    for (; i > index; i--) {
        arr->data[i] = arr->data[i - 1];
    }

    arr->data[i] = element;

    return 0;
}

int insert_bs(Array* arr, unsigned element) {
    if (arr->index == 0) {
        return -1;
    }

    unsigned left = 0;
    unsigned right = arr->index;
    unsigned middle;

    while (left < right) {
        middle = (unsigned) ((right - left) / 2) + left;
        if (element < arr->data[middle]) {
            right = middle - 1;
        }
        else if (element > arr->data[middle]) {
            left = middle + 1;
        }
        else break;
    }
    insert_a(arr, element, middle);
    return 0;
}

void print_array(Array* arr) {
    for (unsigned i = 0; i < arr->index; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}



# endif