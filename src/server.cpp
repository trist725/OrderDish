
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <io.h>

#include "globle.h"
#include "server.h"
#include "list.h"
#include "file.h"
#include "UI.h"
#include "public.h"

#include "SERVER_emp_data.h"
#include "SERVER_desk_data.h"
#include "SERVER_menu_data.h"
#include "SERVER_order_dish.h"
#include "SERVER_ipay.h"
#include "SERVER_emp_turnover.h"
#include "SERVER_income.h"

extern PNode head_emp;
extern PNode head_desk;
extern PNode head_menu;
extern int emp_db_exists;
extern int desk_db_exists;
extern int menu_db_exists;
char acInput_Emp_Num[MAX_INPUT + 1];
/////////////////////////////////////////////////////////////////////////
//函数名：SERVER_login
//
//函数功能：登录模块,控制用户输入工号和密码,并根据不同账号进入其相应功能选单
//			
//函数参数说明：无
//
//返回值：0 -- 管理员
//		  1 -- 服务员
//		  2 -- 经理/Boss
///////////////////////////////////////////////////////////////////////
int SERVER_login()
{
	int count, i;
	int Account_Input_Over = 0;//账号输入控制开关
	int Account_Input_err = 1;
	char acInput_Emp_PW[MAX_INPUT + 1];
	PNode p;
	struct stEmp stAdmin = {0, "admin", "admin"};	//超级管理员
	struct stEmp *p0;

	emp_db_exists = access("db/emp.dat", 0);	//判断基础数据文件是否存在
	desk_db_exists = access("db/desk.dat", 0);
	menu_db_exists = access("db/menu.dat", 0);

	if(0 == emp_db_exists)
	{
		head_emp = (PNode)FILE_find_all(sizeof(struct stEmp), "db/emp.dat");
	}
	else
	{
		head_emp = LIST_init(NULL);	//初始化链表为空
	}
	if(0 == menu_db_exists)
	{
		head_menu = (PNode)FILE_find_all(sizeof(struct stMenu), "db/menu.dat");
	}
	else
	{
		head_menu = LIST_init(NULL);	//初始化链表为空
	}
	if(0 == desk_db_exists)
	{
		head_desk = (PNode)FILE_find_all(sizeof(struct stDesk), "db/desk.dat");
	}
	else
	{
		head_desk = LIST_init(NULL);	//初始化链表为空
	}

	do
	{
		UI_main();
		memset(acInput_Emp_Num, 0, sizeof(acInput_Emp_Num));	//重置输入
		memset(acInput_Emp_PW, 0, sizeof(acInput_Emp_PW));
		GetStr(acInput_Emp_Num, MAX_INPUT, 1);	//输入工号
		Gotoxy(43, 8);	//光标定位
		GetStr(acInput_Emp_PW, MAX_INPUT, 0);	//输入密码
		if((strcmp(acInput_Emp_Num, stAdmin.acNum) == 0)
			&& (strcmp(acInput_Emp_PW, stAdmin.acPw) == 0))	//校验是否为超级管理员
		{
			if(0 == emp_db_exists)
			{
//			SERVER_reread_emp();
			}
			UI_sub(0);
			return 0;
		}
		else
			if(0 == emp_db_exists)
			{
//			SERVER_reread_emp();
				count = LIST_count(head_emp);	//获取员工数+1(包含了head)
				for(i = 1; i < count; i++)	//i=1是为了排除head
				{
					p = LIST_get(i + 1, head_emp);	//获取链表中的结点
					p0 = (struct stEmp*)(p ->cmData);	//强制转换数据域为实际类型
					if((strcmp(acInput_Emp_Num, p0 ->acNum) == 0) && 
						(strcmp(acInput_Emp_PW, p0 ->acPw) == 0))
					{
						UI_sub(p0 ->nRole);
						return p0 ->nRole;
					}
				}
				printf("\n\t\t您输入的用户名或者密码不正确,请按任意键重新输入..");
				getch();
			}
			else
			{
				printf("\n\t\t您输入的用户名或者密码不正确,请按任意键重新输入..");
				getch();
				continue;
			}
	}
	while(!Account_Input_Over);
	return 3;
}

