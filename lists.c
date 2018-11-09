#include<lists.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/mman.h>
list_t *list_new() {
	//return calloc(1, sizeof(list_t));
	return mmap(NULL, sizeof(list_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
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
		munmap(iter->next, sizeof(list_t));//free(iter->next);
		iter->next = NULL;
		return 0;
	} else {
		list_t *backup = iter->next->next;
		munmap(iter->next, sizeof(list_t));
		iter->next = backup;
		return 0;
	}
}
