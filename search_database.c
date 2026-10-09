#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "inverted_search.h"

void search_database(m_node *ht[], char *word)
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

    /* Search main node */
    m_node *main_temp = ht[index];

    while (main_temp != NULL)
    {
        if (strcmp(main_temp->word, word) == 0)
        {
            break;
        }

        main_temp = main_temp->next;
    }

    /* Word not found */
    if (main_temp == NULL)
    {
        printf("Word %s is not found in the database\n", word);
        return;
    }

    /* Word found - traverse subnodes */
    s_node *sub_temp = main_temp->sub;

    while (sub_temp != NULL)
    {
        printf("word %s is found at the database and it is present in %d files in file %s %d times\n",
               word,
               main_temp->filecount,
               sub_temp->filename,
               sub_temp->w_count);

        sub_temp = sub_temp->subnext;
    }
}