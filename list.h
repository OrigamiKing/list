/*
 * list.h
 *
 *  Created on: 2016年9月14日
 *      Author: shang
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>

typedef struct ListElmt_
{
	void *data;
	struct ListElmt_ *next;
} ListElmt, *pListElmt;

typedef struct List_
{
	int size;
	int	(*match)(const void *key1, const void *key);
	void (*destroy)(void *data);

	pListElmt head;
	pListElmt tail;
} List, *pList;

void list_init(pList list, void (*destroy)(void *data));
void list_destroy(pList list);
void list_print(pList list, void (*display)(void *data));
void list_sort(pList list, int (*comp)(void *data_a, void *data_b));
int list_ins_next(pList list, pListElmt element, const void *data);
int list_rem_next(pList list, pListElmt element, void **data);

#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_is_head(list, element) ((element) == (list)->head ? 1: 0)
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define list_data(element) ((element)->data)
#define list_next(element) ((element)->next)

#endif /* LIST_H_ */
