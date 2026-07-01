#include "inverted.h"  

/* Function definitions */

static int is_txt(char *name)   // Function to check if file has .txt extension
{
    char *ext = strrchr(name, '.');   // Find last occurrence of '.' in filename
    if(ext == NULL)   // If no extension found
        return FAILURE;   // Return failure

    if(strcmp(ext, ".txt") == 0)   // Compare extension with ".txt"
        return SUCCESS;   // Return success if it matches

    return FAILURE;   // Return failure if extension is not .txt
}

static int is_empty_file(char *fname)   // Function to check if file is empty
{
    FILE *fp = fopen(fname, "r");   // Open file in read mode

    if(fp == NULL)   // If file not found or cannot open
        return FAILURE;   // Return failure

    fseek(fp, 0, SEEK_END);   // Move file pointer to end

    if(ftell(fp) == 0)   // Check file size
    {
        fclose(fp);   // Close file
        return FAILURE;   // Return failure if file is empty
    }

    fclose(fp);   // Close file
    return SUCCESS;   // Return success if file has data
}

int check_duplicates(F_node *head, char *f_name)   // Function to check duplicate file names in list
{
    while(head)   // Traverse linked list
    {
        if(strcmp(head->f_name, f_name) == 0)   // Compare existing filename with given filename
            return SUCCESS;   // Return success if duplicate found
        head = head->link;   // Move to next node
    }
    return FAILURE;   // Return failure if no duplicate found
}

int insert_last(F_node **head, char *f_name)   // Function to insert file name at end of linked list
{
    F_node *new = malloc(sizeof(F_node));   // Allocate memory for new node
    if(new == NULL)   // Check allocation failure
        return FAILURE;   // Return failure

    strcpy(new->f_name, f_name);   // Copy file name into node
    new->link = NULL;   // Set next pointer to NULL

    if(*head == NULL)   // If list is empty
    {
        *head = new;   // Assign new node as head
        return SUCCESS;   // Return success
    }

    F_node *temp = *head;   // Create temporary pointer
    while(temp->link)   // Traverse to last node
        temp = temp->link;   // Move to next node

    temp->link = new;   // Link last node to new node
    return SUCCESS;   // Return success
}

void validate_files(int argc, char *argv[], F_node **head)   // Function to validate input files
{
    if(argc <= 1)   // Check if no files are passed
    {
        printf("No files passed\n");   // Print message
        return;   // Exit function
    }

    for(int i = 1; i < argc; i++)   // Loop through all input files
    {
        if(is_txt(argv[i]) == FAILURE)   // Check if file is not .txt
        {
            printf("%s : Invalid extension\n", argv[i]);   // Print error
            continue;   // Skip to next file
        }

        int status = is_empty_file(argv[i]);   // Check if file is empty or not present

        if(status == FAILURE)   // If file not present or empty
        {
            printf("%s : File not present\n", argv[i]);   // Print message
            continue;   // Skip file
        }

        if(status == FAILURE)   // (Repeated condition - logical duplication)
        {
            printf("%s : Empty file\n", argv[i]);   // Print message
            continue;   // Skip file
        }

        if(check_duplicates(*head, argv[i]) == SUCCESS)   // Check for duplicate file
        {
            printf("%s : Duplicate file\n", argv[i]);   // Print message
            continue;   // Skip duplicate file
        }

        insert_last(head, argv[i]);   // Insert valid file into list
    }

    if(*head == NULL)   // If no valid files inserted
        printf("No valid files\n");   // Print message
}
