#include<lists.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/mman.h>

#include     <stdio.h>
list_t *list_new() {
	//return calloc(1, sizeof(list_t));
	list_t *new = mmap(NULL, sizeof(list_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	memset(new, 0, sizeof(list_t));
	return new;
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
	return i + 1;
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
	ssize_t i;
	list_t *iter = list;
	for(i = 0; memcmp(iter->data, data, 18) != 0; i++) {
		if(iter->next == NULL) {
			return -1;
		}
		iter = iter->next;
	}
	return i - 1;
}
int list_delete(list_t *list, size_t n) {
	if(list == NULL) {
		return -1;
	}
	list_t *iter = list;
	size_t i;
	for(i = 0; i < n - 1; i++) {
		iter = iter->next;
		if(iter->next == NULL) {
			return -1;
		}
	}
	if(iter->next->next == NULL) { //if the last item is being deleted
		munmap(iter->next, sizeof(list_t));
		iter->next = NULL;
		return 0;
	} else {
		list_t *new = iter->next->next;
		munmap(iter->next, sizeof(list_t));
		iter->next = new;
		return 0;
	}
}
