
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "UI.h"
#include "public.h"
#include "globle.h"
#include "list.h"
#include "file.h"
#include "SERVER_desk_data.h"


PNode head_desk;
int desk_db_exists;
/////////////////////////////////////////////////////////////////////////
//函数名：SERVER_reread_desk
//
//函数功能：重读台桌信息文件到通用链表
//			
//函数参数说明：无
//
//返回值：无
//说明:调用该函数后该链表数据域仍为void*型,使用前请强转为实际类型
///////////////////////////////////////////////////////////////////////
//void SERVER_reread_desk()
//{
//	int count = LIST_count(head_desk);
//	if(count > 1)
//	{
//		LIST_free(head_desk);	//先释放
//		head_desk = (PNode)FILE_find_all(sizeof(struct stDesk), "db/desk.dat");	//读取文件中台桌信息并存到通用链表
//	}
//	else
//		{
//			head_desk = (PNode)FILE_find_all(sizeof(struct stDesk), "db/desk.dat");
//		}
//}

///////////////////////////////////////////////////////////////////////
//函数名：SERVER_desk_choice
//
//函数功能：台桌信息管理
//			
//函数参数说明：无
//
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_desk_choice()
{
	int n, flag = 1, ret;
	do
	{
		UI_sub0_desk();
		scanf("%d", &n);
		fflush(stdin);
	/*	SERVER_reread_desk();*/
		switch(n)
		{
		case 1:
			ret = SERVER_desk_add();
			if(ret)
			{
				break;
			}
			else
			{
				return 0;
			}
		case 2:
			ret = SERVER_desk_del();
			if(ret)
			{
				break;
			}
			else
			{
				return 0;
			}
			return 0;
		case 3:
			ret = SERVER_desk_update();
			if(ret)
			{
				break;
			}
			else
			{
				return 0;
			}
			return 0;
		case 4:
			ret = SERVER_desk_index();
			if(ret)
			{
				break;
			}
			else
			{
				return 0;
			}
		case 5:
			return 1;
		default:
			printf("输入错误!请重新输入!");
			break;
		}
	}
	while(flag);
}

////////////////////////////////////////////////////////////////////////
//函数名：SERVER_desk_index
//
//函数功能：台桌信息查询
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_desk_index()
{
	if(0 == desk_db_exists)
	{
		int n, i, j = 0, count;
		int flag = 1;
		int num, stat;
		char info[21];
		memset(info, 0, sizeof(info));
		struct stDesk* p0;
		PNode p;

		do
		{
			UI_desk_index();
			scanf("%d", &n);
			fflush(stdin);
			switch(n)
			{
			case 1:
				j = 0;
				printf("请输入您要查询的桌号:");
				scanf("%d", &num);
				fflush(stdin);
				count = LIST_count(head_desk);	//获取台桌数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_desk);	//获取链表中的结点
					p0 = (struct stDesk*)(p ->cmData);	//强制转换数据域为实际类型
					if(num == p0 ->nNum)
					{
						j++;
						printf("\n找到信息%d:\n桌号\t状态\t描述\t\n%d\t%d\t%s\n", j, p0 ->nNum, p0 ->iStat, p0 ->acInfo);
					}
				}
				if(0 == j)
				{
					printf("未找到您要的信息,请按任意键继续..");
					getch();
					break;
				}
				else
				{
					printf("请按任意键继续..");
					getch();
					break;
				}
			case 2:
				j = 0;
				printf("请输入您要查询的台桌状态(0--不可用,1--可用):");
				scanf("%d", &stat);
				fflush(stdin);
				count = LIST_count(head_desk);	//获取台桌数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_desk);	//获取链表中的结点
					p0 = (struct stDesk*)(p ->cmData);	//强制转换数据域为实际类型
					if(stat == p0 ->iStat)
					{
						j++;
						printf("\n找到信息%d:\n桌号\t状态\t描述\t\n%d\t%d\t%s\n", j, p0 ->nNum, p0 ->iStat, p0 ->acInfo);
					}
				}
				if(0 == j)
				{
					printf("未找到您要的信息,请按任意键继续..");
					getch();
					break;
				}
				else
				{
					printf("请按任意键继续..");
					getch();
					break;
				}
			case 3:
				return 1;
			}
		}
		while(flag);
	}
	else
	{		
		printf("\n数据库中无数据可供查询,请按任意键继续..");
		getch();
		return 1;
	}
}

