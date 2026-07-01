/* 
NAME : MITHUN H N
DATE : 23/04/2026
Description : This project implements an inverter search using a hash table to efficiently store and retrieve words from multiple text files. It reads input .txt filesvalidates them, and organizes each word along with its frequency and the files in which it appears. The system supports operations such as creating the database, displaying contents, searching for specific words, saving the database to a file, and updating it from stored data. By using hashing and linked structures, the project ensures fast lookup and efficient data management.

*/


#include "inverted.h"  

int main(int argc, char *argv[])   // Main function with command-line arguments
{
    F_node *head = NULL;   // Initialize file list head pointer
    M_node *HT[27]={NULL};   // Initialize hash table with 27 indices (a–z + others)

    // Validate_files

    validate_files(argc, argv, &head);   // Validate input files and store valid ones in linked list

    int option;   // Variable to store user menu choice
    do   // Loop until user chooses exit
    {
        printf("Select your choice among following operations:\n1. Create Database\n2. Display Database\n3. Save Database\n4. Search\n5. Update Database\n6. Exit\n\nEnter your choice : ");   // Display menu options

        scanf("%d", &option);   // Read user choice

        switch (option)   // Perform action based on user choice
        {
            case 1:   // Create database
                create_database(HT, head);   // Build inverted index from files
                break;   // Exit case

            case 2:   // Display database
                display_database(HT);   // Show database content
                break;   // Exit case

            case 3:   // Save database
                save_database(HT);   // Save database to file
                break;   // Exit case

            case 4:   // Search word
                search_database(HT);   // Search for a word in database
                break;   // Exit case

            case 5:   // Update database
                update_database(HT, &head);   // Update existing database with new data
                break;   // Exit case

            case 6:   // Exit option
                break;   // Do nothing, loop will terminate

            default:   // Invalid choice
                printf("INFO : Please enter the valid option\n");   // Print error message
        }
    }while( option != 6 );   // Continue loop until user selects exit

    return 0;   // Return success and terminate program
}
