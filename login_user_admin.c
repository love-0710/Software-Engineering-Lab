#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for user information
struct User {
    char username[30];
    char password[20];
};

// Function to register a new user
void registerUser() {
    struct User newUser;
    FILE *file = fopen("users.txt", "a");

    printf("\nEnter Username: ");
    scanf("%s", newUser.username);
    printf("Enter Password: ");
    scanf("%s", newUser.password);

    // Write the new user information to the file
    fprintf(file, "%s %s\n", newUser.username, newUser.password);

    fclose(file);
    printf("\nRegistration Successful!\n");
}

// Function to authenticate a user
int authenticateUser(char *username, char *password) {
    struct User user;
    FILE *file = fopen("users.txt", "r");

    while (fscanf(file, "%s %s", user.username, user.password) == 2) {
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) {
            fclose(file);
            return 1; // Authentication successful
        }
    }

    fclose(file);
    return 0; // Authentication failed
}

// Function to display all user data (for admin)
void displayAllUserData() {
    struct User user;
    FILE *file = fopen("users.txt", "r");

    printf("\nAll User Data:\n");
    while (fscanf(file, "%s %s", user.username, user.password) == 2) {
        printf("Username: %s, Password: %s\n", user.username, user.password);
    }

    fclose(file);
}

int main() {
    int option;
    char username[30], password[20];

    while (1) {
        printf("\nPress '1' to Register\nPress '2' to Login\nPress '3' to Exit\n");
        scanf("%d", &option);

        switch (option) {
            case 1:
                registerUser();
                break;
            case 2:
                printf("\nEnter Username: ");
                scanf("%s", username);
                printf("Enter Password: ");
                scanf("%s", password);

                if (authenticateUser(username, password)) {
                    printf("\nLogin Successful!\n");

                    // Check if the logged-in user is an admin
                    if (strcmp(username, "admin") == 0) {
                        displayAllUserData();
                    } else {
                        // Display specific user data if needed
                        // Add your logic here
                    }
                } else {
                    printf("\nIncorrect Login Details\n");
                }
                break;
            case 3:
                printf("\nExiting the program.\n");
                exit(0);
            default:
                printf("\nInvalid option. Please try again.\n");
        }
    }

    return 0;
}
