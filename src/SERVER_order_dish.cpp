
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include "globle.h"
#include "server.h"
#include "string.h"
#include "list.h"
#include "public.h"
#include "file.h"
#include "SERVER_order_dish.h"
#include "SERVER_emp_data.h"
#include "SERVER_desk_data.h"
#include "SERVER_menu_data.h"


extern PNode head_desk;
extern PNode head_menu;
extern int desk_db_exists;
extern int menu_db_exists;
extern char acInput_Emp_Num[MAX_INPUT + 1];
PNode head_order_bill;	//订单链表
PNode head_tmp_order;	//临时点菜链表
/////////////////////////////////////////////////////////////////////
//函数名：SERVER_open_desk
//
//函数功能：开桌
//
//函数参数说明:
//				
//返回值：0 -- 退出 1 -- 返回
////////////////////////////////////////////////////////////////////
int SERVER_open_desk()
{
	//SERVER_reread_desk();
	if((0 == desk_db_exists))
	{
		int Dcount = LIST_count(head_desk);
		if(Dcount > 1)
		{
			int count, i, flag = 1, open_desk;
			char cAffirm;
			struct stDesk* p0;
			PNode p;
			system("cls");
			printf("\t\t桌号\t状态\t\t描述\n");
			count = LIST_count(head_desk);
			for(i = 1; i < count; i++)	//i=1是为了排除head
			{
				p = LIST_get(i + 1, head_desk);	//获取链表中的结点
				p0 = (struct stDesk*)(p ->cmData);	//强制转换数据域为实际类型
				printf("\t\t%0004d\t%d\t\t%s\n", p0 ->nNum, p0 ->iStat, p0 ->acInfo);	//打印台桌信息
			}
			do
			{
				flag = 0;
				printf("\n\t\t请输入您要开的桌号或者输入0退出:");
				scanf("%d", &open_desk);
				fflush(stdin);
				if(0 == open_desk)
				{
					return 1;
				}
				else
				{
					for(i = 1; i < count; i++)	//i=1是为了排除head
					{
						p = LIST_get(i + 1, head_desk);	//获取链表中的结点
						p0 = (struct stDesk*)(p ->cmData);	//强制转换数据域为实际类型
						if((open_desk == p0 ->nNum) && (1 == p0 ->iStat))
						{
							p0 ->iStat = 0;
							p0 ->iOrder = 0;
							FILE_update(p0, sizeof(struct stDesk), i, "db/desk.dat");	//同步更新文件
							printf("\n开桌成功!是否立即点菜?\"Y\"或\"N\":");						
							do
							{
								scanf("%c", &cAffirm);
								fflush(stdin);
								switch(cAffirm)
								{
								case 'y':
									SERVER_order_dish(1, open_desk);			
								case 'Y':
									SERVER_order_dish(1, open_desk);
								case 'n':
									return 1;
								case 'N':
									return 1;
								default:
									printf("\n输入错误,请重新输入:");
									flag = 1;
									break;
								}
							}
							while(flag);
						}
						else
							if((open_desk == p0 ->nNum) && (0 == p0 ->iStat))
							{
								printf("\n该台桌当前不可用,请选择其它台桌..");
								getch();
								flag = 1;
								break;
							}
					}
					if(!flag)
					{
						printf("\n你要开的桌号不存在,请重新输入..");
						getch();
						flag = 1;
					}
				}
			}
			while(flag);
		}
		else
		{
			printf("数据库中缺少必要的数据,无法执行该操作..");
			getch();
			return 1;
		}
	}
	else
	{
		printf("数据库中缺少必要的数据,无法执行该操作..");
		getch();
		return 1;
	}
}

