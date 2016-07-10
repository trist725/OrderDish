
#include <stdlib.h>
#include "globle.h"
#include "list.h"

/***********************************
���ܣ�
��ʼ�������ͷ�ڵ�
������
data -- ��Ҫ����Ļ�����
����ֵ��
����ͷ�ڵ�
˵��:
����headͷ��㲻����ʵ������,
��ɴ���NULL����
***********************************/
PNode LIST_init(void* data)
{
	PNode head;

	if((head = (PNode)malloc(sizeof(cmNode))) != NULL)
	{
		head ->cmData = data;
		head ->Next = NULL;
		return head;
	}
	else
	{
		return NULL;
	}
}

/***********************************
���ܣ�
�����ݱ��浽�����β��
������
data -- ��Ҫ���������,�����ǽṹ��
�Ǹ���malloc����Ķѿռ�
head -- �����ͷ�ڵ�
����ֵ��
1 �ɹ� 0 ʧ��
***********************************/
int LIST_add(void* data, PNode head)
{
	PNode p0 = NULL, p = head;

	if((p0 = (PNode)malloc(sizeof(cmNode))) != NULL)
	{
		while((p ->Next) != NULL)	//ֱ������β��
		{
			p = p ->Next;
		}
		p ->Next = p0;
		p0 ->cmData = data;
		p0 ->Next = NULL;
		return 1;
	}
	return 0;
}

/***********************************
���ܣ�
��������Ľڵ�ĸ���
������
Head �����ͷ�ڵ�
����ֵ��
�ڵ����
˵��:
����������ʵ�����ݵ�ͷ���
***********************************/
int LIST_count(PNode head)
{
	int count = 0;
	PNode p = head;

	while(p ->Next != NULL)
	{
		count++;
		p = p ->Next; 
	}
	return (count + 1);
}

/***********************************
���ܣ�
����ָ��λ�õĽڵ�
������
index -- �ڵ��������е��±�
head -- �����ͷ�ڵ�
����ֵ��
�±��Ӧ�Ľڵ��ַ
˵��:
���±����������ʵ�����ݵ�ͷ���
***********************************/
PNode LIST_get(int index, PNode head)
{
	PNode p = head;

	for(; index > 1; index--)
	{
		if(p ->Next != NULL)
		{
			p = p ->Next;
		}
		else
		{
			return p;	//�ýڵ�ǡ�������һ���ڵ�
		}
	}
	return p;
}

/***********************************
���ܣ�
�ͷ���������еĽڵ�,��������������
��ɾ��,ȫ���ͷ�
������	
head -- �����ͷ�ڵ�
����ֵ��
�ͷŵĽڵ���
***********************************/
int LIST_free(PNode head)
{
	int count = 0;
	PNode p = head, p1;
	void* p0;

	while(p ->Next != NULL)
	{
		if((p0 = p ->cmData) != NULL)	//�ͷŲ��ǿ�(head)��������ָ�������
		{
			free(p0);
		}
		p1 = p;
		p = p ->Next;
		free(p1);	//�ͷ�����
		count++;
	}
	free(p);

	return (count + 1);
}

/***********************************
���ܣ�
	ɾ������ĳ�ڵ�(��ɾ��,ֱ���ͷ�)
������	
	data -- Ҫɾ���Ľڵ�
	head -- ����ͷ�ڵ�
����ֵ��
1 �ɹ� 0 ʧ��
Head �����ͷ�ڵ�
����ֵ��
1 �ɹ� 0 ʧ��
***********************************/
int LIST_remove(void* data, PNode head)
{
	PNode p0, p1, p = head;

	while(p ->cmData != data)
	{
		if(p ->Next == NULL)
		{
			return 0;
		}
		p0 = p;
		p = p ->Next;
	}
	free(p ->cmData);
	p1 = p;
	p = p ->Next;
	free(p1);
	p0 ->Next = p;
	return 1;
}

/***********************************
���ܣ�
	��������ĳ�ڵ�
������	
	source -- Ҫ���µ�����
	dest -- ����Ϊ������
	head -- ����ͷ�ڵ�
����ֵ��
1 �ɹ� 0 ʧ��
Head �����ͷ�ڵ�
����ֵ��
1 �ɹ� 0 ʧ��
***********************************/
int LIST_update(void* source, void* dest, PNode head)
{
	PNode p = head;

	while(p ->cmData != source)
	{
		if(p ->Next == NULL)
		{
			return 0;
		}
		p = p ->Next;
	}
	p ->cmData = dest;
	return 1;
}