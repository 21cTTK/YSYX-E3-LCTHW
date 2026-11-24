#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    void *value;
} ListNode;

typedef struct List {
    int count;
    ListNode *first;
    ListNode *last;
} List;

List *List_create(void);
/* Destroy the nodes and the list, leaving values alone. */
void List_destroy(List *list);
/* Free each value and leave its node in the list. */
void List_clear(List *list);
void List_clear_destroy(List *list);

#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

void List_push(List *list, void *value);
void *List_pop(List *list);
void List_unshift(List *list, void *value);
void *List_shift(List *list);
void *List_remove(List *list, ListNode *node);

#define LIST_FOREACH(L, S, M, V) \
    for (ListNode *V = (L)->S; V != NULL; V = V->M)

/* Copy nodes without copying the values. */
List *List_copy(const List *list);

/* Append right's nodes to left and leave right empty. */
void List_join(List *left, List *right);

/* Keep index nodes in list and return the remaining nodes as another list. */
List *List_split(List *list, int index);

#endif