/////////////////////////////////////////////////////////////////////
//函数名：SERVER_order_dish
//
//函数功能：点菜
//
//函数参数说明:
//				mode:0--直接点菜,1--从开桌进入点菜
//
//返回值：0 -- 结束 1 -- 返回
////////////////////////////////////////////////////////////////////
int SERVER_order_dish(int mode, int desk)
{	
	//SERVER_reread_desk();	//重读数据
	//SERVER_reread_menu();
	int Mcount = LIST_count(head_menu);	//获取数据数
	int Dcount = LIST_count(head_desk);

	if((0 == desk_db_exists)	//判断是否有数据
		&& (0 == menu_db_exists)
		&& (Mcount > 1)
		&& (Dcount > 1))
	{
		head_order_bill = LIST_init(NULL);	//订单链表初始化
		head_tmp_order = LIST_init(NULL);	//临时点菜链表初始化
		int order_num, num, n, flag, flag1, flag2, flag3, flag4, flag5, flag6, i, j, cho, count, count1, desk_num;
		float sum = 0;
		struct stOrder* p2;
		struct stMenu* p0;
		struct stDesk* p1;
		PNode p, p3;
		if(mode)	//从开桌进入点菜
		{
			flag3 = 1;
			if(flag3)
			{
				system("cls");
				printf("\n\n");
				Print_Str_Center("点菜界面");
				printf("\n\n\t\t菜编号\t菜名\t\t价格");
				count = LIST_count(head_menu);
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_menu);	//获取链表中的结点
					p0 = (struct stMenu*)(p ->cmData);	//强制转换数据域为实际类型
					printf("\n\t\t%00005d\t%s\t%.2f\t\n", p0 ->nNum, p0 ->acName, p0 ->fPrice);	//列出菜谱
				}
			}
			do
			{
				flag2 = 0;
rechoice:			printf("\n\n请选择(0.返回 1.加菜 2.减菜 3.确认(生成订单)):");
				scanf("%d", &cho);
				fflush(stdin);
				switch(cho)
				{
				case 0: return 1;
				case 1:
					do
					{
						flag = 1; flag4 = 1;
						printf("\n\n请输入您要点的菜的编号:");
						scanf("%d", &order_num);
						fflush(stdin);
						printf("\n请输入您要点的菜的份数:");
						scanf("%d", &num);
						fflush(stdin);
						for(i = 1; i < count; i++)	//i=1是为了排除head
						{
							p = LIST_get(i + 1, head_menu);
							p0 = (struct stMenu*)(p ->cmData);
							if(order_num == p0 ->nNum)	//如果这道菜存在
							{	
								flag3 = 0;
								flag4 = 0;
								flag1 = 1;
								count1 = LIST_count(head_tmp_order);
								for(j = 1; j < count1; j++)
								{
									p3 = LIST_get(j + 1, head_tmp_order);
									p2 = (struct stOrder*)(p3 ->cmData);
									if(order_num == p2 ->nNum)	//如果已点
									{
										p2 ->nNum += num;
										sum += (p2 ->Menu_T.fPrice * num);
										LIST_update(p3 ->cmData, p2, head_tmp_order);
										flag1 = 0;
										break;
									}
								}
								if(flag1)	//如果未点
								{
									p2 = (struct stOrder*)malloc(sizeof(struct stOrder));
									p2 ->Menu_T = *p0;
									p2 ->nNum = num;
									sum += (p2 ->Menu_T.fPrice * num);
									LIST_add(p2, head_tmp_order);	//加入临时点菜链表
									p2 ->Menu_T.iStat = 1;
								}
								system("cls");
								printf("\t总金额:%.2f", sum);
								printf("\n\n");
								Print_Str_Center("点菜界面");
								printf("\n\n\t\t菜编号\t菜名\t\t价格\t份数");

								for(i = 1; i < count; i++)
								{
									flag5 = 1;
									p = LIST_get(i + 1, head_menu);
									p0 = (struct stMenu*)(p ->cmData);
									count1 = LIST_count(head_tmp_order);
									for(j = 1; j < count1; j++)
									{
										p3 = LIST_get(j + 1, head_tmp_order);
										p2 = (struct stOrder*)(p3 ->cmData);
										if(p0 ->nNum == p2 ->Menu_T.nNum)
										{
											printf("\n\t*\t%00005d\t%s\t%.2f\t%d\n", p0 ->nNum, p0 ->acName, p0 ->fPrice, p2 ->nNum);//检查该菜是否已点,已点则在编号前加个*号
											flag5 = 0;
											break;
										}
									}		
									if(flag5)
									{	
										printf("\n\t\t%00005d\t%s\t%.2f\t%d\n", p0 ->nNum, p0 ->acName, p0 ->fPrice, 0);
									}
								}
							}
						}
						if(flag4)
						{
							printf("\n您输入的菜编号不存在,请重新输入..");
							flag = 1;
							getch();
						}
						else
						{
							flag6 = 0;
							do
							{
								printf("\n0--返回,1--继续:");
								scanf("%d", &n);
								fflush(stdin);		
								switch(n)	//输入校验
								{
								case 0: goto rechoice;
								case 1: break;
								default:
									printf("\n输入错误,请重新输入!");
									flag6 = 1;
									break;
								}
							}while(flag6);
						}
					}while(flag);
					break;
				case 2:
					do
					{
rescan:			flag = 0; flag4 = 1;
						printf("\n\n请输入您要减的菜的编号或者输入0返回:");
						scanf("%d", &order_num);
						fflush(stdin);
						if(0 == order_num)
						{
							return 1;
						}
						else
						{
							printf("\n请输入您要减的菜的份数:");
							scanf("%d", &num);
							fflush(stdin);
							for(i = 1; i < count; i++)	//i=1是为了排除head
							{
								p = LIST_get(i + 1, head_menu);
								p0 = (struct stMenu*)(p ->cmData);
								if(order_num == p0 ->nNum)	//如果这道菜存在
								{	
									flag4 = 0;
									flag1 = 1;
									count1 = LIST_count(head_tmp_order);
									for(j = 1; j < count1; j++)
									{
										p3 = LIST_get(j + 1, head_tmp_order);
										p2 = (struct stOrder*)(p3 ->cmData);
										if(p0 ->nNum == p2 ->nNum)	//如果已点
										{
											if(p2 ->nNum >= num)	//校验减的份数是否多于已点的份数
											{
												p2 ->nNum -= num;
												sum -= (p2 ->Menu_T.fPrice * num);
												flag1 = 0;
												break;
											}
											else
											{
												printf("\n您只点了%d份,不能减%d份..", p2 ->nNum, num);
												goto rescan;	//返回重新输入份数
											}
										}
									}
									if(flag1)	//如果未点
									{
										printf("\n这道菜您还未点...");
										goto rescan;	//返回重新输入份数
									}
									system("cls");
									printf("\n\n");
									Print_Str_Center("点菜界面");
									printf("\n\n\t\t菜编号\t菜名\t\t价格\t份数");

									for(i = 1; i < count; i++)
									{
										flag5 = 1;
										p = LIST_get(i + 1, head_menu);
										p0 = (struct stMenu*)(p ->cmData);
										count1 = LIST_count(head_tmp_order);
										for(j = 1; j < count1; j++)
										{
											p3 = LIST_get(j + 1, head_tmp_order);
											p2 = (struct stOrder*)(p3 ->cmData);
											if(p0 ->nNum == p2 ->Menu_T.nNum)
											{
												printf("\n\t*\t%00005d\t%s\t%.2f\t%d\n", p0 ->nNum, p0 ->acName, p0 ->fPrice, p2 ->nNum);//检查该菜是否已点,已点则在编号前加个*号
												flag5 = 0;
												break;
											}
										}		
										if(flag5)
										{	
											printf("\n\t\t%00005d\t%s\t%.2f\t%d\n", p0 ->nNum, p0 ->acName, p0 ->fPrice, 0);
										}
									}
								}
							}
							if(flag4)
							{
								printf("\n您输入的菜编号不存在,请重新输入..");
								flag = 1;
								getch();
							}
							else
							{
								flag6 = 0;
								do
								{
									printf("\n0--返回,1--继续:");
									scanf("%d", &n);
									fflush(stdin);		
									switch(n)	//输入校验
									{
									case 0: goto rechoice;
									case 1: break;
									default:
										printf("\n输入错误,请重新输入!");
										flag6 = 1;
										break;
									}
								}while(flag6);
							}
						}
					}while(flag);
					break;
				case 3:
					if(sum > 0)
					{
						count = LIST_count(head_desk);
						for(i = 1; i < count; i++)	//i=1是为了排除head
						{
							p = LIST_get(i + 1, head_desk);
							p1 = (struct stDesk*)(p ->cmData);
							if(desk == p1 ->nNum)
							{
								p1 ->iStat = 1;	//台桌状态改为已点菜
								break;
							}
						}
						SERVER_creat_bill(desk, sum);
						printf("\n点菜成功!祝您快乐用餐..");
						getch();
						return 1;
					}
					else
					{
						printf("\n请您点菜后再确认生成订单..");
						break;
					}
				default: 
					printf("\n输入错误,请重新输入");
					flag2 = 1;
					break;
				}
			}while(flag2);
		}
		else	//直接点菜
		{
			int Dcount = LIST_count(head_desk);
			if(Dcount > 1)
			{
				int count, i, flag = 1;
				char cAffirm;
				struct stDesk* p0;
				PNode p;
				system("cls");
				printf("\t\t桌号\t状态\t\t描述\n");
				count = LIST_count(head_desk);
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_desk);	//获取链表中的结点
					p0 = (struct stDesk*)(p ->cmData);	//强制转换数据域为实际类型
					printf("\t\t%0004d\t%d\t\t%s\n", p0 ->nNum, p0 ->iStat, p0 ->acInfo);	//打印台桌信息
				}
				do
				{
					flag = 0;
					printf("\n\t如果您未开桌,请先开桌,如果您已经开桌,请输入桌号或者输入0返回:");
					scanf("%d", &desk_num);
					fflush(stdin);
					if(0 == desk_num)
					{
						return 1;
					}
					else
					{
						for(i = 1; i < count; i++)	//i=1是为了排除head
						{
							p = LIST_get(i + 1, head_desk);	//获取链表中的结点
							p0 = (struct stDesk*)(p ->cmData);	//强制转换数据域为实际类型
							if((desk_num == p0 ->nNum) && (1 == p0 ->iStat))
							{
								p0 ->iStat = 0;
								p0 ->iOrder = 0;
								FILE_update(p0, sizeof(struct stDesk), i, "db/desk.dat");
								printf("\n开桌成功!是否立即点菜?\"Y\"或\"N\":");						
								do
								{
									scanf("%c", &cAffirm);
									fflush(stdin);
									switch(cAffirm)
									{
									case 'y':
										SERVER_order_dish(1, desk_num);
									case 'Y':
										SERVER_order_dish(1, desk_num);
									case 'n':
										return 1;
									case 'N':
										return 1;
									default:
										printf("\n输入错误,请重新输入:");
										flag = 1;
										break;
									}
								}
								while(flag);
							}
							else
								if((desk_num == p0 ->nNum) && (0 == p0 ->iStat))
								{
									printf("\n该台桌当前不可用,请选择其它台桌..");
									getch();
									flag = 1;
									break;
								}
								else
									if((desk_num == p0 ->nNum) && (0 == p0 ->iOrder))
									{
										printf("\n该台桌当前未点菜,是否立即点菜?\"Y\"或\"N\":");
										do
										{
											scanf("%c", &cAffirm);
											fflush(stdin);
											switch(cAffirm)
											{
											case 'y':
												SERVER_order_dish(1, desk_num);
											case 'Y':
												SERVER_order_dish(1, desk_num);
											case 'n':
												return 1;
											case 'N':
												return 1;
											default:
												printf("\n输入错误,请重新输入:");
												flag = 1;
												break;
											}
										}
										while(flag);
									}
						}
						if(!flag)
						{
							printf("\n你要开的桌号不存在,请重新输入..");
							getch();
							flag = 1;
						}
					}
				}
				while(flag);
			}
			else
			{
				printf("数据库中缺少必要的数据,无法执行该操作..");
				getch();
				return 0;
			}
		}
	}
	else
	{
		printf("数据库中缺少必要的数据,无法执行该操作..");
		getch();
		return 0;
	}
}

