#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>

void listContacts(AddressBook *addressBook, int sortCriteria)
{
    // ... (Sorting logic remains the same) ...
    Contact temp;
    for (int i = 0; i < addressBook->contactCount - 1; i++) {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) {
            if ((sortCriteria == 1 && strcasecmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name) > 0) ||
                (sortCriteria == 2 && strcasecmp(addressBook->contacts[j].phone, addressBook->contacts[j+1].phone) > 0) ||
                (sortCriteria == 3 && strcasecmp(addressBook->contacts[j].email, addressBook->contacts[j+1].email) > 0))
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }

    // Magenta for table header and borders
    printf("\033[1;35m----------------------------------------------------------------------\n");
    printf("%-20s | %-15s | %-25s\n", "NAME", "PHONE NUMBER", "MAIL ID");
    printf("----------------------------------------------------------------------\033[0m\n");

    // Bright Cyan for contact content
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("\033[1;36m%-20s | %-15s | %-25s\033[0m\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("\033[1;35m----------------------------------------------------------------------\033[0m\n");
}

void initialize(AddressBook *addressBook) {
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


int validate_name(char *name)
// ... (validation logic remains the same) ...
{
    if(isalpha(*name))
        name++;

    else
        return 1;

    while(*name)
    {
        if(isalpha(*name) || *name == ' ' || *name == '.')
            name++;

        else
            return 1;
    }
    return 0;
}

int validate_mobile(AddressBook *addressBook, char *mobile)
{
// ... (validation logic remains the same) ...
    if(strlen(mobile) != 10)
        return 1;

    for(int i = 0; mobile[i]; i++)
    {
        if(!isdigit(mobile[i]))
            return 1;
    }

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, mobile) == 0)
        {
            printf("\033[1;31mWe found same Phone number...\033[0m\n"); 
            return 1;
        }
    }

    return 0;
}

int validate_mail_id(AddressBook *addressBook, char *mail_id)
{
// ... (validation logic remains the same) ...
    if(!islower(*mail_id))
        return 1;

    char *at_pos = strchr(mail_id, '@');
    if(at_pos == NULL || strchr(at_pos + 1, '@') != NULL)
        return 1;

    char *com_pos = strstr(at_pos, ".com");
    if(com_pos == NULL || strcmp(com_pos, ".com") != 0)
        return 1;

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, mail_id) == 0)
        {
            printf("\033[1;31mWe found same Mail Id...\033[0m\n"); 
            return 1;
        }
    }

    return 0;
}

void createContact(AddressBook *addressBook)
{
    char name[50];
    int valid_name;
    do {
        printf("\033[1;33mEnter the name: \033[0m");
        scanf(" %49[^\n]", name);
        valid_name = validate_name(name);
        if(valid_name)
            printf("\033[1;31mERROR: Invalid name......\033[0m\n"); 
    } while (valid_name);

    char mobile[15];
    int valid_mobile;
    do {
        printf("\033[1;33mEnter the mobile number: \033[0m"); 
        scanf(" %14[^\n]", mobile);
        valid_mobile = validate_mobile(addressBook, mobile);
        if(valid_mobile)
            printf("\033[1;31mERROR: Invalid mobile number......\033[0m\n"); 
    } while (valid_mobile);

    char mail_id[50];
    int valid_mail;
    do {
        printf("\033[1;33mEnter the mail_id: \033[0m"); 
        scanf(" %49[^\n]", mail_id);
        valid_mail = validate_mail_id(addressBook, mail_id);
        if(valid_mail)
            printf("\033[1;31mERROR: Invalid email id.....\033[0m\n"); 
    } while (valid_mail);

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, mobile);
    strcpy(addressBook->contacts[addressBook->contactCount].email, mail_id);
    addressBook->contactCount++;
    printf("\033[1;36m----------------------------------------------------------------------\n");
    printf("Contact saved successfully!\n");
    printf("----------------------------------------------------------------------\033[0m\n");
}

int search_name(AddressBook *addressBook, char *name_search)
{
    int count = 0, arr[100], choice;
    printf("\033[1;35m--- Found Contacts (Matching '%s') ---\033[0m\n", name_search); 
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcasestr(addressBook->contacts[i].name, name_search))
        {
            printf("\033[1;36m%d  -> Name: %-20s | Phone Number: %-15s | Mail ID: %-25s\033[0m\n",count + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            arr[count++] = i;
        }
    }
    printf("\033[1;35m***********************************************************************************************\033[0m\n");


    if (count == 1)
    {
        printf("\033[1;36m-----------------------------------------------------------------------------------------------\n");
        printf("Contact found: Name: %-20s | Phone: %-15s | Mail: %-25s\n",
               addressBook->contacts[arr[0]].name, addressBook->contacts[arr[0]].phone, addressBook->contacts[arr[0]].email);
        printf("-----------------------------------------------------------------------------------------------\033[0m\n");
        return arr[0];
    }
    else if (count > 1)
    {
        printf("\033[1;33mWe found multiple contacts, please enter index value: \033[0m"); 
        scanf("%d", &choice);

        if (choice >= 1 && choice <= count)
        {
            printf("\033[1;36m-----------------------------------------------------------------------------------------------\n");
            printf("Contact selected: Name: %-16s | Phone: %-11s | Mail: %-21s\n",
                   addressBook->contacts[arr[choice - 1]].name, addressBook->contacts[arr[choice - 1]].phone, addressBook->contacts[arr[choice - 1]].email);
            printf("-----------------------------------------------------------------------------------------------\033[0m\n");
            return arr[choice - 1];
        }
        else
        {
            printf("\033[1;31mInvalid choice!\033[0m\n"); 
            return -1;
        }
    }
    else
    {
        printf("\033[1;31mNo contact found with %s\033[0m\n", name_search); 
        return -1;
    }
}


