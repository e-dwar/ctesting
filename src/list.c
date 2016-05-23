#include <stdlib.h>
#include "list.h"

struct list *
list_empty (void)
{
    return NULL;
}

int
list_is_empty (struct list *list)
{
    return list == NULL;
}

int
list_length (struct list *list)
{
    if (list_is_empty(list)) {
        return 0;
    } else {
        return 1 + list_length(list->next);
    }
}

void
list_push (struct list **list, void *elem)
{
    struct list *h;
    int size = sizeof(struct list);
    h = (struct list *)malloc(size);
    h->value = elem;
    h->next = *list;
    *list = h;
}

void *
list_pop (struct list **list)
{
    if (list_is_empty(*list)) {
        return NULL;
    } else {
        struct list *next = (*list)->next;
        void *value = (*list)->value;
        free(*list);
        *list = next;
        return value;
    }
}

void *
list_remove_where (struct list **list, int (*pred) (void *value))
{
    if (list_is_empty(*list)) {
        return NULL;
    } else if (pred((*list)->value)) {
        return list_pop(list);
    } else {
        list = (struct list **)(&((*list)->next));
        return list_remove_where(list, pred);
    }
}
