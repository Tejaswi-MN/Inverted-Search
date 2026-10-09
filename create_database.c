#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "inverted_search.h"

void create_database(m_node *ht[], char *filename)
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

        /* Find hash index */
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

        /* Search for the word in the main node list */
        m_node *temp = ht[index];

        while (temp != NULL)
        {
            if (strcmp(temp->word, word) == 0)
            {
                break;
            }

            temp = temp->next;
        }

        /* Word does not exist - create main node */
        if (temp == NULL)
        {
            m_node *new_node = malloc(sizeof(m_node));

            if (new_node == NULL)
            {
                fclose(fptr);
                return;
            }

            new_node->word = malloc(strlen(word) + 1);

            if (new_node->word == NULL)
            {
                free(new_node);
                fclose(fptr);
                return;
            }

            strcpy(new_node->word, word);

            new_node->filecount = 1;
            new_node->next = ht[index];

            /* Create first subnode */
            s_node *sub_new = malloc(sizeof(s_node));

            if (sub_new == NULL)
            {
                free(new_node->word);
                free(new_node);
                fclose(fptr);
                return;
            }

            sub_new->filename = malloc(strlen(filename) + 1);

            if (sub_new->filename == NULL)
            {
                free(sub_new);
                free(new_node->word);
                free(new_node);
                fclose(fptr);
                return;
            }

            strcpy(sub_new->filename, filename);

            sub_new->w_count = 1;
            sub_new->subnext = NULL;

            new_node->sub = sub_new;

            ht[index] = new_node;
        }
        else
        {
            /*
             * Word already exists.
             * Search its subnode list for the current file.
             */
            s_node *sub_temp = temp->sub;

            while (sub_temp != NULL)
            {
                if (strcmp(sub_temp->filename, filename) == 0)
                {
                    break;
                }

                sub_temp = sub_temp->subnext;
            }

            /* Same word in same file */
            if (sub_temp != NULL)
            {
                sub_temp->w_count++;
            }
            else
            {
                /*
                 * Same word but in a new file.
                 * Create a new subnode.
                 */
                s_node *sub_new = malloc(sizeof(s_node));

                if (sub_new == NULL)
                {
                    fclose(fptr);
                    return;
                }

                sub_new->filename = malloc(strlen(filename) + 1);

                if (sub_new->filename == NULL)
                {
                    free(sub_new);
                    fclose(fptr);
                    return;
                }

                strcpy(sub_new->filename, filename);

                sub_new->w_count = 1;

                sub_new->subnext = temp->sub;
                temp->sub = sub_new;

                temp->filecount++;
            }
        }
    }

    fclose(fptr);
}