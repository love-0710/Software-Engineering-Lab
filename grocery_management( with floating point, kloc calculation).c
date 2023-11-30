#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
                        // Proceed to Grocery Management System

                        struct date {
                            int day;
                            int month;
                            int year;
                        };

                        struct details {
                            char name[20];
                            int price;
                            int total_price;
                            int code;
                            int qty;
                            struct date mfg;
                        };

                        struct details item[50];
                        int n, i;

                        printf("Enter number of items:");
                        scanf("%d", &n);
                        fflush(stdin);
                        for (i = 0; i < n; i++) {
                            fflush(stdin);
                            printf("Item name: \n");
                            scanf("%s", item[i].name);
                            fflush(stdin);
                            printf("Item code: \n");
                            scanf("%d", &item[i].code);
                            fflush(stdin);
                            printf("Quantity: \n");
                            scanf("%d", &item[i].qty);
                            fflush(stdin);
                            printf("price: \n");
                            scanf("%d", &item[i].price);
                            fflush(stdin);
                            printf("Manufacturing date(dd-mm-yyyy): \n");
                            scanf("%d-%d-%d", &item[i].mfg.day, &item[i].mfg.month, &item[i].mfg.year);
                        }

                        printf("                              *****  INVENTORY ***** \n");
                        printf("----------------------------------------------------------------------------------\n");
                        printf("S.N.|    NAME           |   CODE   |  QUANTITY |  PRICE | TOTAL PRICE | MFG.DATE |\n");
                        printf("----------------------------------------------------------------------------------\n");
                        for (i = 0; i < n; i++)
                            printf("%d     %-15s        %-d          %-5d       %-5d     %-5d      %d/%d/%d \n", i + 1, item[i].name, item[i].code, item[i].qty,
                                   item[i].price, item[i].qty * item[i].price, item[i].mfg.day, item[i].mfg.month, item[i].mfg.year);
                        printf("----------------------------------------------------------------------------------\n");

                        int input;
                        int output;
                        int inquiries;
                        int files;
                        int interface;
                        float ufp;
                        float fp;

                        printf("Enter the value of External Input: \n");
                        scanf("%d", &input);
                        printf("Enter the value of External Output: \n");
                        scanf("%d", &output);
                        printf("Enter the value of External Inquiries: \n");
                        scanf("%d", &inquiries);
                        printf("Enter the value of Internal Files: \n");
                        scanf("%d", &files);
                        printf("Enter the value of External Internal File: \n");
                        scanf("%d", &interface);
                        printf("Factor: 14 * 3\n");
                        printf("Factor: 42\n");
                        printf("CAF: 0.65+(0.01*42)\n");
                        printf("CAF: 1.07 \n");

                        ufp = 4 * input + 5 * output + 4 * inquiries + 10 * files + 7 * interface;
                        printf("UFP: %f \n", ufp);

                        fp = ufp * 1.07;
                        printf("FP: %f \n", fp);

                        int kloc;
                        int preference;
                        int choice;

                        printf("Enter the value of Kloc: ");
                        scanf("%d", &kloc);
                        printf("Enter Choice:\n 1. Organic\n 2. Semi-Detached\n 3. Embedded\n");
                        scanf("%d", &choice);
                        switch (choice) {
                        case 1:
                            {
                                int E = 2.1 * pow(kloc, 1.05);
                                printf("E: %d \n", E);
                                int T = 2.5 * pow(E, 0.38);
                                printf("T: %d \n", T);
                                break;
                            }

                        case 2:
                            {
                                int E = 3.0 * pow(kloc, 1.12);
                                printf("E: %d \n", E);
                                int T = 2.5 * pow(E, 0.33);
                                printf("T: %d \n", T);
                                break;
                            }

                        case 3:
                            {
                                int E = 3.6 * pow(kloc, 1.20);
                                printf("E: %d \n", E);
                                int T = 2.5 * pow(E, 0.32);
                                printf("T: %d \n", T);
                                break;
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

//gcc grocery_management.c -o grocery_management -lm
//./grocery_management
