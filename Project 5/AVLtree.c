#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
//#include <string.h>

// Estrutura da árvore
typedef struct Tree{
    int nodeValue, rightNodeHeight, leftNodeHeight;
    struct Tree *rightNode, *leftNode;
}tree;

tree *leftRotation(tree *root){
    tree *rotatedNode, *rotatedNodeRightChild;
    rotatedNode = root->rightNode;
    rotatedNodeRightChild = rotatedNode->leftNode;
    root->rightNode = rotatedNodeRightChild;
    rotatedNode->leftNode = root;
    if(root->rightNode == NULL) root->rightNodeHeight = 0;
    else if((root->rightNode)->leftNodeHeight > (root->rightNode)->rightNodeHeight)
        root->rightNodeHeight = (root->rightNode)->leftNodeHeight+1;
    else root->rightNodeHeight = (root->rightNode)->rightNodeHeight +1;
    if((rotatedNode->leftNode)->leftNodeHeight > (rotatedNode->rightNode)->rightNodeHeight) rotatedNode->leftNodeHeight = (rotatedNode->leftNode)->leftNodeHeight+1;
    else rotatedNode->leftNodeHeight = (rotatedNode->leftNode)->rightNodeHeight + 1;
    return rotatedNode;
}

tree *rightRotation(tree *root){
    tree *rotatedNode, *rotatedNodeLeftChild;
    rotatedNode = root->leftNode;
    rotatedNodeLeftChild = rotatedNode->rightNode;
    root->leftNode = rotatedNodeLeftChild;
    rotatedNode->rightNode = root;

    if(root->leftNode == NULL) root->leftNodeHeight = 0;
    else if ((root->leftNode)->leftNodeHeight > (root->leftNode)->rightNodeHeight) root->leftNodeHeight = (root->leftNode)->leftNodeHeight + 1;
    else root->leftNodeHeight = (root->leftNode)->rightNodeHeight + 1;

    if((rotatedNode->rightNode)->leftNodeHeight > (rotatedNode->rightNode)->rightNodeHeight) rotatedNode->rightNodeHeight = (rotatedNode->rightNode)->leftNodeHeight + 1;
    else rotatedNode->rightNodeHeight = (rotatedNode->rightNode)->rightNodeHeight+1;

    return rotatedNode;
}

tree *balancingFunction(tree *root){
    int difference, differenceChild;

    difference = (root->rightNodeHeight) - (root->leftNodeHeight);

    if(difference == 2){
        differenceChild = (root->rightNode)->rightNodeHeight - (root->rightNode)->leftNodeHeight;
        if(differenceChild >= 0) root = leftRotation(root);
        else{
            root->rightNode = rightRotation(root->rightNode);
            root = leftRotation(root);
        }
    }
    else if(difference == -2){
        differenceChild = (root->leftNode)->rightNodeHeight - (root->leftNode)->leftNodeHeight;
        if(differenceChild <=0) rightRotation(root);
        else{
            root->leftNode = leftRotation(root->leftNode);
            root = rightRotation(root);
        }
    }

    return root;
}

tree *updateHeights(tree *root){
    if(root != NULL){
        root->leftNode = updateHeights(root->leftNode);
        if(root->leftNode == NULL) root->leftNodeHeight = 0;
        else if((root->leftNode)->leftNodeHeight > (root->leftNode)->rightNodeHeight) root->leftNodeHeight = (root->leftNode)->leftNodeHeight+1;
        else root->leftNodeHeight = (root->leftNode)->rightNodeHeight+1;

        root->rightNode = updateHeights(root->rightNode);
        if(root->rightNode == NULL) root->rightNodeHeight = 0;
        else if ((root->rightNode)->leftNodeHeight > (root->rightNode)->rightNodeHeight) root->rightNodeHeight = (root->rightNode)->leftNodeHeight+1;
        else root->rightNodeHeight = (root->rightNode)->rightNodeHeight + 1;

        root = balancingFunction(root);
    }

    return root;
}



tree *insertFunction(tree *root, int element){
    tree *new = malloc(sizeof(tree));
    if(root == NULL){
        new->nodeValue = element;
        new->rightNodeHeight = 0;
        new->leftNodeHeight = 0;
        new->leftNode = NULL;
        new->rightNode = NULL;
        root = new;
    }
    else if(element < root->nodeValue){
        root->leftNode = insertFunction(root->leftNode, element);
        if((root->leftNode)->rightNodeHeight > (root->leftNode)->leftNodeHeight) root->leftNodeHeight = (root->leftNode)->rightNodeHeight+1;
        else root->leftNodeHeight = (root->leftNode)->leftNodeHeight+1;
        root = balancingFunction(root);
    }
    else{
        root->rightNode = insertFunction(root->rightNode, element);
        if((root->rightNode)->rightNodeHeight > (root->rightNode)->leftNodeHeight) root->rightNodeHeight = (root->rightNode)->rightNodeHeight+1;
        else root->rightNodeHeight = (root->rightNode)->leftNodeHeight+1;
        root = balancingFunction(root);
    }
    return root;
}

