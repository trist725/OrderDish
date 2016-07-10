
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globle.h"
#include "public.h"
#include "UI.h"


/////////////////////////////////////////////////////////////////////////
//��������Main_Menu
//
//�������ܣ���ӡ���˵�
//			
//��������˵������
//
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_main()	
{
	char c1[] = {"��ӭʹ�ò͹ݵ�˹���ϵͳ!"};
	char c2[] = {"����:"};
	char c3[] = {"����:"};

	system("cls");
	printf("\n\n");
	Print_Str_Center(c1);
	printf("\n\n");
	Print_Str_Center(c2);
	printf("\n");
	Print_Str_Center(c3);
	printf("\n\n");
	printf("    *���ź�����������ܳ���%dλ,ֻ������Ӣ����ĸ(���ִ�Сд)�Ͱ���������*", MAX_INPUT);
	Gotoxy((COL - strlen(c2)) / 2 + strlen(c2) + 1, 6);	//��궨λ
}

/////////////////////////////////////////////////////////////////////////
//��������UI_sub
//
//�������ܣ�1.���ݽ�ɫ��ͬ�����ͬ�����Ӳ˵�
//			
//��������˵����Role:0 -- �������Ա�����Ӳ˵�
//					 1 -- �������Ա�����Ӳ˵�
//					 2 -- ���BOSS/�������Ӳ˵�
//
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_sub(int Role)
{
	char c4[] = {"1.̨������"};
	char c5[] = {"2.���׹���"};
	char c6[] = {"3.��Ա����"};
	char c7[] = {"4.ע��"};
	char c8[] = {"5.�˳�"};

	char c9[] = {"1.����"};
	char c10[] = {"2.���"};
	char c11[] = {"3.����/δ�򵥲�ѯ"};
	char c17[] = {"4.Ӫҵ���ѯ"};
	char c18[] = {"5.ע��"};
	char c19[] = {"6.�˳�"};

	char c16[] = {"1.Ӫ��ͳ��"};
	char c20[] = {"2.ע��"};
	char c21[] = {"3.�˳�"};

	char c12[] = {"��������Ҫѡ��Ĺ���:"};
	char c13[] = {"����Ա����"};
	char c14[] = {"����Ա����"};
	char c15[] = {"Boss/�������"};

	system("cls");
	printf("\n\n");
	switch(Role)	//����ѡ������
	{
	case 0:	//�������Ա�����Ӳ˵�
		Print_Str_Center(c13);
		printf("\n\n\n");
		Print_Str_Center(c4);
		Print_Str_Center(c5);
		Print_Str_Center(c6);
		Print_Str_Center(c7);
		Print_Str_Center(c8);
		printf("\n\n\n");
		Print_Str_Center(c12);
		Gotoxy((COL - strlen(c12)) / 2 + strlen(c12) + 1, 15);
		break;
	case 1:	//�������Ա�����Ӳ˵�
		Print_Str_Center(c14);
		printf("\n\n\n");
		Print_Str_Center(c9);
		Print_Str_Center(c10);
		Print_Str_Center(c11);
		Print_Str_Center(c17);
		Print_Str_Center(c18);
		Print_Str_Center(c19);
		printf("\n\n\n");
		Print_Str_Center(c12);
		Gotoxy((COL - strlen(c12)) / 2 + strlen(c12) + 1, 16);
		break;
	case 2:	//���Boss/�������Ӳ˵�
		Print_Str_Center(c15);
		printf("\n\n\n");
		Print_Str_Center(c16);
		Print_Str_Center(c20);
		Print_Str_Center(c21);
		printf("\n\n\n");
		Print_Str_Center(c12);
		Gotoxy((COL - strlen(c12)) / 2 + strlen(c12) + 1, 13);
		break;
	default:
		printf("���δ���!\n");
		break;
	}
}

