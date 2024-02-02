#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* implementation
Linked lists
Fundamental function ; insert, delete and advanced ver with avail pointer.
doubly linked list with circularity
*/
typedef struct node* listPointer;
typedef struct node {
    char* data;
    listPointer link;
}node;

typedef struct dlcl* dlclPointer;
typedef struct dlcl {
    char* data;
    dlclPointer rLink;
    dlclPointer lLink;
}dlcl;

listPointer start;
listPointer end; // similar to filepointer or stack pointer etc... showing current pointer.
listPointer ptr;
listPointer avail; 

int count=0;

void insert(char* msg, listPointer prev, int value) {
    // make memory space
    listPointer temp = (listPointer)malloc(sizeof(node));
    temp->data = strdup(msg);

    if (!prev) {
        start = temp;
        temp->link = NULL;
        end = temp;
        return;
    }

    temp->link = prev->link;
    prev->link = temp;

    if (!value) end = temp;
}

void delete(listPointer prev) { 
    if (!prev || !prev->link) {
        return;
    }
    listPointer temp = prev->link;
    prev->link = temp->link;
    free(temp->data); // Free the dynamically allocated string
    free(temp);       // Free the node itself
}

void availInsert(char* msg, listPointer prev) {
    // insert node with availPointer

    if(avail) {
        listPointer temp = avail;
        avail = avail->link;
        temp->link = prev->link;
        prev->link = temp;
    }

    else {
        // same as the original insert. memory allocation....
    }
}

void availDelete(listPointer prev) {
    listPointer temp = prev->link;
    prev->link = temp->link;
    temp->link = avail;
    avail = temp;
}

void dlclInsert(char* msg, dlclPointer prev) {
    dlclPointer temp = (dlclPointer)malloc(sizeof(dlcl));
    temp->data = strdup(msg);
    
    prev->rLink = temp;
    temp->lLink = prev;
    prev->rLink->lLink = temp;
    temp->rLink = prev->rLink;  // caution !! not prev->rLink->rLink !!
}

void dlclDelete(dlclPointer temp) { // unlike original linked list deletion, we can use dlclPointer which should be deleted.
    temp->lLink->rLink = temp->rLink;
    temp->rLink->lLink = temp->lLink;
    free(temp);
}

void findWord(char* msg, int judge) {   // 'judge' is used to consider whether it is count or not 
    count = 0;
    for (listPointer temp = start; temp; temp = temp->link) {        
        if(judge == count) {
            ptr = temp;
            return;
        }
        else {
            count++;
            if (strcmp(msg, temp->data) == 0) {
                ptr = temp;
                return;
            }   
            if (!(temp->link)) return;
        }       
    }
}

void print() {
    for (listPointer temp = start; temp; temp = temp->link) {  // condition ; temp -> link (x)  
        printf("\n|%8s|", temp->data);
        if (ptr == temp) printf("    <--- current ptr");
        printf("\n----------\n");
        if (!(temp->link)) break;
        printf("    |\n    |");
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

            if (strcmp(positionWord, "end") == 0) {
                insert(inputWord, end, 0);
            }

            else {
                findWord(positionWord,-1);
                if (ptr) {
                    insert(inputWord, ptr, 1);
                    ptr = NULL;
                }
                
                else printf("\nerror : no such word\n");
            }
        }

        else if (input == 'd') {
            printf("which word to delete? : ");
            scanf("%s", inputWord);
            printf("\n");
            
            ptr = NULL;
            findWord(inputWord,-1);

            if (ptr) {
                int a = count-1;
                if(a) {
                    findWord(inputWord,a);
                    delete(ptr);
                }
                else {
                    listPointer temp = ptr;
                    start = temp->link;
                    free(temp->data);
                    free(temp);
                }
                ptr = NULL;
            }
                
            else printf("error : no such word\n");

        }

        else if (input == 'f') {
            printf("word : ");
            scanf("%s", positionWord);
            findWord(positionWord,-1);
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