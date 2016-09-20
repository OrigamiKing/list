/*
 * clist.h
 *
 *  Created on: 2016年9月17日
 *      Author: shang
 */

#ifndef CLIST_H_
#define CLIST_H_

#include <stdlib.h>

typedef struct CListElmt_
{
	void *data;
	struct CListElmt_ *next;
} CListElmt, *pCListElmt;

typedef struct CList_
{
	int size;
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *data);
	CListElmt *head;
} CList, *pCList;

void clist_init(pCList list, void (*destroy)(void *data));
void clist_destroy(pCList list);
int clist_ins_next(pCList list, pCListElmt element, const void *data);
int clist_rem_next(pCList list, pCListElmt element, void **data);

#define clist_size(list) ((list)->size)
#define clist_head(list) ((list)->head)
#define clist_data(element) ((element)->data)
#define clist_next(element) ((element)->next)

#endif /* CLIST_H_ */
