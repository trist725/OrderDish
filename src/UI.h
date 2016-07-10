/***
*UI.h - 1.������ϵͳ�󲿷ֹ���ѡ���Ĵ�ӡ
*
*
*
* ������:������UI.cpp
*
*
*
****/
#ifndef _UI_H_
#define _UI_H_


////////////////////////////////////////////////////////////////////////
//��������Main_Menu
//
//�������ܣ���ӡ���˵�
//			
//��������˵������
//
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_main();

///////////////////////////////////////////////////////////////////////
//��������UI_sub1
//
//�������ܣ�1.���ݽ�ɫ��ͬ�����ͬ�����Ӳ˵�
//			
//��������˵����Role:0 -- �������Ա�����Ӳ˵�
//					 1 -- �������Ա�����Ӳ˵�
//					 2 -- ���BOSS/���������Ӳ˵�
//
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_sub(int Role);

/*//////////////////////////////////////////////////////////////////////
��������UI_sub_menu

�������ܣ�1.���ݽ�ɫ��ͬ�����ͬ�����Ӳ˵�
			
��������˵����n:	 1 -- ���Ӳ˵�����
					 2 -- ɾ�������еĲ�
					 3 -- �޸Ĳ����еĲ�
					 4 -- ��ѯ������Ϣ
					 5 -- ����
����ֵ����
////////////////////////////////////////////////////////////////////*/
void UI_sub0_menu();

/*//////////////////////////////////////////////////////////////////////
��������UI_sub_desk

�������ܣ�1.���ݽ�ɫ��ͬ�����ͬ�����Ӳ˵�
			
��������˵����n:	 1 -- ����̨����Ϣ
					 2 -- ɾ��̨����Ϣ
					 3 -- �޸�̨����Ϣ
					 4 -- ��ѯ̨����Ϣ
					 5 -- ����
����ֵ����
////////////////////////////////////////////////////////////////////*/
void UI_sub0_desk();

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
void UI_sub0_emp();

/////////////////////////////////////////////////////////////////////////
//��������UI_emp_index
//
//�������ܣ�Ա����Ϣ��ѯ
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_emp_index();

/////////////////////////////////////////////////////////////////////////
//��������UI_desk_index
//
//�������ܣ�Ա����Ϣ��ѯ
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_desk_index();

/////////////////////////////////////////////////////////////////////////
//��������UI_menu_index
//
//�������ܣ�������Ϣ��ѯ
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_menu_index();

/////////////////////////////////////////////////////////////////////////
//��������UI_menu_del
//
//�������ܣ�������Ϣɾ��
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_menu_del();

/////////////////////////////////////////////////////////////////////////
//��������UI_menu_update
//
//�������ܣ�������Ϣ�޸�
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_menu_update();

/////////////////////////////////////////////////////////////////////////
//��������UI_emp_del
//
//�������ܣ�Ա����Ϣ��ѯ
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_emp_del();

/////////////////////////////////////////////////////////////////////////
//��������UI_emp_update
//
//�������ܣ�Ա����Ϣ�޸�
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_emp_update();

/////////////////////////////////////////////////////////////////////////
//��������UI_desk_update
//
//�������ܣ�Ա����Ϣ�޸�
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_desk_update();

/////////////////////////////////////////////////////////////////////////
//��������UI_desk_del
//
//�������ܣ�̨����Ϣɾ��
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_desk_del();

/////////////////////////////////////////////////////////////////////////
//��������UI_desk_index
//
//�������ܣ�Ա����Ϣ��ѯ
//			
//��������˵������
//					  
//����ֵ����
///////////////////////////////////////////////////////////////////////
void UI_desk_index();



#endif _UI_H_