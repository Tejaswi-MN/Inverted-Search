//Tejaswi M N- 26010_092 Project name-Inverted Search 
//Description-> Developed a C-based Inverted Search application using hash tables and linked lists to index words across multiple text files, supporting database creation, display, search, update, and save operations.


#include <stdio.h>
#include <stdlib.h>
#include "inverted_search.h"

int main(int argc, char *argv[])
{
    m_node *ht[SIZE];

    /* Initialize hash table */
    for (int i = 0; i < SIZE; i++)
    {
        ht[i] = NULL;
    }

    /* Validate command line arguments */
    if (validate_arguements(argc, argv) == FAILURE)
    {
        printf("ERROR : Invalid command line arguments\n");
        return FAILURE;
    }

    int choice;

    while (1)
    {
        printf("\n1. Create database\n");
        printf("2. Display database\n");
        printf("3. Search database\n");
        printf("4. Update database\n");
        printf("5. Save database\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                /* Create database */
                for (int i = 1; i < argc; i++)
                {
                    create_database(ht, argv[i]);
                }

                printf("Database created successfully\n");
                break;
            }

            case 2:
            {
                /* Display database */
                display_database(ht);
                break;
            }

            case 3:
            {
                /* Search database */
                char word[100];

                printf("Enter the word to search: ");
                scanf("%99s", word);

                search_database(ht, word);
                break;
            }

            case 4:
            {
                char filename[100];

                printf("Enter the file name to update: ");
                scanf("%99s", filename);

                int len = strlen(filename);

                if (len < 4 || strcmp(filename + len - 4, ".txt") != 0)
                {
                    printf("ERROR: File must have .txt extension\n");
                    break;
                }

                FILE *fptr = fopen(filename, "r");

                if (fptr == NULL)
                {
                    printf("ERROR: File does not exist\n");
                    break;
                }

                fclose(fptr);

                update_database(ht, filename);
                printf("Database updated successfully\n");

                break;
            }

            case 5:
            {
                save_database(ht);
                break;
            }

            case 6:
            {
                /* Exit */
                return SUCCESS;
            }

            default:
            {
                printf("ERROR : Invalid choice\n");
                break;
            }
        }
    }

    return SUCCESS;
}