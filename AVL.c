#include <stdio.h>
#include <stdlib.h>

// use balance factor to judge whether to use rotation or not
// |bf|<= 1 then it's avl tree. but if not, it isn't.

int count=0;
int judge;  // LL ; 1 / LR ; 2 / RL ; 3 / RR ; 4

typedef struct tree* treePointer;
typedef struct tree{
    int data;
    treePointer leftChild;
    treePointer rightChild;
}tree;

void insertion() {

}

void findChild(treePointer temp) {   // just like tree traversal    >> 이렇게하면 전체 자식수를 세는건데??
// before calling function, be cautious to initialize count = 0
    if(!temp) return;
    findchild(temp->leftChild);
    count++;
    findChild(temp->rightChild);
}

treePointer bfCheck(treePointer root) { // for every insertion, check bf.
    // let given root node x
    count=0;
    findChild(root->leftChild);
    int leftCount = count;

    count=0;    
    findChild(root->rightChild);
    int rightCount = count;

    if(leftCount-rightCount>1 || leftCount-rightCount<-1) return root;    
}

void checkType(treePointer temp) {
    
}

treePointer check(treePointer root) {  // check every node in tree and return if it needs to be rotated.
    treePointer hola=NULL;
    for(treePointer temp = root; temp; temp = temp->leftChild) {
        if(!temp->leftChild) break;
        if(bfCheck(temp)) {
            checkType(bfcheck(temp));
            return(bfcheck(temp));
        }
    }
    for(treePointer temp = root; temp; temp = temp->rightChild) {
        if(!temp->rightChild) break;
        if(bfCheck(temp)) {
            checkType(bfcheck(temp));
            return(bfcheck(temp));
        }
    }
    return NULL;
}


