#include <stdio.h>

/*
Insertion sort
Bubble sort
Selection sort
Quick sort
Merge sort
Heap sort
*/

int heapArr[11] ={0,};  // blank in first index
int count=1;
int descendCount=10;

void insertionSort(int* arr) {  // using LOO(left out of order). insert in the right position.
    int temp = 0;
    int k = 0;
    for (int i = 1; i < 10; i++) {
        temp = arr[i];
        for (k = i - 1; k >= 0 && arr[k] > temp; k--) arr[k + 1] = arr[k];    // push.
        arr[k + 1] = temp;
    }

    printf("Insertion sort : ");
    for (int i = 0; i < 10; i++) printf("%d ", arr[i]);
    printf("\n");

}

void bubbleSort(int* arr) {
    int temp = 0;

    for (int i = 0; i < 10; i++) {
        for (int k = 0; k < 9 - i; k++) {
            if (arr[k] > arr[k + 1]) {
                temp = arr[k + 1];
                arr[k + 1] = arr[k];
                arr[k] = temp;
            }
        }
    }

    printf("Bubble sort : ");
    for (int i = 0; i < 10; i++) printf("%d ", arr[i]);
    printf("\n");
}

void selectionSort(int* arr) {  // similar to insertion, but it is swaping, not pushing.
    int min;
    int index = 0;
    int temp;
    for (int i = 0; i < 10; i++) {
        min = 10000;
        for (int k = i; k < 10; k++) {
            if (min > arr[k]) {
                min = arr[k];
                index = k;
            }
        }
        temp = arr[i];
        arr[i] = arr[index];
        arr[index] = temp;
    }

    printf("Selection sort : ");
    for (int i = 0; i < 10; i++) printf("%d ", arr[i]);
    printf("\n");
}

void quickSort(int* arr, int left, int right) {  //divide and conquer using pivot
    int pivot = arr[left];
    int temp = 0;
    int i = left + 1;
    int j = right;

    if (left < right) { // left < right condition makes stacks of functions to be stopped.( in the last stack. left == right)
        for (;;) {
            for (;;) if (arr[i] < pivot) i++;
            else break;
            for (;;) if (arr[j] > pivot) j--;
            else break;
            if (i < j) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
                j--;
            }
            else {
                temp = arr[left];
                arr[left] = arr[j];
                arr[j] = temp;
                break;
            }
        }
        quickSort(arr, left, j - 1);
        quickSort(arr, j + 1, right);
    }
    else return;
}

void mergeSort(int* arr) {

}

void heapInsertion(int var) {
    heapArr[count] = var;
    int temp = count;
    int curr;
    for(;var < heapArr[temp/2] && temp != 1; temp /= 2) {  // if parent is bigger than child
        curr = heapArr[temp/2];
        heapArr[temp/2]=heapArr[temp];
        heapArr[temp]=curr;
    }
    count++;
}

int heapDeletion() {    // 1. remove first node. 2. replace first position with the last one. 3. rearrange
    int parent = 1;
    int result = heapArr[1];
    heapArr[1] = heapArr[descendCount];
    heapArr[descendCount--] = 0;
    
    for(;;) {
        if(heapArr[parent]>heapArr[parent*2] || heapArr[parent]>heapArr[parent*2+1]) {
            if(heapArr[parent*2]<heapArr[parent*2+1]) {
                int temp= heapArr[parent];
                heapArr[parent] = heapArr[parent*2];
                heapArr[parent*2]=temp;
            }
            else {
                int temp= heapArr[parent];
                heapArr[parent] = heapArr[parent*2+1];
                heapArr[parent*2+1]=temp;
            }
        }
        else break;
    }

    return result;
}

void heapSort(int* arr) {   // using min heap insertion.

    for(int i=0;i<10;i++) heapInsertion(arr[i]);
    
    printf("Heap sort : ");
    for (int i = 0; i < 10; i++) printf("%d ", arr[i]);
    printf("\n");
}

void main() {
    int arr1[10] = { 30, 24, 61, 23, 10, 42, 75, 15, 5, 40 };
    insertionSort(arr1);

    int arr2[10] = { 30, 24, 61, 23, 10, 42, 75, 15, 5, 40 };
    bubbleSort(arr2);

    int arr3[10] = { 30, 24, 61, 23, 10, 42, 75, 15, 5, 40 };
    selectionSort(arr3);

    int arr4[10] = { 30, 24, 61, 23, 10, 42, 75, 15, 5, 40 };
    quickSort(arr4, 0, 9);

    printf("Quick sort : ");
    for (int k = 0; k < 10; k++) printf("%d ", arr4[k]);
    printf("\n");

    int arr5[10] = { 30, 24, 61, 23, 10, 42, 75, 15, 5, 40 };
    //mergeSort(arr5);

    int arr6[10] = { 30, 24, 61, 23, 10, 42, 75, 15, 5, 40 };
    heapSort(arr6);
}