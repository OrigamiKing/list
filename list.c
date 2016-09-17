/*
 * list.c
 *
 *  Created on: 2016年9月14日
 *      Author: shang
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "list.h"
/**
 * list_init
 * 功能：初始化链表
 */
void list_init(pList list, void (*destroy)(void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;

	return;
}

/**
 * list_destroy
 * 功能：销毁链表
 */
void list_destroy(pList list)
{
	void *data;
	while (list_size(list) > 0)
	{
		if (list_rem_next(list, NULL, (void **) &data)
				== 0&& list->destroy != NULL)
		{
			list->destroy(data);
		}
	}
	memset(list, 0, sizeof(List));
	return;
}

/**
 * list_show
 * 功能：打印链表
 */
void list_print(pList list, void (*display)(void *data))
{
	assert(NULL != display);
	int count;
	pListElmt element = list_head(list);
	for (count = 0; count < list_size(list); ++count)
	{
		display(element->data);
		element = element->next;
	}
	return;
}

/**
 * list_sort
 * 功能：链表排序
 */
void list_sort(pList list, int (*comp)(void *data_a, void *data_b))
{
	assert(comp != NULL);
	if (list_size(list) < 2)
		return;
	pListElmt element;
	pListElmt element_next;
	for (element = list_head(list); element != NULL; element = element->next)
	{
		for (element_next = element->next; element_next != NULL; element_next =
				element_next->next)
		{
			if (comp(element->data, element_next->data)){
				ListElmt element_tmp;
				element_tmp.data = element_next->data;
				element_next->data = element->data;
				element->data = element_tmp.data;
			}
		}
	}

	return;

}

/**
 * list_ins_next
 * 功能：在指定位置后插入数据
 */
int list_ins_next(pList list, pListElmt element, const void *data)
{
	pListElmt new_element;
	if ((new_element = (pListElmt) malloc(sizeof(ListElmt))) == NULL)
		return -1;
	new_element->data = (void *) data;
	if (element == NULL)
	{
		if (list_size(list) == 0)
			list->tail = new_element;
		new_element->next = list->head;
		list->head = new_element;
	}
	else
	{
		if (element->next == NULL)
			list->tail = new_element;
		new_element->next = element->next;
		element->next = new_element;
	}

	++list->size;

	return 0;
}

/**
 * list_rem_next
 */
int list_rem_next(pList list, pListElmt element, void **data)
{
	pListElmt old_element;

	if (list_size(list) == 0)
		return -1;
	if (element == NULL)
	{
		*data = list->head->data;
		old_element = list->head;
		list->head = list->head->next;

		if (list_size(list) == 1)
			list->tail = NULL;
	}
	else
	{
		if (element->next == NULL)
			return -1;
		*data = element->next->data;
		old_element = element->next;
		element->next = element->next->next;

		if (element->next == NULL)
			list->tail = element;
	}

	free(old_element);
	list->size--;
	return 0;
}