int searchFunction(tree *root, int element, int found){
    if(root != NULL && found == 0){
        if(root->nodeValue == element)
            found = 1;
        else if(element < root->nodeValue)
            found = searchFunction(root->leftNode, element, found);
        else
            found = searchFunction(root->rightNode, element, found);
    }
    return found;
}

tree *removeFunction(tree *root, int element){
    tree *traversalNode, *temporaryNode;
    if(root == NULL) return root;
    if(root->nodeValue == element){
        if(root->rightNode == root->leftNode){
            free(root);
            return NULL;
        }
        else if (root->leftNode == NULL){
            traversalNode = root->rightNode;
            free(root);
            return traversalNode;
        }
        else if (root->rightNode == NULL){
            traversalNode = root->leftNode;
            free(root);
            return traversalNode;
        }
        else {
            temporaryNode = root->rightNode;
            traversalNode = root->rightNode;
            while(traversalNode->leftNode != NULL){
                traversalNode = traversalNode->leftNode;
            }
            traversalNode->leftNode = root->leftNode;
            free(root);
            return temporaryNode;
        }
    }
    else if(root->nodeValue < element){
        root->rightNode = removeFunction(root->rightNode, element);
    }
    else{
        root->leftNode = removeFunction(root->leftNode, element);
    }

    root = updateHeights(root);
    return root;
}

void showTreeFunction(tree *root){
    if(root != NULL){
        printf("%d ", root->nodeValue);
        showTreeFunction(root->leftNode);
        showTreeFunction(root->rightNode);
    }
}

tree *cleanTree(tree **root){
    if(*root != NULL) {
        if((*root)->leftNode != NULL) cleanTree(&((*root)->leftNode));
        if((*root)->rightNode != NULL) cleanTree(&((*root)->rightNode));

        free(*root);
        *root = NULL;
    }
}

// Function to clean the entire AVL tree
void clearAVLTree(tree **rootPtr) {
    if (*rootPtr != NULL) {
        // Clean the tree starting from the root
        if ((*rootPtr)->leftNode != NULL) {
            clearAVLTree(&((*rootPtr)->leftNode)); // Clean the left subtree
        }
        if ((*rootPtr)->rightNode != NULL) {
            clearAVLTree(&((*rootPtr)->rightNode)); // Clean the right subtree
        }
        free(*rootPtr); // Deallocate memory for the current node
        *rootPtr = NULL; // Set the root pointer to NULL
    }
}


int main() {
    setlocale(LC_ALL, "Portuguese");

    tree *root = NULL;
    int op, element, found;
    puts("What do you want to do?\nEnter:\n1)Insert a number\n2)Delete a number\n3)Search for a number\n4)Show Tree (in preorder)\n5)Empty the tree\n6)Exit");
    scanf("%d", &op);
    puts("----------------------");

    while(op != 6){
        switch(op) {
            case 1:
                puts("Enter an integer:");
                scanf("%d", &element);
                puts("Inserting...");
                root = insertFunction(root, element);
                puts("Insertion finished!");
                puts("----------------------");
                break;
            case 2:
                puts("What number would you like to delete?");
                scanf("%d", &element);
                puts("Deleting...");
                root = removeFunction(root, element);
                if(root == NULL) puts("The tree is empty!");
                else puts("Deletion finished!");
                puts("----------------------");
                break;
            case 3:
                found = 0;
                puts("What number would you like to search on the tree?");
                scanf("%d", &element);
                puts("Searching...");
                found = searchFunction(root,element,found);
                if(found) printf("The number %d is on the tree!\n", element);
                else printf("Number not found!\n");
                puts("----------------------");
                break;
            case 4:
                puts("Here's the tree:");
                puts("----------------------");
                showTreeFunction(root);
                puts("\n----------------------");
                break;
            case 5:
                puts("Cleaning tree...:");
                cleanTree(&root);
                if(root == NULL) puts("\nTree cleaned!");
                break;
            default:
                puts("Invalid option!");
                break;
        }
        puts("What else would you like to do?\nEnter:\n1)Insert a number\n2)Delete a number\n3)Search for a number\n4)Show Tree (in preorder)\n5)Empty the tree\n6)Exit");
        scanf("%d", &op);

    }
    puts("Execution finished! Shutting down...Bye!");
    return 0;
}
