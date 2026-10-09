#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H
#include <string.h>
#define SIZE 28
#define FAILURE 0
#define SUCCESS 1
typedef struct subnode s_node;

typedef struct mainnode
{
    char *word;
    int filecount;
    s_node *sub;
    struct mainnode *next;
} m_node;

struct subnode
{
    char *filename;
    int w_count;
    s_node *subnext;
};
void create_database(m_node *ht[], char *filename);
int validate_arguements(int argc, char *argv[]);
void update_database(m_node *ht[], char *filename);
void save_database(m_node *ht[]);
void display_database(m_node *ht[]);
void search_database(m_node *ht[], char *word);
int validate_update_file(char *filename, m_node *ht[]);
#endif