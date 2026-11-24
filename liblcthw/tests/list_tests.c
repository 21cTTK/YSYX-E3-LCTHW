#include "minunit.h"
#include <lcthw/list.h>

static List *list;
static char *test1 = "test1 data";
static char *test2 = "test2 data";
static char *test3 = "test3 data";

static char *test_create(void)
{
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");
    mu_assert(List_count(list) == 0 && !list->first && !list->last,
            "New list is not empty.");
    return NULL;
}

static char *test_push_pop(void)
{
    List_push(list, test1);
    List_push(list, test2);
    List_push(list, test3);

    mu_assert(List_count(list) == 3, "Wrong count after push.");
    mu_assert(List_first(list) == test1 && List_last(list) == test3, "Wrong endpoints.");
    mu_assert(list->first->next->prev == list->first && list->last->prev->next == list->last,
            "Wrong links.");

    mu_assert(List_pop(list) == test3, "Wrong first value on pop.");
    mu_assert(List_pop(list) == test2, "Wrong second value on pop.");
    mu_assert(List_pop(list) == test1, "Wrong last value on pop.");
    mu_assert(!List_pop(list) && !list->first && !list->last && !List_count(list),
            "List not empty after pop.");
    return NULL;
}

static char *test_unshift(void)
{
    List_unshift(list, test1);
    List_unshift(list, test2);
    List_unshift(list, test3);
    mu_assert(List_count(list) == 3 && List_first(list) == test3 && List_last(list) == test1,
            "Wrong list after unshift.");
    return NULL;
}

static char *test_remove(void)
{
    mu_assert(List_remove(list, list->first->next) == test2, "Wrong removed element.");
    mu_assert(List_count(list) == 2, "Wrong count after remove.");
    mu_assert(list->first->next == list->last && list->last->prev == list->first,
            "Wrong links after remove.");
    return NULL;
}

static char *test_shift(void)
{
    mu_assert(List_shift(list) == test3, "Wrong first value on shift.");
    mu_assert(List_shift(list) == test1, "Wrong second value on shift.");
    mu_assert(!List_shift(list) && !list->first && !list->last && !List_count(list),
            "List not empty after shift.");
    return NULL;
}

static char *test_destroy(void)
{
    char *data = malloc(1);
    mu_assert(data != NULL, "Could not allocate list value.");
    List_push(list, data);
    List_clear(list);
    mu_assert(List_count(list) == 1 && List_first(list) == NULL, "Clear should keep the node.");
    List_clear_destroy(list);
    return NULL;
}

static char *all_tests(void)
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift);
    mu_run_test(test_remove);
    mu_run_test(test_shift);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
