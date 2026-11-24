#include "minunit.h"
#include <lcthw/list_algos.h>

static int one = 1;
static int two = 2;
static int another_two = 2;
static int three = 3;

static int compare(const void *a, const void *b)
{
    int left = *(const int *)a;
    int right = *(const int *)b;
    return (left > right) - (left < right);
}

static List *make_list(void)
{
    List *list = List_create();
    if (list) {
        List_push(list, &three);
        List_push(list, &two);
        List_push(list, &one);
        List_push(list, &another_two);
    }
    return list;
}

static int in_order(List *list)
{
    int *expected[] = { &one, &two, &another_two, &three };
    int i = 0;

    if (!list || List_count(list) != 4 || !list->first || !list->last ||
            list->first->prev || list->last->next)
        return 0;

    LIST_FOREACH(list, first, next, node) {
        if (i == 4 || node->value != expected[i] ||
                (node->next && node->next->prev != node))
            return 0;
        i++;
    }
    return i == 4;
}

static char *test_bubble_sort(void)
{
    List *list = make_list();
    mu_assert(list, "Could not create list.");
    mu_assert(List_bubble_sort(list, compare) == 0 && in_order(list), "Bubble sort failed.");
    mu_assert(List_bubble_sort(list, compare) == 0 && in_order(list), "Sorted bubble input changed.");
    List_destroy(list);
    return NULL;
}

static char *test_merge_sort(void)
{
    List *list = make_list();
    mu_assert(list, "Could not create list.");
    List *sorted = List_merge_sort(list, compare);
    mu_assert(sorted != list && in_order(sorted), "Merge sort failed.");
    mu_assert(List_first(list) == &three && List_count(list) == 4,
            "Merge sort changed its input.");
    List_destroy(sorted);
    List_destroy(list);
    return NULL;
}

static char *test_short_lists(void)
{
    List *list = List_create();
    mu_assert(list, "Could not create list.");
    mu_assert(List_bubble_sort(list, compare) == 0 && List_merge_sort(list, compare) == list,
            "Empty list should already be sorted.");
    List_push(list, &one);
    mu_assert(List_bubble_sort(list, compare) == 0 && List_merge_sort(list, compare) == list,
            "Singleton should already be sorted.");
    mu_assert(List_first(list) == &one && List_last(list) == &one, "Wrong singleton.");
    List_destroy(list);
    return NULL;
}

static char *test_insert_sorted(void)
{
    List *list = List_create();
    mu_assert(list, "Could not create list.");
    mu_assert(List_insert_sorted(list, &three, compare) == 0, "First insert failed.");
    mu_assert(List_insert_sorted(list, &two, compare) == 0, "Front insert failed.");
    mu_assert(List_insert_sorted(list, &one, compare) == 0, "Front insert failed.");
    mu_assert(List_insert_sorted(list, &another_two, compare) == 0 && in_order(list),
            "Insertion did not keep the list sorted or stable.");
    List_destroy(list);
    return NULL;
}

static char *test_bottom_up(void)
{
    List *list = make_list();
    mu_assert(list, "Could not create list.");
    List *sorted = List_merge_sort_bottom_up(list, compare);
    mu_assert(sorted != list && in_order(sorted), "Bottom-up sort failed.");
    mu_assert(List_first(list) == &three && List_count(list) == 4,
            "Bottom-up sort changed its input.");
    List_destroy(sorted);
    List_destroy(list);
    return NULL;
}

static char *all_tests(void)
{
    mu_suite_start();
    mu_run_test(test_bubble_sort);
    mu_run_test(test_merge_sort);
    mu_run_test(test_short_lists);
    mu_run_test(test_insert_sorted);
    mu_run_test(test_bottom_up);
    return NULL;
}

RUN_TESTS(all_tests);
