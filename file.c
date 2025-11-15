#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr = fopen("contacts.txt","w");
    fprintf(fptr,"%d\n",addressBook->contactCount);
    for(int i=0; i<addressBook->contactCount; i++)
    {
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr = fopen("contacts.txt","r");
    fscanf(fptr,"%d ",&addressBook->contactCount);
    for(int i=0; i<addressBook->contactCount;i++)
    {
        fscanf(fptr," %[^,],%[^,],%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}