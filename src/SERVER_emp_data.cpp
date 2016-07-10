
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
//��������SERVER_reread_emp
//
//�������ܣ��ض�Ա����Ϣ�ļ���ͨ������
//			
//��������˵������
//
//����ֵ����
//˵��:���øú������������������Ϊvoid*��,ʹ��ǰ��ǿתΪʵ������
///////////////////////////////////////////////////////////////////////
//void SERVER_reread_emp()
//{
//	int count = LIST_count(head_emp);
//	if(count > 1)
//	{
//		LIST_free(head_emp);	//���ͷ�
//		head_emp = (PNode)FILE_find_all(sizeof(struct stEmp), "db/emp.dat");	//��ȡ�ļ���Ա����Ϣ���浽ͨ������
//	}
//	else
//	{
//		head_emp = (PNode)FILE_find_all(sizeof(struct stEmp), "db/emp.dat");
//	}
//}

///////////////////////////////////////////////////////////////////////
//��������SERVER_emp_choice
//
//�������ܣ���Ա��Ϣ����
//			
//��������˵������
//
//����ֵ��0 -- ���� 1 -- ����
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
			printf("�������!����������!");
			break;
		}
	}
	while(flag);
}

////////////////////////////////////////////////////////////////////////
//��������SERVER_emp_index
//
//�������ܣ���Ա��Ϣ��ѯ
//			
//��������˵��:
//					 
//����ֵ��0 -- ���� 1 -- ����
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
				printf("��������Ҫ��ѯ�Ĺ���(������%d���ֽڳ���):", MAX_INPUT);
				GetStr(num, MAX_INPUT, 1);
				count = LIST_count(head_emp);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_emp);	//��ȡ�����еĽ��
					p0 = (struct stEmp*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(strcmp(num, p0 ->acNum) == 0)
					{
						j++;
						printf("\n�ҵ���Ϣ%d:\n����\t����\tȨ��\t\n%s\t%s\t%d\n", j, p0 ->acName, p0 ->acNum, p0 ->nRole);
					}
				}
				if(0 == j)
				{
					printf("δ�ҵ���Ҫ����Ϣ,�밴���������..");
					getch();
					break;
				}
				else
				{
					printf("�밴���������..");
					getch();
					break;
				}
			case 2:
				j = 0;
				printf("��������Ҫ��ѯ��Ա������(������%d���ֽڳ���):", MAX_INPUT);
				scanf("%s", name);	//GetStr()��֧�ֻ�ȡ����,������scanf
				fflush(stdin);
				count = LIST_count(head_emp);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_emp);	//��ȡ�����еĽ��
					p0 = (struct stEmp*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(strcmp(name, p0 ->acName) == 0)
					{
						j++;
						printf("\n�ҵ���Ϣ%d:\n����\t����\tȨ��\t\n%s\t%s\t%d\n", j, p0 ->acName, p0 ->acNum, p0 ->nRole);
					}
				}
				if(0 == j)
				{
					printf("δ�ҵ���Ҫ����Ϣ,�밴���������..");
					getch();
					break;
				}
				else
				{
					printf("�밴���������..");
					getch();
					break;
				}
			case 3:
				j = 0;
				printf("��������Ҫ��ѯ��Ա��Ȩ��(0-����Ա,1-����Ա,2-Boss/����):");
				scanf("%d", &role);
				fflush(stdin);
				count = LIST_count(head_emp);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_emp);	//��ȡ�����еĽ��
					p0 = (struct stEmp*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(role == p0 ->nRole)
					{
						j++;
						printf("\n�ҵ���Ϣ%d:\n����\t����\tȨ��\t\n%s\t%s\t%d\n", j, p0 ->acName, p0 ->acNum, p0 ->nRole);
					}
				}
				if(0 == j)
				{
					printf("δ�ҵ���Ҫ����Ϣ,�밴���������..");
					getch();
					break;
				}
				else
				{
					printf("�밴���������..");
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
		printf("\n���ݿ��������ݿɹ���ѯ,�밴���������..");
		getch();
		return 1;
	}
}