int search_number(AddressBook *addressBook,char *number_search)
{
    for(int i=0; i<addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone,number_search)==0)
        {
            printf("\033[1;36m-----------------------------------------------------------------------------------------------\n");
            printf("Contact found: Name: %-20s | Phone: %-15s | Mail: %-25s\n",
                   addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            printf("-----------------------------------------------------------------------------------------------\033[0m\n");
            return i;
        }
    }
        printf("\033[1;31mNo contact found with %s\033[0m\n",number_search); 
        return -1;
}

int search_mail(AddressBook *addressBook,char *mail_search)
{
    for(int i=0; i<addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email,mail_search) == 0)
        {
            printf("\033[1;36m-----------------------------------------------------------------------------------------------\n");
            printf("Contact found: Name: %-20s | Phone: %-15s | Mail: %-25s\n",
                   addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            printf("-----------------------------------------------------------------------------------------------\033[0m\n");
            return i;

        }
    }
    printf("\033[1;31mNo contact found with %s\033[0m\n",mail_search); 
    return -1;
}

void searchContact(AddressBook *addressBook)
{
    int choice;
    char input[50];
    printf("\n\033[1;35m--- SEARCH CRITERIA ---\n");
    printf("-----------------------\033[0m\n");
    printf("\033[1;36m1. Based on Name\n");
    printf("2. Based on Mobile Num\n");
    printf("3. Based on Mail ID\n");
    printf("4. Exit\033[0m\n");
    printf("\033[1;35m-----------------------\033[0m\n"); 
    printf("\033[1;33mEnter choice from menu: \033[0m"); 

    if(scanf("%d",&choice)==1)
    {
        printf("\033[1;35m***********************************************************************************************\033[0m\n");
        switch(choice)
        {
            case 1:
                printf("\033[1;33mEnter name: \033[0m");
                scanf(" %49[^\n]",input);
                search_name(addressBook, input);
                break;
            case 2:
                printf("\033[1;33mEnter number: \033[0m"); 
                scanf(" %49[^\n]",input);
                search_number(addressBook, input);
                break;
            case 3:
                printf("\033[1;33mEnter mail_id: \033[0m"); 
                scanf(" %49[^\n]",input);
                search_mail(addressBook, input);
                break;
            case 4:
                printf("\033[1;36mExiting search successfully.....\033[0m\n"); 
                break;
            default:
                printf("\033[1;31m\nInvalid choice....\nExiting search successfully.....\033[0m\n"); 
                break;
        }
    }
    else
    {
        printf("\033[1;31mError: Invalid input...\nTry again...\033[0m\n"); 
        while(getchar() != '\n');
    }
}

void choice_based_edit(AddressBook *addressBook, int i)
{
    int choice;
    char name_edit[50], number_edit[11], mail_edit[50];
    printf("\n\033[1;35m--- What would you like to edit ---\n");
    printf("-----------------------------------\033[0m\n");
    printf("\033[1;36m1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Mail ID\n");
    printf("4. Exit\033[0m\n");
    printf("\033[1;35m-----------------------------------\033[0m\n"); 
    printf("\033[1;33mEnter your choice: \033[0m"); 

    if(scanf("%d", &choice)==1)
    {
        switch (choice) {
            case 1:
            {
                printf("\033[1;33mEnter new name: \033[0m"); 
                scanf(" %49[^\n]", name_edit);
                strcpy(addressBook->contacts[i].name, name_edit);
                printf("\033[1;36mName updated successfully.\033[0m\n"); 
                break;
            }
            case 2:
            {
                printf("\033[1;33mEnter new Phone Number: \033[0m"); 
                scanf(" %10[^\n]", number_edit);
                strcpy(addressBook->contacts[i].phone, number_edit);
                printf("\033[1;36mPhone Number updated successfully.\033[0m\n"); 
                break;
            }
            case 3:
                printf("\033[1;33mEnter new Mail ID: \033[0m"); 
                scanf(" %49[^\n]", mail_edit);
                strcpy(addressBook->contacts[i].email, mail_edit);
                printf("\033[1;36mMail ID updated successfully.\033[0m\n"); 
                break;

            case 4:
                printf("\033[1;36mExiting edit field selection.......\033[0m\n"); 
                return;

            default:
                printf("\033[1;31mInvalid choice.\033[0m\n"); 
                return;
        }
    }
    else
    {
        printf("\033[1;31mError: Invalid input...\nTry again...\033[0m\n"); 
        while(getchar() != '\n');
    }
    printf("\033[1;36m-----------------------------------------------------------------------------------------------\n");
    printf("Updated: Name: %-20s | Phone: %-15s | Mail: %-25s\n",
           addressBook->contacts[i].name,
           addressBook->contacts[i].phone,
           addressBook->contacts[i].email);
    printf("-----------------------------------------------------------------------------------------------\033[0m\n");
}


