#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXHEAP 1
#define BINARYSEARCHTREE 0
#define MAXSIZE 100

#define FROMLEFT 1
#define FROMRIGHT 0
/*  implementation 

Binary tree ; max heap, binary search tree with insertion & deletion
Binary tree traversal ; inorder, preorder, postorder

what is max heap? ;  complete binary tree (feature of heap) whose parent > child (feature of 'max') for all nodes
*/ 

typedef struct tree* treePointer;
typedef struct tree{
    int data;
    treePointer rightChild;
    treePointer leftChild;
}tree;

treePointer root;

int maxHeap[MAXSIZE] = {0, };

void maxHeapInsertion(int data) {
    int i;
    for(i=1;i<MAXSIZE;i++) {    // we consider whether this is the right position to insert or not with zero, so input must not be 0 
        if(maxHeap[i]==0) break;
    }
    maxHeap[i] = data;

    while(1) {
        if(i == 1) break;
        if(maxHeap[i]>maxHeap[i/2]) {
            int temp = maxHeap[i];  // swap & move to parent
            maxHeap[i] = maxHeap[i/2];
            maxHeap[i/2] = temp;
        }
        i/=2;
    } 
}

void maxHeapDeletion() {   // delete top node (largest node) due to the feature of max heap..
    int i;
    for(i=1;i<MAXSIZE;i++) {
        if(maxHeap[i]==0) break;
    }
    int totalNum = i-1;
    int temp = maxHeap[totalNum];
    maxHeap[totalNum] = 0;   //initialize
    maxHeap[1] = temp;
    i=1;
    int largerChild;

    while(totalNum>=i) {    // compare with a larger child
        if(maxHeap[2*i]<maxHeap[2*i+1]) largerChild = 2*i+1;
        else    largerChild = 2*i;
    
        if(maxHeap[i]<maxHeap[largerChild] && maxHeap[i] != 0) {
            temp = maxHeap[i];  // swap & move to parent
            maxHeap[i] = maxHeap[largerChild];
            maxHeap[largerChild] = temp;
            i = largerChild;
        }
        else break;
    }

}

void binarySearchTreeInsertion(int data) {
    treePointer temp = root;
    while (temp) {
        if (temp->data > data)
            if (temp->leftChild) temp = temp->leftChild;
            else break;
        else if (temp->data < data) {
            if (temp->rightChild) temp = temp->rightChild;
            else break;
        }
        else {
            printf("error : duplication \n");
            return;
        }
    }

    treePointer add = (treePointer)malloc(sizeof(tree));
    add->data = data;
    add->rightChild = NULL;
    add->leftChild = NULL;

    if (temp) {
        if (temp->data > data) temp->leftChild = add;
        else temp->rightChild = add;
    }

    else {
        root = add;
    }

}

void binarySearchTreeDeletion(int data) {
    /*  3 cases available
    1. leaf
    2. node with 1 child
    3. node with 2 child    >> find smallest in right child family or lagest in left child family
    */
    treePointer temp = root;
    treePointer prev = NULL;
    int flag = 0;

    while (temp) {  // find 'data' node which has input in data
        if (temp->data > data)
            if (temp->leftChild) {
                prev = temp;
                flag = FROMLEFT;
                temp = temp->leftChild;
            }
            else {
                printf("error : no such data\n");
                return;
            }
        else if (temp->data < data) {
            if (temp->rightChild) {
                prev = temp;
                flag = FROMRIGHT;
                temp = temp->rightChild;
            }
            else {
                printf("error : no such data\n");
                return;
            }
        }
        else {
            break;
        }
    }
    treePointer originalTemp = temp;
   
    // 삭제부분 문제 확실히 있음.


    if (!temp->leftChild && !temp->rightChild) free(originalTemp);   // with leaf node
    else if (!temp->leftChild) {    // with 1 right child
        for (; temp && temp->rightChild; temp = temp->rightChild) {}
        if (flag == FROMLEFT) prev->leftChild = temp;
        else prev->rightChild = temp;
        temp->rightChild = originalTemp->rightChild;
        free(originalTemp);
    }
    else if (!temp->rightChild) {   // with 1 left child
        for (; temp && temp->leftChild; temp = temp->leftChild) {}
        if (flag == FROMLEFT) prev->leftChild = temp;
        else prev->rightChild = temp;
        temp->leftChild = originalTemp->leftChild;
        free(originalTemp);
    }
    else {  // with 2 child
        temp = temp->leftChild;
        for (; temp && temp->rightChild; temp = temp->rightChild) {} // find largest num in leftchild
        if (flag == FROMLEFT) prev->leftChild = temp;
        else prev->rightChild = temp;
        temp->leftChild = originalTemp->leftChild;
        temp->rightChild = originalTemp->rightChild;
        free(originalTemp);
    }
}

void print(int var) {
    if(var == MAXHEAP) {
        printf("max heap ; ");
       for(int i=1;i<MAXSIZE;i++) {
            if(maxHeap[i]==0) break;
            printf("%d ",*(maxHeap+i)); 
        }
    }
}

int main() {
    int type;
    int data;
    int choice;

    printf("tree type? 0 for max heap, 1 for binary search tree : ");
    scanf("%d",&type);

    if(!type) {
        for(;;) {
        printf("0 to insert, 1 to delete : ");
        scanf("%d",&choice);
        printf("\n");

        if(choice==0) {
            printf("num? : ");
            scanf("%d",&data);
            printf("\n");
            maxHeapInsertion(data);
        }

        else if (choice == 1) {
            maxHeapDeletion();
        }

        print(MAXHEAP);
        printf("\n\n");
        }
    }

    else {
        for(;;) {
            printf("0 to insert, 1 to delete : ");
            scanf("%d",&choice);
            printf("\n");
            if(choice==0) {
                printf("num? : ");
                scanf("%d",&data);
                printf("\n");  
                binarySearchTreeInsertion(data);
            }
        }
    }
    


    return 0;
}