////////////////////////////////////////////////////////////////////////
//��������SERVER_emp_add
//
//�������ܣ���Ա��Ϣ����
//			
//��������˵��:
//					 
//����ֵ��0 -- ���� 1 -- ����
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

	printf("��������Ҫ���ӵ�Ա����Ȩ��(0-����Ա,1-����Ա,2-Boss/����):");
	do
	{
		scanf("%d", &p ->nRole);
		fflush(stdin);
		switch(p ->nRole)	//����У��
		{
		case 0: flag = 0; break;
		case 1: flag = 0; break;
		case 2: flag = 0; break;
		default:
			printf("\n�������,����������!");
			flag = 1;
			break;
		}
	}
	while(flag);
	do	//��֤��ӵ���Ϣ�Ƿ��Ѿ�����
	{
		flag = 0;
		printf("\n��������Ҫ���ӵ�Ա���Ĺ���(������%d���ֽڳ���):", MAX_INPUT);
		GetStr(p ->acNum, MAX_INPUT, 1);
		if(0 == emp_db_exists)
		{
			count = LIST_count(head_emp);	//��ȡ̨����+1(������head)
			for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
			{
				p2 = LIST_get(i + 1, head_emp);	//��ȡ�����еĽ��
				p0 = (struct stEmp*)(p2 ->cmData);	//ǿ��ת��������Ϊʵ������
				if(strcmp(p ->acNum, p0 ->acNum) == 0)
				{
					printf("\n�ù����Ѿ�����,����������..");
					getch();
					flag = 1;
					break;
				}
			}
		}
	}
	while(flag);
	printf("\n��������Ҫ���ӵ�Ա��������(������%d���ֽڳ���):", MAX_INPUT);
	GetStr(p ->acPw, MAX_INPUT, 0);
	printf("\n��������Ҫ���ӵ�Ա��������(������20���ֽڳ���):");
	scanf("%s", p ->acName);
	fflush(stdin);
	printf("\n�������,����ӵ�Ա����ϢΪ:\nȨ��\t����\t����\t����\n%d\t%s\t%s\t%s\n������\"Y\"����\"N\"��ȷ�ϻ���ȡ��:", 
		p ->nRole, p ->acNum, "****", p ->acName);
	do
	{
		scanf("%c", &cAffirm);
		fflush(stdin);
		switch(cAffirm)
		{
		case 'y':
			printf("\n��Ϣ��ӳɹ�!�밴���������..");
			getch();
			if(0 == emp_db_exists)
			{
				if(FILE_add(p, sizeof(struct stEmp), "db/emp.dat"))	//���浽�ļ�
				{
					LIST_add(p, head_emp);	//ͬ������cache
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
				if(FILE_write_all(head_emp, sizeof(struct stEmp), "db/emp.dat"))	//���浽�ļ�
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
			printf("\n��Ϣ��ӳɹ�!�밴���������..");
			getch();
			if(0 == emp_db_exists)
			{
				if(FILE_add(p, sizeof(struct stEmp), "db/emp.dat"))	//���浽�ļ�
				{
					LIST_add(p, head_emp);	//ͬ������cache
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
				if(FILE_write_all(head_emp, sizeof(struct stEmp), "db/emp.dat"))	//���浽�ļ�
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
			printf("\n�������˱���ղ����������,�밴���������..");
			getch();
			return 1;
		case 'N':
			printf("\n�������˱���ղ����������,�밴���������..");
			getch();
			return 1;
		default:
			printf("\n�������,�밴�����������������");
			getch();
			flag = 1;
			break;
		}
	}
	while(flag);
}

///////////////////////////////////////////////////////////////////////
//��������SERVER_emp_del
//
//�������ܣ���Ա��Ϣɾ��
//			
//��������˵��:
//					 
//����ֵ��0 -- ���� 1 -- ����
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
			switch(n)	//����У��
			{
			case 1:
				j = 0;
				printf("��������Ҫɾ����Ա������(������%d���ֽڳ���):", MAX_INPUT);
				GetStr(del_emp.acNum, MAX_INPUT, 1);
				count = LIST_count(head_emp);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_emp);	//��ȡ�����еĽ��
					p0 = (struct stEmp*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(strcmp(del_emp.acNum, p0 ->acNum) == 0)
					{
						j++;
						printf("\n�ҵ�����Ϊ%s����Ϣ:\n��ɫ\t����\t����\n%d\t%s\t%s", del_emp.acNum, p0 ->nRole, p0 ->acNum, p0 ->acName);
						printf("\n������\"Y\"����\"N\"��ȷ�ϻ���ȡ��ɾ��:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								printf("\n��Ϣɾ���ɹ�!�밴���������..");
								getch();
								if(LIST_remove(p ->cmData, head_emp))
								{
									FILE_write_all(head_emp, sizeof(struct stEmp), "db/emp.dat");	//ͬ�������ļ�
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
								printf("\n��Ϣɾ���ɹ�!�밴���������..");
								getch();
								if(LIST_remove(p ->cmData, head_emp))
								{
									FILE_write_all(head_emp, sizeof(struct stEmp), "db/emp.dat");	//ͬ�������ļ�
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
								printf("\n��������ɾ���ղ����������,�밴���������..");
								getch();
								return 1;
							case 'N':
								printf("\n��������ɾ���ղ����������,�밴���������..");
								getch();
								return 1;
							default:
								printf("\n�������,�밴�����������������");
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
					printf("δ�ҵ���Ҫ����Ϣ,�밴���������..");
					getch();
					return 1;
				}
			case 2:
				j = 0;
				printf("��������Ҫɾ����Ա������(������20���ֽڳ���):");
				scanf("%s", del_emp.acName);
				fflush(stdin);
				count = LIST_count(head_emp);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_emp);	//��ȡ�����еĽ��
					p0 = (struct stEmp*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(strcmp(del_emp.acName, p0 ->acName) == 0)
					{
						j++;
						printf("\n�ҵ�����Ϊ%s����Ϣ%d:\n��ɫ\t����\t����\n%d\t%s\t%s", j, del_emp.acNum, p0 ->nRole, p0 ->acNum, p0 ->acName);
						printf("\n������\"Y\"����\"N\"��ȷ�ϻ���ȡ��ɾ��:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								printf("\n��Ϣɾ���ɹ�!�밴���������..");
								getch();
								if(LIST_remove(p ->cmData, head_emp))
								{
									FILE_write_all(head_emp, sizeof(struct stEmp), "db/emp.dat");	//ͬ�������ļ�
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
								printf("\n��Ϣɾ���ɹ�!�밴���������..");
								getch();
								if(LIST_remove(p ->cmData, head_emp))
								{
									FILE_write_all(head_emp, sizeof(struct stEmp), "db/emp.dat");	//ͬ�������ļ�
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
								printf("\n��������ɾ��������\n..");
								flag = 0;
									break;
							case 'N':
								printf("\n��������ɾ��������\n..");
								flag = 0;
									break;
							default:
								printf("\n�������,�밴�����������������");
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
					printf("δ�ҵ���Ҫ����Ϣ,�밴���������..");
					getch();
					return 1;
				}
			case 3:
				j = 0;
				printf("��������Ҫɾ����Ա����ɫ(0-����Ա,1-����Ա,2-Boss/����):");
				scanf("%d", &del_emp.nRole);
				fflush(stdin);
				count = LIST_count(head_emp);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_emp);	//��ȡ�����еĽ��
					p0 = (struct stEmp*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(del_emp.nRole == p0 ->nRole)
					{
						j++;
						printf("\n�ҵ��û���ɫΪ%d����Ϣ:\n��ɫ\t����\t����\n%d\t%s\t%s",del_emp.nRole, p0 ->nRole, p0 ->acNum, p0 ->acName);
						printf("\n������\"Y\"����\"N\"��ȷ�ϻ���ȡ��:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								printf("\n��Ϣɾ���ɹ�!�밴���������..");
								getch();
								if(LIST_remove(p ->cmData, head_emp))
								{
									FILE_write_all(head_emp, sizeof(struct stEmp), "db/emp.dat");	//ͬ�������ļ�
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
								printf("\n��Ϣɾ���ɹ�!�밴���������..");
								getch();
								if(LIST_remove(p ->cmData, head_emp))
								{
									FILE_write_all(head_emp, sizeof(struct stEmp), "db/emp.dat");	//ͬ�������ļ�
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
								printf("\n��������ɾ��������\n..");
								flag = 0;
									break;
							case 'N':
								printf("\n��������ɾ��������\n..");
								flag = 0;
									break;
							default:
								printf("\n�������,�밴�����������������");
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
					printf("δ�ҵ���Ҫ����Ϣ,�밴���������..");
					getch();
					return 1;
				}
			case 4:
				return 1;
			default:
				printf("\n�������,����������!");
				flag = 1;
				break;
			}
		}
		while(flag);
	}
	else
	{
		printf("\n���ݿ���������,�޷�ִ�иò���,�밴���������..");
		getch();
		return 1;
	}
}


///////////////////////////////////////////////////////////////////////
//��������SERVER_emp_update
//
//�������ܣ���Ա��Ϣ�޸�
//
//��������˵��:
//
//����ֵ��0 -- ���� 1 -- ����
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
			switch(n)	//����У��
			{
			case 1:
				j = flag = 0;
				printf("��������Ҫ�޸ĵ�Ա������(������%d���ֽڳ���):", MAX_INPUT);
				GetStr(up_emp.acNum, MAX_INPUT, 1);
				count = LIST_count(head_emp);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_emp);	//��ȡ�����еĽ��
					p0 = (struct stEmp*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(strcmp(up_emp.acNum, p0 ->acNum) == 0)
					{
						j++;
						printf("\n�ҵ�����Ϊ%s����Ϣ%d:\n��ɫ\t����\t����\n%d\t%s\t%s", up_emp.acNum, j, p0 ->nRole, p0 ->acNum, p0 ->acName);
						printf("\n������\"Y\"����\"N\"��ȷ�ϻ���ȡ���޸�:");
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
									printf("\n�޸�ǰ������ԭ����(������%d���ֽڳ���):", MAX_INPUT);
									GetStr(up_emp.acPw, MAX_INPUT, 0);
									if(strcmp(up_emp.acPw, p0 ->acPw) == 0)
									{
										printf("\n������������(������%d���ֽڳ���):", MAX_INPUT);
										GetStr(p1 ->acPw, MAX_INPUT, 0);
										flag = 0;
									}
									else
									{
										printf("\n�����������,����������:");
										flag = 1;
									}
								}
								while(flag);
								printf("\n�����޸�Ϊ(������%d���ֽڳ���):", MAX_INPUT);
								GetStr(p1 ->acNum, MAX_INPUT, 1);
								printf("\n�����޸�Ϊ(������20���ֽڳ���):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n�û���ɫ�޸�Ϊ(0-����Ա,1-����Ա,2-Boss/����):");
								do
								{
									scanf("%d", &p1 ->nRole);
									fflush(stdin);
									switch(p1 ->nRole)	//����У��
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n�������,����������!");
										flag = 1;
										break;
									}
								}
								while(flag);			
								if(LIST_update(p ->cmData, p1, head_emp))
								{
									FILE_update(p1, sizeof(struct stEmp), i, "db/emp.dat");	//ͬ�������ļ�
									free(p0);
									printf("\n��Ϣ�޸ĳɹ�!�밴���������..");
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
									printf("\n�޸�ǰ������ԭ����(������%d���ֽڳ���):", MAX_INPUT);
									GetStr(up_emp.acPw, MAX_INPUT, 0);
									if(strcmp(up_emp.acPw, p0 ->acPw) == 0)
									{
										printf("\n������������(������%d���ֽڳ���):", MAX_INPUT);
										GetStr(p1 ->acPw, MAX_INPUT, 0);
										flag = 0;
									}
									else
									{
										printf("\n�����������,����������:");
										flag = 1;
									}
								}
								while(flag);
								printf("\n�����޸�Ϊ(������%d���ֽڳ���):", MAX_INPUT);
								GetStr(p1 ->acNum, MAX_INPUT, 1);
								printf("\n�����޸�Ϊ(������20���ֽڳ���):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n�û���ɫ�޸�Ϊ(0-����Ա,1-����Ա,2-Boss/����):");
								do
								{
									scanf("%d", &p1 ->nRole);
									fflush(stdin);
									switch(p1 ->nRole)	//����У��
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n�������,����������!");
										flag = 1;
										break;
									}
								}
								while(flag);			
								if(LIST_update(p ->cmData, p1, head_emp))
								{
									FILE_update(p1, sizeof(struct stEmp), i, "db/emp.dat");	//ͬ�������ļ�
									free(p0);
									printf("\n��Ϣ�޸ĳɹ�!�밴���������..");
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
								printf("\n���������޸ĸ�����,�밴���������..");
								getch();
								return 1;
							case 'N':
								printf("\n���������޸ĸ�����,�밴���������..");
								getch();
								return 1;
							default:
								printf("\n�������,�밴�����������������");
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
					printf("δ�ҵ���Ҫ����Ϣ,�밴���������..");
					getch();
					return 1;
				}
			case 2:
				j = flag = 0;
				printf("��������Ҫ�޸ĵ�Ա������(������20���ֽڳ���):");
				scanf("%s", up_emp.acName);
				fflush(stdin);
				count = LIST_count(head_emp);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_emp);	//��ȡ�����еĽ��
					p0 = (struct stEmp*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(strcmp(up_emp.acName, p0 ->acName) == 0)
					{
						j++;
						printf("\n�ҵ�����Ϊ%s����Ϣ%d:\n��ɫ\t����\t����\n%d\t%s\t%s", up_emp.acNum, j, p0 ->nRole, p0 ->acNum, p0 ->acName);
						printf("\n������\"Y\"����\"N\"��ȷ�ϻ���ȡ���޸�:");
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
									printf("\n�޸�ǰ������ԭ����(������%d���ֽڳ���):", MAX_INPUT);
									GetStr(up_emp.acPw, MAX_INPUT, 0);
									if(strcmp(up_emp.acPw, p0 ->acPw) == 0)
									{
										printf("\n������������(������%d���ֽڳ���):", MAX_INPUT);
										GetStr(p1 ->acPw, MAX_INPUT, 0);
										flag = 0;
									}
									else
									{
										printf("\n�����������,����������:");
										flag = 1;
									}
								}
								while(flag);
								printf("\n�����޸�Ϊ(������%d���ֽڳ���):", MAX_INPUT);
								GetStr(p1 ->acNum, MAX_INPUT, 1);
								printf("\n�����޸�Ϊ(������20���ֽڳ���):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n�û���ɫ�޸�Ϊ(0-����Ա,1-����Ա,2-Boss/����):");
								do
								{
									scanf("%d", &p1 ->nRole);
									fflush(stdin);
									switch(p1 ->nRole)	//����У��
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n�������,����������!");
										flag = 1;
										break;
									}
								}
								while(flag);							
								if(LIST_update(p ->cmData, p1, head_emp))
								{
									FILE_update(p1, sizeof(struct stEmp), i, "db/emp.dat");	//ͬ�������ļ�
									free(p0);
									printf("\n��Ϣ�޸ĳɹ�!�밴���������..");
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
									printf("\n�޸�ǰ������ԭ����(������%d���ֽڳ���):", MAX_INPUT);
									GetStr(up_emp.acPw, MAX_INPUT, 0);
									if(strcmp(up_emp.acPw, p0 ->acPw) == 0)
									{
										printf("\n������������(������%d���ֽڳ���):", MAX_INPUT);
										GetStr(p1 ->acPw, MAX_INPUT, 0);
										flag = 0;
									}
									else
									{
										printf("\n�����������,����������:");
										flag = 1;
									}
								}
								while(flag);
								printf("\n�����޸�Ϊ(������%d���ֽڳ���):", MAX_INPUT);
								GetStr(p1 ->acNum, MAX_INPUT, 1);
								printf("\n�����޸�Ϊ(������20���ֽڳ���):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n�û���ɫ�޸�Ϊ(0-����Ա,1-����Ա,2-Boss/����):");
								do
								{
									scanf("%d", &p1 ->nRole);
									fflush(stdin);
									switch(p1 ->nRole)	//����У��
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n�������,����������!");
										flag = 1;
										break;
									}
								}
								while(flag);							
								if(LIST_update(p ->cmData, p1, head_emp))
								{
									FILE_update(p1, sizeof(struct stEmp), i, "db/emp.dat");	//ͬ�������ļ�
									free(p0);
									printf("\n��Ϣ�޸ĳɹ�!�밴���������..");
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
								printf("\n���������޸ĸ�����,�밴���������..");
								getch();
								return 1;
							case 'N':
								printf("\n���������޸ĸ�����,�밴���������..");
								getch();
								return 1;
							default:
								printf("\n�������,�밴�����������������");
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
					printf("δ�ҵ���Ҫ����Ϣ,�밴���������..");
					getch();
					return 1;
				}
			case 3:
				printf("��������Ҫ�޸ĵ�Ա����ɫ(0-����Ա,1-����Ա,2-Boss/����):");
				scanf("%d", &up_emp.nRole);
				fflush(stdin);
				count = LIST_count(head_emp);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_emp);	//��ȡ�����еĽ��
					p0 = (struct stEmp*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(up_emp.nRole == p0 ->nRole)
					{
						j++;
						printf("\n�ҵ��û���ɫΪ%d����Ϣ%d:\n��ɫ\t����\t����\n%d\t%s\t%s",up_emp.nRole, j, p0 ->nRole, p0 ->acNum, p0 ->acName);
						printf("\n������\"Y\"����\"N\"��ȷ�ϻ���ȡ��:");
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
									printf("\n�޸�ǰ������ԭ����(������%d���ֽڳ���):", MAX_INPUT);
									GetStr(up_emp.acPw, MAX_INPUT, 0);
									if(strcmp(up_emp.acPw, p0 ->acPw) == 0)
									{
										printf("\n������������(������%d���ֽڳ���):", MAX_INPUT);
										GetStr(p1 ->acPw, MAX_INPUT, 0);
										flag = 0;
									}
									else
									{
										printf("\n�����������,����������:");
										flag = 1;
									}
								}
								while(flag);
								printf("\n�����޸�Ϊ(������%d���ֽڳ���):", MAX_INPUT);
								GetStr(p1 ->acNum, MAX_INPUT, 1);
								printf("\n�����޸�Ϊ(������20���ֽڳ���):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n�û���ɫ�޸�Ϊ(0-����Ա,1-����Ա,2-Boss/����):");
								do
								{
									scanf("%d", &p1 ->nRole);
									fflush(stdin);
									switch(p1 ->nRole)	//����У��
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n�������,����������!");
										flag = 1;
										break;
									}
								}
								while(flag);							
								if(LIST_update(p ->cmData, p1, head_emp))
								{
									FILE_update(p1, sizeof(struct stEmp), i, "db/emp.dat");	//ͬ�������ļ�
									free(p0);
									flag = 0;
									printf("\n��Ϣ�޸ĳɹ�!�밴���������..");
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
									printf("\n�޸�ǰ������ԭ����(������%d���ֽڳ���):", MAX_INPUT);
									GetStr(up_emp.acPw, MAX_INPUT, 0);
									if(strcmp(up_emp.acPw, p0 ->acPw) == 0)
									{
										printf("\n������������(������%d���ֽڳ���):", MAX_INPUT);
										GetStr(p1 ->acPw, MAX_INPUT, 0);
										flag = 0;
									}
									else
									{
										printf("\n�����������,����������:");
										flag = 1;
									}
								}
								while(flag);
								printf("\n�����޸�Ϊ(������%d���ֽڳ���):", MAX_INPUT);
								GetStr(p1 ->acNum, MAX_INPUT, 1);
								printf("\n�����޸�Ϊ(������20���ֽڳ���):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n�û���ɫ�޸�Ϊ(0-����Ա,1-����Ա,2-Boss/����):");
								do
								{
									scanf("%d", &p1 ->nRole);
									fflush(stdin);
									switch(p1 ->nRole)	//����У��
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n�������,����������!");
										flag = 1;
										break;
									}
								}
								while(flag);							
								if(LIST_update(p ->cmData, p1, head_emp))
								{
									FILE_update(p1, sizeof(struct stEmp), i, "db/emp.dat");	//ͬ�������ļ�
									free(p0);
									flag = 0;
									printf("\n��Ϣ�޸ĳɹ�!�밴���������..");
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
								printf("\n���������޸ĸ�����\n..");
								flag = 0;
									break;
							case 'N':
								printf("\n���������޸ĸ�����\n..");
								flag = 0;
									break;
							default:
								printf("\n�������,�밴�����������������");
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
					printf("δ�ҵ���Ҫ����Ϣ,�밴���������..");
					getch();
					return 1;
				}
			case 4:
				return 1;
			default:
				printf("\n�������,����������!");
				flag = 1;
				break;
			}
		}
		while(flag);
	}
	else
	{
		printf("\n���ݿ���������,�޷��޸�!,�밴���������");
		getch();
		return 1;
	}
}


