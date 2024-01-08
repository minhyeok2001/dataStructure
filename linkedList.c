#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* goal
Linked lists, chains, circular list
Fundamental function ; insert, delete and advanced ver with avail pointer.
doubly linked list
*/
typedef struct node* listPointer;
typedef struct node {
    char* data;
    listPointer link;
}node;

listPointer start;
listPointer end; // similar to filepointer or stack pointer etc... showing current pointer.
listPointer ptr;

void insert(char* msg, listPointer prev) {
    // make memory space
    listPointer temp = (listPointer)malloc(sizeof(node));
    temp->data = msg;

    if (!prev) {
        start = temp;
        temp->link = NULL;
        end = temp;
        return;
    }

    temp->link = prev->link;
    prev->link = temp;

    end = temp;
}

void delete(listPointer prev) {

    if (!(prev->link)) return;
    if (!(prev->link->link)) {
        free(prev->link);
        prev->link = NULL;
        return;
    }
    free(prev->link);
    prev->link = prev->link->link;
}

void findWord(char* msg) {
    for (listPointer temp = start; temp; temp = temp->link) {
        if (strcmp(msg, temp->data) == 0) {
            ptr = temp;
            return;
        }
        if (!(temp->link)) return;
    }
    printf("%s not founded\n", msg);
}

void print() {
    int count = 0;
    for (listPointer temp = start; temp; temp = temp->link) {  // condition ; temp -> link (x)  
        printf("\ncount : %d\n----------\n", ++count);
        printf("|%8s|", temp->data);
        if (ptr == temp) printf("    <--- current ptr");
        printf("\n----------\n");
        if (!(temp->link)) break;
        printf("    |\n    |\n");
    }
}
int main() {

    char positionWord[10];
    char input;
    char inputWord[10];

    for (;;) {
        printf("insert ; i      delete ; d      find ; f        print ; p\n");
        scanf("%c", &input);
        if (input == 'i') {
            printf("position?  (base on 'right below ~~'  // if end of list, then enter 'end'): ");
            scanf("%s", positionWord);
            printf("\nword : ");
            scanf("%s", inputWord);
            printf("\n");

            if (strcmp(positionWord, "end") == 0) insert(inputWord, end);
            else {
                findWord(positionWord);
                if (ptr) {
                    insert(inputWord, ptr);
                    ptr = NULL;
                }
            }
        }

        else if (input == 'd') {

        }

        else if (input == 'f') {
            printf("word : ");
            scanf("%s", &positionWord);
            findWord(positionWord);
            printf("\n");
        }

        else if (input == 'p') {
            print();
        }

        else fprintf(stderr, "\nerror : invalid input\n");

        getchar();
    }
    return 0;
}