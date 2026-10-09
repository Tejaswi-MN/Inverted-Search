#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "inverted_search.h"

void update_database(m_node *ht[], char *filename)
{
    char word[100];

    FILE *fptr = fopen(filename, "r");

    if (fptr == NULL)
    {
        return;
    }

    while (fscanf(fptr, "%99s", word) == 1)
    {
        char first = word[0];
        int index;

        if (isupper(first))
        {
            index = first - 'A';
        }
        else if (islower(first))
        {
            index = first - 'a';
        }
        else if (isdigit(first))
        {
            index = 26;
        }
        else
        {
            index = 27;
        }

        m_node *main_temp = ht[index];

        while (main_temp != NULL)
        {
            if (strcmp(main_temp->word, word) == 0)
            {
                break;
            }

            main_temp = main_temp->next;
        }

        /* Word doesn't exist */
        if (main_temp == NULL)
        {
            m_node *new_main = malloc(sizeof(m_node));

            if (new_main == NULL)
            {
                fclose(fptr);
                return;
            }

            new_main->word = malloc(strlen(word) + 1);

            if (new_main->word == NULL)
            {
                free(new_main);
                fclose(fptr);
                return;
            }

            strcpy(new_main->word, word);

            new_main->filecount = 1;

            s_node *new_sub = malloc(sizeof(s_node));

            if (new_sub == NULL)
            {
                free(new_main->word);
                free(new_main);
                fclose(fptr);
                return;
            }

            new_sub->filename = malloc(strlen(filename) + 1);

            if (new_sub->filename == NULL)
            {
                free(new_sub);
                free(new_main->word);
                free(new_main);
                fclose(fptr);
                return;
            }

            strcpy(new_sub->filename, filename);

            new_sub->w_count = 1;
            new_sub->subnext = NULL;

            new_main->sub = new_sub;

            new_main->next = ht[index];
            ht[index] = new_main;
        }
        else
        {
            /* Word exists, search for the file */
            s_node *sub_temp = main_temp->sub;

            while (sub_temp != NULL)
            {
                if (strcmp(sub_temp->filename, filename) == 0)
                {
                    break;
                }

                sub_temp = sub_temp->subnext;
            }

            /* Same word and same file */
            if (sub_temp != NULL)
            {
                sub_temp->w_count++;
            }
            else
            {
                /* Same word, but new file */
                s_node *new_sub = malloc(sizeof(s_node));

                if (new_sub == NULL)
                {
                    fclose(fptr);
                    return;
                }

                new_sub->filename = malloc(strlen(filename) + 1);

                if (new_sub->filename == NULL)
                {
                    free(new_sub);
                    fclose(fptr);
                    return;
                }

                strcpy(new_sub->filename, filename);

                new_sub->w_count = 1;

                new_sub->subnext = main_temp->sub;
                main_temp->sub = new_sub;

                main_temp->filecount++;
            }
        }
    }

    fclose(fptr);
}