/*//////////////////////////////////////////////////////////////////////
��������UI_sub_emp

�������ܣ�1.���ݽ�ɫ��ͬ�����ͬ�����Ӳ˵�
			
��������˵����n:	 1 -- ������Ա��Ϣ
					 2 -- ɾ����Ա��Ϣ
					 3 -- �޸���Ա��Ϣ
					 4 -- ��ѯ��Ա��Ϣ
					 5 -- ����
����ֵ����
////////////////////////////////////////////////////////////////////*/
void UI_sub0_emp()
{
	char c1[] = {"1.������Ա��Ϣ"};
	char c2[] = {"2.ɾ����Ա��Ϣ"};
	char c3[] = {"3.�޸���Ա��Ϣ"};
	char c4[] = {"4.��ѯ��Ա��Ϣ"};
	char c5[] = {"5.����"};
	char c6[] = {"��Ա��Ϣ����"};
	char c7[] = {"��������Ҫѡ��Ĺ���:"};

	system("cls");
	printf("\n\n");
	Print_Str_Center(c6);
	printf("\n\n");
	Print_Str_Center(c1);
	Print_Str_Center(c2);
	Print_Str_Center(c3);
	Print_Str_Center(c4);
	Print_Str_Center(c5);
	printf("\n\n\n");
	Print_Str_Center(c7);
	Gotoxy((COL - strlen(c7)) / 2 + strlen(c7) + 1, 14);
}

/*//////////////////////////////////////////////////////////////////////
��������UI_sub0_menu

�������ܣ�1.���ݽ�ɫ��ͬ�����ͬ�����Ӳ˵�
			
��������˵����n:	 1 -- ��Ӳ˵�����
					 2 -- ɾ�������еĲ�
					 3 -- �޸Ĳ����еĲ�
					 4 -- ��ѯ������Ϣ
					 5 -- ����
����ֵ����
////////////////////////////////////////////////////////////////////*/
void UI_sub0_menu()
{
	char c1[] = {"1.��Ӳ˵�����"};
	char c2[] = {"2.ɾ�������еĲ�"};
	char c3[] = {"3.�޸Ĳ����еĲ�"};
	char c4[] = {"4.��ѯ������Ϣ"};
	char c5[] = {"5.����"};
	char c6[] = {"������Ϣ����"};
	char c7[] = {"��������Ҫѡ��Ĺ���:"};

	system("cls");
	printf("\n\n");
	Print_Str_Center(c6);
	printf("\n\n");
	Print_Str_Center(c1);
	Print_Str_Center(c2);
	Print_Str_Center(c3);
	Print_Str_Center(c4);
	Print_Str_Center(c5);
	printf("\n\n\n");
	Print_Str_Center(c7);
	Gotoxy((COL - strlen(c7)) / 2 + strlen(c7) + 1, 14);
}

/*//////////////////////////////////////////////////////////////////////
��������UI_sub0_desk

�������ܣ�1.���ݽ�ɫ��ͬ�����ͬ�����Ӳ˵�
			
��������˵����n:	 1 -- ����̨����Ϣ
					 2 -- ɾ��̨����Ϣ
					 3 -- �޸�̨����Ϣ
					 4 -- ��ѯ̨����Ϣ
					 5 -- ����
����ֵ����
////////////////////////////////////////////////////////////////////*/
void UI_sub0_desk()
{
	char c1[] = {"1.����̨����Ϣ"};
	char c2[] = {"2.ɾ��̨����Ϣ"};
	char c3[] = {"3.�޸�̨����Ϣ"};
	char c4[] = {"4.��ѯ̨����Ϣ"};
	char c5[] = {"5.����"};
	char c6[] = {"̨����Ϣ����"};
	char c7[] = {"��������Ҫѡ��Ĺ���:"};

	system("cls");
	printf("\n\n");
	Print_Str_Center(c6);
	printf("\n\n");
	Print_Str_Center(c1);
	Print_Str_Center(c2);
	Print_Str_Center(c3);
	Print_Str_Center(c4);
	Print_Str_Center(c5);
	printf("\n\n\n");
	Print_Str_Center(c7);
	Gotoxy((COL - strlen(c7)) / 2 + strlen(c7) + 1, 14);
}