/////////////////////////////////////////////////////////////////////
//函数名：SERVER_creat_bill
//
//函数功能：生成订单
//
//函数参数说明:desk--生成该订单的桌号,一个桌号对应多个订单
//				sum--订单总金额
//
//返回值：无
////////////////////////////////////////////////////////////////////
void SERVER_creat_bill(int desk, float sum)
{
	char ac1[15] = "bill/";	//目录名
	char ac2[9];
	struct stIncome income_T;
	struct stBill* p = (struct stBill*)malloc(sizeof(struct stBill));
	write_cur_time(p ->acDate, 0);	//日期
	strcpy(ac2, p ->acDate);	//以日期作为文件名,每天一个订单文件
	strcat(ac1, ac2);
	write_cur_time(p ->acTime, 1);	//单号
	p ->DeskNum = desk;	//桌号
	strcpy(p ->nEmpNum, acInput_Emp_Num);	//服务员工号
	p ->iPay = 0;	//支付状态
	p ->sum = sum;	//总金额
	LIST_add(p, head_order_bill);
	income_T.fSum = sum;
	strcpy(income_T.acDate, p ->acDate);
	strcpy(income_T.acEmpNum, acInput_Emp_Num);
	if(0 == access(ac1, 0))
	{
		FILE_add(p, sizeof(struct stBill), ac1);	//订单文件
		FILE_add(&income_T, sizeof(struct stIncome), "db/income.dat");	//统计文件
	}
	else
	{
		FILE_write_all(head_order_bill, sizeof(struct stBill), ac1);	//订单文件
		FILE* fp = fopen("db/income.dat", "w");	//统计文件
		if(fp == NULL)
		{
			fwrite(&income_T, sizeof(struct stIncome), 1, fp);
			fclose(fp);
		}
		else
		{
			printf("\nfile error!");
			getch();
			exit(0);
		}
	}
}

/////////////////////////////////////////////////////////////////////////
//函数名：write_cur_time
//
//函数功能：获取当前时间并以字符串形式写入date
//			
//函数参数说明：
//				mode:1--写到秒,作为单号,0--写到日,作为日期方便营收统计
//返回值：无
///////////////////////////////////////////////////////////////////////
void write_cur_time(char *date,int mode)
{
	struct tm *st_T;
	time_t t_t;
	time(&t_t);
	st_T = localtime(&t_t);
	if(mode)
	{
		sprintf(date, "%0004d%02d%02d%02d%02d%02d", st_T ->tm_year + 1900, st_T ->tm_mon + 1,
			st_T ->tm_mday, st_T ->tm_hour, st_T ->tm_min, st_T ->tm_sec);
	}
	else
	{
		sprintf(date, "%0004d%02d%02d", st_T ->tm_year + 1900, st_T ->tm_mon + 1,st_T ->tm_mday);
	}
}