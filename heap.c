#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapify(int array[], int n, int i){
    int root = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < n && array[left] > array[root]) root = left;

    if(right < n && array[right] > array[root]) root = right;

    if(root != i){
        swap(&array[i], &array[root]);

        heapify(array, n, root);
    }

}

void buildHeap(int array[], int n){
    int start = (n/2)-1;

    for(int i=start;i>=0;i--){
        heapify(array,n,i);
    }
}

void printHeap(int array[], int n){
    puts("Here's the heap:");
    printf("|");
    for(int i=0; i<n; i++){
        printf(" %d |", array[i]);
    }
    printf("\n\n");
}

void insertHeap(int **array, int number, int n){
    *array = (int*) realloc(*array, n*sizeof(int));
    if (*array == NULL){
        puts("Failed.");
        return;
    }

    (*array)[n-1] = number;
    int start = (n/2)-1;
    for(int j=start;j>=0;j--){
        heapify(*array,n,j);
    }
}

int findPosition(int *array, int n, int element){
    int pos, i;
    for(i=0;i<=n;i++){
        if(array[i] == element){
            pos = i;
            return pos;
        }
    }
    return -1;
}

void deleteHeap(int **array, int *n, int element) {
    int pos;
    pos = findPosition(*array, (*n), element);

    if (pos == -1) {
        puts("Element not found.");
        return;
    }

    (*array)[pos] = (*array)[(*n) - 1];

    (*n)--; // Decrement the heap size
    *array = (int*)realloc(*array, (*n) * sizeof(int));
    if (*array == NULL) {
        puts("Memory reallocation failed.");
        return;
    }

    for (int i = pos; i < (*n) / 2; i++) { // Corrected the loop range
        heapify(*array, *n, i);
    }

    printHeap(*array, *n);
}


int main() {

    int n;
    int number;
    int option = -1;

    puts("Let's build your heap.");
    puts("With how many elements would you like to initialize the heap?");
    scanf("%d", &n);

    int *array = malloc(n * sizeof(int));

    for(int i=0;i<n;i++){
        puts("Enter an integer:");
        scanf("%d", &array[i]);
    }

    buildHeap(array, n);
    printHeap(array,n);

    puts("What do you want to do?\nEnter:\n1)Insert a number\n2)Delete a number\n\n>>Press 0 to exit.");
    scanf("%d", &option);

    while (option!=0){
        switch(option) {
            case 1:
                puts("Enter an integer:");
                scanf("%d", &number);
                puts("Inserting...");
                n = n+1;
                insertHeap(&array, number, n);
                printHeap(array, n);
                break;
            case 2:
                puts("Enter the number you want to delete:");
                scanf("%d", &number);
                puts("Deleting...");
                deleteHeap(&array, &n, number);
                break;
            default:
                puts("Invalid option. Try again.");
                break;
        }
        puts("What do you want to do?\nEnter:\n1)Insert a number\n2)Delete a number\n\n>>Press 0 to exit.");
        scanf("%d", &option);
    }
    puts("Shutting down...bye,bye!");
    return 0;
}
