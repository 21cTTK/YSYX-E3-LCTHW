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

int List_insert_sorted(List *list, void *value, List_compare cmp)
{
    if (!list || !cmp)
        return -1;

    ListNode *after = list->first;
    while (after && cmp(after->value, value) <= 0) {
        after = after->next;
    }

    ListNode *node = malloc(sizeof(ListNode));
    if (!node)
        return -1;

    ListNode *before = after ? after->prev : list->last;
    *node = (ListNode){ .prev = before, .next = after, .value = value };

    if (before) {
        before->next = node;
    } else {
        list->first = node;
    }

    if (after) {
        after->prev = node;
    } else {
        list->last = node;
    }

    list->count++;
    return 0;
}

static List List_take_run(List *input, int width)
{
    List run = { 0 };

    while (input->first && run.count < width) {
        List_move_first(&run, input);
    }
    return run;
}

List *List_merge_sort_bottom_up(List *list, List_compare cmp)
{
    if (!list || !cmp)
        return NULL;
    if (List_count(list) <= 1)
        return list;

    List *sorted = List_copy(list);
    if (!sorted)
        return NULL;

    int count = List_count(sorted);
    for (int width = 1; width < count;) {
        List input = *sorted;
        *sorted = (List){ 0 };

        while (input.first) {
            List left = List_take_run(&input, width);
            List right = List_take_run(&input, width);
            List_merge(&left, &right, cmp);
            List_join(sorted, &left);
        }

        if (width > count / 2)
            break;
        width *= 2;
    }
    return sorted;
}
