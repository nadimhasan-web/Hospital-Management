#ifndef AUTH_H
#define AUTH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to register a new user
void registerUser() {
    char username[100], password[100];
    printf("\n--- Register ---\n");
    printf("Enter a username: ");
    scanf("%s", username);
    printf("Enter a password: ");
    scanf("%s", password);

    FILE *outFile = fopen("users.txt", "a");
    if (outFile != NULL) {
        fprintf(outFile, "%s %s\n", username, password);
        fclose(outFile);
        printf("Registration successful!\n");
    } else {
        printf("Error: Unable to save user data.\n");
    }
}

// Function to log in an existing user
int loginUser() {
    char username[100], password[100], storedUser[100], storedPass[100];
    printf("\n--- Login ---\n");
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    FILE *inFile = fopen("users.txt", "r");
    if (inFile != NULL) {
        while (fscanf(inFile, "%s %s", storedUser, storedPass) == 2) {
            if (strcmp(storedUser, username) == 0 && strcmp(storedPass, password) == 0) {
                printf("Login successful!\n");
                fclose(inFile);
                return 1;
            }
        }
        fclose(inFile);
        printf("Invalid username or password.\n");
    } else {
        printf("Error: Unable to access user data.\n");
    }
    return 0;
}

#endif

