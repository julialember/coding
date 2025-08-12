#include <stdio.h>
void qSort(int[],int,int);
void bbleSort(int[], int); 

int main() {
    int nums[] = {1,2,3,4,5,6,7,8,9,10}; 
    qSort(nums, 0, 9);
    for (int i = 0; i<10; i++) printf("%d", nums[i]);
    bbleSort(nums, 9); 
    printf("\n");
    for (int i = 0; i<10; i++) printf("%d", nums[i]);
}

void swap(int* a, int*b) {
    int temp = *a;
    *a = *b;
    *b = temp; 
}

void qSort(int nums[], int low, int high){
    if (low>=high) return;
    int i = low, q = high; 
    int pivot = nums[(low + high)/2]; 
    while (i<=q) {
        while (nums[i] > pivot && i <= high) i++; 
        while (nums[q] < pivot && q >= low) q--;
        if (i <= q) swap(&nums[i++], &nums[q--]); 
    }
    qSort(nums, low, q);
    qSort(nums, i, high);
}

void bbleSort(int nums[], int size) {
    for (int i = 0; i<size ; i++) 
        for (int q = 0; q < size - i; q++) 
            if (nums[q] > nums[q + 1]) swap(&nums[q], &nums[q+1]);
}