/////////////////////////////////////////////////////////////////////////
//��������UI_emp_index
//
//�������ܣ�Ա����Ϣ��ѯ
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_emp_index()
{
	char c1[] = {"1.�����Ų�ѯ"};
	char c2[] = {"2.��������ѯ"};
	char c3[] = {"3.���û�Ȩ�޲�ѯ"};
	char c4[] = {"��ѯԱ����Ϣ"};
	char c5[] = {"4.����"};
	char c7[] = {"��������Ҫѡ��Ĺ���:"};

	system("cls");
	printf("\n\n");
	Print_Str_Center(c4);
	printf("\n\n");
	Print_Str_Center(c1);
	Print_Str_Center(c2);
	Print_Str_Center(c3);
	Print_Str_Center(c5);
	printf("\n\n\n");
	Print_Str_Center(c7);
	Gotoxy((COL - strlen(c7)) / 2 + strlen(c7) + 1, 13);
}

/////////////////////////////////////////////////////////////////////////
//��������UI_menu_index
//
//�������ܣ�������Ϣ��ѯ
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_menu_index()
{
	char c1[] = {"1.���˱�Ų�ѯ"};
	char c2[] = {"2.��������ѯ"};
	char c3[] = {"3.���۸��ѯ"};
	char c4[] = {"��ѯ������Ϣ"};
	char c5[] = {"4.����"};
	char c7[] = {"��������Ҫѡ��Ĺ���:"};

	system("cls");
	printf("\n\n");
	Print_Str_Center(c4);
	printf("\n\n");
	Print_Str_Center(c1);
	Print_Str_Center(c2);
	Print_Str_Center(c3);
	Print_Str_Center(c5);
	printf("\n\n\n");
	Print_Str_Center(c7);
	Gotoxy((COL - strlen(c7)) / 2 + strlen(c7) + 1, 13);
}

/////////////////////////////////////////////////////////////////////////
//��������UI_desk_index
//
//�������ܣ�Ա����Ϣ��ѯ
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_desk_index()
{
	char c1[] = {"1.�����Ų�ѯ"};
	char c2[] = {"2.��״̬��ѯ"};
	char c4[] = {"��ѯ̨����Ϣ"};
	char c5[] = {"3.����"};
	char c7[] = {"��������Ҫѡ��Ĺ���:"};

	system("cls");
	printf("\n\n");
	Print_Str_Center(c4);
	printf("\n\n");
	Print_Str_Center(c1);
	Print_Str_Center(c2);
	Print_Str_Center(c5);
	printf("\n\n\n");
	Print_Str_Center(c7);
	Gotoxy((COL - strlen(c7)) / 2 + strlen(c7) + 1, 12);
}

/////////////////////////////////////////////////////////////////////////
//��������UI_menu_del
//
//�������ܣ�������Ϣɾ��
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_menu_del()
{
	char c1[] = {"1.���˱��ɾ��"};
	char c2[] = {"2.������ɾ��"};
	char c3[] = {"3.���۸�ɾ��"};
	char c4[] = {"��ѯ������Ϣ"};
	char c5[] = {"4.����"};
	char c7[] = {"��������Ҫѡ��Ĺ���:"};

	system("cls");
	printf("\n\n");
	Print_Str_Center(c4);
	printf("\n\n");
	Print_Str_Center(c1);
	Print_Str_Center(c2);
	Print_Str_Center(c3);
	Print_Str_Center(c5);
	printf("\n\n\n");
	Print_Str_Center(c7);
	Gotoxy((COL - strlen(c7)) / 2 + strlen(c7) + 1, 13);
}

