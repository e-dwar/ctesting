#ifndef LIST_H
#define LIST_H

struct list {
    void *value;
    void *next;
};

struct list * list_empty (void);
int list_is_empty (struct list *list);
int list_length (struct list *list);
void list_push (struct list **list, void *elem);
void * list_pop (struct list **list);
void * list_remove_where (struct list **list, int (*pred) (void *value));

#endif
