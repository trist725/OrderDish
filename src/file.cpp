
#include <stdio.h>
#include <stdlib.h>
#include "globle.h"
#include "file.h"
#include "list.h"	//���ڴ�����ļ��м�¼ʱ��ͨ��������

/***********************************
���ܣ�
������׷�ӵ��ļ���β��
������
data -- Ҫ׷�ӵ�����
size -- �����С
file -- �ļ�·��
����ֵ��
1 -- �ɹ�, 0 -- ʧ��
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
���ܣ�
���ļ��е�index���������дΪdata
������
data -- Ҫ���µ�����
size -- �����С
index -- λ��
file -- �ļ�·��
����ֵ��
1 -- �ɹ�, 0 -- ʧ��
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
���ܣ�
��ȡ�ļ�����������(�����ǽṹ��),
�������,������ͷָ��
������
size -- �ļ��д洢�Ľṹ���С
file -- �ļ�·��
����ֵ��
������ָ���������͵�ַ��void��ָ��,
�������������ͷ�ڵ��ַ,
����ļ���ʧ���򷵻�NULL
***********************************/
void* FILE_find_all(int size, char* file)
{
	FILE* fp;
	PNode head;
	void* p;
	if((fp = fopen(file, "r")) != NULL)
	{
		head = LIST_init(NULL);	//����ͨ������ģ��,��ʼ��ͷ���
		while(1)
		{
			if(((p = malloc(size)) != NULL) && (fread(p, size, 1, fp) == 1))	//������󲻹�size�ֽ�ֹͣ,����feof�ж��ļ�ĩβ����
			{	
				LIST_add(p, head);	//����һ��������ͨ������β��
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
���ܣ�
�������е�����ȫ��д���ļ���
������
head -- �ļ�ͷָ��
size -- �ṹ���С
file -- �ļ�·��
����ֵ��
1 -- �ɹ�, 0 -- ʧ��
˵��:����ļ��Ѿ�����,���ᱻɾ����д
***********************************/
int FILE_write_all(PNode head, int size, char* file)
{
	int i;
	int count = LIST_count(head);	//��ȡ����ڵ���
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