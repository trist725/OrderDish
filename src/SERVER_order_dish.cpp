
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
PNode head_order_bill;	//��������
PNode head_tmp_order;	//��ʱ�������
/////////////////////////////////////////////////////////////////////
//��������SERVER_open_desk
//
//�������ܣ�����
//
//��������˵��:
//				
//����ֵ��0 -- �˳� 1 -- ����
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
			printf("\t\t����\t״̬\t\t����\n");
			count = LIST_count(head_desk);
			for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
			{
				p = LIST_get(i + 1, head_desk);	//��ȡ�����еĽ��
				p0 = (struct stDesk*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
				printf("\t\t%0004d\t%d\t\t%s\n", p0 ->nNum, p0 ->iStat, p0 ->acInfo);	//��ӡ̨����Ϣ
			}
			do
			{
				flag = 0;
				printf("\n\t\t��������Ҫ�������Ż�������0�˳�:");
				scanf("%d", &open_desk);
				fflush(stdin);
				if(0 == open_desk)
				{
					return 1;
				}
				else
				{
					for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
					{
						p = LIST_get(i + 1, head_desk);	//��ȡ�����еĽ��
						p0 = (struct stDesk*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
						if((open_desk == p0 ->nNum) && (1 == p0 ->iStat))
						{
							p0 ->iStat = 0;
							p0 ->iOrder = 0;
							FILE_update(p0, sizeof(struct stDesk), i, "db/desk.dat");	//ͬ�������ļ�
							printf("\n�����ɹ�!�Ƿ��������?\"Y\"��\"N\":");						
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
									printf("\n�������,����������:");
									flag = 1;
									break;
								}
							}
							while(flag);
						}
						else
							if((open_desk == p0 ->nNum) && (0 == p0 ->iStat))
							{
								printf("\n��̨����ǰ������,��ѡ������̨��..");
								getch();
								flag = 1;
								break;
							}
					}
					if(!flag)
					{
						printf("\n��Ҫ�������Ų�����,����������..");
						getch();
						flag = 1;
					}
				}
			}
			while(flag);
		}
		else
		{
			printf("���ݿ���ȱ�ٱ�Ҫ������,�޷�ִ�иò���..");
			getch();
			return 1;
		}
	}
	else
	{
		printf("���ݿ���ȱ�ٱ�Ҫ������,�޷�ִ�иò���..");
		getch();
		return 1;
	}
}

