#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int strongPasswordChecker(char* password) {
    int length = strlen(password);
    int missingTypes = 3;
    bool hasLower = false;
    bool hasUpper = false;
    bool hasDigit = false;
    
    // Check the existing characters in the password
    for (int i = 0; i < length; i++) {
        if (!hasLower && password[i] >= 'a' && password[i] <= 'z')
            hasLower = true;
        if (!hasUpper && password[i] >= 'A' && password[i] <= 'Z')
            hasUpper = true;
        if (!hasDigit && password[i] >= '0' && password[i] <= '9')
            hasDigit = true;
    }
    
    // Check the missing types of characters
    missingTypes -= hasLower;
    missingTypes -= hasUpper;
    missingTypes -= hasDigit;
    
    int steps = 0;
    int requiredSteps = 0;
    int repeatingCount = 0;
    
    // Handle the case when password length is less than 6
    if (length < 6) {
        requiredSteps = 6 - length;
        steps += requiredSteps;
    }
    
    // Handle the case when password length is greater than 20
    if (length > 20) {
        int overLength = length - 20;
        int deleteSteps = overLength;
        
        // Reduce the delete steps by replacing repeating characters
        for (int i = 0; i < length; i++) {
            if (i > 1 && password[i] == password[i - 1] && password[i] == password[i - 2]) {
                if (deleteSteps > 0) {
                    deleteSteps--;
                    steps--;
                } else {
                    repeatingCount++;
                }
            }
        }
        
        steps += overLength;
        steps += repeatingCount;
    }
    
    // Handle the case when password length is between 6 and 20
    if (length >= 6 && length <= 20) {
        // Reduce the required steps by replacing repeating characters
        for (int i = 0; i < length; i++) {
            if (i > 1 && password[i] == password[i - 1] && password[i] == password[i - 2]) {
                if (requiredSteps > 0) {
                    requiredSteps--;
                    steps--;
                } else {
                    repeatingCount++;
                }
            }
        }
        
        steps += repeatingCount;
        steps += requiredSteps;
    }
    
    // Find the maximum of missingTypes and repeatingCount to get the final steps required
    steps += (missingTypes > repeatingCount) ? missingTypes : repeatingCount;
    
    return steps;
}

int main() {
    char password[50];
    printf("Enter the password: ");
    scanf("%s", password);
    
    int steps = strongPasswordChecker(password);
    printf("Minimum number of steps required: %d\n", steps);
    
    return 0;
}