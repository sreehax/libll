#include<stddef.h>
#include<sys/types.h>
#ifndef LISTS_H_
#define LISTS_H_
typedef struct list {
	char data[18];
	struct list *next;
} list_t;

list_t *list_new();
size_t list_add(list_t *list, char *data);
int list_get(list_t *list, char *data, size_t n);
ssize_t list_find(list_t *list, char *data);
int list_delete(list_t *list, size_t n);
#endif
