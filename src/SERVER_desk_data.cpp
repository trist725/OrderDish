
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
//��������SERVER_reread_desk
//
//�������ܣ��ض�̨����Ϣ�ļ���ͨ������
//			
//��������˵������
//
//����ֵ����
//˵��:���øú������������������Ϊvoid*��,ʹ��ǰ��ǿתΪʵ������
///////////////////////////////////////////////////////////////////////
//void SERVER_reread_desk()
//{
//	int count = LIST_count(head_desk);
//	if(count > 1)
//	{
//		LIST_free(head_desk);	//���ͷ�
//		head_desk = (PNode)FILE_find_all(sizeof(struct stDesk), "db/desk.dat");	//��ȡ�ļ���̨����Ϣ���浽ͨ������
//	}
//	else
//		{
//			head_desk = (PNode)FILE_find_all(sizeof(struct stDesk), "db/desk.dat");
//		}
//}

///////////////////////////////////////////////////////////////////////
//��������SERVER_desk_choice
//
//�������ܣ�̨����Ϣ����
//			
//��������˵������
//
//����ֵ��0 -- ���� 1 -- ����
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
			printf("�������!����������!");
			break;
		}
	}
	while(flag);
}

////////////////////////////////////////////////////////////////////////
//��������SERVER_desk_index
//
//�������ܣ�̨����Ϣ��ѯ
//			
//��������˵��:
//					 
//����ֵ��0 -- ���� 1 -- ����
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
				printf("��������Ҫ��ѯ������:");
				scanf("%d", &num);
				fflush(stdin);
				count = LIST_count(head_desk);	//��ȡ̨����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_desk);	//��ȡ�����еĽ��
					p0 = (struct stDesk*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(num == p0 ->nNum)
					{
						j++;
						printf("\n�ҵ���Ϣ%d:\n����\t״̬\t����\t\n%d\t%d\t%s\n", j, p0 ->nNum, p0 ->iStat, p0 ->acInfo);
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
				printf("��������Ҫ��ѯ��̨��״̬(0--������,1--����):");
				scanf("%d", &stat);
				fflush(stdin);
				count = LIST_count(head_desk);	//��ȡ̨����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_desk);	//��ȡ�����еĽ��
					p0 = (struct stDesk*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(stat == p0 ->iStat)
					{
						j++;
						printf("\n�ҵ���Ϣ%d:\n����\t״̬\t����\t\n%d\t%d\t%s\n", j, p0 ->nNum, p0 ->iStat, p0 ->acInfo);
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
//��������SERVER_desk_add
//
//�������ܣ�̨����Ϣ����
//			
//��������˵��:
//					 
//����ֵ��0 -- ���� 1 -- ����
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

	printf("��������Ҫ���ӵ�̨����״̬(0--������,1--����):");
	do
	{
		scanf("%d", &p ->iStat);
		fflush(stdin);
		switch(p ->iStat)	//����У��
		{
		case 0: flag = 0; break;
		case 1: flag = 0; break;
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
		printf("\n��������Ҫ���ӵ�̨��������(4λ����):");
		scanf("%d", &p ->nNum);
		fflush(stdin);
		if(0 == desk_db_exists)
		{
			count = LIST_count(head_desk);	//��ȡ̨����+1(������head)
			for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
			{
				p2 = LIST_get(i + 1, head_desk);	//��ȡ�����еĽ��
				p0 = (struct stDesk*)(p2 ->cmData);	//ǿ��ת��������Ϊʵ������
				if(p ->nNum == p0 ->nNum)
				{
					printf("\n�������Ѿ�����,����������..");
					getch();
					flag = 1;
					break;
				}
			}
		}
	}
	while(flag);
	printf("\n��������Ҫ���ӵ�̨����������Ϣ(������20���ֽڳ���):");
	scanf("%s", p ->acInfo);
	fflush(stdin);
	p ->iOrder = 0;
	printf("\n�������,����ӵ�̨����ϢΪ:\n����\t״̬\t����\n%d\t%d\t%s\n������\"Y\"����\"N\"��ȷ�ϻ���ȡ��:", 
		p ->nNum, p ->iStat, p ->acInfo);
	do
	{
		scanf("%c", &cAffirm);
		fflush(stdin);
		switch(cAffirm)
		{
		case 'y':
			printf("\n��Ϣ��ӳɹ�!�밴���������..");
			getch();
			if(0 == desk_db_exists)
			{
				if(FILE_add(p, sizeof(struct stDesk), "db/desk.dat"))	//���浽�ļ�
				{
					LIST_add(p, head_desk);	//ͬ������cache
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
				if(FILE_write_all(head_desk, sizeof(struct stDesk), "db/desk.dat"))	//���浽�ļ�
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
			printf("\n��Ϣ��ӳɹ�!�밴���������..");
			getch();
			if(0 == desk_db_exists)
			{
				if(FILE_add(p, sizeof(struct stDesk), "db/desk.dat"))	//���浽�ļ�
				{
					LIST_add(p, head_desk);	//ͬ������cache
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
				if(FILE_write_all(head_desk, sizeof(struct stDesk), "db/desk.dat"))	//���浽�ļ�
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
//��������SERVER_desk_del
//
//�������ܣ�̨����Ϣɾ��
//			
//��������˵��:
//					 
//����ֵ��0 -- ���� 1 -- ����
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
			switch(n)	//����У��
			{
			case 1:
				j = 0;
				printf("��������Ҫɾ����̨������(4λ����):");
				scanf("%d", &del_desk.nNum);
				fflush(stdin);
				count = LIST_count(head_desk);	//��ȡ̨����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_desk);	//��ȡ�����еĽ��
					p0 = (struct stDesk*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(del_desk.nNum == p0 ->nNum)
					{
						j++;
						printf("\n������Ϊ%d����Ϣ:\n����\t״̬\t����\n%d\t%d\t%s", del_desk.nNum, p0 ->nNum, p0 ->iStat, p0 ->acInfo);
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
								if(LIST_remove(p ->cmData, head_desk))
								{
									FILE_write_all(head_desk, sizeof(struct stDesk), "db/desk.dat");	//ͬ�������ļ�
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
								printf("\n��Ϣɾ���ɹ�!�밴���������..");
								getch();
								if(LIST_remove(p ->cmData, head_desk))
								{
									FILE_write_all(head_desk, sizeof(struct stDesk), "db/desk.dat");	//ͬ�������ļ�
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
				printf("��������Ҫɾ����̨��״̬(0--������,1--����):");
				scanf("%d", &del_desk.iStat);
				fflush(stdin);
				count = LIST_count(head_desk);	//��ȡ̨����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_desk);	//��ȡ�����еĽ��
					p0 = (struct stDesk*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(del_desk.iStat == p0 ->iStat)
					{
						j++;
						printf("\n�ҵ�״̬Ϊ%d����Ϣ%d:\n����\t״̬\t����\n%d\t%d\t%s", del_desk.iStat, j, p0 ->nNum, p0 ->iStat, p0 ->acInfo);
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
								if(LIST_remove(p ->cmData, head_desk))
								{
									FILE_write_all(head_desk, sizeof(struct stDesk), "db/desk.dat");	//ͬ�������ļ�
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
								printf("\n��Ϣɾ���ɹ�!�밴���������..");
								getch();
								if(LIST_remove(p ->cmData, head_desk))
								{
									FILE_write_all(head_desk, sizeof(struct stDesk), "db/desk.dat");	//ͬ�������ļ�
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
								printf("\n��������ɾ��������..");
								flag = 0;
								break;
							case 'N':
								printf("\n��������ɾ��������..");
								flag = 0;
								break;
							default:
								printf("\n�������,�밴���������������");
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
//��������SERVER_desk_update
//
//�������ܣ�̨����Ϣ�޸�
//
//��������˵��:
//
//����ֵ��0 -- ���� 1 -- ����
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
			switch(n)	//����У��
			{
			case 1:
				j = flag = 0;
				printf("��������Ҫ�޸ĵ�̨����(4λ����):");
				scanf("%d", &up_desk.nNum);
				count = LIST_count(head_desk);	//��ȡ̨����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_desk);	//��ȡ�����еĽ��
					p0 = (struct stDesk*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(up_desk.nNum == p0 ->nNum)
					{
						j++;
						printf("\n�ҵ�����Ϊ%d����Ϣ%d:\n����\t״̬\t����\n%d\t%d\t%s", up_desk.nNum, j, p0 ->nNum, p0 ->iStat, p0 ->acInfo);
						printf("\n������\"Y\"����\"N\"��ȷ�ϻ���ȡ���޸�:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								p1 = (struct stDesk*)malloc(sizeof(struct stDesk));
								printf("\n�����޸�Ϊ(4λ����):");
								scanf("%d", &p1 ->nNum);
								fflush(stdin);
								printf("\n״̬�޸�Ϊ(0--������,1--����):");	
								do
								{
									scanf("%d", &p1 ->iStat);
									fflush(stdin);
									switch(p1 ->iStat)	//����У��
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n�������,����������!");
										flag = 1;
										break;
									}
								}while(flag);
								printf("\n̨�������޸�Ϊ(������20���ֽڳ���):");
								scanf("%s", p1 ->acInfo);
								fflush(stdin);			
								if(LIST_update(p ->cmData, p1, head_desk))
								{
									FILE_update(p1, sizeof(struct stDesk), i, "db/desk.dat");	//ͬ������
									free(p0);
									printf("\n��Ϣ�޸ĳɹ�!\n..");
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
								printf("\n�����޸�Ϊ(4λ����):");
								scanf("%d", &p1 ->nNum);
								fflush(stdin);
								printf("\n״̬�޸�Ϊ(0--������,1--����):");	
								do
								{
									scanf("%d", &p1 ->iStat);
									fflush(stdin);
									switch(p1 ->iStat)	//����У��
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n�������,����������!");
										flag = 1;
										break;
									}
								}while(flag);
								printf("\n̨�������޸�Ϊ(������20���ֽڳ���):");
								scanf("%s", p1 ->acInfo);
								fflush(stdin);			
								if(LIST_update(p ->cmData, p1, head_desk))
								{
									FILE_update(p1, sizeof(struct stDesk), i, "db/desk.dat");	//ͬ������
									free(p0);
									printf("\n��Ϣ�޸ĳɹ�!\n..");
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
				break;
			case 2:
				j = flag = 0;
				printf("��������Ҫ�޸ĵ�̨��״̬(0--������,1--����):");
				scanf("%d", &up_desk.iStat);
				fflush(stdin);
				count = LIST_count(head_desk);	//��ȡ̨����+1(������head)
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_desk);	//��ȡ�����еĽ��
					p0 = (struct stDesk*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					if(up_desk.iStat == p0 ->iStat)
					{
						j++;
						printf("\n�ҵ�״̬Ϊ%d����Ϣ%d:\n����\t״̬\t����\n%d\t%d\t%s", up_desk.iStat, j, p0 ->nNum, p0 ->iStat, p0 ->acInfo);
						printf("\n������\"Y\"����\"N\"��ȷ�ϻ���ȡ���޸�:");
						do
						{
							scanf("%c", &cAffirm);
							fflush(stdin);
							switch(cAffirm)
							{
							case 'y':
								p1 = (struct stDesk*)malloc(sizeof(struct stDesk));
								printf("\n�����޸�Ϊ(4λ����):");
								scanf("%d", &p1 ->nNum);
								fflush(stdin);
								do
								{
									printf("\n״̬�޸�Ϊ(0--������,1--����):");
									scanf("%d", &p1 ->iStat);
									fflush(stdin);
									switch(p1 ->iStat)	//����У��
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n�������,����������!");
										flag = 1;
										break;
									}
								}while(flag);
								printf("\n̨�������޸�Ϊ(������20���ֽڳ���):");
								scanf("%s", p1 ->acInfo);
								fflush(stdin);
								printf("\n��Ϣ�޸ĳɹ�\n!..");
								getch();
								if(LIST_update(p ->cmData, p1, head_desk))
								{
									FILE_update(p1, sizeof(struct stDesk), i, "db/desk.dat");	//ͬ�������ļ�
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
								printf("\n�����޸�Ϊ(4λ����):");
								scanf("%d", &p1 ->nNum);
								fflush(stdin);
								do
								{
									printf("\n״̬�޸�Ϊ(0--������,1--����):");
									scanf("%d", &p1 ->iStat);
									fflush(stdin);
									switch(p1 ->iStat)	//����У��
									{
									case 0: flag = 0; break;
									case 1: flag = 0; break;
									case 2: flag = 0; break;
									default:
										printf("\n�������,����������!");
										flag = 1;
										break;
									}
								}while(flag);
								printf("\n̨�������޸�Ϊ(������20���ֽڳ���):");
								scanf("%s", p1 ->acInfo);
								fflush(stdin);
								printf("\n��Ϣ�޸ĳɹ�\n!..");
								getch();
								if(LIST_update(p ->cmData, p1, head_desk))
								{
									FILE_update(p1, sizeof(struct stDesk), i, "db/desk.dat");	//ͬ�������ļ�
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
			case 3:
				return 1;
			default:
				printf("\n�������,����������!");
				flag = 1;
				break;
			}		
		}while(flag);
	}
	else
	{
		printf("\n���ݿ���������,�޷��޸�!,�밴���������");
		getch();
		return 1;
	}
}
