#ifndef _LINKED_LIST
#define _LINKED_LIST

#include <stddef.h>

typedef struct lnode
{
	void *data;
	struct lnode *next;
} lnode_t;

typedef struct llist
{
	lnode_t *first;
} linked_list_t;

linked_list_t *linked_list();
void linked_list_free(linked_list_t *);

void linked_list_add(linked_list_t *, void *);
void linked_list_del(linked_list_t *, size_t);
size_t linked_list_sz(linked_list_t*);
void linked_list_add_after(linked_list_t *, int, void *);
void linked_list_add_before(linked_list_t *, int, void *);

lnode_t lnode(void *);
void lnode_free(lnode_t *);

#endif