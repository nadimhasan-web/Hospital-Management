#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auth.h" // Include auth.h for user authentication

#define MAX_PATIENTS 100

// Patient structure
typedef struct {
    int id;
    char name[100];
    char disease[100];
    int daysStayed;
    double totalAmount;
} Patient;

Patient patients[MAX_PATIENTS];
int patientCount = 0;

// Function to add a new patient
void addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("Patient list is full!\n");
        return;
    }

    Patient p;
    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    getchar(); // Consume newline character
    printf("Enter Patient Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = '\0'; // Remove newline character
    printf("Enter Disease: ");
    fgets(p.disease, sizeof(p.disease), stdin);
    p.disease[strcspn(p.disease, "\n")] = '\0'; // Remove newline character
    printf("Enter Days Stayed: ");
    scanf("%d", &p.daysStayed);

    // Calculate total payable amount
    p.totalAmount = p.daysStayed * 500;

    // Add patient to array
    patients[patientCount] = p; // Assign to current index
    patientCount++;             // Increment patient count

    printf("Patient added successfully! Total payable amount is: %.2lf\n", p.totalAmount);
}

// Function to delete a patient by ID
void deletePatient() {
    int id, found = 0;
    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            for (int j = i; j < patientCount - 1; j++) {
                patients[j] = patients[j + 1];
            }
            patientCount--;
            found = 1;
            printf("Patient deleted successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Patient not found!\n");
    }
}

// Function to search for a patient by ID
void searchPatient() {
    int id, found = 0;
    printf("Enter Patient ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            printf("\nPatient Details:\n");
            printf("ID: %d\n", patients[i].id);
            printf("Name: %s\n", patients[i].name);
            printf("Disease: %s\n", patients[i].disease);
            printf("Days Stayed: %d\n", patients[i].daysStayed);
            printf("Total Amount: %.2lf\n", patients[i].totalAmount);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Patient not found!\n");
    }
}

// Function to display all patients
void displayAllPatients() {
    if (patientCount == 0) {
        printf("No patients to display!\n");
        return;
    }

    printf("\n--- All Patients ---\n");
    for (int i = 0; i < patientCount; i++) {
        printf("Patient %d:\n", i + 1);
        printf("ID: %d\n", patients[i].id);
        printf("Name: %s\n", patients[i].name);
        printf("Disease: %s\n", patients[i].disease);
        printf("Days Stayed: %d\n", patients[i].daysStayed);
        printf("Total Amount: %.2lf\n", patients[i].totalAmount);
        printf("--------------------------\n");
    }
}

// Main function
int main() {
    int loggedIn = 0;
    int authChoice;

    printf("--- Welcome to the Hospital Management System ---\n");
    printf("Please log in or register to continue.\n");

    // Authentication loop
    do {
        printf("\n1. Register\n");
        printf("2. Login\n");
        printf("Enter your choice: ");
        scanf("%d", &authChoice);

        if (authChoice == 1) {
            registerUser();
        } else if (authChoice == 2) {
            loggedIn = loginUser();
            if (!loggedIn) {
                printf("Login failed. Please try again.\n");
            }
        } else {
            printf("Invalid choice. Try again.\n");
        }
    } while (!loggedIn);

    // Main menu loop
    int choice;
    do {
        printf("\n--- Hospital Management System Menu ---\n");
        printf("1. Add Patient\n");
        printf("2. Delete Patient\n");
        printf("3. Search Patient\n");
        printf("4. Display All Patients\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            addPatient();
        } else if (choice == 2) {
            deletePatient();
        } else if (choice == 3) {
            searchPatient();
        } else if (choice == 4) {
            displayAllPatients();
        } else if (choice == 5) {
            printf("Exiting the system. Goodbye!\n");
        } else {
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
