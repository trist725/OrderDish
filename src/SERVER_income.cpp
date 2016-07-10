

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
//函数名：SERVER_income
//
//函数功能：营收统计
//
//函数参数说明:
//				
//返回值：0 -- 退出 1 -- 返回
////////////////////////////////////////////////////////////////////
int SERVER_income()
{
	char startDate[9] = {0}, endDate[9] = {0};
	struct stIncome *p0;
	PNode p, head_income;
	int count, i;
	long sum = 0;
	FILE* fp;
	printf("\n请输入您要查询的开始日期(8位,XXXX年XX月XX日):");
	GetStr(startDate, 8, 1);
	printf("\n请输入您要查询的结束日期(8位,XXXX年XX月XX日):");
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
			printf("\n该日期段内总营收为:%.2f", sum);
		}
		else
		{
			printf("\n未找到记录..\n");
			getch();
			return 1;
		}
		printf("\n\n您该日的总营业额为:%.2f 单位(人民币:元)", sum);
		printf("\n\n请按任意键继续..");
		getch();
	}
	else
	{
		printf("\n数据库中找不到数据记录..");
		getch();
		return 1;
	}
}