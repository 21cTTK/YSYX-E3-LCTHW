#include <lcthw/list.h>
#include <lcthw/dbg.h>
#include <assert.h>

static void List_check(const List *list)
{
    (void)list;
    assert(list);
    assert(list->count >= 0);
    assert((list->count == 0) == (list->first == NULL && list->last == NULL));
    assert(!list->count || (list->first && list->last));
    assert(!list->first || list->first->prev == NULL);
    assert(!list->last || list->last->next == NULL);
}

List *List_create(void)
{
    return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{
    List_check(list);
    LIST_FOREACH(list, first, next, cur) {
        if (cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}

void List_clear(List *list)
{
    List_check(list);
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
        cur->value = NULL;
    }
}

void List_clear_destroy(List *list)
{
    List_check(list);
    ListNode *cur = list->first;
    while (cur) {
        ListNode *next = cur->next;
        free(cur->value);
        free(cur);
        cur = next;
    }
    free(list);
}

void List_push(List *list, void *value)
{
    List_check(list);
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;

error:
    return;
}

void *List_pop(List *list)
{
    List_check(list);
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value)
{
    List_check(list);
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;

error:
    return;
}

void *List_shift(List *list)
{
    List_check(list);
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
    List_check(list);
    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL");

    if (node->prev) {
        node->prev->next = node->next;
    } else {
        list->first = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        list->last = node->prev;
    }

    list->count--;
    void *result = node->value;
    free(node);
    return result;

error:
    return NULL;
}

List *List_copy(const List *list)
{
    List_check(list);
    List *copy = List_create();
    if (!copy)
        return NULL;

    LIST_FOREACH(list, first, next, cur) {
        List_push(copy, cur->value);
    }

    if (copy->count != list->count) {
        List_destroy(copy);
        return NULL;
    }
    return copy;
}

void List_join(List *left, List *right)
{
    List_check(left);
    List_check(right);
    if (left == right || !right->first)
        return;

    if (left->last) {
        left->last->next = right->first;
        right->first->prev = left->last;
    } else {
        left->first = right->first;
    }
    left->last = right->last;
    left->count += right->count;
    *right = (List){ 0 };
}

List *List_split(List *list, int index)
{
    List_check(list);
    if (index < 0 || index > list->count)
        return NULL;

    List *tail = List_create();
    if (!tail || index == list->count)
        return tail;

    if (index == 0) {
        List_join(tail, list);
        return tail;
    }

    ListNode *node = list->first;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }

    tail->first = node;
    tail->last = list->last;
    tail->count = list->count - index;
    list->last = node->prev;
    list->last->next = NULL;
    list->count = index;
    node->prev = NULL;
    return tail;
}