////////////////////////////////////////////////////////////////////////
//函数名：SERVER_desk_add
//
//函数功能：台桌信息增加
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_desk_add()
{
	int flag = 0, count, i;
	char cAffirm;
	PNode p2;
	struct stDesk* p0;
	struct stDesk* p = (struct stDesk*)malloc(sizeof(struct stDesk));
	if(p == NULL)
	{
		printf("\nmalloc error");
		getch();
		return 0;
	}
	memset(p, 0, sizeof(struct stDesk));

	printf("请输入您要增加的台桌的状态(0--不可用,1--可用):");
	do
	{
		scanf("%d", &p ->iStat);
		fflush(stdin);
		switch(p ->iStat)	//输入校验
		{
		case 0: flag = 0; break;
		case 1: flag = 0; break;
		default:
			printf("\n输入错误,请重新输入!");
			flag = 1;
			break;
		}
	}
	while(flag);
	do	//验证添加的信息是否已经存在
	{
		flag = 0;
		printf("\n请输入您要增加的台桌的桌号(4位数字):");
		scanf("%d", &p ->nNum);
		fflush(stdin);
		if(0 == desk_db_exists)
		{
			count = LIST_count(head_desk);	//获取台桌数+1(包含了head)
			for(i = 1; i < count; i++)	//i=1是为了排除head
			{
				p2 = LIST_get(i + 1, head_desk);	//获取链表中的结点
				p0 = (struct stDesk*)(p2 ->cmData);	//强制转换数据域为实际类型
				if(p ->nNum == p0 ->nNum)
				{
					printf("\n该桌号已经存在,请重新输入..");
					getch();
					flag = 1;
					break;
				}
			}
		}
	}
	while(flag);
	printf("\n请输入您要增加的台桌的描述信息(不超过20个字节长度):");
	scanf("%s", p ->acInfo);
	fflush(stdin);
	p ->iOrder = 0;
	printf("\n输入完毕,您添加的台桌信息为:\n桌号\t状态\t描述\n%d\t%d\t%s\n请输入\"Y\"或者\"N\"来确认或者取消:", 
		p ->nNum, p ->iStat, p ->acInfo);
	do
	{
		scanf("%c", &cAffirm);
		fflush(stdin);
		switch(cAffirm)
		{
		case 'y':
			printf("\n信息添加成功!请按任意键返回..");
			getch();
			if(0 == desk_db_exists)
			{
				if(FILE_add(p, sizeof(struct stDesk), "db/desk.dat"))	//保存到文件
				{
					LIST_add(p, head_desk);	//同步更新cache
//					SERVER_reread_desk();
					return 1;
				}
				else
				{
					printf("\nfile w error!");
					getch();
					return 0;
				}
			}
			else
			{
				LIST_add(p, head_desk);
				if(FILE_write_all(head_desk, sizeof(struct stDesk), "db/desk.dat"))	//保存到文件
				{
//					SERVER_reread_desk();
					desk_db_exists =0;
					return 1;
				}
				else
				{
					printf("\nfile w error!");
					getch();
					return 0;
				}
			}		
		case 'Y':
			printf("\n信息添加成功!请按任意键返回..");
			getch();
			if(0 == desk_db_exists)
			{
				if(FILE_add(p, sizeof(struct stDesk), "db/desk.dat"))	//保存到文件
				{
					LIST_add(p, head_desk);	//同步更新cache
//					SERVER_reread_desk();
					return 1;
				}
				else
				{
					printf("\nfile w error!");
					getch();
					return 0;
				}
			}
			else
			{
				LIST_add(p, head_desk);
				if(FILE_write_all(head_desk, sizeof(struct stDesk), "db/desk.dat"))	//保存到文件
				{
//					SERVER_reread_desk();
					desk_db_exists =0;
					return 1;
				}
				else
				{
					printf("\nfile w error!");
					getch();
					return 0;
				}
			}	
		case 'n':
			printf("\n您放弃了保存刚才输入的数据,请按任意键返回..");
			getch();
			return 1;
		case 'N':
			printf("\n您放弃了保存刚才输入的数据,请按任意键返回..");
			getch();
			return 1;
		default:
			printf("\n输入错误,请按任意键后请重新输入");
			getch();
			flag = 1;
			break;
		}
	}
	while(flag);
}

