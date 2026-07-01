#include "inverted.h"  

void display_database(M_node *HT[])   // Function to display inverted index database
{
    int empty = 1;   // Flag to check if database is empty

    printf("\n%-10s %-15s %-12s %-18s %-10s\n",   // Print table header with formatting
           "Index", "Word", "FileCount", "FileName", "WordCount");   // Column names
    printf("--------------------------------------------------------------------------\n");   // Print separator line

    for(int i = 0; i < 27; i++)   // Traverse all hash table indices (0–26)
    {
        M_node *temp = HT[i];   // Get main node list at current index

        while(temp)   // Traverse main node list (words)
        {
            empty = 0;   // Mark database as not empty

            S_node *s = temp->sub_link;   // Pointer to sub list (files for word)
            int first = 1;   // Flag to print word details only once

            while(s)   // Traverse sub node list (file details)
            {
                if(first)   // If first file entry for the word
                {
                    printf("%-10d %-15s %-12d %-18s %-10d\n",   // Print full row with word details
                           i,   // Print index
                           temp->word,   // Print word
                           temp->file_count,   // Print number of files containing word
                           s->filename,   // Print file name
                           s->word_count);   // Print word count in file
                    first = 0;   // Set flag to false after first print
                }
                else   // For subsequent file entries of same word
                {
                    printf("%-10s %-15s %-12s %-18s %-10d\n",   // Print row without repeating word details
                           "",   // Empty index column
                           "",   // Empty word column
                           "",   // Empty file count column
                           s->filename,   // Print file name
                           s->word_count);   // Print word count
                }

                s = s->sub_link;   // Move to next sub node
            }

            temp = temp->main_link;   // Move to next word in same index
        }
    }

    if(empty)   // If no data found in database
        printf("Database is empty\n");   // Print message
}
