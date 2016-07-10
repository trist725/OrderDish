
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
//函数名：SERVER_emp_turnover
//
//函数功能：服务员营业额查询
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
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
	printf("\n请输入您要查询的日期(8位,XXXX年XX月XX日):");
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
				printf("\n未找到记录..\n");
				getch();
				return 1;
			}
			printf("\n\n您该日的总营业额为:%d 单位(人民币:元)", sum);
			printf("\n\n请按任意键继续..");
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
		printf("\n未找到记录..\n");
		getch();
		return 1;
	}
}