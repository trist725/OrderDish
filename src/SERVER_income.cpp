

#include <stdio.h>
#include <conio.h>
//#include <stdlib.h>
#include <io.h>
#include "globle.h"
#include "string.h"
#include "list.h"
#include "public.h"
#include "file.h"
#include "SERVER_income.h"



/////////////////////////////////////////////////////////////////////
//��������SERVER_income
//
//�������ܣ�Ӫ��ͳ��
//
//��������˵��:
//				
//����ֵ��0 -- �˳� 1 -- ����
////////////////////////////////////////////////////////////////////
int SERVER_income()
{
	char startDate[9] = {0}, endDate[9] = {0};
	struct stIncome *p0;
	PNode p, head_income;
	int count, i;
	long sum = 0;
	FILE* fp;
	printf("\n��������Ҫ��ѯ�Ŀ�ʼ����(8λ,XXXX��XX��XX��):");
	GetStr(startDate, 8, 1);
	printf("\n��������Ҫ��ѯ�Ľ�������(8λ,XXXX��XX��XX��):");
	GetStr(endDate, 8, 1);
	if(0 == access("db/income.dat", 0))
	{
		if((fp = fopen("db/income.dat", "r")) != NULL)
		{
			head_income = (PNode)FILE_find_all(sizeof(struct stIncome), "db/income.dat");
			fclose(fp);
			count = LIST_count(head_income);
			for(i = 1; i < count; i++)
			{
				p = LIST_get(i + 1, head_income);
				p0 = (struct stIncome*)(p ->cmData);
				if(strcmp(p0 ->acDate, startDate) == 0)
				{
					sum += p0 ->fSum;
					if(strcmp(p0 ->acDate, endDate) == 0)
					{
						break;
					}
					else
					{
						continue;
					}
				}
			}
			printf("\n�����ڶ�����Ӫ��Ϊ:%.2f", sum);
		}
		else
		{
			printf("\nδ�ҵ���¼..\n");
			getch();
			return 1;
		}
		printf("\n\n�����յ���Ӫҵ��Ϊ:%.2f ��λ(�����:Ԫ)", sum);
		printf("\n\n�밴���������..");
		getch();
	}
	else
	{
		printf("\n���ݿ����Ҳ������ݼ�¼..");
		getch();
		return 1;
	}
}