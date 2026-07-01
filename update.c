#include "inverted.h" 

int update_database(M_node *HT[], F_node **head) 
{
    char filename[20];   // Buffer to store input filename
    FILE *fp;   // File pointer for file operations
    F_node *new_file;   // Pointer to track newly added file node

    printf("Enter a filename : ");   // Prompt user to enter filename
    scanf("%s", filename);   // Read filename from user

    /* check .txt extension */
    if(strstr(filename, ".txt") == NULL)   // Check if filename does not contain ".txt"
    {
        printf("INFO : Not a txt file\n");   // Print error message
        return FAILURE;   // Return failure
    }

    /* check duplicate */
    if(check_duplicates(*head, filename))   // Check if file already exists in list
    {
        printf("INFO : File already present\n");   // Print duplicate message
        return FAILURE;   // Return failure
    }

    /* check file presence */
    fp = fopen(filename, "r");   // Try to open file in read mode
    if(fp == NULL)   // If file cannot be opened
    {
        printf("INFO : File not found\n");   // Print error message
        return FAILURE;   // Return failure
    }

    /* check empty file */
    fseek(fp, 0, SEEK_END);   // Move file pointer to end
    if(ftell(fp) == 0)   // Check if file size is zero
    {
        printf("INFO : File is empty\n");   // Print empty file message
        fclose(fp);   // Close file
        return FAILURE;   // Return failure
    }
    fclose(fp);   // Close file after validation

    /* insert into file list */
    insert_last(head, filename);   // Add new file to linked list of files

    /* get last node (new file) */
    new_file = *head;   // Start from head of file list
    while(new_file->link != NULL)   // Traverse to last node
    {
        new_file = new_file->link;   // Move to next node
    }

    /* update database only for this file */
    create_database(HT, new_file);   // Update inverted index using only the new file

    printf("INFO : Database updated successfully\n");   // Print success message

    return SUCCESS;   // Return success
}
