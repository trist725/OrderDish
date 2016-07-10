
#include <stdio.h>
#include <stdlib.h>
#include "globle.h"
#include "file.h"
#include "list.h"	//向内存读入文件中记录时与通用链表交互

/***********************************
功能：
将数据追加到文件的尾部
参数：
data -- 要追加的数据
size -- 缓冲大小
file -- 文件路径
返回值：
1 -- 成功, 0 -- 失败
***********************************/
int FILE_add(void* data, int size, char* file)
{
	FILE* fp;
	if((fp = fopen(file, "a")) != NULL)
	{
		fwrite(data, size, 1, fp);
		fclose(fp);
		return 1;
	}
	else
	{
		return 0;
	}
}

/***********************************
功能：
将文件中第index块的数据重写为data
参数：
data -- 要更新的数据
size -- 缓冲大小
index -- 位置
file -- 文件路径
返回值：
1 -- 成功, 0 -- 失败
***********************************/
int FILE_update(void* data, int size, int index, char* file)
{
	FILE* fp;
	if((fp = fopen(file, "r+")) != NULL)
	{
		fseek(fp, size * (index -1), 0);
		fwrite(data, size, 1, fp);
		fclose(fp);
		return 1;
	}
	else
	{
		return 0;
	}
}

/***********************************
功能：
读取文件中所有内容(可能是结构体),
组成链表,并返回头指针
参数：
size -- 文件中存储的结构体大小
file -- 文件路径
返回值：
返回能指向任意类型地址的void型指针,
它带回了链表的头节点地址,
如果文件打开失败则返回NULL
***********************************/
void* FILE_find_all(int size, char* file)
{
	FILE* fp;
	PNode head;
	void* p;
	if((fp = fopen(file, "r")) != NULL)
	{
		head = LIST_init(NULL);	//调用通用链表模块,初始化头结点
		while(1)
		{
			if(((p = malloc(size)) != NULL) && (fread(p, size, 1, fp) == 1))	//读到最后不够size字节停止,若用feof判断文件末尾会多读
			{	
				LIST_add(p, head);	//数据一个个读入通用链表尾部
			}
			else
			{
				if(p == NULL)
				{
					fclose(fp);
					return NULL;
				}
				else
				{
					free(p);
					fclose(fp);
					return head;
				}	
			}
		}
	}
	else
	{
		return NULL;
	}
}

/***********************************
功能：
将链表中的数据全部写到文件中
参数：
head -- 文件头指针
size -- 结构体大小
file -- 文件路径
返回值：
1 -- 成功, 0 -- 失败
说明:如果文件已经存在,将会被删除重写
***********************************/
int FILE_write_all(PNode head, int size, char* file)
{
	int i;
	int count = LIST_count(head);	//获取链表节点数
	FILE* fp;
	PNode p;
	if((fp = fopen(file, "w")) != NULL)
	{
		for(i = 1; i < count; i++)
		{
			p = LIST_get((i + 1), head);
			{
				fwrite(p ->cmData, size, 1, fp);
			}
		}
		fclose(fp);
		return 1;
	}
	else
	{
		return 0;
	}
}