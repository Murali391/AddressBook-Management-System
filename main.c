#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    addressBook.contactCount = 0;
    initialize(&addressBook); // Initialize the address book

    do {
        // Magenta for the main menu header
        printf("\n\033[1;35m========== ADDRESS BOOK MENU ==========\n");
        printf("=======================================\033[0m\n");
        // Bright Cyan for menu choices
        printf("\033[1;36m1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save and Exit\033[0m\n");
        printf("\033[1;35m---------------------------------------\033[0m\n"); // Magenta separator
        printf("\033[1;33mEnter your choice: \033[0m"); // Yellow prompt

        if(scanf("%d",&choice)==1)
        {
            printf("\033[1;35m**********************************************************************\033[0m\n"); // Magenta separator
            switch (choice) {
                case 1:
                    createContact(&addressBook);
                    break;
                case 2:
                    searchContact(&addressBook);
                    break;
                case 3:
                    editContact(&addressBook);
                    break;
                case 4:
                    deleteContact(&addressBook);
                    break;
                case 5:
                    // Magenta for sort menu header
                    printf("\033[1;35m--- Select Sort Criteria ---\033[0m\n");
                    // Bright Cyan for sort menu choices
                    printf("\033[1;36m1. Sort by name\n");
                    printf("2. Sort by phone\n");
                    printf("3. Sort by email\n");
                    printf("4. Exit\033[0m\n");
                    printf("\033[1;35m----------------------------\033[0m\n"); // Magenta separator
                    printf("\033[1;33mEnter your choice: \033[0m"); // Yellow prompt
                    int sortChoice;
                    if(scanf("%d", &sortChoice)==1)
                    {
                        listContacts(&addressBook, sortChoice);
                        break;
                    }
                    else
                    {
                        printf("\033[1;31mError: Invalid input...\nTry again...\033[0m\n"); // Red error
                        while(getchar() != '\n');
                        break;
                    }
                case 6:
                    printf("\033[1;36mSaving and Exiting...\033[0m\n"); // Cyan success message
                    saveContactsToFile(&addressBook);
                    break;
                default:
                    printf("\033[1;31mInvalid choice. Please try again.\033[0m\n"); // Red error
            }
        }
    else
    {
        printf("\033[1;31mError: Invalid input...\nTry again...\033[0m\n"); // Red error
        while(getchar() != '\n');
    }
    } while (choice != 6);
       return 0;
}