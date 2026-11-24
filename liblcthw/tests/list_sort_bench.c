#include <lcthw/list_algos.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

static int compare(const void *a, const void *b)
{
    unsigned int left = *(const unsigned int *)a;
    unsigned int right = *(const unsigned int *)b;
    return (left > right) - (left < right);
}

int main(void)
{
    const int sizes[] = { 128, 512, 2048, 8192 };
    uint32_t seed = 1;
    puts("size,bubble_ms,merge_ms");

    for (size_t i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        int size = sizes[i];
        unsigned int *values = malloc(size * sizeof(*values));
        List *input = List_create();
        if (!values || !input) {
            free(values);
            if (input)
                List_destroy(input);
            return 1;
        }

        for (int j = 0; j < size; j++) {
            seed = seed * UINT32_C(1664525) + UINT32_C(1013904223);
            values[j] = seed;
            List_push(input, &values[j]);
        }
        List *bubble = List_copy(input);
        if (!bubble || List_count(bubble) != size) {
            if (bubble)
                List_destroy(bubble);
            List_destroy(input);
            free(values);
            return 1;
        }

        clock_t start = clock();
        List_bubble_sort(bubble, compare);
        clock_t bubble_time = clock() - start;

        start = clock();
        List *merge = List_merge_sort(input, compare);
        clock_t merge_time = clock() - start;

        int ok = merge && List_count(merge) == size;
        if (ok) {
            ListNode *other = merge->first;
            LIST_FOREACH(bubble, first, next, cur) {
                if (compare(cur->value, other->value) != 0)
                    ok = 0;
                other = other->next;
            }
        }

        if (merge)
            List_destroy(merge);
        List_destroy(bubble);
        List_destroy(input);
        free(values);
        if (!ok)
            return 1;

        printf("%d,%.3f,%.3f\n", size,
                1000.0 * bubble_time / CLOCKS_PER_SEC,
                1000.0 * merge_time / CLOCKS_PER_SEC);
    }
    return 0;
}
