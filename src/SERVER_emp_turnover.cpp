
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <io.h>

#include "globle.h"
#include "list.h"
#include "file.h"
#include "public.h"
#include "SERVER_emp_turnover.h"

extern char acInput_Emp_Num[MAX_INPUT + 1];
////////////////////////////////////////////////////////////////////////
//��������SERVER_emp_turnover
//
//�������ܣ�����ԱӪҵ���ѯ
//			
//��������˵��:
//					 
//����ֵ��0 -- ���� 1 -- ����
///////////////////////////////////////////////////////////////////////
int SERVER_emp_turnover()
{
	char acDate[9] = {0};
	char ac1[15] = "bill/";
	int i, count, sum = 0;
	PNode head_bill, p;
	struct stBill* p0;
	FILE* fp;
	system("cls");
	printf("\n��������Ҫ��ѯ������(8λ,XXXX��XX��XX��):");
	GetStr(acDate, 8, 1);
	strcat(ac1, acDate);
	if(0 == access(ac1, 0))
	{
		if((fp = fopen(ac1, "r")) != NULL)
		{
			head_bill = (PNode)FILE_find_all(sizeof(struct stBill), ac1);
			fclose(fp);
			count = LIST_count(head_bill);
			if(count > 1)
			{
				for(i = 1; i < count; i++)
				{
					p = LIST_get(i + 1, head_bill);
					p0 = (struct stBill*)(p ->cmData);
					if(strcmp(p0 ->nEmpNum, acInput_Emp_Num) == 0)
					{
						sum += p0 ->sum;
					}
				}
			}
			else
			{
				printf("\nδ�ҵ���¼..\n");
				getch();
				return 1;
			}
			printf("\n\n�����յ���Ӫҵ��Ϊ:%d ��λ(�����:Ԫ)", sum);
			printf("\n\n�밴���������..");
			getch();
		}
		else
		{
			printf("\nfile open error!");
			getch();
			exit(1);
		}
	}
	else
	{
		printf("\nδ�ҵ���¼..\n");
		getch();
		return 1;
	}
}