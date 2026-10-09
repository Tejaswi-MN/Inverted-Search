#include <stdio.h>
#include <string.h>
#include "inverted_search.h"

void save_database(m_node *ht[])
{
    char filename[100];
    char choice;

    printf("Enter the file name to save database: ");
    scanf("%99s", filename);

    /* Check .txt extension */
    int len = strlen(filename);

    if (len < 4 || strcmp(filename + len - 4, ".txt") != 0)
    {
        printf("ERROR : File name must have .txt extension\n");
        return;
    }

    /* Check whether file already exists */
    FILE *fptr = fopen(filename, "r");

    if (fptr != NULL)
    {
        fclose(fptr);

        printf("File already exists. Do you want to overwrite? (y/n): ");
        scanf(" %c", &choice);

        if (choice != 'y' && choice != 'Y')
        {
            printf("Database not saved\n");
            return;
        }
    }

    /* Open file for writing */
    fptr = fopen(filename, "w");

    if (fptr == NULL)
    {
        printf("ERROR : Unable to open file\n");
        return;
    }

    /* Traverse hash table */
    for (int i = 0; i < SIZE; i++)
    {
        m_node *main_temp = ht[i];

        while (main_temp != NULL)
        {
            fprintf(fptr, "#%d;%s;%d",
                    i,
                    main_temp->word,
                    main_temp->filecount);

            /* Traverse subnodes */
            s_node *sub_temp = main_temp->sub;

            while (sub_temp != NULL)
            {
                fprintf(fptr, ";%s;%d",
                        sub_temp->filename,
                        sub_temp->w_count);

                sub_temp = sub_temp->subnext;
            }

            fprintf(fptr, "\n");

            main_temp = main_temp->next;
        }
    }

    fclose(fptr);

    printf("Database saved successfully\n");
}