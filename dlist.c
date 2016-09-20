/*
 * dlist.c
 *
 *  Created on: 2016年9月16日
 *      Author: shang
 */
#include <stdlib.h>
#include <string.h>
#include "dlish.h"

/**
 * dlist_init
 * 功能：初始化链表
 */
void dlist_init(pDList list, void (*destroy)(void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;

	return;
}

/**
 * dlist_destroy
 * 功能：销毁链表
 */
void dlist_destroy(pDList list)
{
	void *data;
	while (dlist_size(list) > 0)
	{
		if (dlist_remove(list, NULL, (void **) &data)
				== 0&& list->destroy != NULL)
		{
			list->destroy(data);
		}
	}
	memset(list, 0, sizeof(DList));
	return;
}

/**
 * dlist_ins_next
 * 功能：在指定位置后插入数据
 */
int dlist_ins_next(pDList list, pDListElmt element, const void *data)
{
	pDListElmt new_element;
	if(element == NULL && dlist_size(list) != 0)
		return -1;
	if ((new_element = (pDListElmt) malloc(sizeof(DListElmt))) == NULL)
		return -1;
	new_element->data = (void*) data;

	if(dlist_size(list) == 0)
	{
		list->head = new_element;
		list->head->prev = NULL;
		list->head->next = NULL;
		list->tail = new_element;
	}
	else
	{
		new_element->next = element->next;
		new_element->prev = element;

		if(element->next == NULL)
			list->tail = new_element;
		else
			element->next->prev = new_element;
		element->next = new_element;
	}

	++list->size;
	return 0;
}

/**
 * dlist_ins_prev
 * 功能：在指定位置前插入数据
 */
int dlist_ins_prev(pDList list, pDListElmt element, const void *data)
{
	DListElmt *new_element;

	if(element == NULL && dlist_size(list) != 0	)
		return -1;

	if((new_element = (pDListElmt)malloc(sizeof(DListElmt))) == NULL)
		return -1;

	new_element->data = (void *)data;
	if(dlist_size(list) == 0)
	{
		list->head = new_element;
		list->head->prev = NULL;
		list->head->next = NULL;
		list->tail = new_element;
	}
	else
	{
		new_element->next = element;
		new_element->prev = element->prev;
		if(element->prev == NULL)
			list->head = new_element;
		else
			element->prev->next = new_element;
	}

	++list->size;
	return 0;
}

/**
 * dlist_remove
 * 功能：删除指定位置数据
 */
int dlist_remove(pDList list, pDListElmt element, void **data)
{
	if(element == NULL || dlist_size(list) == 0)
		return -1;
	*data = element->data;

	if(element == list->head)
	{
		list->head = element->next;
		if(list->head == NULL)
			list->tail = NULL;
		else
			element->next->prev = NULL;
	}
	else
	{
		element->prev->next = element->next;
		if(element->next == NULL)
			list->tail = element->prev;
		else
			element->next->prev = element->prev;
	}

	free(element);

	list->size--;
	return 0;
}

