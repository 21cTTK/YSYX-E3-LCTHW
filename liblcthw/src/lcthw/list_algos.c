#include <lcthw/list_algos.h>

static void ListNode_swap(ListNode *a, ListNode *b)
{
    void *value = a->value;
    a->value = b->value;
    b->value = value;
}

int List_bubble_sort(List *list, List_compare cmp)
{
    if (!list || !cmp)
        return -1;
    if (List_count(list) <= 1)
        return 0;

    ListNode *end = NULL;
    int swapped;

    do {
        swapped = 0;
        ListNode *cur = list->first;
        for (; cur->next != end; cur = cur->next) {
            if (cmp(cur->value, cur->next->value) > 0) {
                ListNode_swap(cur, cur->next);
                swapped = 1;
            }
        }
        end = cur;
    } while (swapped);

    return 0;
}

static void List_move_first(List *to, List *from)
{
    ListNode *node = from->first;
    from->first = node->next;
    if (from->first) {
        from->first->prev = NULL;
    } else {
        from->last = NULL;
    }
    from->count--;

    node->prev = to->last;
    node->next = NULL;
    if (to->last) {
        to->last->next = node;
    } else {
        to->first = node;
    }
    to->last = node;
    to->count++;
}

static void List_merge(List *left, List *right, List_compare cmp)
{
    List result = { 0 };

    while (left->first && right->first) {
        if (cmp(List_first(left), List_first(right)) <= 0) {
            List_move_first(&result, left);
        } else {
            List_move_first(&result, right);
        }
    }

    List_join(&result, left);
    List_join(&result, right);
    *left = result;
}

static int List_sort_nodes(List *list, List_compare cmp)
{
    if (List_count(list) <= 1)
        return 0;

    List *right = List_split(list, List_count(list) / 2);
    if (!right)
        return -1;

    int rc = List_sort_nodes(list, cmp) || List_sort_nodes(right, cmp);
    if (rc == 0) {
        List_merge(list, right, cmp);
    } else {
        List_join(list, right);
    }
    List_destroy(right);
    return rc;
}

List *List_merge_sort(List *list, List_compare cmp)
{
    if (!list || !cmp)
        return NULL;
    if (List_count(list) <= 1)
        return list;

    List *sorted = List_copy(list);
    if (sorted && List_sort_nodes(sorted, cmp) != 0) {
        List_destroy(sorted);
        return NULL;
    }
    return sorted;
}
