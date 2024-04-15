#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
//#include <string.h>

// Estrutura da árvore
typedef struct Tree{
    int num;
    struct Tree *rt, *lf;
}tree;


tree *insertFunction(tree *aux, int num){
    tree *new = malloc(sizeof(tree));
    if(aux == NULL){
        new->num = num;
        new->lf = NULL;
        new->rt = NULL;
        aux = new;
    }
    else if(num < aux->num){
        aux->lf = insertFunction(aux->lf, num);
    }
    else{
        aux->rt = insertFunction(aux->rt, num);
    }
    return aux;
}

int searchFunction(tree *aux, int num, int found){
    if(aux != NULL && found == 0){
        if(aux->num == num)
            found = 1;
        else if(num < aux->num)
            found = searchFunction(aux->lf, num, found);
        else
            found = searchFunction(aux->rt, num, found);
    }
    return found;
}

tree *removeFunction(tree *aux, int num){
    tree *p, *p2;
    if(aux == NULL) return aux;
    if(aux->num == num){
        if(aux->rt == aux->lf){
            free(aux);
            return NULL;
        }
        else if (aux->lf == NULL){
            p = aux->rt;
            free(aux);
            return p;
        }
        else if (aux->rt == NULL){
            p = aux->lf;
            free(aux);
            return p;
            }
        else {
            p2 = aux->rt;
            p = aux->rt;
            while(p->lf != NULL){
                p = p->lf;
            }
            p->lf = aux->lf;
            free(aux);
            return p2;
        }
    }
    else if(aux->num < num){
        aux->rt = removeFunction(aux->rt, num);
    }
    else{
        aux->lf = removeFunction(aux->lf, num);
    }
    return aux;
}

void showTreeFunction(tree *aux){
    if(aux != NULL){
        printf("%d ", aux->num);
        showTreeFunction(aux->lf);
        showTreeFunction(aux->rt);
    }
}


int main() {
    setlocale(LC_ALL, "Portuguese");

    tree*aux = NULL, *aux2;
    int op, num, n, found;
    puts("What do you want to do?\nEnter:\n1)Insert a number\n2)Delete a number\n3)Search for a number\n4)Show Tree (in preorder)\n5)Exit");
    scanf("%d", &op);
    puts("----------------------");

    while(op != 5){
        switch(op) {
            case 1:
                puts("How many numbers would you like to insert?");
                scanf("%d", &n);
                puts("Inserting...");
                for(int i=0;i<n;i++) {
                    puts("Enter an integer:");
                    scanf("%d", &num);
                    aux = insertFunction(aux, num);
                    aux2 = aux;
                }
                puts("Insertion finished!");
                puts("----------------------");
                break;
            case 2:
                puts("What number would you like to delete?");
                scanf("%d", &num);
                puts("Deleting...");
                aux = removeFunction(aux, num);
                aux2 = aux;
                if(aux == NULL) puts("The tree is empty!");
                else puts("Deletion finished!");
                puts("----------------------");
                break;
            case 3:
                found = 0;
                puts("What number would you like to search on the tree?");
                scanf("%d", &num);
                puts("Searching...");
                found = searchFunction(aux,num,found);
                if(found) printf("The number %d is on the tree!\n", num);
                else printf("Number not found!\n");
                puts("----------------------");
                break;
            case 4:
                puts("Here's the tree:");
                puts("----------------------");
                showTreeFunction(aux);
                puts("\n----------------------");
                break;
            default:
                puts("Invalid option!");
                break;
        }
        puts("What else would you like to do?\nEnter:\n1)Insert a number\n2)Delete a number\n3)Search for a number\n4)Show Tree (in preorder)\n5)Exit");
        scanf("%d", &op);

    }
    puts("Execution finished! Shutting down...Bye!");
    return 0;
}
