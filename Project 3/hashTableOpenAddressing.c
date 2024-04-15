#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <math.h>

int hashFunction(int num, int table_size){
    int function_result;
    function_result = round(num % table_size);
    if(function_result != 0) return function_result-1;
    return function_result;
}

void insertFunction(int hashtable[], int num, int table_size){
    int position = hashFunction(num, table_size);
    int i=0;

    while(i<table_size){
        if(i==position){
            if(hashtable[i]==0){
                hashtable[i] = num;
            }
            else{
                position = hashFunction(num+1, table_size);
            }
        }
        i++;
    }
}

void deleteFunction(int hashtable[], int size, int index){
    if(size == 0 || index < 0 || index >= size) {
        printf("Invalid index.\n");
        return;
    }
    else{
            for (int i = index; i < size - 1; i++) {
                hashtable[i] = hashtable[i + 1];
            }
    }

}

void searchFunction(int hashtable[], int size, int num){
    //int position = hashFunction(num, size);
    int i = 0;
    //printf("position: %d\n", position);
    puts("Searching....\n");
    while(i<size){
        if(hashtable[i] == num){
            printf("The number %d is on the Hash Table, its index is %d", num, i);
            return;
        }
        i++;
    }
    puts("---");
    printf("\n%d", i);
    printf("\nElement not found");
}


int main() {
    setlocale(LC_ALL, "Portuguese");
    int i=0, j=0, n;

    srand(time(NULL));

    //n = rand() % 51;
    n=10;

    int hashtable[n];
    int random_numbers[n];


    for(i=0; i < n; i++) {
        random_numbers[i] = rand() % (n - 1);
    }

    for (i = 0; i < n; i++) {
            hashtable[i] = 0;
    };

    for (i = 0; i < n; i++) {
        insertFunction(hashtable, random_numbers[i], n);
    };

    printf("\nOriginal HashTable\n--------------------------------------------------------------\n");
    while (j < n) {
        printf("%d\n", hashtable[j]);
        j++;
    }

    deleteFunction(hashtable, n, 3);

    printf("\nModified HashTable\n--------------------------------------------------------------\n");

    j = 0;
    while (j < n) {
        printf("%d\n", hashtable[j]);
        j++;
    }

    searchFunction(hashtable, n, 5);

    return 0;



}


