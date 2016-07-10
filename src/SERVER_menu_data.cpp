
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "UI.h"
#include "public.h"
#include "globle.h"
#include "list.h"
#include "file.h"
#include "SERVER_menu_data.h"


PNode head_menu;
int menu_db_exists;
/////////////////////////////////////////////////////////////////////////
//函数名：SERVER_reread_menu
//
//函数功能：重读菜谱息文件到通用链表
//			
//函数参数说明：无
//
//返回值：无
//说明:调用该函数后该链表数据域仍为void*型,使用前请强转为实际类型
///////////////////////////////////////////////////////////////////////
//void SERVER_reread_menu()
//{
//	int count = LIST_count(head_menu);
//	if(count > 1)
//	{
//		LIST_free(head_menu);	//先释放
//		head_menu = (PNode)FILE_find_all(sizeof(struct stMenu), "db/menu.dat");	//读取文件中菜谱信息并存到通用链表
//	}
//	else
//	{
//		head_menu = (PNode)FILE_find_all(sizeof(struct stMenu), "db/menu.dat");
//	}
//}

///////////////////////////////////////////////////////////////////////
//函数名：SERVER_menu_choice
//
//函数功能：菜谱信息管理
//			
//函数参数说明：无
//
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_menu_choice()
{
	int n, flag = 1, ret;
	do
	{
		UI_sub0_menu();
		scanf("%d", &n);
		fflush(stdin);
	/*	SERVER_reread_menu();*/
		switch(n)
		{
		case 1:
			ret = SERVER_menu_add();
			if(ret)
			{
				break;
			}
			else
			{
				return 0;
			}
		case 2:
			ret = SERVER_menu_del();
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
			ret = SERVER_menu_update();
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
			ret = SERVER_menu_index();
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
//函数名：SERVER_menu_index
//
//函数功能：人员信息查询
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_menu_index()
{
	if(0 == menu_db_exists)
	{
		int n, i, j = 0, count;
		int flag = 1;
		struct stMenu ind_menu, *p0;
		memset(&ind_menu, 0, sizeof(ind_menu));
		PNode p;

		do
		{
			UI_menu_index();
			scanf("%d", &n);
			fflush(stdin);
			switch(n)
			{
			case 1:
				j = 0;
				printf("请输入您要查询的菜编号(5位数字):");
				scanf("%d", &ind_menu.nNum);
				fflush(stdin);
				count = LIST_count(head_menu);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_menu);	//获取链表中的结点
					p0 = (struct stMenu*)(p ->cmData);	//强制转换数据域为实际类型
					if(ind_menu.nNum == p0 ->nNum)
					{
						j++;
						printf("\n找到信息%d:\n菜编号\t菜名\t价格\t\n%00005d\t%s\t%.2f\n", j, p0 ->nNum, p0 ->acName, p0 ->fPrice);
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
				printf("请输入您要查询的菜名(不超过20个字节长度):");
				scanf("%s", ind_menu.acName);	//GetStr()不支持获取中文,必须用scanf
				fflush(stdin);
				count = LIST_count(head_menu);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_menu);	//获取链表中的结点
					p0 = (struct stMenu*)(p ->cmData);	//强制转换数据域为实际类型
					if(strcmp(ind_menu.acName, p0 ->acName) == 0)
					{
						j++;
						printf("\n找到信息%d:\n菜编号\t菜名\t价格\t\n%00005d\t%s\t%.2f\n", j, p0 ->nNum, p0 ->acName, p0 ->fPrice);
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
				j = 0;
				printf("请输入您要查询的菜的价格:");
				scanf("%f", &ind_menu.fPrice);
				fflush(stdin);
				count = LIST_count(head_menu);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_menu);	//获取链表中的结点
					p0 = (struct stMenu*)(p ->cmData);	//强制转换数据域为实际类型
					if(ind_menu.fPrice == p0 ->fPrice)
					{
						j++;
						printf("\n找到信息%d:\n菜编号\t菜名\t价格\t\n%00005d\t%s\t%.2f\n", j, p0 ->nNum, p0 ->acName, p0 ->fPrice);
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
			case 4:
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
//函数名：SERVER_menu_add
//
//函数功能：人员信息增加
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_menu_add()
{
	int flag = 0, count, i;
	char cAffirm;
	PNode p2;
	struct stMenu* p0;
	struct stMenu* p = (struct stMenu*)malloc(sizeof(struct stMenu));
	if(p == NULL)
	{
		printf("\nmalloc error");
		getch();
		return 0;
	}
	memset(p, 0, sizeof(struct stMenu));


	do	//验证添加的信息是否已经存在
	{
		flag = 0;
		printf("请输入您要增加的菜的编号(5位数字):");
		scanf("%d", &p ->nNum);
		fflush(stdin);
		if(0 == menu_db_exists)
		{
			count = LIST_count(head_menu);	//获取台桌数+1(包含了head)
			for(i = 1; i < count; i++)	//i=1是为了排除head
			{
				p2 = LIST_get(i + 1, head_menu);	//获取链表中的结点
				p0 = (struct stMenu*)(p2 ->cmData);	//强制转换数据域为实际类型
				if(p ->nNum == p0 ->nNum)
				{
					printf("\n该菜编号已经存在,请重新输入..");
					getch();
					flag = 1;
					break;
				}
			}
		}
	}
	while(flag);
	printf("\n请输入您要增加的菜名(不超过20个字节长度):");
	scanf("%s", p ->acName);
	fflush(stdin);
	printf("\n请输入您要增加的菜的价格:");
	scanf("%f", &p ->fPrice);
	fflush(stdin);
	p ->iStat = 0;
	printf("\n输入完毕,您添加的菜信息为:\n菜编号\t菜名\t\t价格\n%00005d\t%s\t%.2f\n请输入\"Y\"或者\"N\"来确认或者取消:", 
		p ->nNum, p ->acName, p ->fPrice);
	do
	{
		scanf("%c", &cAffirm);
		fflush(stdin);
		switch(cAffirm)
		{
		case 'y':
			printf("\n信息添加成功!请按任意键返回..");
			getch();
			if(0 == menu_db_exists)
			{
				if(FILE_add(p, sizeof(struct stMenu), "db/menu.dat"))	//保存到文件
				{
					LIST_add(p, head_menu);	//同步更新cache
//					SERVER_reread_menu();
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
				LIST_add(p, head_menu);
				if(FILE_write_all(head_menu, sizeof(struct stMenu), "db/menu.dat"))	//保存到文件
				{
					menu_db_exists = 0;
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
			if(0 == menu_db_exists)
			{
				if(FILE_add(p, sizeof(struct stMenu), "db/menu.dat"))	//保存到文件
				{
					LIST_add(p, head_menu);	//同步更新cache
//					SERVER_reread_menu();
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
				LIST_add(p, head_menu);
				if(FILE_write_all(head_menu, sizeof(struct stMenu), "db/menu.dat"))	//保存到文件
				{
					menu_db_exists = 0;
					return 1;
				}
				else
				{
					printf("\nfile write error!");
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
//函数名：SERVER_menu_del
//
//函数功能：菜谱信息删除
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_menu_del()
{
	if(0 == menu_db_exists)
	{
		int flag = 0, n, j, count, i;
		char cAffirm;
		struct stMenu del_menu;
		memset(&del_menu, 0, sizeof(del_menu));
		PNode p;
		struct stMenu* p0;
		do
		{
			UI_menu_del();
			scanf("%d", &n);
			fflush(stdin);
			switch(n)	//输入校验
			{
			case 1:
				j = 0;
				printf("请输入您要删除的菜编号(5位数字):");
				scanf("%d", &del_menu.nNum);
				fflush(stdin);
				count = LIST_count(head_menu);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_menu);	//获取链表中的结点
					p0 = (struct stMenu*)(p ->cmData);	//强制转换数据域为实际类型
					if(del_menu.nNum == p0 ->nNum)
					{
						j++;
						printf("\n找到信息%d:\n菜编号\t菜名\t\t价格\t\n%00005d\t%s\t%.2f\n", j, p0 ->nNum, p0 ->acName, p0 ->fPrice);
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
								if(LIST_remove(p ->cmData, head_menu))
								{
									FILE_write_all(head_menu, sizeof(struct stMenu), "db/menu.dat");	//同步更新文件
//									SERVER_reread_menu();
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
								if(LIST_remove(p ->cmData, head_menu))
								{
									FILE_write_all(head_menu, sizeof(struct stMenu), "db/menu.dat");	//同步更新文件
//									SERVER_reread_menu();
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
				printf("请输入您要删除的菜名(不超过20个字节长度):");
				scanf("%s", del_menu.acName);
				fflush(stdin);
				count = LIST_count(head_menu);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_menu);	//获取链表中的结点
					p0 = (struct stMenu*)(p ->cmData);	//强制转换数据域为实际类型
					if(strcmp(del_menu.acName, p0 ->acName) == 0)
					{
						j++;
						printf("\n找到信息%d:\n菜编号\t菜名\t价格\t\n%00005d\t%s\t%.2f\n", j, p0 ->nNum, p0 ->acName, p0 ->fPrice);
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
								if(LIST_remove(p ->cmData, head_menu))
								{
									FILE_write_all(head_menu, sizeof(struct stMenu), "db/menu.dat");	//同步更新文件
//									SERVER_reread_menu();
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
								if(LIST_remove(p ->cmData, head_menu))
								{
									FILE_write_all(head_menu, sizeof(struct stMenu), "db/menu.dat");	//同步更新文件
//									SERVER_reread_menu();
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
			case 3:
				j = 0;
				printf("请输入您要删除的菜的价格:");
				scanf("%f", &del_menu.fPrice);
				fflush(stdin);
				count = LIST_count(head_menu);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_menu);	//获取链表中的结点
					p0 = (struct stMenu*)(p ->cmData);	//强制转换数据域为实际类型
					if(del_menu.fPrice == p0 ->fPrice)
					{
						j++;
						printf("\n找到信息%d:\n菜编号\t菜名\t价格\t\n%00005d\t%s\t%.2f\n", j, p0 ->nNum, p0 ->acName, p0 ->fPrice);
						printf("\n请输入\"Y\"或者\"N\"来确认或者取消:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								printf("\n信息删除成功!请按任意键返回..");
								getch();
								if(LIST_remove(p ->cmData, head_menu))
								{
									FILE_write_all(head_menu, sizeof(struct stMenu), "db/menu.dat");	//同步更新文件
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
								if(LIST_remove(p ->cmData, head_menu))
								{
									FILE_write_all(head_menu, sizeof(struct stMenu), "db/menu.dat");	//同步更新文件
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
								printf("\n您放弃了删除该数据\n..");
								flag = 0;
								break;
							case 'N':
								printf("\n您放弃了删除该数据\n..");
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
			case 4:
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
//函数名：SERVER_menu_update
//
//函数功能：人员信息修改
//
//函数参数说明:
//
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_menu_update()
{
	if(0 == menu_db_exists)
	{
		int flag, n, j = 0, count, i;
		char cAffirm;
		struct stMenu up_menu, *p0;
		memset(&up_menu, 0, sizeof(up_menu));

		PNode p = NULL;
		struct stMenu* p1;
		memset(p1, 0, sizeof(struct stMenu));
		do
		{
			UI_menu_update();
			scanf("%d", &n);
			fflush(stdin);
			switch(n)	//输入校验
			{
			case 1:
				j = flag = 0;
				printf("请输入您要修改的菜编号(5位数字):");
				scanf("%d", &up_menu.nNum);
				count = LIST_count(head_menu);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_menu);	//获取链表中的结点
					p0 = (struct stMenu*)(p ->cmData);	//强制转换数据域为实际类型
					if(up_menu.nNum, p0 ->nNum)
					{
						j++;
						printf("\n找到信息%d:\n菜编号\t菜名\t价格\t\n%00005d\t%s\t%.2f\n", j, p0 ->nNum, p0 ->acName, p0 ->fPrice);
						printf("\n请输入\"Y\"或者\"N\"来确认或者取消修改:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								p1 = (struct stMenu*)malloc(sizeof(struct stMenu));
								flag = 0;
								printf("\n菜编号修改为(5位数字):");
								scanf("%d",p1 ->nNum);
								fflush(stdin);
								printf("\n菜名修改为(不超过20个字节长度):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n菜价格修改为:");
								scanf("%f", &p1 ->fPrice);
								fflush(stdin);
								while(flag);

								if(LIST_update(p ->cmData, p1, head_menu))
								{
									FILE_update(p1, sizeof(struct stMenu), i, "db/menu.dat");	//同步更新文件
									free(p0);
									printf("\n信息修改成功!请按任意键返回..");
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
								p1 = (struct stMenu*)malloc(sizeof(struct stMenu));
								flag = 0;
								printf("\n菜编号修改为(5位数字):");
								scanf("%d",p1 ->nNum);
								fflush(stdin);
								printf("\n菜名修改为(不超过20个字节长度):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n菜价格修改为:");
								scanf("%f", &p1 ->fPrice);
								fflush(stdin);
								while(flag);

								if(LIST_update(p ->cmData, p1, head_menu))
								{
									FILE_update(p1, sizeof(struct stMenu), i, "db/menu.dat");	//同步更新文件
									free(p0);
									printf("\n信息修改成功!请按任意键返回..");
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
			case 2:
				j = flag = 0;
				printf("请输入您要修改的菜名(不超过20个字节长度):");
				scanf("%s", up_menu.acName);
				fflush(stdin);
				count = LIST_count(head_menu);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_menu);	//获取链表中的结点
					p0 = (struct stMenu*)(p ->cmData);	//强制转换数据域为实际类型
					if(strcmp(up_menu.acName, p0 ->acName) == 0)
					{
						j++;
						printf("\n找到信息%d:\n菜编号\t菜名\t价格\t\n%00005d\t%s\t%.2f\n", j, p0 ->nNum, p0 ->acName, p0 ->fPrice);
						printf("\n请输入\"Y\"或者\"N\"来确认或者取消修改:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								p1 = (struct stMenu*)malloc(sizeof(struct stMenu));
								flag = 0;
								printf("\n菜编号修改为(5位数字):");
								scanf("%d",p1 ->nNum);
								fflush(stdin);
								printf("\n菜名修改为(不超过20个字节长度):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n菜价格修改为:");
								scanf("%f", &p1 ->fPrice);
								fflush(stdin);
								while(flag);
								if(LIST_update(p ->cmData, p1, head_menu))
								{
									FILE_update(p1, sizeof(struct stMenu), i, "db/menu.dat");	//同步更新文件
									free(p0);
									printf("\n信息修改成功!请按任意键返回..");
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
								p1 = (struct stMenu*)malloc(sizeof(struct stMenu));
								flag = 0;
								printf("\n菜编号修改为(5位数字):");
								scanf("%d",p1 ->nNum);
								fflush(stdin);
								printf("\n菜名修改为(不超过20个字节长度):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n菜价格修改为:");
								scanf("%f", &p1 ->fPrice);
								fflush(stdin);
								while(flag);
								if(LIST_update(p ->cmData, p1, head_menu))
								{
									FILE_update(p1, sizeof(struct stMenu), i, "db/menu.dat");	//同步更新文件
									free(p0);
									printf("\n信息修改成功!请按任意键返回..");
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
			case 3:
				printf("请输入您要修改的菜的价格:");
				scanf("%f", &up_menu.fPrice);
				fflush(stdin);
				count = LIST_count(head_menu);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_menu);	//获取链表中的结点
					p0 = (struct stMenu*)(p ->cmData);	//强制转换数据域为实际类型
					if(up_menu.fPrice == p0 ->fPrice)
					{
						j++;
						printf("\n找到信息%d:\n菜编号\t菜名\t价格\t\n%d\t%s\t%.2f\n", j, p0 ->nNum, p0 ->acName, p0 ->fPrice);
						printf("\n请输入\"Y\"或者\"N\"来确认或者取消:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								p1 = (struct stMenu*)malloc(sizeof(struct stMenu));
								flag = 0;
								printf("\n菜编号修改为(5位数字):");
								scanf("%d",p1 ->nNum);
								fflush(stdin);
								printf("\n菜名修改为(不超过20个字节长度):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n菜价格修改为:");
								scanf("%f", &p1 ->fPrice);
								fflush(stdin);
								while(flag);

								if(LIST_update(p ->cmData, p1, head_menu))
								{
									FILE_update(p1, sizeof(struct stMenu), i, "db/menu.dat");	//同步更新文件
									printf("\n信息修改成功!请按任意键返回..");
									getch();
									free(p0);
									flag = 0;
									break;
								}
								else
								{
									printf("\nerror!");
									getch();
									free(p1);
									return 0;
								}
							case 'Y':
								p1 = (struct stMenu*)malloc(sizeof(struct stMenu));
								flag = 0;
								printf("\n菜编号修改为(5位数字):");
								scanf("%d",p1 ->nNum);
								fflush(stdin);
								printf("\n菜名修改为(不超过20个字节长度):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n菜价格修改为:");
								scanf("%f", &p1 ->fPrice);
								fflush(stdin);
								while(flag);

								if(LIST_update(p ->cmData, p1, head_menu))
								{
									FILE_update(p1, sizeof(struct stMenu), i, "db/menu.dat");	//同步更新文件
									printf("\n信息修改成功!请按任意键返回..");
									free(p0);
									getch();
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
			case 4:
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
		printf("\n数据库中无数据,无法修改!,请按任意键继续");
		getch();
		return 1;
	}
}


