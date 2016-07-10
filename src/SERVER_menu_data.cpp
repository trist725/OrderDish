
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
//��������SERVER_reread_menu
//
//�������ܣ��ض�����Ϣ�ļ���ͨ������
//			
//��������˵������
//
//����ֵ����
//˵��:���øú������������������Ϊvoid*��,ʹ��ǰ��ǿתΪʵ������
///////////////////////////////////////////////////////////////////////
//void SERVER_reread_menu()
//{
//	int count = LIST_count(head_menu);
//	if(count > 1)
//	{
//		LIST_free(head_menu);	//���ͷ�
//		head_menu = (PNode)FILE_find_all(sizeof(struct stMenu), "db/menu.dat");	//��ȡ�ļ��в�����Ϣ���浽ͨ������
//	}
//	else
//	{
//		head_menu = (PNode)FILE_find_all(sizeof(struct stMenu), "db/menu.dat");
//	}
//}

///////////////////////////////////////////////////////////////////////
//��������SERVER_menu_choice
//
//�������ܣ�������Ϣ����
//			
//��������˵������
//
//����ֵ��0 -- ���� 1 -- ����
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
			printf("�������!����������!");
			break;
		}
	}
	while(flag);
}

////////////////////////////////////////////////////////////////////////
//��������SERVER_menu_index
//
//�������ܣ���Ա��Ϣ��ѯ
//			
//��������˵��:
//					 
//����ֵ��0 -- ���� 1 -- ����
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
				printf("��������Ҫ��ѯ�Ĳ˱��(5λ����):");
				scanf("%d", &ind_menu.nNum);
				fflush(stdin);
				count = LIST_count(head_menu);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_menu);	//��ȡ�����еĽ��
					p0 = (struct stMenu*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(ind_menu.nNum == p0 ->nNum)
					{
						j++;
						printf("\n�ҵ���Ϣ%d:\n�˱��\t����\t�۸�\t\n%00005d\t%s\t%.2f\n", j, p0 ->nNum, p0 ->acName, p0 ->fPrice);
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
				printf("��������Ҫ��ѯ�Ĳ���(������20���ֽڳ���):");
				scanf("%s", ind_menu.acName);	//GetStr()��֧�ֻ�ȡ����,������scanf
				fflush(stdin);
				count = LIST_count(head_menu);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_menu);	//��ȡ�����еĽ��
					p0 = (struct stMenu*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(strcmp(ind_menu.acName, p0 ->acName) == 0)
					{
						j++;
						printf("\n�ҵ���Ϣ%d:\n�˱��\t����\t�۸�\t\n%00005d\t%s\t%.2f\n", j, p0 ->nNum, p0 ->acName, p0 ->fPrice);
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
				printf("��������Ҫ��ѯ�Ĳ˵ļ۸�:");
				scanf("%f", &ind_menu.fPrice);
				fflush(stdin);
				count = LIST_count(head_menu);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_menu);	//��ȡ�����еĽ��
					p0 = (struct stMenu*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(ind_menu.fPrice == p0 ->fPrice)
					{
						j++;
						printf("\n�ҵ���Ϣ%d:\n�˱��\t����\t�۸�\t\n%00005d\t%s\t%.2f\n", j, p0 ->nNum, p0 ->acName, p0 ->fPrice);
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
//��������SERVER_menu_add
//
//�������ܣ���Ա��Ϣ����
//			
//��������˵��:
//					 
//����ֵ��0 -- ���� 1 -- ����
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


	do	//��֤��ӵ���Ϣ�Ƿ��Ѿ�����
	{
		flag = 0;
		printf("��������Ҫ���ӵĲ˵ı��(5λ����):");
		scanf("%d", &p ->nNum);
		fflush(stdin);
		if(0 == menu_db_exists)
		{
			count = LIST_count(head_menu);	//��ȡ̨����+1(������head)
			for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
			{
				p2 = LIST_get(i + 1, head_menu);	//��ȡ�����еĽ��
				p0 = (struct stMenu*)(p2 ->cmData);	//ǿ��ת��������Ϊʵ������
				if(p ->nNum == p0 ->nNum)
				{
					printf("\n�ò˱���Ѿ�����,����������..");
					getch();
					flag = 1;
					break;
				}
			}
		}
	}
	while(flag);
	printf("\n��������Ҫ���ӵĲ���(������20���ֽڳ���):");
	scanf("%s", p ->acName);
	fflush(stdin);
	printf("\n��������Ҫ���ӵĲ˵ļ۸�:");
	scanf("%f", &p ->fPrice);
	fflush(stdin);
	p ->iStat = 0;
	printf("\n�������,����ӵĲ���ϢΪ:\n�˱��\t����\t\t�۸�\n%00005d\t%s\t%.2f\n������\"Y\"����\"N\"��ȷ�ϻ���ȡ��:", 
		p ->nNum, p ->acName, p ->fPrice);
	do
	{
		scanf("%c", &cAffirm);
		fflush(stdin);
		switch(cAffirm)
		{
		case 'y':
			printf("\n��Ϣ��ӳɹ�!�밴���������..");
			getch();
			if(0 == menu_db_exists)
			{
				if(FILE_add(p, sizeof(struct stMenu), "db/menu.dat"))	//���浽�ļ�
				{
					LIST_add(p, head_menu);	//ͬ������cache
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
				if(FILE_write_all(head_menu, sizeof(struct stMenu), "db/menu.dat"))	//���浽�ļ�
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
			printf("\n��Ϣ��ӳɹ�!�밴���������..");
			getch();
			if(0 == menu_db_exists)
			{
				if(FILE_add(p, sizeof(struct stMenu), "db/menu.dat"))	//���浽�ļ�
				{
					LIST_add(p, head_menu);	//ͬ������cache
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
				if(FILE_write_all(head_menu, sizeof(struct stMenu), "db/menu.dat"))	//���浽�ļ�
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
//��������SERVER_menu_del
//
//�������ܣ�������Ϣɾ��
//			
//��������˵��:
//					 
//����ֵ��0 -- ���� 1 -- ����
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
			switch(n)	//����У��
			{
			case 1:
				j = 0;
				printf("��������Ҫɾ���Ĳ˱��(5λ����):");
				scanf("%d", &del_menu.nNum);
				fflush(stdin);
				count = LIST_count(head_menu);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_menu);	//��ȡ�����еĽ��
					p0 = (struct stMenu*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(del_menu.nNum == p0 ->nNum)
					{
						j++;
						printf("\n�ҵ���Ϣ%d:\n�˱��\t����\t\t�۸�\t\n%00005d\t%s\t%.2f\n", j, p0 ->nNum, p0 ->acName, p0 ->fPrice);
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
								if(LIST_remove(p ->cmData, head_menu))
								{
									FILE_write_all(head_menu, sizeof(struct stMenu), "db/menu.dat");	//ͬ�������ļ�
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
								printf("\n��Ϣɾ���ɹ�!�밴���������..");
								getch();
								if(LIST_remove(p ->cmData, head_menu))
								{
									FILE_write_all(head_menu, sizeof(struct stMenu), "db/menu.dat");	//ͬ�������ļ�
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
				printf("��������Ҫɾ���Ĳ���(������20���ֽڳ���):");
				scanf("%s", del_menu.acName);
				fflush(stdin);
				count = LIST_count(head_menu);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_menu);	//��ȡ�����еĽ��
					p0 = (struct stMenu*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(strcmp(del_menu.acName, p0 ->acName) == 0)
					{
						j++;
						printf("\n�ҵ���Ϣ%d:\n�˱��\t����\t�۸�\t\n%00005d\t%s\t%.2f\n", j, p0 ->nNum, p0 ->acName, p0 ->fPrice);
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
								if(LIST_remove(p ->cmData, head_menu))
								{
									FILE_write_all(head_menu, sizeof(struct stMenu), "db/menu.dat");	//ͬ�������ļ�
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
								printf("\n��Ϣɾ���ɹ�!�밴���������..");
								getch();
								if(LIST_remove(p ->cmData, head_menu))
								{
									FILE_write_all(head_menu, sizeof(struct stMenu), "db/menu.dat");	//ͬ�������ļ�
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
			case 3:
				j = 0;
				printf("��������Ҫɾ���Ĳ˵ļ۸�:");
				scanf("%f", &del_menu.fPrice);
				fflush(stdin);
				count = LIST_count(head_menu);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_menu);	//��ȡ�����еĽ��
					p0 = (struct stMenu*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(del_menu.fPrice == p0 ->fPrice)
					{
						j++;
						printf("\n�ҵ���Ϣ%d:\n�˱��\t����\t�۸�\t\n%00005d\t%s\t%.2f\n", j, p0 ->nNum, p0 ->acName, p0 ->fPrice);
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
								if(LIST_remove(p ->cmData, head_menu))
								{
									FILE_write_all(head_menu, sizeof(struct stMenu), "db/menu.dat");	//ͬ�������ļ�
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
								if(LIST_remove(p ->cmData, head_menu))
								{
									FILE_write_all(head_menu, sizeof(struct stMenu), "db/menu.dat");	//ͬ�������ļ�
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
//��������SERVER_menu_update
//
//�������ܣ���Ա��Ϣ�޸�
//
//��������˵��:
//
//����ֵ��0 -- ���� 1 -- ����
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
			switch(n)	//����У��
			{
			case 1:
				j = flag = 0;
				printf("��������Ҫ�޸ĵĲ˱��(5λ����):");
				scanf("%d", &up_menu.nNum);
				count = LIST_count(head_menu);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_menu);	//��ȡ�����еĽ��
					p0 = (struct stMenu*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(up_menu.nNum, p0 ->nNum)
					{
						j++;
						printf("\n�ҵ���Ϣ%d:\n�˱��\t����\t�۸�\t\n%00005d\t%s\t%.2f\n", j, p0 ->nNum, p0 ->acName, p0 ->fPrice);
						printf("\n������\"Y\"����\"N\"��ȷ�ϻ���ȡ���޸�:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								p1 = (struct stMenu*)malloc(sizeof(struct stMenu));
								flag = 0;
								printf("\n�˱���޸�Ϊ(5λ����):");
								scanf("%d",p1 ->nNum);
								fflush(stdin);
								printf("\n�����޸�Ϊ(������20���ֽڳ���):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n�˼۸��޸�Ϊ:");
								scanf("%f", &p1 ->fPrice);
								fflush(stdin);
								while(flag);

								if(LIST_update(p ->cmData, p1, head_menu))
								{
									FILE_update(p1, sizeof(struct stMenu), i, "db/menu.dat");	//ͬ�������ļ�
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
								p1 = (struct stMenu*)malloc(sizeof(struct stMenu));
								flag = 0;
								printf("\n�˱���޸�Ϊ(5λ����):");
								scanf("%d",p1 ->nNum);
								fflush(stdin);
								printf("\n�����޸�Ϊ(������20���ֽڳ���):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n�˼۸��޸�Ϊ:");
								scanf("%f", &p1 ->fPrice);
								fflush(stdin);
								while(flag);

								if(LIST_update(p ->cmData, p1, head_menu))
								{
									FILE_update(p1, sizeof(struct stMenu), i, "db/menu.dat");	//ͬ�������ļ�
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
				printf("��������Ҫ�޸ĵĲ���(������20���ֽڳ���):");
				scanf("%s", up_menu.acName);
				fflush(stdin);
				count = LIST_count(head_menu);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_menu);	//��ȡ�����еĽ��
					p0 = (struct stMenu*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(strcmp(up_menu.acName, p0 ->acName) == 0)
					{
						j++;
						printf("\n�ҵ���Ϣ%d:\n�˱��\t����\t�۸�\t\n%00005d\t%s\t%.2f\n", j, p0 ->nNum, p0 ->acName, p0 ->fPrice);
						printf("\n������\"Y\"����\"N\"��ȷ�ϻ���ȡ���޸�:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								p1 = (struct stMenu*)malloc(sizeof(struct stMenu));
								flag = 0;
								printf("\n�˱���޸�Ϊ(5λ����):");
								scanf("%d",p1 ->nNum);
								fflush(stdin);
								printf("\n�����޸�Ϊ(������20���ֽڳ���):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n�˼۸��޸�Ϊ:");
								scanf("%f", &p1 ->fPrice);
								fflush(stdin);
								while(flag);
								if(LIST_update(p ->cmData, p1, head_menu))
								{
									FILE_update(p1, sizeof(struct stMenu), i, "db/menu.dat");	//ͬ�������ļ�
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
								p1 = (struct stMenu*)malloc(sizeof(struct stMenu));
								flag = 0;
								printf("\n�˱���޸�Ϊ(5λ����):");
								scanf("%d",p1 ->nNum);
								fflush(stdin);
								printf("\n�����޸�Ϊ(������20���ֽڳ���):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n�˼۸��޸�Ϊ:");
								scanf("%f", &p1 ->fPrice);
								fflush(stdin);
								while(flag);
								if(LIST_update(p ->cmData, p1, head_menu))
								{
									FILE_update(p1, sizeof(struct stMenu), i, "db/menu.dat");	//ͬ�������ļ�
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
				printf("��������Ҫ�޸ĵĲ˵ļ۸�:");
				scanf("%f", &up_menu.fPrice);
				fflush(stdin);
				count = LIST_count(head_menu);	//��ȡԱ����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_menu);	//��ȡ�����еĽ��
					p0 = (struct stMenu*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(up_menu.fPrice == p0 ->fPrice)
					{
						j++;
						printf("\n�ҵ���Ϣ%d:\n�˱��\t����\t�۸�\t\n%d\t%s\t%.2f\n", j, p0 ->nNum, p0 ->acName, p0 ->fPrice);
						printf("\n������\"Y\"����\"N\"��ȷ�ϻ���ȡ��:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								p1 = (struct stMenu*)malloc(sizeof(struct stMenu));
								flag = 0;
								printf("\n�˱���޸�Ϊ(5λ����):");
								scanf("%d",p1 ->nNum);
								fflush(stdin);
								printf("\n�����޸�Ϊ(������20���ֽڳ���):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n�˼۸��޸�Ϊ:");
								scanf("%f", &p1 ->fPrice);
								fflush(stdin);
								while(flag);

								if(LIST_update(p ->cmData, p1, head_menu))
								{
									FILE_update(p1, sizeof(struct stMenu), i, "db/menu.dat");	//ͬ�������ļ�
									printf("\n��Ϣ�޸ĳɹ�!�밴���������..");
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
								printf("\n�˱���޸�Ϊ(5λ����):");
								scanf("%d",p1 ->nNum);
								fflush(stdin);
								printf("\n�����޸�Ϊ(������20���ֽڳ���):");
								scanf("%s", p1 ->acName);
								fflush(stdin);
								printf("\n�˼۸��޸�Ϊ:");
								scanf("%f", &p1 ->fPrice);
								fflush(stdin);
								while(flag);

								if(LIST_update(p ->cmData, p1, head_menu))
								{
									FILE_update(p1, sizeof(struct stMenu), i, "db/menu.dat");	//ͬ�������ļ�
									printf("\n��Ϣ�޸ĳɹ�!�밴���������..");
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


