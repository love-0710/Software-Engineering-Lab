#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for user information
struct User {
    char username[30];
    char password[20];
};

// Create Structure of Library
struct Library {
    char book_name[20];
    char author[20];
    int pages;
    float price;
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

// Driver Code for E-library Management System
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
                    // Proceed to E-library Management System
                    struct Library lib[100];
                    char ar_nm[30];
                    int i, input, count;

                    i = input = count = 0;

                    while (input != 5) {
                        printf("\n\n********######"
                               "WELCOME TO E-LIBRARY "
                               "#####********\n");
                        printf("\n\n1. Add book infor"
                               "mation\n2. Display "
                               "book information\n");
                        printf("3. List all books of "
                               "given author\n");
                        printf("4. List the count of book"
                               "s in the library\n");
                        printf("5. Exit");

                        printf("\n\nEnter one of "
                               "the above: ");
                        scanf("%d", &input);

                        switch (input) {
                        case 1:
                            printf("Enter book name = ");
                            scanf("%s", lib[i].book_name);

                            printf("Enter author name = ");
                            scanf("%s", lib[i].author);

                            printf("Enter pages = ");
                            scanf("%d", &lib[i].pages);

                            printf("Enter price = ");
                            scanf("%f", &lib[i].price);
                            count++;
                            break;

                        case 2:
                            printf("you have entered"
                                   " the following "
                                   "information\n");
                            for (i = 0; i < count; i++) {
                                printf("book name = %s",
                                       lib[i].book_name);

                                printf("\t author name = %s",
                                       lib[i].author);

                                printf("\t pages = %d",
                                       lib[i].pages);

                                printf("\t price = %f",
                                       lib[i].price);
                            }
                            break;

                        case 3:
                            printf("Enter author name : ");
                            scanf("%s", ar_nm);
                            for (i = 0; i < count; i++) {
                                if (strcmp(ar_nm,
                                           lib[i].author)
                                    == 0)
                                    printf("%s %s %d %f",
                                           lib[i].book_name,
                                           lib[i].author,
                                           lib[i].pages,
                                           lib[i].price);
                            }
                            break;

                        case 4:
                            printf("\n No of books in "
                                   "brary : %d",
                                   count);
                            break;
                        case 5:
                            exit(0);
                        }
                    }
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
