

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include "globle.h"
#include "public.h"
#include "list.h"
#include "file.h"
#include "SERVER_desk_data.h"


extern PNode head_desk;

////////////////////////////////////////////////////////////////////////
//函数名：SERVER_ipay
//
//函数功能：已买/未买单查询
//			
//函数参数说明:
//
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_ipay()
{
	char acDate[9] = {0};
	char ac1[15] = "bill/";
	char acBillNum[19] = {0};
	int i, j, count, count1, sum = 0, flag, flag0, flag1;
	char ipay;
	PNode head_bill, p, p2;
	struct stBill* p0;
	struct stDesk* p1;
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
				printf("\n\t\t单号\t桌号\t\t状态(0-未买单,1-已买单)\t总金额\n");
				for(i = 1; i < count; i++)
				{
					p = LIST_get(i + 1, head_bill);
					p0 = (struct stBill*)(p ->cmData);
					printf("\n\t\t%s\t%d\t\t%6d\t%d\n", p0 ->acTime, p0 ->DeskNum, p0 ->iPay, p0 ->sum);
				}
				do
				{
					flag = flag1 = 0;
					flag0 = 1;
					printf("\n\n立即买单?\"Y\"\"N\":");
					scanf("%c", &ipay);
					fflush(stdin);
					switch(ipay)
					{
					case 'Y':
						do
						{
							printf("\n请输入您要买的单号:");
							GetStr(acBillNum, 14, 1);
							for(i = 1; i < count; i++)
							{
								p = LIST_get(i + 1, head_bill);
								p0 = (struct stBill*)(p ->cmData);
								if(strcmp(acBillNum, p0 ->acTime) == 0)
								{
									p0 ->iPay = 1;	//支付状态改为已支付
									FILE_update(p0, sizeof(struct stBill), i, ac1);	//更新文件
					/*				LIST_update(void* source, p0, head_bill)*/
//									SERVER_reread_desk();
									count1 = LIST_count(head_desk);
									for(j = 1; j < count1; j++)
									{
										p2 = LIST_get(j + 1, head_desk);
										p1 = (struct stDesk*)(p2 ->cmData);
										if(p0 ->DeskNum == p1 ->nNum)
										{
											p1 ->iStat = 1;	//台桌状态改为可用
											FILE_update(p1, sizeof(struct stDesk), j, "db/desk.dat");	//更新文件
											break;
										}
									}
									flag0 = 0;
									break;
								}
							}
							if(flag0)
							{
								printf("\n无此单号,请重新输入..");
								flag1 = 1;
							}
						}
						while(flag1);
						break;
					case 'y':
						do
						{
							printf("\n请输入您要买的单号:");
							GetStr(acBillNum, 14, 1);
							for(i = 1; i < count; i++)
							{
								p = LIST_get(i + 1, head_bill);
								p0 = (struct stBill*)(p ->cmData);
								if(strcmp(acBillNum, p0 ->acTime) == 0)
								{
									p0 ->iPay = 1;	//支付状态改为已支付
									FILE_update(p0, sizeof(struct stBill), i, ac1);	//更新文件
//									SERVER_reread_desk();
									count1 = LIST_count(head_desk);
									for(j = 1; j < count1; j++)
									{
										p2 = LIST_get(j + 1, head_desk);
										p1 = (struct stDesk*)(p2 ->cmData);
										if(p0 ->DeskNum == p1 ->nNum)
										{
											p1 ->iStat = 1;	//台桌状态改为可用
											FILE_update(p1, sizeof(struct stDesk), j, "db/desk.dat");	//更新文件
											break;
										}
									}
									flag0 = 0;
									break;
								}
							}
							if(flag0)
							{
								printf("\n无此单号,请重新输入..");
								flag1 = 1;
							}
						}
						while(flag1);
						break;
					case 'n':
						printf("\n请按任意键返回..");
						getch();
						return 1;
					case 'N':
						printf("\n请按任意键返回..");
						getch();
						return 1;
					default:
						printf("\n输入错误,请重新输入..");
						flag = 1;
						break;
					}
				}
				while(flag);

			}
			else
			{
				printf("\n未找到记录..\n");
				getch();
				return 1;
			}
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