///////////////////////////////////////////////////////////////////////
//函数名：SERVER_desk_del
//
//函数功能：台桌信息删除
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_desk_del()
{
	if(0 == desk_db_exists)
	{
		int flag = 0, n, j, count, i;
		char cAffirm;
		struct stDesk del_desk;
		memset(&del_desk, 0, sizeof(del_desk));
		PNode p;
		struct stDesk* p0;
		do
		{
			UI_desk_del();
			scanf("%d", &n);
			fflush(stdin);
			switch(n)	//输入校验
			{
			case 1:
				j = 0;
				printf("请输入您要删除的台桌桌号(4位数字):");
				scanf("%d", &del_desk.nNum);
				fflush(stdin);
				count = LIST_count(head_desk);	//获取台桌数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_desk);	//获取链表中的结点
					p0 = (struct stDesk*)(p ->cmData);	//强制转换数据域为实际类型
					if(del_desk.nNum == p0 ->nNum)
					{
						j++;
						printf("\n找桌号为%d的信息:\n桌号\t状态\t描述\n%d\t%d\t%s", del_desk.nNum, p0 ->nNum, p0 ->iStat, p0 ->acInfo);
						printf("\n请输入\"Y\"或者\"N\"来确认或者取消删除:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								printf("\n信息删除成功!请按任意键返回..");
								getch();
								if(LIST_remove(p ->cmData, head_desk))
								{
									FILE_write_all(head_desk, sizeof(struct stDesk), "db/desk.dat");	//同步更新文件
//									SERVER_reread_desk();
									return 1;
								}
								else
								{
									printf("\nerror!");
									getch();
									return 0;
								}
							case 'Y':
								printf("\n信息删除成功!请按任意键返回..");
								getch();
								if(LIST_remove(p ->cmData, head_desk))
								{
									FILE_write_all(head_desk, sizeof(struct stDesk), "db/desk.dat");	//同步更新文件
//									SERVER_reread_desk();
									return 1;
								}
								else
								{
									printf("\nerror!");
									getch();
									return 0;
								}
							case 'n':
								printf("\n您放弃了删除刚才输入的数据,请按任意键返回..");
								getch();
								return 1;
							case 'N':
								printf("\n您放弃了删除刚才输入的数据,请按任意键返回..");
								getch();
								return 1;
							default:
								printf("\n输入错误,请按任意键后请重新输入");
								getch();
								flag = 1;
								break;
							}
						}
						while(flag);
					}
				}
				if(0 == j)
				{
					printf("未找到您要的信息,请按任意键返回..");
					getch();
					return 1;
				}
			case 2:
				j = 0;
				printf("请输入您要删除的台桌状态(0--不可用,1--可用):");
				scanf("%d", &del_desk.iStat);
				fflush(stdin);
				count = LIST_count(head_desk);	//获取台桌数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_desk);	//获取链表中的结点
					p0 = (struct stDesk*)(p ->cmData);	//强制转换数据域为实际类型
					if(del_desk.iStat == p0 ->iStat)
					{
						j++;
						printf("\n找到状态为%d的信息%d:\n桌号\t状态\t描述\n%d\t%d\t%s", del_desk.iStat, j, p0 ->nNum, p0 ->iStat, p0 ->acInfo);
						printf("\n请输入\"Y\"或者\"N\"来确认或者取消删除:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								printf("\n信息删除成功!请按任意键返回..");
								getch();
								if(LIST_remove(p ->cmData, head_desk))
								{
									FILE_write_all(head_desk, sizeof(struct stDesk), "db/desk.dat");	//同步更新文件
//									SERVER_reread_desk();
									flag = 0;
									break;
								}
								else
								{
									printf("\nerror!");
									getch();
									return 0;
								}
							case 'Y':
								printf("\n信息删除成功!请按任意键返回..");
								getch();
								if(LIST_remove(p ->cmData, head_desk))
								{
									FILE_write_all(head_desk, sizeof(struct stDesk), "db/desk.dat");	//同步更新文件
//									SERVER_reread_desk();
									flag = 0;
									break;
								}
								else
								{
									printf("\nerror!");
									getch();
									return 0;
								}
							case 'n':
								printf("\n您放弃了删除该数据..");
								flag = 0;
								break;
							case 'N':
								printf("\n您放弃了删除该数据..");
								flag = 0;
								break;
							default:
								printf("\n输入错误,请按任意键后重新输入");
								getch();
								flag = 1;
								break;
							}
						}
						while(flag);
					}
				}
				if(0 == j)
				{
					printf("未找到您要的信息,请按任意键返回..");
					getch();
					return 1;
				}
			case 3:
				return 1;
			default:
				printf("\n输入错误,请重新输入!");
				flag = 1;
				break;
			}
		}
		while(flag);
	}
	else
	{
		printf("\n数据库中无数据,无法执行该操作,请按任意键继续..");
		getch();
		return 1;
	}
}


