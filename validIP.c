#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool isValidIPv4(char* ip) {
    int count = 0;
    char* token = strtok(ip, ".");
    
    while (token != NULL) {
        count++;
        
        if (count > 4 || strlen(token) == 0 || strlen(token) > 3)
            return false;
        
        for (int i = 0; i < strlen(token); i++) {
            if (!isdigit(token[i]))
                return false;
        }
        
        int num = atoi(token);
        if (num < 0 || num > 255 || (token[0] == '0' && strlen(token) > 1))
            return false;
        
        token = strtok(NULL, ".");
    }
    
    return count == 4;
}

bool isValidIPv6(char* ip) {
    int count = 0;
    char* token = strtok(ip, ":");
    
    while (token != NULL) {
        count++;
        
        if (count > 8 || strlen(token) == 0 || strlen(token) > 4)
            return false;
        
        for (int i = 0; i < strlen(token); i++) {
            if (!isxdigit(token[i]))
                return false;
        }
        
        token = strtok(NULL, ":");
    }
    
    return count == 8;
}

char* validIPAddress(char* IP) {
    if (IP == NULL || strlen(IP) == 0)
        return "Neither";
    
    if (isValidIPv4(IP))
        return "IPv4";
    
    if (isValidIPv6(IP))
        return "IPv6";
    
    return "Neither";
}

int main() {
    char queryIP[50];
    printf("Enter the IP address: ");
    if (fgets(queryIP, sizeof(queryIP), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    // Remove trailing newline character, if present
    int length = strlen(queryIP);
    if (length > 0 && queryIP[length - 1] == '\n') {
        queryIP[length - 1] = '\0';
    }
    
    char* result = validIPAddress(queryIP);
    printf("IP type: %s\n", result);
    
    return 0;
}
