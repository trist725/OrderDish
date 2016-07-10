/***
*
*globle.h - 1.������ϵͳ�ṹ����������
*			2.������ϵͳ��ϵͳ�õ�������ȫ�ֺ�
*
****/

#ifndef _GLOBLE_H_
#define _GLOBLE_H_

#define COL 80	//һ�е�����
#define MAX_INPUT 10	//������ַ���


/////////////////////Ա����Ϣģ��////////////////////////
struct stEmp
{
	int nRole;	//��ɫ,0--����Ա,1--����Ա,2--����
	char acNum[11];	//����
	char acPw[11];	//����
	char acName[21];	//����
};

/////////////////////��ģ��/////////////////////////////
struct stMenu
{
	int nNum;	//�˱��
	int iStat;	//�Ƿ��ѵ�,0--δ��,1--�ѵ�
	char acName[20];	//����
	float fPrice;	//�۸�
};

/////////////////////̨��ģ��///////////////////////////
struct stDesk
{
	int nNum;	//����
	int iStat; //̨��״̬ 0--������,1--����
	int iOrder;	//�����Ƿ��Ѿ����,0--δ��,1--�ѵ�,�û����ɼ�,���ʱ��
	char acInfo[20]; //̨������
};

/////////////////////��ʱ���ģ��///////////////////////////
struct stOrder
{
	struct stMenu Menu_T;	//��ģ��
	int nNum;	//����
};

/////////////////////����ģ��///////////////////////////
struct stBill
{
	char nEmpNum[MAX_INPUT + 1];	//����Ա����
	int DeskNum;	//����
	char acDate[9];	//����
	char acTime[15];	//����(����ʱ��) ��ȷ��s
	int iPay;	//�Ƿ��� 0--��, 1--��
	float sum;	//�ܽ��
};

/////////////////////����ģ��///////////////////////////
struct stIncome
{
	char acDate[9];
	char acEmpNum[MAX_INPUT];
	float fSum;
};

#endif _GLOBLE_H_