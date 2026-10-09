#include <stdio.h>
#include "inverted_search.h"

void display_database(m_node *ht[])
{
    for (int i = 0; i < SIZE; i++)
    {
        m_node *main_temp = ht[i];

        while (main_temp != NULL)
        {
            printf("[%d] [%s] %d file(s) : ",
                   i,
                   main_temp->word,
                   main_temp->filecount);

            s_node *sub_temp = main_temp->sub;

            while (sub_temp != NULL)
            {
                printf("file : %s : %d time(s) ",
                       sub_temp->filename,
                       sub_temp->w_count);

                sub_temp = sub_temp->subnext;
            }

            printf("\n");

            main_temp = main_temp->next;
        }
    }
}