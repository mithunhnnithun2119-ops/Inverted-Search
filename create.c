#include "inverted.h"   

int get_index(char *word)   
{
    if(word[0] >= 'a' && word[0] <= 'z')   // Check if first character is lowercase letter
        return word[0] - 'a';   // Return index (0–25) for lowercase

    if(word[0] >= 'A' && word[0] <= 'Z')   // Check if first character is uppercase letter
        return word[0] - 'A';   // Return index (0–25) for uppercase

    return 26;   // Return 26 for non-alphabet characters
}

void create_database(M_node *HT[], F_node *head)   // Function to create inverted index database
{
    char word[25];   // Buffer to store each word read from file

    while(head)   // Traverse through file list
    {
        FILE *fp = fopen(head->f_name, "r");   // Open file in read mode
        if(fp == NULL)   // Check if file failed to open
        {
            head = head->link;   // Move to next file
            continue;   // Skip current file
        }

        while(fscanf(fp, "%s", word) != EOF)   // Read each word from file until end
        {
            int index = get_index(word);   // Get index based on first character
            if(index < 0 || index > 26)   // Validate index range
                continue;   // Skip invalid index

            M_node *temp = HT[index];   // Pointer to traverse main node list at index
            M_node *prev = NULL;   // Pointer to track previous main node

            while(temp)   // Traverse main node list
            {
                if(strcmp(temp->word, word) == 0)   // Check if word already exists
                    break;   // Stop if word found

                prev = temp;   // Update previous pointer
                temp = temp->main_link;   // Move to next main node
            }

            if(temp == NULL)   // If word not found in main list
            {
                M_node *m_new = malloc(sizeof(M_node));   // Create new main node
                strcpy(m_new->word, word);   // Copy word into main node
                m_new->file_count = 1;   // Initialize file count
                m_new->main_link = NULL;   // Set next pointer to NULL

                S_node *s_new = malloc(sizeof(S_node));   // Create new sub node
                strcpy(s_new->filename, head->f_name);   // Store file name
                s_new->word_count = 1;   // Initialize word count
                s_new->sub_link = NULL;   // Set next pointer to NULL

                m_new->sub_link = s_new;   // Link sub node to main node

                if(prev == NULL)   // If inserting at head of hash table index
                    HT[index] = m_new;   // Assign new node as first element
                else
                    prev->main_link = m_new;   // Link previous node to new node
            }
            else   // If word already exists in main list
            {
                S_node *s_temp = temp->sub_link;   // Pointer to traverse sub list
                S_node *s_prev = NULL;   // Pointer to track previous sub node

                while(s_temp)   // Traverse sub node list
                {
                    if(strcmp(s_temp->filename, head->f_name) == 0)   // Check if file already exists
                        break;   // Stop if file found

                    s_prev = s_temp;   // Update previous pointer
                    s_temp = s_temp->sub_link;   // Move to next sub node
                }

                if(s_temp)   // If file already exists
                {
                    s_temp->word_count++;   // Increment word count for that file
                }
                else   // If file not found in sub list
                {
                    S_node *s_new = malloc(sizeof(S_node));   // Create new sub node
                    strcpy(s_new->filename, head->f_name);   // Store file name
                    s_new->word_count = 1;   // Initialize word count
                    s_new->sub_link = NULL;   // Set next pointer to NULL

                    if(s_prev == NULL)   // If inserting at beginning of sub list
                        temp->sub_link = s_new;   // Assign new sub node as first
                    else
                        s_prev->sub_link = s_new;   // Link previous sub node to new node

                    temp->file_count++;   // Increment file count for this word
                }
            }
        }

        fclose(fp);   // Close the file after processing
        head = head->link;   // Move to next file in list
    }
}

