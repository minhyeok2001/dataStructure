#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//1. make stack, queue, circular queue 

/*  implementation
1. choose which one to use, stack or queue. >> if queue, choose circular or not 
2. push or pop
3. display if input exists.
*/

int stackArr[100] ={0,};
int top = -1;

void stack(int var, char*arr) {
    if (strcmp(arr,"push")==0) stackArr[++top]= var;
    else if (strcmp(arr,"pop")==0) {
        if(top==-1) {
            fprintf(stderr,"error : empty stack\n");
            return ;
        }
        fprintf(stdout,"%d\n",stackArr[top--]);
    }
    else fprintf(stderr,"error : invalid input");
}


int main() {
    int var=0;
    char message[10];

for(;;){

    fprintf(stdout,"what to use? ( stack , queue )\n");
    fscanf(stdin,"%s",message);
    if (strcmp(message,"stack")==0) {
        fprintf(stdout,"push or pop? (if push, add var right next to push. Ex) push 3\n");
        fscanf(stdin,"%s",message);
        if(strcmp(message,"push")==0) fscanf(stdin,"%d",&var);
        stack(var,message);
    } 

}
    


    return 0;
}