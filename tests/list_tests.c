#include "../src/test.h"
#include "../src/list.h"
#include "list_tests_internals.h"
#include "list_tests.h"

/* main */

void
list_tests (void)
{
    test_print_h2(
        "List tests"
    );
    test_run(5, (test_t[]){
        list_tests_init,
        list_tests_pop,
        list_tests_push_push,
        list_tests_push_pop,
        list_tests_remove
    });
}

/* tests */

int
list_tests_init (void)
{
    /* init */

    struct list *list;
    list = list_empty();

    /* tests */

    test_print_intro(
        "Initializing"
    );

    return
    test_should(
        "yield an empty list",
        list_is_empty(list)
    )
    & test_should(
        "yield a list of 0 element",
        list_length(list) == 0
    );
}

int
list_tests_pop (void)
{
    /* init */

    struct list *list = list_empty();
    list_pop(&list);

    /* tests */

    test_print_intro(
        "Poping an empty list"
    );

    return
    test_should(
        "yield an empty list",
        list_is_empty(list)
    );
}

int
list_tests_push_push (void)
{
    /* init */

    int check_order = 1;
    int i = 1, ints[] = { 1, 2 };
    struct list *next, *list;
    list = list_empty();
    list_push(&list, ints + 0);
    list_push(&list, ints + 1);

    next = list;
    while (check_order && !list_is_empty(next)) {
        check_order = check_order && (
            next->value == (
                (void *)(ints + (i--))
            )
        );
        next = (struct list *)(
            next->next
        );
    }

    /* tests */

    test_print_intro(
        "Pushing two elements"
    );

    return
    test_should(
        "not yield an empty list",
        !list_is_empty(list)
    )
    & test_should(
        "yield a list of 2 elements",
        list_length(list) == 2
    )
    & test_should(
        "push in the correct order",
        check_order
    );
}

int
list_tests_push_pop (void)
{
    /* init */

    int *popped, pushed = 1;
    struct list *list = list_empty();
    list_push(&list, &pushed);
    popped = (int *)list_pop(&list);

    /* tests */

    test_print_intro(
        "Pushing and poping one element"
    );

    return
    test_should(
        "yield an empty list",
        list_is_empty(list)
    )
    & test_should(
        "yield a list of 0 element",
        list_length(list) == 0
    )
    & test_should(
        "pop the pushed element",
        popped == &pushed
        && *popped == pushed
    );
}

int
list_tests_remove (void)
{
    /* init */

    int i, check_elems = 1;
    int ints[] = { 1, 2, 3 };
    struct list *list, *next;
    list = list_empty();
    list_push(&list, ints + 0);
    list_push(&list, ints + 1);
    list_push(&list, ints + 2);
    i = *((int *)list_remove_where(
        &list, list_tests_predicate
    ));

    next = list;
    while (check_elems && !list_is_empty(next)) {
        check_elems = check_elems && ((
            *((int *)(next->value)) == ints[0]
        ) || (
            *((int *)(next->value)) == ints[2]
        ));
        next = (struct list *)(
            next->next
        );
    }

    /* tests */

    test_print_intro(
        "Removing the second of three elements"
    );

    return
    test_should(
        "yield a list of 2 elements",
        list_length(list) == 2
    )
    & test_should(
        "yield a list with elements 1 and 3",
        check_elems
    )
    & test_should(
        "pop the second element",
        i == ints[1]
    );
}

int
list_tests_predicate (void *value)
{
    return *((int *)value) == 2;
}
