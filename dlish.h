/*
 * dlish.h
 *
 *  Created on: 2016年9月16日
 *      Author: shang
 */

#ifndef DLISH_H_
#define DLISH_H_

#include <stdlib.h>

typedef struct DListElmt_
{
	void *data;
	struct DListElmt_ *prev;
	struct DListElmt_ *next;
} DListElmt, *pDListElmt;

typedef struct DList_
{
	int size;
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *data);

	pDListElmt head;
	pDListElmt tail;
} DList, *pDList;

void dlist_init(pDList list, void (*destroy)(void *data));
void dlist_destroy(pDList list);
int dlist_ins_next(pDList list, pDListElmt element, const void *data);
int dlist_ins_prev(pDList list, pDListElmt element, const void *data);
int dlist_remove(pDList list, pDListElmt element, void **data);

#define dlist_size(list) ((list)->size)
#define dlist_head(list) ((list)->head)
#define dlist_tail(list) ((list)->tail)
#define dlist_is_head(element) ((element)->prev == NULL ? 1 : 0)
#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define dlist_data(element) ((element)->data)
#define dlist_next(element) ((element)->next)
#define dlist_prev(element) ((element)->prev)

#endif /* DLISH_H_ */