void editContact(AddressBook *addressBook)
{
    int option;
    printf("\n\033[1;35m--- Search By to Edit Contact ---\n");
    printf("---------------------------------\033[0m\n");
    printf("\033[1;36m1. Name\n");
    printf("2. Phone number\n");
    printf("3. Mail ID\n");
    printf("4. Exit\033[0m\n");
    printf("\033[1;35m---------------------------------\033[0m\n"); 
    printf("\033[1;33mEnter the choice to search and edit: \033[0m"); 

    if(scanf("%d", &option)==1)
    {
        switch (option) {
            case 1:
            {
                char name[50];
                printf("\033[1;33mEnter name that you want to edit: \033[0m"); 
                scanf(" %49[^\n]", name);

                int i = search_name(addressBook, name);
                if (i == -1)
                    printf("\033[1;31mContact not found. Cannot edit.\033[0m\n"); 
                else
                    choice_based_edit(addressBook, i);
                break;
            }
            case 2:
            {
                char number[11];
                printf("\033[1;33mEnter number that you want to edit: \033[0m"); 
                scanf(" %10[^\n]",number);
                int i = search_number(addressBook, number);
                if(i == -1)
                    printf("\033[1;31mContact not found. Cannot edit.\033[0m\n"); 
                else
                    choice_based_edit(addressBook, i);
                break;
            }
            case 3:
            {
                char mail_id[50];
                printf("\033[1;33mEnter Mail ID that you want to edit: \033[0m"); 
                scanf(" %49[^\n]",mail_id);
                int i = search_mail(addressBook, mail_id);
                if(i == -1)
                    printf("\033[1;31mContact not found. Cannot edit.\033[0m\n"); 
                else
                    choice_based_edit(addressBook, i);
                break;
            }
            case 4:
                printf("\033[1;36mExiting edit menu.\033[0m\n"); 
                break;
            default:
                printf("\033[1;31mInvalid option.\033[0m\n"); 
        }
    }
    else
    {
        printf("\033[1;31mError: Invalid input...\nTry again...\033[0m\n"); 
        while(getchar() != '\n');
    }
}

void choice_based_delete(AddressBook *addressBook, int index)
{
    char confirm;
    printf("\033[1;31mAre you sure you want to delete this contact? (y/n): \033[0m");
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y')
    {
        for (int i = index; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }

        addressBook->contactCount--;

        // Bright Cyan success block
        printf("\033[1;36m----------------------------------------\n");
        printf("Contact deleted successfully.\n");
        printf("----------------------------------------\033[0m\n");
    }
    else
    {
        printf("\033[1;36mDeletion cancelled.\033[0m\n"); 
    }
}


void deleteContact(AddressBook *addressBook)
{
    int choice;
    // Magenta menu header
    printf("\n\033[1;35m--- Search By to Delete Contact ---\n");
    printf("---------------------------------\033[0m\n");
    // Bright Cyan menu choices
    printf("\033[1;36m1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Mail ID\n");
    printf("4. Exit\033[0m\n");
    printf("\033[1;35m---------------------------------\033[0m\n"); 
    printf("\033[1;33mEnter the choice to search and delete: \033[0m"); 

    if(scanf("%d",&choice)==1)
    {
        switch(choice)
        {
            case 1:
                char name[50];
                printf("\033[1;33mEnter the name: \033[0m"); 
                scanf(" %49[^\n]",name);
                int i = search_name(addressBook, name);
                if (i == -1)
                    printf("\033[1;31mContact not found. Cannot delete.\033[0m\n"); 
                else
                    choice_based_delete(addressBook, i);
                break;
            case 2:
            {
                char number[11];
                printf("\033[1;33mEnter number that you want to delete: \033[0m"); 
                scanf(" %10[^\n]",number);
                int i = search_number(addressBook, number);
                if(i == -1)
                    printf("\033[1;31mContact not found. Cannot delete.\033[0m\n"); 
                else
                    choice_based_delete(addressBook, i);
                break;
            }
            case 3:
            {
                char mail_id[50];
                printf("\033[1;33mEnter Mail ID that you want to delete: \033[0m"); 
                scanf(" %49[^\n]",mail_id);
                int i = search_mail(addressBook, mail_id);
                if(i == -1)
                    printf("\033[1;31mContact not found. Cannot delete.\033[0m\n"); 
                else
                    choice_based_delete(addressBook, i);
                break;
            }
            case 4:
                printf("\033[1;36mExiting delete menu.\033[0m\n"); 
                break;
            default:
                printf("\033[1;31mInvalid option.\033[0m\n"); 
        }
    }
    else
    {
        printf("\033[1;31mError: Invalid input...\nTry again...\033[0m\n"); 
        while(getchar() != '\n');
    }

}