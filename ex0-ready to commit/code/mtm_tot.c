#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isPowerOf2(int x) {
    return x > 0 && (x & (x - 1)) == 0;
}

int findExponent(int x) {
    int j = 0;
    while (x > 1) {
        x /= 2; // Right shift by 1 (equivalent to x = x / 2)
        j++;
    }
    return j;
}

void result(int *arr, int size){
    int sum = 0;
    for(int i = 0; i < size; i++){
        if(isPowerOf2(arr[i])){
            int j = findExponent(arr[i]);
            printf("The number %d is a power of 2: %d = 2^%d\n",arr[i],arr[i], j);
            sum += j;
        }
    }
    printf("Total exponent sum is %d\n", sum);
}



int main(void) {
    int size;
    printf("Enter size of input:\n");
    if(scanf("%d",&size) != 1){
        return 0;
    }
    if(size <= 0){
        printf("Invalid size\n");
        return 0;
    }
    int *numbers = malloc(size*sizeof(int));
    if(numbers == NULL){
        return 0;
    }
    printf("Enter numbers:\n");
    for(int i = 0; i < size; i++){
        if(scanf("%d", &numbers[i]) != 1){
            free(numbers);
            printf("Invalid number\n");
            return 0;
        }
    }
    result(numbers, size);
    free(numbers);
    return 0;
}
