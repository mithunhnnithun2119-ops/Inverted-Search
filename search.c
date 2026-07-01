#include "inverted.h" 

void search_database(M_node *HT[])   // Function to search a word in the inverted index database
{
    char word[25];   // Buffer to store input word
    printf("Enter word: ");   // Prompt user to enter word
    scanf("%s", word);   // Read word from user

    int index = get_index(word);   // Get hash index based on first character

    M_node *temp = HT[index];   // Get main node list at calculated index

    printf("\n%-10s %-15s %-12s %-18s %-10s\n",   // Print table header
           "Index", "Word", "FileCount", "FileName", "WordCount");   // Column names
    printf("--------------------------------------------------------------------------\n");   // Print separator

    while(temp)   // Traverse main node list (words)
    {
        if(strcmp(temp->word, word) == 0)   // Check if word matches
        {
            printf("%-10d %-15s %-12d\n", index, temp->word, temp->file_count);   // Print word details

            S_node *s = temp->sub_link;   // Pointer to sub list (file details)
            while(s)   // Traverse sub node list
            {
                printf("%-10s %-15s %-12s %-18s %-10d\n",   // Print file details for the word
                       "",   // Empty index column
                       "",   // Empty word column
                       "",   // Empty file count column
                       s->filename,   // Print file name
                       s->word_count);   // Print word count in file
                s = s->sub_link;   // Move to next sub node
            }
            return;   // Exit function after finding the word
        }
        temp = temp->main_link;   // Move to next word in same index
    }

    printf("Word not found\n");   // Print message if word not present
}
