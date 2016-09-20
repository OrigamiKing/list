/*
 * clist.c
 *
 *  Created on: 2016年9月17日
 *      Author: shang
 */

#include <stdlib.h>
#include <string.h>

#include "clist.h"

/**
 * clist_init
 */
void clist_init(pCList list, void (*destroy)(void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;

	return;
}

/**
 * clist_destroy
 */
void clist_destroy(pCList list)
{
	void *data;

	while(clist_size(list) > 0)
	{
		if (clist_rem_next(list, list->head, (void **)&data) == 0
				&& list->destroy != NULL)
		{
			list->destroy(data);
		}
	}

	memset(list, 0, sizeof(CList));
	return;
}

/**
 * clist_ins_next
 */
int clist_ins_next(pCList list, pCListElmt element, const void *data)
{
	pCListElmt new_element;
	if((new_element = (pCListElmt)malloc(sizeof(CListElmt))) == NULL)
		return -1;
	new_element->data = data;
	if(clist_size(list) == 0)
	{
		new_element->next = element->next;
		list->head = new_element;
	}
	else
	{
		new_element->next = element->next;
		element->next = new_element;
	}

	++list->size;
	return 0;
}

int clist_rem_next(pCList list, pCListElmt element, void **data)
{
	pCListElmt old_element;

	if(clist_size(list) == 0)
		return -1;
	*data = element->next->data;
	if(element->next == element)
	{
		old_element = element->next;
		list->head = NULL;
	}
	else
	{
		old_element = element->next;
		element->next = element->next->next;
		if(old_element == clist_head(list))
			list->head = old_element->next;
	}

	free(old_element);

	list->size--;
	return 0;
}