///////////////////////////////////////////////////////////////////////
//函数名：SERVER_desk_update
//
//函数功能：台桌信息修改
//
//函数参数说明:
//
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_desk_update()
{
	if(0 == desk_db_exists)
	{
		int flag, n, j = 0, count, i;
		char cAffirm;
		struct stDesk up_desk;
		struct stDesk* p0;
		memset(&up_desk, 0, sizeof(up_desk));

		PNode p;
		struct stDesk* p1;
		do
		{
			UI_desk_update();
			scanf("%d", &n);
			fflush(stdin);
			switch(n)	//输入校验
			{
			case 1:
				j = flag = 0;
				printf("请输入您要修改的台桌号(4位数字):");
				scanf("%d", &up_desk.nNum);
				count = LIST_count(head_desk);	//获取台桌数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_desk);	//获取链表中的结点
					p0 = (struct stDesk*)(p ->cmData);	//强制转换数据域为实际类型
					if(up_desk.nNum == p0 ->nNum)
					{
						j++;
						printf("\n找到桌号为%d的信息%d:\n桌号\t状态\t描述\n%d\t%d\t%s", up_desk.nNum, j, p0 ->nNum, p0 ->iStat, p0 ->acInfo);
						printf("\n请输入\"Y\"或者\"N\"来确认或者取消修改:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								p1 = (struct stDesk*)malloc(sizeof(struct stDesk));
								printf("\n桌号修改为(4位数字):");
								scanf("%d", &p1 ->nNum);
								fflush(stdin);
								printf("\n状态修改为(0--不可用,1--可用):");	
								do
								{
									scanf("%d", &p1 ->iStat);
									fflush(stdin);
									switch(p1 ->iStat)	//输入校验
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n输入错误,请重新输入!");
										flag = 1;
										break;
									}
								}while(flag);
								printf("\n台桌描述修改为(不超过20个字节长度):");
								scanf("%s", p1 ->acInfo);
								fflush(stdin);			
								if(LIST_update(p ->cmData, p1, head_desk))
								{
									FILE_update(p1, sizeof(struct stDesk), i, "db/desk.dat");	//同步更新
									free(p0);
									printf("\n信息修改成功!\n..");
									getch();
									return 1;
								}
								else
								{
									printf("\nerror!");
									free(p1);
									getch();
									return 0;
								}
							case 'Y':
								p1 = (struct stDesk*)malloc(sizeof(struct stDesk));
								printf("\n桌号修改为(4位数字):");
								scanf("%d", &p1 ->nNum);
								fflush(stdin);
								printf("\n状态修改为(0--不可用,1--可用):");	
								do
								{
									scanf("%d", &p1 ->iStat);
									fflush(stdin);
									switch(p1 ->iStat)	//输入校验
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n输入错误,请重新输入!");
										flag = 1;
										break;
									}
								}while(flag);
								printf("\n台桌描述修改为(不超过20个字节长度):");
								scanf("%s", p1 ->acInfo);
								fflush(stdin);			
								if(LIST_update(p ->cmData, p1, head_desk))
								{
									FILE_update(p1, sizeof(struct stDesk), i, "db/desk.dat");	//同步更新
									free(p0);
									printf("\n信息修改成功!\n..");
									getch();
									return 1;
								}
								else
								{
									printf("\nerror!");
									free(p1);
									getch();
									return 0;
								}
							case 'n':
								printf("\n您放弃了修改该数据,请按任意键返回..");
								getch();
								return 1;
							case 'N':
								printf("\n您放弃了修改该数据,请按任意键返回..");
								getch();
								return 1;
							default:
								printf("\n输入错误,请按任意键后请重新输入");
								getch();
								flag = 1;
								break;
							}
						}						
						while(flag);

					}
				}			
				if(0 == j)
				{
					printf("未找到您要的信息,请按任意键返回..");
					getch();
					return 1;
				}
				break;
			case 2:
				j = flag = 0;
				printf("请输入您要修改的台桌状态(0--不可用,1--可用):");
				scanf("%d", &up_desk.iStat);
				fflush(stdin);
				count = LIST_count(head_desk);	//获取台桌数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_desk);	//获取链表中的结点
					p0 = (struct stDesk*)(p ->cmData);	//强制转换数据域为实际类型
					if(up_desk.iStat == p0 ->iStat)
					{
						j++;
						printf("\n找到状态为%d的信息%d:\n桌号\t状态\t描述\n%d\t%d\t%s", up_desk.iStat, j, p0 ->nNum, p0 ->iStat, p0 ->acInfo);
						printf("\n请输入\"Y\"或者\"N\"来确认或者取消修改:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								p1 = (struct stDesk*)malloc(sizeof(struct stDesk));
								printf("\n桌号修改为(4位数字):");
								scanf("%d", &p1 ->nNum);
								fflush(stdin);
								do
								{
									printf("\n状态修改为(0--不可用,1--可用):");
									scanf("%d", &p1 ->iStat);
									fflush(stdin);
									switch(p1 ->iStat)	//输入校验
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n输入错误,请重新输入!");
										flag = 1;
										break;
									}
								}while(flag);
								printf("\n台桌描述修改为(不超过20个字节长度):");
								scanf("%s", p1 ->acInfo);
								fflush(stdin);
								printf("\n信息修改成功\n!..");
								getch();
								if(LIST_update(p ->cmData, p1, head_desk))
								{
									FILE_update(p1, sizeof(struct stDesk), i, "db/desk.dat");	//同步更新文件
									free(p0);
									flag = 0;
									break;
								}
								else
								{
									printf("\nerror!");
									free(p1);
									getch();
									return 0;
								}
							case 'Y':
								p1 = (struct stDesk*)malloc(sizeof(struct stDesk));
								printf("\n桌号修改为(4位数字):");
								scanf("%d", &p1 ->nNum);
								fflush(stdin);
								do
								{
									printf("\n状态修改为(0--不可用,1--可用):");
									scanf("%d", &p1 ->iStat);
									fflush(stdin);
									switch(p1 ->iStat)	//输入校验
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n输入错误,请重新输入!");
										flag = 1;
										break;
									}
								}while(flag);
								printf("\n台桌描述修改为(不超过20个字节长度):");
								scanf("%s", p1 ->acInfo);
								fflush(stdin);
								printf("\n信息修改成功\n!..");
								getch();
								if(LIST_update(p ->cmData, p1, head_desk))
								{
									FILE_update(p1, sizeof(struct stDesk), i, "db/desk.dat");	//同步更新文件
									free(p0);
									flag = 0;
									break;
								}
								else
								{
									printf("\nerror!");
									free(p1);
									getch();
									return 0;
								}
							case 'n':
								printf("\n您放弃了修改该数据\n..");
								flag = 0;
								break;
							case 'N':
								printf("\n您放弃了修改该数据\n..");
								flag = 0;
								break;
							default:
								printf("\n输入错误,请按任意键后请重新输入");
								getch();
								flag = 1;
								break;
							}
						}
						while(flag);
					}
				}
				if(0 == j)
				{
					printf("未找到您要的信息,请按任意键返回..");
					getch();
					return 1;
				}
			case 3:
				return 1;
			default:
				printf("\n输入错误,请重新输入!");
				flag = 1;
				break;
			}		
		}while(flag);
	}
	else
	{
		printf("\n数据库中无数据,无法修改!,请按任意键继续");
		getch();
		return 1;
	}
}
