#include "inverted.h"   

void save_database(M_node *HT[])   // Function to save inverted index database into a file
{
    FILE *fp = fopen("database.txt", "w");   // Open (or create) file in write mode

    if(fp == NULL)   // Check if file opening failed
    {
        printf("File not created\n");   // Print error message
        return;   // Exit function
    }

    fprintf(fp, "%-10s %-15s %-12s %-18s %-10s\n",   // Write table header to file
            "Index", "Word", "FileCount", "FileName", "WordCount");   // Column names
    fprintf(fp, "--------------------------------------------------------------------------\n");   // Write separator line

    for(int i = 0; i < 27; i++)   // Loop through all hash table indices (0–26)
    {
        M_node *temp = HT[i];   // Get main node list at current index

        while(temp)   // Traverse main node list (words)
        {
            S_node *s = temp->sub_link;   // Pointer to sub list (file details for word)
            int first = 1;   // Flag to print word details only once

            while(s)   // Traverse sub node list (files)
            {
                if(first)   // If first file entry for the word
                {
                    fprintf(fp, "%-10d %-15s %-12d %-18s %-10d\n",   // Write full row with word details
                            i,   // Index value
                            temp->word,   // Word
                            temp->file_count,   // Number of files containing the word
                            s->filename,   // File name
                            s->word_count);   // Word count in that file
                    first = 0;   // Set flag to false after first entry
                }
                else   // For remaining file entries of same word
                {
                    fprintf(fp, "%-10s %-15s %-12s %-18s %-10d\n",   // Write row without repeating word details
                            "",   // Empty index column
                            "",   // Empty word column
                            "",   // Empty file count column
                            s->filename,   // File name
                            s->word_count);   // Word count
                }

                s = s->sub_link;   // Move to next sub node
            }

            temp = temp->main_link;   // Move to next main node (word)
        }
    }

    fclose(fp);   // Close file after writing
    printf("Database saved successfully\n");   // Print success message
}