/////////////////////////////////////////////////////////////////////
//��������SERVER_order_dish
//
//�������ܣ����
//
//��������˵��:
//				mode:0--ֱ�ӵ��,1--�ӿ���������
//
//����ֵ��0 -- ���� 1 -- ����
////////////////////////////////////////////////////////////////////
int SERVER_order_dish(int mode, int desk)
{	
	//SERVER_reread_desk();	//�ض�����
	//SERVER_reread_menu();
	int Mcount = LIST_count(head_menu);	//��ȡ������
	int Dcount = LIST_count(head_desk);

	if((0 == desk_db_exists)	//�ж��Ƿ�������
		&& (0 == menu_db_exists)
		&& (Mcount > 1)
		&& (Dcount > 1))
	{
		head_order_bill = LIST_init(NULL);	//���������ʼ��
		head_tmp_order = LIST_init(NULL);	//��ʱ��������ʼ��
		int order_num, num, n, flag, flag1, flag2, flag3, flag4, flag5, flag6, i, j, cho, count, count1, desk_num;
		float sum = 0;
		struct stOrder* p2;
		struct stMenu* p0;
		struct stDesk* p1;
		PNode p, p3;
		if(mode)	//�ӿ���������
		{
			flag3 = 1;
			if(flag3)
			{
				system("cls");
				printf("\n\n");
				Print_Str_Center("��˽���");
				printf("\n\n\t\t�˱��\t����\t\t�۸�");
				count = LIST_count(head_menu);
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_menu);	//��ȡ�����еĽ��
					p0 = (struct stMenu*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					printf("\n\t\t%00005d\t%s\t%.2f\t\n", p0 ->nNum, p0 ->acName, p0 ->fPrice);	//�г�����
				}
			}
			do
			{
				flag2 = 0;
rechoice:			printf("\n\n��ѡ��(0.���� 1.�Ӳ� 2.���� 3.ȷ��(���ɶ���)):");
				scanf("%d", &cho);
				fflush(stdin);
				switch(cho)
				{
				case 0: return 1;
				case 1:
					do
					{
						flag = 1; flag4 = 1;
						printf("\n\n��������Ҫ��Ĳ˵ı��:");
						scanf("%d", &order_num);
						fflush(stdin);
						printf("\n��������Ҫ��Ĳ˵ķ���:");
						scanf("%d", &num);
						fflush(stdin);
						for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
						{
							p = LIST_get(i + 1, head_menu);
							p0 = (struct stMenu*)(p ->cmData);
							if(order_num == p0 ->nNum)	//�������˴���
							{	
								flag3 = 0;
								flag4 = 0;
								flag1 = 1;
								count1 = LIST_count(head_tmp_order);
								for(j = 1; j < count1; j++)
								{
									p3 = LIST_get(j + 1, head_tmp_order);
									p2 = (struct stOrder*)(p3 ->cmData);
									if(order_num == p2 ->nNum)	//����ѵ�
									{
										p2 ->nNum += num;
										sum += (p2 ->Menu_T.fPrice * num);
										LIST_update(p3 ->cmData, p2, head_tmp_order);
										flag1 = 0;
										break;
									}
								}
								if(flag1)	//���δ��
								{
									p2 = (struct stOrder*)malloc(sizeof(struct stOrder));
									p2 ->Menu_T = *p0;
									p2 ->nNum = num;
									sum += (p2 ->Menu_T.fPrice * num);
									LIST_add(p2, head_tmp_order);	//������ʱ�������
									p2 ->Menu_T.iStat = 1;
								}
								system("cls");
								printf("\t�ܽ��:%.2f", sum);
								printf("\n\n");
								Print_Str_Center("��˽���");
								printf("\n\n\t\t�˱��\t����\t\t�۸�\t����");

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
											printf("\n\t*\t%00005d\t%s\t%.2f\t%d\n", p0 ->nNum, p0 ->acName, p0 ->fPrice, p2 ->nNum);//���ò��Ƿ��ѵ�,�ѵ����ڱ��ǰ�Ӹ�*��
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
							printf("\n������Ĳ˱�Ų�����,����������..");
							flag = 1;
							getch();
						}
						else
						{
							flag6 = 0;
							do
							{
								printf("\n0--����,1--����:");
								scanf("%d", &n);
								fflush(stdin);		
								switch(n)	//����У��
								{
								case 0: goto rechoice;
								case 1: break;
								default:
									printf("\n�������,����������!");
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
						printf("\n\n��������Ҫ���Ĳ˵ı�Ż�������0����:");
						scanf("%d", &order_num);
						fflush(stdin);
						if(0 == order_num)
						{
							return 1;
						}
						else
						{
							printf("\n��������Ҫ���Ĳ˵ķ���:");
							scanf("%d", &num);
							fflush(stdin);
							for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
							{
								p = LIST_get(i + 1, head_menu);
								p0 = (struct stMenu*)(p ->cmData);
								if(order_num == p0 ->nNum)	//�������˴���
								{	
									flag4 = 0;
									flag1 = 1;
									count1 = LIST_count(head_tmp_order);
									for(j = 1; j < count1; j++)
									{
										p3 = LIST_get(j + 1, head_tmp_order);
										p2 = (struct stOrder*)(p3 ->cmData);
										if(p0 ->nNum == p2 ->nNum)	//����ѵ�
										{
											if(p2 ->nNum >= num)	//У����ķ����Ƿ�����ѵ�ķ���
											{
												p2 ->nNum -= num;
												sum -= (p2 ->Menu_T.fPrice * num);
												flag1 = 0;
												break;
											}
											else
											{
												printf("\n��ֻ����%d��,���ܼ�%d��..", p2 ->nNum, num);
												goto rescan;	//���������������
											}
										}
									}
									if(flag1)	//���δ��
									{
										printf("\n���������δ��...");
										goto rescan;	//���������������
									}
									system("cls");
									printf("\n\n");
									Print_Str_Center("��˽���");
									printf("\n\n\t\t�˱��\t����\t\t�۸�\t����");

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
												printf("\n\t*\t%00005d\t%s\t%.2f\t%d\n", p0 ->nNum, p0 ->acName, p0 ->fPrice, p2 ->nNum);//���ò��Ƿ��ѵ�,�ѵ����ڱ��ǰ�Ӹ�*��
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
								printf("\n������Ĳ˱�Ų�����,����������..");
								flag = 1;
								getch();
							}
							else
							{
								flag6 = 0;
								do
								{
									printf("\n0--����,1--����:");
									scanf("%d", &n);
									fflush(stdin);		
									switch(n)	//����У��
									{
									case 0: goto rechoice;
									case 1: break;
									default:
										printf("\n�������,����������!");
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
						for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
						{
							p = LIST_get(i + 1, head_desk);
							p1 = (struct stDesk*)(p ->cmData);
							if(desk == p1 ->nNum)
							{
								p1 ->iStat = 1;	//̨��״̬��Ϊ�ѵ��
								break;
							}
						}
						SERVER_creat_bill(desk, sum);
						printf("\n��˳ɹ�!ף�������ò�..");
						getch();
						return 1;
					}
					else
					{
						printf("\n������˺���ȷ�����ɶ���..");
						break;
					}
				default: 
					printf("\n�������,����������");
					flag2 = 1;
					break;
				}
			}while(flag2);
		}
		else	//ֱ�ӵ��
		{
			int Dcount = LIST_count(head_desk);
			if(Dcount > 1)
			{
				int count, i, flag = 1;
				char cAffirm;
				struct stDesk* p0;
				PNode p;
				system("cls");
				printf("\t\t����\t״̬\t\t����\n");
				count = LIST_count(head_desk);
				for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
				{
					p = LIST_get(i + 1, head_desk);	//��ȡ�����еĽ��
					p0 = (struct stDesk*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
					printf("\t\t%0004d\t%d\t\t%s\n", p0 ->nNum, p0 ->iStat, p0 ->acInfo);	//��ӡ̨����Ϣ
				}
				do
				{
					flag = 0;
					printf("\n\t�����δ����,���ȿ���,������Ѿ�����,���������Ż�������0����:");
					scanf("%d", &desk_num);
					fflush(stdin);
					if(0 == desk_num)
					{
						return 1;
					}
					else
					{
						for(i = 1; i < count; i++)	//i=1��Ϊ���ų�head
						{
							p = LIST_get(i + 1, head_desk);	//��ȡ�����еĽ��
							p0 = (struct stDesk*)(p ->cmData);	//ǿ��ת��������Ϊʵ������
							if((desk_num == p0 ->nNum) && (1 == p0 ->iStat))
							{
								p0 ->iStat = 0;
								p0 ->iOrder = 0;
								FILE_update(p0, sizeof(struct stDesk), i, "db/desk.dat");
								printf("\n�����ɹ�!�Ƿ��������?\"Y\"��\"N\":");						
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
										printf("\n�������,����������:");
										flag = 1;
										break;
									}
								}
								while(flag);
							}
							else
								if((desk_num == p0 ->nNum) && (0 == p0 ->iStat))
								{
									printf("\n��̨����ǰ������,��ѡ������̨��..");
									getch();
									flag = 1;
									break;
								}
								else
									if((desk_num == p0 ->nNum) && (0 == p0 ->iOrder))
									{
										printf("\n��̨����ǰδ���,�Ƿ��������?\"Y\"��\"N\":");
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
												printf("\n�������,����������:");
												flag = 1;
												break;
											}
										}
										while(flag);
									}
						}
						if(!flag)
						{
							printf("\n��Ҫ�������Ų�����,����������..");
							getch();
							flag = 1;
						}
					}
				}
				while(flag);
			}
			else
			{
				printf("���ݿ���ȱ�ٱ�Ҫ������,�޷�ִ�иò���..");
				getch();
				return 0;
			}
		}
	}
	else
	{
		printf("���ݿ���ȱ�ٱ�Ҫ������,�޷�ִ�иò���..");
		getch();
		return 0;
	}
}

/////////////////////////////////////////////////////////////////////
//��������SERVER_creat_bill
//
//�������ܣ����ɶ���
//
//��������˵��:desk--���ɸö���������,һ�����Ŷ�Ӧ�������
//				sum--�����ܽ��
//
//����ֵ����
////////////////////////////////////////////////////////////////////
void SERVER_creat_bill(int desk, float sum)
{
	char ac1[15] = "bill/";	//Ŀ¼��
	char ac2[9];
	struct stIncome income_T;
	struct stBill* p = (struct stBill*)malloc(sizeof(struct stBill));
	write_cur_time(p ->acDate, 0);	//����
	strcpy(ac2, p ->acDate);	//��������Ϊ�ļ���,ÿ��һ�������ļ�
	strcat(ac1, ac2);
	write_cur_time(p ->acTime, 1);	//����
	p ->DeskNum = desk;	//����
	strcpy(p ->nEmpNum, acInput_Emp_Num);	//����Ա����
	p ->iPay = 0;	//֧��״̬
	p ->sum = sum;	//�ܽ��
	LIST_add(p, head_order_bill);
	income_T.fSum = sum;
	strcpy(income_T.acDate, p ->acDate);
	strcpy(income_T.acEmpNum, acInput_Emp_Num);
	if(0 == access(ac1, 0))
	{
		FILE_add(p, sizeof(struct stBill), ac1);	//�����ļ�
		FILE_add(&income_T, sizeof(struct stIncome), "db/income.dat");	//ͳ���ļ�
	}
	else
	{
		FILE_write_all(head_order_bill, sizeof(struct stBill), ac1);	//�����ļ�
		FILE* fp = fopen("db/income.dat", "w");	//ͳ���ļ�
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
//��������write_cur_time
//
//�������ܣ���ȡ��ǰʱ�䲢���ַ�����ʽд��date
//			
//��������˵����
//				mode:1--д����,��Ϊ����,0--д����,��Ϊ���ڷ���Ӫ��ͳ��
//����ֵ����
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