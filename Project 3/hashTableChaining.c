#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Linked List node
struct node {
    int key;
    int value;
    struct node* next;
};

// like constructor
void setNode(struct node* node, int key, int value){
    node->key = key;
    node->value = value;
    node->next = NULL;
    puts("Node setted!");
};

struct hashMap {
    int numOfElements, capacity;
    struct node** arr;
};

// like constructor
void initializeHashMap(struct hashMap* mp){
    mp->capacity = 100;
    mp->numOfElements = 0;

    // array of size = 1
    mp->arr = (struct node**)malloc(sizeof(struct node*)
                                    * mp->capacity);
    puts("HashMap initialized!");
}

int hashFunction(struct hashMap* mp, int key){
    int function_result;
    function_result = round(key % mp->capacity);
    if(function_result != 0) return function_result-1;
    return function_result;
}

void insert(struct hashMap* mp, int key, int value){
    int bucketIndex = hashFunction(mp, key);
    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    puts("Starting insertion...");

    setNode(newNode, key, value);

    // Bucket index is empty....no collision
    if (mp->arr[bucketIndex] == NULL) {
        mp->arr[bucketIndex] = newNode;
        puts("Insertion finished!");
    }

    // Collision
    else {
        newNode->next = mp->arr[bucketIndex];
        mp->arr[bucketIndex] = newNode;
        puts("Insertion finished!");
    }

}

void delete (struct hashMap* mp, int key){
    int bucketIndex = hashFunction(mp, key);

    struct node* prevNode = NULL;

    struct node* currNode = mp->arr[bucketIndex];

    while (currNode != NULL) {
        if (key == currNode->key) {

            if (currNode == mp->arr[bucketIndex]) {
                mp->arr[bucketIndex] = currNode->next;
            }

            else {
                prevNode->next = currNode->next;
            }
            free(currNode);
            break;
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
}

int search(struct hashMap* mp, int key){
    int bucketIndex = hashFunction(mp, key);

    // Head of the linked list
    // present at bucket index
    struct node* bucketHead = mp->arr[bucketIndex];
    while (bucketHead != NULL) {

        // Key is found in the hashMap
        printf("BucketHead: %d\nKey: %d", bucketHead->key, key);
        if (bucketHead->key == key) {
            return bucketHead->value;
        }
        bucketHead = bucketHead->next;
    }

    puts("Oops! No data found.\n");
    return -1;
}

// Drivers code
int main(){

    // Initialize the value of mp
    struct hashMap* mp = (struct hashMap*)malloc(sizeof(struct hashMap));
    initializeHashMap(mp);
    insert(mp, 123, 456);
    insert(mp, 789, 101112);
    insert(mp, 131415, 161718);
    insert(mp, 192021, 222324);

    printf("%d\n", search(mp, 123));
    printf("%d\n", search(mp, 789));
    printf("%d\n", search(mp, 131415));
    printf("%d\n", search(mp, 192021));


    puts("Searching...\n");
    printf("%d\n", search(mp, 456));

    printf("\nAfter deletion : \n");

    // Deletion of key
    delete (mp, 161718);
    printf("%d\n", search(mp, 161718));
    free(mp);
    return 0;
}

