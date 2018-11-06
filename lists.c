#include<lists.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
list_t *list_new() {
	return calloc(1, sizeof(list_t));
}
size_t list_add(list_t *list, char *data) {
	if(list == NULL) {
		list = list_new();
		memcpy(list->data, data, 18);
		return 0;
	}
	list_t *iter;
	size_t i = 0;
	for(iter = list; iter->next != NULL; iter = iter->next) {
		i++;
	}
	list_t *new = list_new();
	memcpy(new->data, data, 18);
	iter->next = new;
	return i;
}
int list_get(list_t *list, char *data, size_t n) {
	if(list == NULL) {
		return -1;
	}
	list_t *iter = list;
	for(size_t i = 0; i < n; i++) {
		if(iter->next->next == NULL) {
			return -1;
		}
		iter = iter->next;
	}
	memcpy(data, iter->next->data, 18);
	return 0;
}
ssize_t list_find(list_t *list, char *data) {
	size_t i;
	for(i = 0; memcmp(list->data, data, 18) != 0; i++) {
		if(list->next == NULL) {
			return -1;
		}
		list = list->next;
	}
	return i - 1;
}
int list_delete(list_t *list, size_t n) {
	if(list == NULL) {
		return -1;
	}
	list_t *iter = list;
	size_t i;
	for(i = 0; i < n; i++) {
		if(iter->next->next == NULL) {
			return -1;
		}
		iter = iter->next;
	}
	if(iter->next->next == NULL) {
		free(iter->next);
		iter->next = NULL;
		return 0;
	} else {
		list_t *backup = iter->next->next;
		free(iter->next);
		iter->next = backup;
		return 0;
	}
}