///////////////////////////////////////////////////////////////////////
//函数名：SERVER_fuc_choice
//
//函数功能：各角色功能选单
//			
//函数参数说明：Role: 0 -- 管理员功能菜单
//					  1 -- 服务员功能菜单
//					  2 -- 经理/Boss功能菜单
//返回值：0 -- 结束 1 -- 注销登录,回到登录界面
///////////////////////////////////////////////////////////////////////
int SERVER_fuc_choice(int nRole)
{
	int flag = 0, ret = 0;
	do{
		switch(nRole)
		{
		case 0:
			{
				ret = SERVER_fuc0_choice();
				if(ret)
				{
					break;
				}
				else
				{
					return 0;
				}
			}
		case 1:
			{
				ret = SERVER_fuc1_choice();
				if(ret)
				{
					break;
				}
				else
				{
					return 0;
				}
			}
		case 2:
			{
				ret = SERVER_fuc2_choice();
				if(ret)
				{
					break;
				}
				else
				{
					return 0;
				}
			}
		default:
			printf("\nlogin error..");
			getch();
			return 0;
		}
	}
	while(flag);
}

/////////////////////////////////////////////////////////////////////////
//函数名：SERVER_fuc0_choice
//
//函数功能：管理员功能选单
//			
//函数说明：		  1 -- 台桌数据管理
//					  2 -- 菜谱数据管理
//					  3 -- 人员数据管理
//					  4 -- 注销
//					  5 -- 退出
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_fuc0_choice()
{
	int n, ret = 0, flag =1;
	do
	{
		UI_sub(0);
		scanf("%d", &n);
		fflush(stdin);
		switch(n)
		{
		case 1:
			UI_sub0_desk();
			ret = SERVER_desk_choice();
			if(ret)
			{
				break;
			}
			else
			{
				return 0;
			}
		case 2:
			UI_sub0_menu();
			ret = SERVER_menu_choice();
			if(ret)
			{
				break;
			}
			else
			{
				return 0;
			}
		case 3:
			UI_sub0_emp();
			ret = SERVER_emp_choice();
			if(ret)
			{
				break;
			}
			else
			{
				return 0;
			}
		case 4:
			return 1;
		case 5:
			return 0;
		default:
			printf("输入错误!请重新输入!");
			break;
		}
	}
	while(flag);
}

///////////////////////////////////////////////////////////////////////
//函数名：SERVER_fuc1_choice
//
//函数功能：服务员功能选单
//			
//函数说明：		  1 -- 开桌
//					  2 -- 点菜
//					  3 -- 营业额查询
//					  4 -- 已买/未买单查询
//					  5 -- 注销
//					  6 -- 退出
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_fuc1_choice()
{
	int n, ret = 0, flag = 1, mode;
	do
	{
		mode = 0;
		UI_sub(1);
		scanf("%d", &n);
		fflush(stdin);
		switch(n)
		{
		case 1:
			ret = SERVER_open_desk();
			if(ret)
			{
				break;
			}
			else
			{
				return 0;
			}
		case 2:
			ret = SERVER_order_dish(0, 0);
			if(ret)
			{
				break;
			}
			else
			{
				return 0;
			}
		case 3:
			ret = SERVER_emp_turnover();
			if(ret)
			{
				break;
			}
			else
			{
				return 0;
			}
		case 4:
			ret = SERVER_ipay();
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
		case 6:
			return 0;
		default:
			printf("输入错误!请重新输入!");
			break;
		}
	}
	while(flag);
}

///////////////////////////////////////////////////////////////////////
//函数名：SERVER_fuc2_choice
//
//函数功能：经理/Boss功能选单
//			
//函数说明：		  1 -- 营收统计
//					  2 -- 注销
//					  3 -- 退出
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_fuc2_choice()
{
	int n, ret = 0, flag =1;
	do
	{
		scanf("%d", &n);
		fflush(stdin);
		switch(n)
		{
		case 1:
			ret = SERVER_income();
			if(ret)
			{
				break;
			}
			else
			{
				return 0;
			}
		case 2:
			return 1;
		case 3:
			return 0;
		default:
			printf("输入错误!请重新输入!");
			break;
		}
	}
	while(flag);
}