/////////////////////////////////////////////////////////////////////////
//��������UI_emp_del
//
//�������ܣ�Ա����Ϣɾ��
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_emp_del()
{
	char c1[] = {"1.������ɾ��"};
	char c2[] = {"2.������ɾ��"};
	char c3[] = {"3.���û���ɫɾ��"};
	char c4[] = {"ɾ��Ա����Ϣ"};
	char c5[] = {"4.����"};
	char c7[] = {"��������Ҫѡ��Ĺ���:"};

	system("cls");
	printf("\n\n");
	Print_Str_Center(c4);
	printf("\n\n");
	Print_Str_Center(c1);
	Print_Str_Center(c2);
	Print_Str_Center(c3);
	Print_Str_Center(c5);
	printf("\n\n\n");
	Print_Str_Center(c7);
	Gotoxy((COL - strlen(c7)) / 2 + strlen(c7) + 1, 13);
}

/////////////////////////////////////////////////////////////////////////
//��������UI_desk_del
//
//�������ܣ�̨����Ϣɾ��
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_desk_del()
{
	char c1[] = {"1.������ɾ��"};
	char c2[] = {"2.��״̬ɾ��"};
	char c4[] = {"ɾ��̨����Ϣ"};
	char c5[] = {"3.����"};
	char c7[] = {"��������Ҫѡ��Ĺ���:"};

	system("cls");
	printf("\n\n");
	Print_Str_Center(c4);
	printf("\n\n");
	Print_Str_Center(c1);
	Print_Str_Center(c2);
	Print_Str_Center(c5);
	printf("\n\n\n");
	Print_Str_Center(c7);
	Gotoxy((COL - strlen(c7)) / 2 + strlen(c7) + 1, 12);
}

/////////////////////////////////////////////////////////////////////////
//��������UI_emp_update
//
//�������ܣ�Ա����Ϣ�޸�
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_emp_update()
{
	char c1[] = {"1.�������޸�"};
	char c2[] = {"2.�������޸�"};
	char c3[] = {"3.���û���ɫ�޸�"};
	char c4[] = {"�޸�Ա����Ϣ"};
	char c5[] = {"4.����"};
	char c7[] = {"��������Ҫѡ��Ĺ���:"};

	system("cls");
	printf("\n\n");
	Print_Str_Center(c4);
	printf("\n\n");
	Print_Str_Center(c1);
	Print_Str_Center(c2);
	Print_Str_Center(c3);
	Print_Str_Center(c5);
	printf("\n\n\n");
	Print_Str_Center(c7);
	Gotoxy((COL - strlen(c7)) / 2 + strlen(c7) + 1, 13);
}

/////////////////////////////////////////////////////////////////////////
//��������UI_menu_update
//
//�������ܣ�������Ϣ�޸�
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_menu_update()
{
	char c1[] = {"1.���˱���޸�"};
	char c2[] = {"2.�������޸�"};
	char c3[] = {"3.���۸��޸�"};
	char c4[] = {"��ѯ������Ϣ"};
	char c5[] = {"4.����"};
	char c7[] = {"��������Ҫѡ��Ĺ���:"};

	system("cls");
	printf("\n\n");
	Print_Str_Center(c4);
	printf("\n\n");
	Print_Str_Center(c1);
	Print_Str_Center(c2);
	Print_Str_Center(c3);
	Print_Str_Center(c5);
	printf("\n\n\n");
	Print_Str_Center(c7);
	Gotoxy((COL - strlen(c7)) / 2 + strlen(c7) + 1, 13);
}

/////////////////////////////////////////////////////////////////////////
//��������UI_desk_update
//
//�������ܣ�Ա����Ϣ�޸�
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_desk_update()
{
	char c1[] = {"1.�������޸�"};
	char c2[] = {"2.��״̬�޸�"};
	char c4[] = {"�޸�̨����Ϣ"};
	char c5[] = {"3.����"};
	char c7[] = {"��������Ҫѡ��Ĺ���:"};

	system("cls");
	printf("\n\n");
	Print_Str_Center(c4);
	printf("\n\n");
	Print_Str_Center(c1);
	Print_Str_Center(c2);
	Print_Str_Center(c5);
	printf("\n\n\n");
	Print_Str_Center(c7);
	Gotoxy((COL - strlen(c7)) / 2 + strlen(c7) + 1, 12);
}