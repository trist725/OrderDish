
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "UI.h"
#include "public.h"
#include "globle.h"
#include "list.h"
#include "file.h"
#include "SERVER_emp_data.h"


PNode head_emp;
int emp_db_exists;
/////////////////////////////////////////////////////////////////////////
//函数名：SERVER_reread_emp
//
//函数功能：重读员工信息文件到通用链表
//			
//函数参数说明：无
//
//返回值：无
//说明:调用该函数后该链表数据域仍为void*型,使用前请强转为实际类型
///////////////////////////////////////////////////////////////////////
//void SERVER_reread_emp()
//{
//	int count = LIST_count(head_emp);
//	if(count > 1)
//	{
//		LIST_free(head_emp);	//先释放
//		head_emp = (PNode)FILE_find_all(sizeof(struct stEmp), "db/emp.dat");	//读取文件中员工信息并存到通用链表
//	}
//	else
//	{
//		head_emp = (PNode)FILE_find_all(sizeof(struct stEmp), "db/emp.dat");
//	}
//}

///////////////////////////////////////////////////////////////////////
//函数名：SERVER_emp_choice
//
//函数功能：人员信息管理
//			
//函数参数说明：无
//
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_emp_choice()
{
	int n, flag = 1, ret;
	do
	{
		UI_sub0_emp();
		scanf("%d", &n);
		fflush(stdin);

		switch(n)
		{
		case 1:
			ret = SERVER_emp_add();
			if(ret)
			{
				break;
			}
			else
			{
				return 0;
			}
		case 2:
			ret = SERVER_emp_del();
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
			ret = SERVER_emp_update();
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
			ret = SERVER_emp_index();
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
//函数名：SERVER_emp_index
//
//函数功能：人员信息查询
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_emp_index()
{
	if(0 == emp_db_exists)
	{
		int n, i, j = 0, count;
		int role, flag = 1;
		char num[11];
		char name[21];
		memset(num, 0, sizeof(num));
		memset(name, 0, sizeof(name));
		struct stEmp* p0;
		PNode p;

		do
		{
			UI_emp_index();
			scanf("%d", &n);
			fflush(stdin);
			switch(n)
			{
			case 1:
				j = 0;
				printf("请输入您要查询的工号(不超过%d个字节长度):", MAX_INPUT);
				GetStr(num, MAX_INPUT, 1);
				count = LIST_count(head_emp);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_emp);	//获取链表中的结点
					p0 = (struct stEmp*)(p ->cmData);	//强制转换数据域为实际类型
					if(strcmp(num, p0 ->acNum) == 0)
					{
						j++;
						printf("\n找到信息%d:\n姓名\t工号\t权限\t\n%s\t%s\t%d\n", j, p0 ->acName, p0 ->acNum, p0 ->nRole);
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
				printf("请输入您要查询的员工姓名(不超过%d个字节长度):", MAX_INPUT);
				scanf("%s", name);	//GetStr()不支持获取中文,必须用scanf
				fflush(stdin);
				count = LIST_count(head_emp);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_emp);	//获取链表中的结点
					p0 = (struct stEmp*)(p ->cmData);	//强制转换数据域为实际类型
					if(strcmp(name, p0 ->acName) == 0)
					{
						j++;
						printf("\n找到信息%d:\n姓名\t工号\t权限\t\n%s\t%s\t%d\n", j, p0 ->acName, p0 ->acNum, p0 ->nRole);
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
				printf("请输入您要查询的员工权限(0-管理员,1-服务员,2-Boss/经理):");
				scanf("%d", &role);
				fflush(stdin);
				count = LIST_count(head_emp);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_emp);	//获取链表中的结点
					p0 = (struct stEmp*)(p ->cmData);	//强制转换数据域为实际类型
					if(role == p0 ->nRole)
					{
						j++;
						printf("\n找到信息%d:\n姓名\t工号\t权限\t\n%s\t%s\t%d\n", j, p0 ->acName, p0 ->acNum, p0 ->nRole);
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
//函数名：SERVER_emp_add
//
//函数功能：人员信息增加
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_emp_add()
{
	int flag = 0, count, i;
	char cAffirm;
	PNode p2;
	struct stEmp* p0;
	struct stEmp* p = (struct stEmp*)malloc(sizeof(struct stEmp));
	if(p == NULL)
	{
		printf("\nmalloc error");
		getch();
		return 0;
	}
	memset(p, 0, sizeof(struct stEmp));

	printf("请输入您要增加的员工的权限(0-管理员,1-服务员,2-Boss/经理):");
	do
	{
		scanf("%d", &p ->nRole);
		fflush(stdin);
		switch(p ->nRole)	//输入校验
		{
		case 0: flag = 0; break;
		case 1: flag = 0; break;
		case 2: flag = 0; break;
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
		printf("\n请输入您要增加的员工的工号(不超过%d个字节长度):", MAX_INPUT);
		GetStr(p ->acNum, MAX_INPUT, 1);
		if(0 == emp_db_exists)
		{
			count = LIST_count(head_emp);	//获取台桌数+1(包含了head)
			for(i = 1; i < count; i++)	//i=1是为了排除head
			{
				p2 = LIST_get(i + 1, head_emp);	//获取链表中的结点
				p0 = (struct stEmp*)(p2 ->cmData);	//强制转换数据域为实际类型
				if(strcmp(p ->acNum, p0 ->acNum) == 0)
				{
					printf("\n该工号已经存在,请重新输入..");
					getch();
					flag = 1;
					break;
				}
			}
		}
	}
	while(flag);
	printf("\n请输入您要增加的员工的密码(不超过%d个字节长度):", MAX_INPUT);
	GetStr(p ->acPw, MAX_INPUT, 0);
	printf("\n请输入您要增加的员工的姓名(不超过20个字节长度):");
	scanf("%s", p ->acName);
	fflush(stdin);
	printf("\n输入完毕,您添加的员工信息为:\n权限\t工号\t密码\t姓名\n%d\t%s\t%s\t%s\n请输入\"Y\"或者\"N\"来确认或者取消:", 
		p ->nRole, p ->acNum, "****", p ->acName);
	do
	{
		scanf("%c", &cAffirm);
		fflush(stdin);
		switch(cAffirm)
		{
		case 'y':
			printf("\n信息添加成功!请按任意键返回..");
			getch();
			if(0 == emp_db_exists)
			{
				if(FILE_add(p, sizeof(struct stEmp), "db/emp.dat"))	//保存到文件
				{
					LIST_add(p, head_emp);	//同步更新cache
//					SERVER_reread_emp();
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
				LIST_add(p, head_emp);
				if(FILE_write_all(head_emp, sizeof(struct stEmp), "db/emp.dat"))	//保存到文件
				{
					emp_db_exists = 0;
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
			if(0 == emp_db_exists)
			{
				if(FILE_add(p, sizeof(struct stEmp), "db/emp.dat"))	//保存到文件
				{
					LIST_add(p, head_emp);	//同步更新cache
//					SERVER_reread_emp();
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
				LIST_add(p, head_emp);
				if(FILE_write_all(head_emp, sizeof(struct stEmp), "db/emp.dat"))	//保存到文件
				{
					emp_db_exists = 0;
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
//函数名：SERVER_emp_del
//
//函数功能：人员信息删除
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_emp_del()
{
	if(0 == emp_db_exists)
	{
		int flag = 0, n, j, count, i;
		char cAffirm;
		struct stEmp del_emp;
		memset(&del_emp, 0, sizeof(del_emp));
		PNode p;
		struct stEmp* p0;
		do
		{
			UI_emp_del();
			scanf("%d", &n);
			fflush(stdin);
			switch(n)	//输入校验
			{
			case 1:
				j = 0;
				printf("请输入您要删除的员工工号(不超过%d个字节长度):", MAX_INPUT);
				GetStr(del_emp.acNum, MAX_INPUT, 1);
				count = LIST_count(head_emp);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_emp);	//获取链表中的结点
					p0 = (struct stEmp*)(p ->cmData);	//强制转换数据域为实际类型
					if(strcmp(del_emp.acNum, p0 ->acNum) == 0)
					{
						j++;
						printf("\n找到工号为%s的信息:\n角色\t工号\t姓名\n%d\t%s\t%s", del_emp.acNum, p0 ->nRole, p0 ->acNum, p0 ->acName);
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
								if(LIST_remove(p ->cmData, head_emp))
								{
									FILE_write_all(head_emp, sizeof(struct stEmp), "db/emp.dat");	//同步更新文件
//									SERVER_reread_emp();
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
								if(LIST_remove(p ->cmData, head_emp))
								{
									FILE_write_all(head_emp, sizeof(struct stEmp), "db/emp.dat");	//同步更新文件
//									SERVER_reread_emp();
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
				printf("请输入您要删除的员工姓名(不超过20个字节长度):");
				scanf("%s", del_emp.acName);
				fflush(stdin);
				count = LIST_count(head_emp);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_emp);	//获取链表中的结点
					p0 = (struct stEmp*)(p ->cmData);	//强制转换数据域为实际类型
					if(strcmp(del_emp.acName, p0 ->acName) == 0)
					{
						j++;
						printf("\n找到姓名为%s的信息%d:\n角色\t工号\t姓名\n%d\t%s\t%s", j, del_emp.acNum, p0 ->nRole, p0 ->acNum, p0 ->acName);
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
								if(LIST_remove(p ->cmData, head_emp))
								{
									FILE_write_all(head_emp, sizeof(struct stEmp), "db/emp.dat");	//同步更新文件
//									SERVER_reread_emp();
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
								if(LIST_remove(p ->cmData, head_emp))
								{
									FILE_write_all(head_emp, sizeof(struct stEmp), "db/emp.dat");	//同步更新文件
//									SERVER_reread_emp();
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
			case 3:
				j = 0;
				printf("请输入您要删除的员工角色(0-管理员,1-服务员,2-Boss/经理):");
				scanf("%d", &del_emp.nRole);
				fflush(stdin);
				count = LIST_count(head_emp);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_emp);	//获取链表中的结点
					p0 = (struct stEmp*)(p ->cmData);	//强制转换数据域为实际类型
					if(del_emp.nRole == p0 ->nRole)
					{
						j++;
						printf("\n找到用户角色为%d的信息:\n角色\t工号\t姓名\n%d\t%s\t%s",del_emp.nRole, p0 ->nRole, p0 ->acNum, p0 ->acName);
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
								if(LIST_remove(p ->cmData, head_emp))
								{
									FILE_write_all(head_emp, sizeof(struct stEmp), "db/emp.dat");	//同步更新文件
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
								if(LIST_remove(p ->cmData, head_emp))
								{
									FILE_write_all(head_emp, sizeof(struct stEmp), "db/emp.dat");	//同步更新文件
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
//函数名：SERVER_emp_update
//
//函数功能：人员信息修改
//
//函数参数说明:
//
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_emp_update()
{
	if(0 == emp_db_exists)
	{
		int flag, n, j = 0, count, i;
		char cAffirm;
		struct stEmp up_emp;
		struct stEmp* p0;
		memset(&up_emp, 0, sizeof(up_emp));

		PNode p = NULL;
		struct stEmp* p1;
		do
		{
			UI_emp_update();
			scanf("%d", &n);
			fflush(stdin);
			switch(n)	//输入校验
			{
			case 1:
				j = flag = 0;
				printf("请输入您要修改的员工工号(不超过%d个字节长度):", MAX_INPUT);
				GetStr(up_emp.acNum, MAX_INPUT, 1);
				count = LIST_count(head_emp);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_emp);	//获取链表中的结点
					p0 = (struct stEmp*)(p ->cmData);	//强制转换数据域为实际类型
					if(strcmp(up_emp.acNum, p0 ->acNum) == 0)
					{
						j++;
						printf("\n找到工号为%s的信息%d:\n角色\t工号\t姓名\n%d\t%s\t%s", up_emp.acNum, j, p0 ->nRole, p0 ->acNum, p0 ->acName);
						printf("\n请输入\"Y\"或者\"N\"来确认或者取消修改:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								flag = 0;
								p1 = (struct stEmp*)malloc(sizeof(struct stEmp));
								do
								{
									printf("\n修改前请输入原密码(不超过%d个字节长度):", MAX_INPUT);
									GetStr(up_emp.acPw, MAX_INPUT, 0);
									if(strcmp(up_emp.acPw, p0 ->acPw) == 0)
									{
										printf("\n请输入新密码(不超过%d个字节长度):", MAX_INPUT);
										GetStr(p1 ->acPw, MAX_INPUT, 0);
										flag = 0;
									}
									else
									{
										printf("\n密码输入错误,请重新输入:");
										flag = 1;
									}
								}
								while(flag);
								printf("\n工号修改为(不超过%d个字节长度):", MAX_INPUT);
								GetStr(p1 ->acNum, MAX_INPUT, 1);
								printf("\n姓名修改为(不超过20个字节长度):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n用户角色修改为(0-管理员,1-服务员,2-Boss/经理):");
								do
								{
									scanf("%d", &p1 ->nRole);
									fflush(stdin);
									switch(p1 ->nRole)	//输入校验
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n输入错误,请重新输入!");
										flag = 1;
										break;
									}
								}
								while(flag);			
								if(LIST_update(p ->cmData, p1, head_emp))
								{
									FILE_update(p1, sizeof(struct stEmp), i, "db/emp.dat");	//同步更新文件
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
								flag = 0;
								p1 = (struct stEmp*)malloc(sizeof(struct stEmp));
								do
								{
									printf("\n修改前请输入原密码(不超过%d个字节长度):", MAX_INPUT);
									GetStr(up_emp.acPw, MAX_INPUT, 0);
									if(strcmp(up_emp.acPw, p0 ->acPw) == 0)
									{
										printf("\n请输入新密码(不超过%d个字节长度):", MAX_INPUT);
										GetStr(p1 ->acPw, MAX_INPUT, 0);
										flag = 0;
									}
									else
									{
										printf("\n密码输入错误,请重新输入:");
										flag = 1;
									}
								}
								while(flag);
								printf("\n工号修改为(不超过%d个字节长度):", MAX_INPUT);
								GetStr(p1 ->acNum, MAX_INPUT, 1);
								printf("\n姓名修改为(不超过20个字节长度):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n用户角色修改为(0-管理员,1-服务员,2-Boss/经理):");
								do
								{
									scanf("%d", &p1 ->nRole);
									fflush(stdin);
									switch(p1 ->nRole)	//输入校验
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n输入错误,请重新输入!");
										flag = 1;
										break;
									}
								}
								while(flag);			
								if(LIST_update(p ->cmData, p1, head_emp))
								{
									FILE_update(p1, sizeof(struct stEmp), i, "db/emp.dat");	//同步更新文件
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
				printf("请输入您要修改的员工姓名(不超过20个字节长度):");
				scanf("%s", up_emp.acName);
				fflush(stdin);
				count = LIST_count(head_emp);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_emp);	//获取链表中的结点
					p0 = (struct stEmp*)(p ->cmData);	//强制转换数据域为实际类型
					if(strcmp(up_emp.acName, p0 ->acName) == 0)
					{
						j++;
						printf("\n找到姓名为%s的信息%d:\n角色\t工号\t姓名\n%d\t%s\t%s", up_emp.acNum, j, p0 ->nRole, p0 ->acNum, p0 ->acName);
						printf("\n请输入\"Y\"或者\"N\"来确认或者取消修改:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								flag = 0;
								p1 = (struct stEmp*)malloc(sizeof(struct stEmp));
								do
								{
									printf("\n修改前请输入原密码(不超过%d个字节长度):", MAX_INPUT);
									GetStr(up_emp.acPw, MAX_INPUT, 0);
									if(strcmp(up_emp.acPw, p0 ->acPw) == 0)
									{
										printf("\n请输入新密码(不超过%d个字节长度):", MAX_INPUT);
										GetStr(p1 ->acPw, MAX_INPUT, 0);
										flag = 0;
									}
									else
									{
										printf("\n密码输入错误,请重新输入:");
										flag = 1;
									}
								}
								while(flag);
								printf("\n工号修改为(不超过%d个字节长度):", MAX_INPUT);
								GetStr(p1 ->acNum, MAX_INPUT, 1);
								printf("\n姓名修改为(不超过20个字节长度):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n用户角色修改为(0-管理员,1-服务员,2-Boss/经理):");
								do
								{
									scanf("%d", &p1 ->nRole);
									fflush(stdin);
									switch(p1 ->nRole)	//输入校验
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n输入错误,请重新输入!");
										flag = 1;
										break;
									}
								}
								while(flag);							
								if(LIST_update(p ->cmData, p1, head_emp))
								{
									FILE_update(p1, sizeof(struct stEmp), i, "db/emp.dat");	//同步更新文件
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
								flag = 0;
								p1 = (struct stEmp*)malloc(sizeof(struct stEmp));
								do
								{
									printf("\n修改前请输入原密码(不超过%d个字节长度):", MAX_INPUT);
									GetStr(up_emp.acPw, MAX_INPUT, 0);
									if(strcmp(up_emp.acPw, p0 ->acPw) == 0)
									{
										printf("\n请输入新密码(不超过%d个字节长度):", MAX_INPUT);
										GetStr(p1 ->acPw, MAX_INPUT, 0);
										flag = 0;
									}
									else
									{
										printf("\n密码输入错误,请重新输入:");
										flag = 1;
									}
								}
								while(flag);
								printf("\n工号修改为(不超过%d个字节长度):", MAX_INPUT);
								GetStr(p1 ->acNum, MAX_INPUT, 1);
								printf("\n姓名修改为(不超过20个字节长度):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n用户角色修改为(0-管理员,1-服务员,2-Boss/经理):");
								do
								{
									scanf("%d", &p1 ->nRole);
									fflush(stdin);
									switch(p1 ->nRole)	//输入校验
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n输入错误,请重新输入!");
										flag = 1;
										break;
									}
								}
								while(flag);							
								if(LIST_update(p ->cmData, p1, head_emp))
								{
									FILE_update(p1, sizeof(struct stEmp), i, "db/emp.dat");	//同步更新文件
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
				printf("请输入您要修改的员工角色(0-管理员,1-服务员,2-Boss/经理):");
				scanf("%d", &up_emp.nRole);
				fflush(stdin);
				count = LIST_count(head_emp);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_emp);	//获取链表中的结点
					p0 = (struct stEmp*)(p ->cmData);	//强制转换数据域为实际类型
					if(up_emp.nRole == p0 ->nRole)
					{
						j++;
						printf("\n找到用户角色为%d的信息%d:\n角色\t工号\t姓名\n%d\t%s\t%s",up_emp.nRole, j, p0 ->nRole, p0 ->acNum, p0 ->acName);
						printf("\n请输入\"Y\"或者\"N\"来确认或者取消:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								flag = 0;
								p1 = (struct stEmp*)malloc(sizeof(struct stEmp));
								do
								{
									printf("\n修改前请输入原密码(不超过%d个字节长度):", MAX_INPUT);
									GetStr(up_emp.acPw, MAX_INPUT, 0);
									if(strcmp(up_emp.acPw, p0 ->acPw) == 0)
									{
										printf("\n请输入新密码(不超过%d个字节长度):", MAX_INPUT);
										GetStr(p1 ->acPw, MAX_INPUT, 0);
										flag = 0;
									}
									else
									{
										printf("\n密码输入错误,请重新输入:");
										flag = 1;
									}
								}
								while(flag);
								printf("\n工号修改为(不超过%d个字节长度):", MAX_INPUT);
								GetStr(p1 ->acNum, MAX_INPUT, 1);
								printf("\n姓名修改为(不超过20个字节长度):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n用户角色修改为(0-管理员,1-服务员,2-Boss/经理):");
								do
								{
									scanf("%d", &p1 ->nRole);
									fflush(stdin);
									switch(p1 ->nRole)	//输入校验
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n输入错误,请重新输入!");
										flag = 1;
										break;
									}
								}
								while(flag);							
								if(LIST_update(p ->cmData, p1, head_emp))
								{
									FILE_update(p1, sizeof(struct stEmp), i, "db/emp.dat");	//同步更新文件
									free(p0);
									flag = 0;
									printf("\n信息修改成功!请按任意键返回..");
								getch();
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
								flag = 0;
								p1 = (struct stEmp*)malloc(sizeof(struct stEmp));
								do
								{
									printf("\n修改前请输入原密码(不超过%d个字节长度):", MAX_INPUT);
									GetStr(up_emp.acPw, MAX_INPUT, 0);
									if(strcmp(up_emp.acPw, p0 ->acPw) == 0)
									{
										printf("\n请输入新密码(不超过%d个字节长度):", MAX_INPUT);
										GetStr(p1 ->acPw, MAX_INPUT, 0);
										flag = 0;
									}
									else
									{
										printf("\n密码输入错误,请重新输入:");
										flag = 1;
									}
								}
								while(flag);
								printf("\n工号修改为(不超过%d个字节长度):", MAX_INPUT);
								GetStr(p1 ->acNum, MAX_INPUT, 1);
								printf("\n姓名修改为(不超过20个字节长度):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n用户角色修改为(0-管理员,1-服务员,2-Boss/经理):");
								do
								{
									scanf("%d", &p1 ->nRole);
									fflush(stdin);
									switch(p1 ->nRole)	//输入校验
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n输入错误,请重新输入!");
										flag = 1;
										break;
									}
								}
								while(flag);							
								if(LIST_update(p ->cmData, p1, head_emp))
								{
									FILE_update(p1, sizeof(struct stEmp), i, "db/emp.dat");	//同步更新文件
									free(p0);
									flag = 0;
									printf("\n信息修改成功!请按任意键返回..");
								getch();
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


