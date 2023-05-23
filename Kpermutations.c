#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Calculate the factorial of a number
int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Backtracking function to generate permutations
void backtrack(int n, int k, int* nums, bool* used, int depth, char* result) {
    if (depth == n) {
        result[depth] = '\0';  // Terminate the string
        return;
    }
    
    int count = factorial(n - 1 - depth);
    for (int i = 1; i <= n; i++) {
        if (used[i]) {
            continue;
        }
        
        if (count < k) {
            k -= count;
            continue;
        }
        
        result[depth] = '0' + i;
        used[i] = true;
        backtrack(n, k, nums, used, depth + 1, result);
        return;
    }
}

// Function to get the kth permutation sequence
char* getPermutation(int n, int k) {
    int* nums = (int*)malloc((n + 1) * sizeof(int));  // Array to store numbers from 1 to n
    bool* used = (bool*)calloc((n + 1), sizeof(bool));  // Array to track used numbers
    char* result = (char*)malloc((n + 1) * sizeof(char));  // Array to store the resulting permutation
    
    for (int i = 1; i <= n; i++) {
        nums[i] = i;  // Initialize the nums array with numbers from 1 to n
    }
    
    backtrack(n, k, nums, used, 0, result);  // Generate the kth permutation using backtracking
    
    free(nums);
    free(used);
    
    return result;
}

int main() {
    int n, k;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("Enter the value of k: ");
    scanf("%d", &k);
    
    char* permutation = getPermutation(n, k);  // Get the kth permutation sequence
    printf("The kth permutation sequence is: %s\n", permutation);
    
    free(permutation);
    
    return 0;
}
