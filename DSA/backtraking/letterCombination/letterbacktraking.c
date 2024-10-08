#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the mappings from digits to letters
const char* keypad[] = {
    "",     // 0
    "",     // 1
    "abc",  // 2
    "def",  // 3
    "ghi",  // 4
    "jkl",  // 5
    "mno",  // 6
    "pqrs", // 7
    "tuv",  // 8
    "wxyz"  // 9
};

// Function to find the letter combinations using backtracking
void backtrack(char** result, int* returnSize, char* current, const char* digits, int index) {
    // If we've processed all digits, add the current combination to the result array
    if (digits[index] == '\0') {
        result[*returnSize] = strdup(current); // Add the current string to result
        (*returnSize)++;
        return;
    }
    
    // Get the letters corresponding to the current digit
    int digit = digits[index] - '0';
    const char* letters = keypad[digit];
    
    // Loop through all possible letters for this digit
    for (int i = 0; letters[i] != '\0'; i++) {
        current[index] = letters[i];
        backtrack(result, returnSize, current, digits, index + 1); // Recursively process the next digit
    }
}

// Main function to return all possible letter combinations for a given digit string
char** letterCombinations(char* digits, int* returnSize) {
    *returnSize = 0; // Initialize the return size to 0
    
    // If the input digits string is empty, return an empty result
    if (digits == NULL || digits[0] == '\0') {
        return NULL;
    }
    
    // Calculate the maximum possible number of combinations (4^length)
    int len = strlen(digits);
    int maxCombinations = 1;
    for (int i = 0; i < len; i++) {
        int digit = digits[i] - '0';
        maxCombinations *= strlen(keypad[digit]);
    }
    
    // Allocate memory for storing the combinations and a temporary buffer for the current combination
    char** result = (char**)malloc(maxCombinations * sizeof(char*));
    char* current = (char*)malloc((len + 1) * sizeof(char));
    current[len] = '\0'; // Null-terminate the current combination
    
    // Call the backtracking function
    backtrack(result, returnSize, current, digits, 0);
    
    // Free the temporary buffer
    free(current);
    
    return result;
}

int main() {
    char digits[] = "23"; // Example input
    int returnSize;
    
    // Get the letter combinations
    char** combinations = letterCombinations(digits, &returnSize);
    
    // Print the results
    printf("Letter combinations for '%s':\n", digits);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", combinations[i]);
        free(combinations[i]); // Free each allocated string
    }
    
    // Free the result array
    free(combinations);
    
    return 0;
}
