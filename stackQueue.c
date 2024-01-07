#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4
//1. make stack, queue, circular queue 

/*  implementation
1. choose which one to use, stack or queue. >> if queue, choose circular or not 
2. push or pop
3. display if input exists.
*/

int stackArr[SIZE] ={0,};
int top = -1;

int queueArr[SIZE] ={0,};
int front = 0;
int rear = 0;

int circularQueueArr[SIZE] ={0,};

void stack(int var, char*arr) {
    if (strcmp(arr,"push")==0) stackArr[++top]= var;
    else if (strcmp(arr,"pop")==0) {
        if(top==-1) {
            fprintf(stderr,"error : empty stack\n");
            return ;
        }
        fprintf(stdout,"%d\n",stackArr[top]);
        stackArr[top--]=0;
    }
    else fprintf(stderr,"error : invalid input");
}

void queue(int var, char*arr) {
    if (strcmp(arr,"push")==0) queueArr[rear++] = var;
    else if (strcmp(arr,"pop")==0) {
        if(front == rear) {
            fprintf(stderr,"error : empty queue\n");
            return ;
        }
        fprintf(stdout,"%d\n",queueArr[front]);
         stackArr[front++]=0;
    }
    else fprintf(stderr,"error : invalid input");

}

// feature : we use orignial size -1 due to calculative benefit. 
// unlike original queue, it recycles space by circulation.

void circularQueue(int var,char*arr) {
    if (strcmp(arr,"push")==0)  
        if ((rear+1)%SIZE==front) fprintf(stderr,"error : full queue\n");
        else {  
            circularQueueArr[rear] = var;
            rear = (rear+1)%SIZE;
        }
    
    else if (strcmp(arr,"pop")==0) {
        if(front == rear) {
            fprintf(stderr,"error : empty queue\n");
            return ;
        }

        fprintf(stdout,"%d\n",circularQueueArr[front]);
        circularQueueArr[front] =0;
        front = (front+1)%SIZE;
    }
    else fprintf(stderr,"error : invalid input\n");

}


int main() {
    int var=0;
    char message[10];
    char queueType[10];

for(;;){
    fprintf(stdout,"stack , queue , status , quit ?\n");
    fscanf(stdin,"%s",message);
    if (strcmp(message,"stack")==0) {
        fprintf(stdout,"push or pop? (if push, add var right next to push. Ex) push 3\n");
        fscanf(stdin,"%s",message);
        if(strcmp(message,"push")==0) fscanf(stdin,"%d",&var);
        stack(var,message);
    } 

    else if (strcmp(message,"queue")==0) {
        fprintf(stdout,"which one to use? basic or circular ?\n");
        fscanf(stdin,"%s",queueType);
        fprintf(stdout,"push or pop? (if push, add var right next to push. Ex) push 3\n");
        fscanf(stdin,"%s",message);
        if(strcmp(message,"push")==0) fscanf(stdin,"%d",&var);
        if(strcmp(queueType,"basic") == 0) queue(var,message);
        else if (strcmp(queueType, "circular") == 0) circularQueue(var,message);
    }

    else if (strcmp(message,"status")==0) {
        fprintf(stdout,"stack : ");
        for(int i=0; i<SIZE;i++) fprintf(stdout,"%d ",stackArr[i]);
        fprintf(stdout,"\nqueue : ");
        for(int i=0; i<SIZE;i++) fprintf(stdout,"%d ",queueArr[i]);
        fprintf(stdout,"\ncircular queue : ");
        for(int i=0; i<SIZE;i++) fprintf(stdout,"%d ",circularQueueArr[i]);
        printf("\n");
    }

    else if (strcmp(message,"quit")==0) break;
    
    else fprintf(stderr,"error : invalid input\n");

}

    return 0;
}