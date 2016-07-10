
#include <stdlib.h>
#include "globle.h"
#include "list.h"

/***********************************
功能：
初始化链表的头节点
参数：
data -- 需要保存的缓冲区
返回值：
返回头节点
说明:
若让head头结点不保存实际数据,
则可传入NULL参数
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
功能：
将数据保存到链表的尾部
参数：
data -- 需要保存的数据,可能是结构体
是个用malloc分配的堆空间
head -- 链表的头节点
返回值：
1 成功 0 失败
***********************************/
int LIST_add(void* data, PNode head)
{
	PNode p0 = NULL, p = head;

	if((p0 = (PNode)malloc(sizeof(cmNode))) != NULL)
	{
		while((p ->Next) != NULL)	//直到链表尾部
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
功能：
返回链表的节点的个数
参数：
Head 链表的头节点
返回值：
节点个数
说明:
包含不保存实际数据的头结点
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
功能：
返回指定位置的节点
参数：
index -- 节点在链表中的下标
head -- 链表的头节点
返回值：
下标对应的节点地址
说明:
该下标包含不保存实际数据的头结点
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
			return p;	//该节点恰好是最后一个节点
		}
	}
	return p;
}

/***********************************
功能：
释放链表的所有的节点,包括主链和子链
真删除,全部释放
参数：	
head -- 链表的头节点
返回值：
释放的节点数
***********************************/
int LIST_free(PNode head)
{
	int count = 0;
	PNode p = head, p1;
	void* p0;

	while(p ->Next != NULL)
	{
		if((p0 = p ->cmData) != NULL)	//释放不是空(head)的数据域指向的子链
		{
			free(p0);
		}
		p1 = p;
		p = p ->Next;
		free(p1);	//释放主链
		count++;
	}
	free(p);

	return (count + 1);
}

/***********************************
功能：
	删除链表某节点(真删除,直接释放)
参数：	
	data -- 要删除的节点
	head -- 链表头节点
返回值：
1 成功 0 失败
Head 链表的头节点
返回值：
1 成功 0 失败
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
功能：
	更新链表某节点
参数：	
	source -- 要更新的数据
	dest -- 更新为该数据
	head -- 链表头节点
返回值：
1 成功 0 失败
Head 链表的头节点
返回值：
1 成功 0 失败
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