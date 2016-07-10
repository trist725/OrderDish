
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
//��������SERVER_login
//
//�������ܣ���¼ģ��,�����û����빤�ź�����,�����ݲ�ͬ�˺Ž�������Ӧ����ѡ��
//			
//��������˵������
//
//����ֵ��0 -- ����Ա
//		  1 -- ����Ա
//		  2 -- ����/Boss
///////////////////////////////////////////////////////////////////////
int SERVER_login()
{
	int count, i;
	int Account_Input_Over = 0;//�˺�������ƿ���
	int Account_Input_err = 1;
	char acInput_Emp_PW[MAX_INPUT + 1];
	PNode p;
	struct stEmp stAdmin = {0, "admin", "admin"};	//��������Ա
	struct stEmp *p0;

	emp_db_exists = access("db/emp.dat", 0);	//�жϻ��������ļ��Ƿ����
	desk_db_exists = access("db/desk.dat", 0);
	menu_db_exists = access("db/menu.dat", 0);

	if(0 == emp_db_exists)
	{
		head_emp = (PNode)FILE_find_all(sizeof(struct stEmp), "db/emp.dat");
	}
	else
	{
		head_emp = LIST_init(NULL);	//��ʼ������Ϊ��
	}
	if(0 == menu_db_exists)
	{
		head_menu = (PNode)FILE_find_all(sizeof(struct stMenu), "db/menu.dat");
	}
	else
	{
		head_menu = LIST_init(NULL);	//��ʼ������Ϊ��
	}
	if(0 == desk_db_exists)
	{
		head_desk = (PNode)FILE_find_all(sizeof(struct stDesk), "db/desk.dat");
	}
	else
	{
		head_desk = LIST_init(NULL);	//��ʼ������Ϊ��
	}

	do
	{
		UI_main();
		memset(acInput_Emp_Num, 0, sizeof(acInput_Emp_Num));	//��������
		memset(acInput_Emp_PW, 0, sizeof(acInput_Emp_PW));
		GetStr(acInput_Emp_Num, MAX_INPUT, 1);	//���빤��
		Gotoxy(43, 8);	//��궨λ
		GetStr(acInput_Emp_PW, MAX_INPUT, 0);	//��������
		if((strcmp(acInput_Emp_Num, stAdmin.acNum) == 0)
			&& (strcmp(acInput_Emp_PW, stAdmin.acPw) == 0))	//У���Ƿ�Ϊ��������Ա
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
				count = LIST_count(head_emp);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_emp);	//��ȡ�����еĽ��
					p0 = (struct stEmp*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if((strcmp(acInput_Emp_Num, p0 ->acNum) == 0) && 
						(strcmp(acInput_Emp_PW, p0 ->acPw) == 0))
					{
						UI_sub(p0 ->nRole);
						return p0 ->nRole;
					}
				}
				printf("\n\t\t��������û����������벻��ȷ,�밴�������������..");
				getch();
			}
			else
			{
				printf("\n\t\t��������û����������벻��ȷ,�밴�������������..");
				getch();
				continue;
			}
	}
	while(!Account_Input_Over);
	return 3;
}

///////////////////////////////////////////////////////////////////////
//��������SERVER_fuc_choice
//
//�������ܣ�����ɫ����ѡ��
//			
//��������˵����Role: 0 -- ����Ա���ܲ˵�
//					  1 -- ����Ա���ܲ˵�
//					  2 -- ����/Boss���ܲ˵�
//����ֵ��0 -- ���� 1 -- ע����¼,�ص���¼����
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
//��������SERVER_fuc0_choice
//
//�������ܣ�����Ա����ѡ��
//			
//����˵����		  1 -- ̨�����ݹ���
//					  2 -- �������ݹ���
//					  3 -- ��Ա���ݹ���
//					  4 -- ע��
//					  5 -- �˳�
//����ֵ��0 -- ���� 1 -- ����
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
			printf("�������!����������!");
			break;
		}
	}
	while(flag);
}

///////////////////////////////////////////////////////////////////////
//��������SERVER_fuc1_choice
//
//�������ܣ�����Ա����ѡ��
//			
//����˵����		  1 -- ����
//					  2 -- ���
//					  3 -- Ӫҵ���ѯ
//					  4 -- ����/δ�򵥲�ѯ
//					  5 -- ע��
//					  6 -- �˳�
//����ֵ��0 -- ���� 1 -- ����
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
			printf("�������!����������!");
			break;
		}
	}
	while(flag);
}

///////////////////////////////////////////////////////////////////////
//��������SERVER_fuc2_choice
//
//�������ܣ�����/Boss����ѡ��
//			
//����˵����		  1 -- Ӫ��ͳ��
//					  2 -- ע��
//					  3 -- �˳�
//����ֵ��0 -- ���� 1 -- ����
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
			printf("�������!����������!");
			break;
		}
	}
	while(flag);
}