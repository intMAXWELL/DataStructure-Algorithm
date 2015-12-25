// polynomiallist.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#define     LIST_OK		0
#define     LIST_ERROR	-1
typedef struct polynomiallist
{
	int factor;//ϵ��
	int power;//��
	struct polynomiallist* next;//��һ�ڵ�
}List;

//��ʼ��������һ���ڵ㲻�����洢����
int init_list(List** list)
{
	if (NULL != *list)
	{
		printf("�����ʼ��ʧ�ܣ�/n");
		return LIST_ERROR;
	}
	*list = (List*)malloc(sizeof(List));
	if (NULL == *list)
	{
		printf("�����ڴ����\n");
		return LIST_ERROR;
	}
	(*list)->next = NULL;
	return LIST_OK;
}
//������������ڵ�
int insert_node(List* list, List* node)
{
	if (NULL == list)
	{
		printf("����û�г�ʼ�����޷�����ڵ㣡\n");
		return LIST_ERROR;
	}
	while (NULL != list->next)
	{
		list = list->next;
	}
	list->next = (List*)malloc(sizeof(List));
	if (NULL == list)
	{
		printf("�����ڴ����\n");
		return LIST_ERROR;
	}
	list = list->next;
	list->factor = node->factor;
	list->power = node->power;
	list->next = NULL;
	return LIST_OK;
}
//��������ɾ���ڵ�
int delete_node(List* list, List* node)
{
	List* tmp = NULL;
	if (NULL == list)
	{
		printf("����û�г�ʼ�����޷�ɾ���ڵ㣡\n");
		return LIST_ERROR;
	}
	while (NULL != list->next)
	{
		if ((node->factor == list->next->factor) && (node->power == list->next->power))
		{
			tmp = list->next;
			list->next = list->next->next;
			free(tmp);
			return LIST_OK;
		}
		list = list->next;
	}
	printf("û���ҵ���Ҫɾ���Ľڵ㣡\n");
	return LIST_ERROR;
}
//ɾ������
int delete_list(List** list)
{
	List* tmp = NULL;
	while (NULL != *list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
	return LIST_OK;
}

//������Ԫ�ظ���
int list_cnt(List* list)
{
	int i = 0;
	if (NULL == list)
	{
		return 0;
	}
	while (NULL != list)
	{
		i++;
		list = list->next;
	}
	return i - 1;
}

//��������������ͬ���ϵ���ϲ�
int sort_list(List* list)
{
	//���Ԫ���Ƿ�����
	int sorted = 0;
	List* node;
	List*tmp;
	List* const head = list;
	if (NULL == list)
	{
		printf("����û�г�ʼ�����޷�����\n");
		return LIST_ERROR;
	}

	//��������е�Ԫ�ظ���С��2�����Ͳ���Ҫ����
	if (list_cnt(list)<2)
	{
		return LIST_OK;
	}

	node = head->next;
	head->next = NULL;
	while (NULL != node)
	{
		sorted = 0;
		list = head;
		while (NULL != list->next)
		{
			//�����������ͬ����ϲ�ϵ��
			if (node->power == list->next->power)
			{
				list->next->factor += node->factor;
				node = node->next;
				sorted = 1;
				break;
			}
			else if (node->power>list->next->power)
			{
				tmp = node;
				node = node->next;
				tmp->next = list->next;
				list->next = tmp;
				sorted = 1;
				break;
			}
			list = list->next;
		}

		//���node��������С�������������
		if (0 == sorted)
		{
			tmp = node;
			node = node->next;
			list->next = tmp;
			tmp->next = NULL;
		}
	}
	return LIST_OK;
}

//����ʽ������㣬���������dest�����С�
int mul_poly(List** dest, List** src)
{
	List data;
	//����������洢�˷�������
	List* pNew = NULL;
	List* head1 = *dest;
	List* head2 = *src;
	init_list(&pNew);
	if (0 == list_cnt(*dest) || 0 == list_cnt(*src))
	{
		printf("�޷����ж���ʽ�ĳ˷����㣡\n");
		return LIST_ERROR;
	}
	while (NULL != (*dest)->next)
	{
		while (NULL != (*src)->next)
		{
			data.factor = ((*dest)->next->factor)*((*src)->next->factor);
			data.power = ((*dest)->next->power) + ((*src)->next->power);
			data.next = NULL;
			insert_node(pNew, &data);
			*src = (*src)->next;
		}
		*src = head2;
		*dest = (*dest)->next;
	}
	sort_list(pNew);
	delete_list(&head1);
	delete_list(&head2);
	*dest = pNew;
	return LIST_OK;

}
int display_poly(List* list)
{
	if (0 == list_cnt(list))
	{
		printf("������û��Ԫ�أ��޷������\n");
		return LIST_ERROR;
	}
	if (0 != list->next->power)
	{
		printf("%dX^%d", list->next->factor, list->next->power);
	}
	else
	{
		printf("%d", list->next->factor);
	}
	list = list->next;
	while (NULL != list->next)
	{
		if (list->next->factor>0)
		{
			if (0 == list->next->power)
			{
				printf("+%d", list->next->factor);
			}
			else
			{
				printf("+%dX^%d", list->next->factor, list->next->power);
			}
		}
		else if (list->next->factor<0)
		{
			if (0 == list->next->power)
			{
				if (0 != list->next->factor)
				{
					printf("%d", list->next->factor);
				}
			}
			else
			{
				printf("%dX^%d", list->next->factor, list->next->power);
			}
		}
		list = list->next;
	}
	return LIST_OK;
}
int main(int argc, char *argv[])
{
	int i;
	int n;
	List data;
	List* dest = NULL;
	List* src = NULL;
	init_list(&dest);
	init_list(&src);
	printf("����ʽ1�ж����\n");
	scanf("%d", &n);
	printf("��ֱ��������ʽ1��ϵ�����������м��ÿո������\n");
	for (i = 0; i<n; i++)
	{
		scanf("%d%d", &data.factor, &data.power);
		insert_node(dest, &data);
	}
	printf("����ʽ2�ж����\n");
	scanf("%d", &n);
	printf("��ֱ��������ʽ2��ϵ�����������м��ÿո������\n");
	for (i = 0; i<n; i++)
	{
		scanf("%d%d", &data.factor, &data.power);
		insert_node(src, &data);
	}
	printf("(");
	display_poly(dest);
	printf(")*(");
	display_poly(src);
	printf(")=");
	mul_poly(&dest, &src);
	display_poly(dest);
	printf("\n");
	delete_list(&dest);
	return 0;
}




