
//#include <stdio.h>
//#include <stdlib.h>
#include <conio.h>
#include <direct.h>		//�����ļ���_mkdir()
#include <io.h>	//�ж��ļ��Ƿ����access()
//#include "globle.h"
//#include "public.h"
#include "server.h"


int main(int argc, char *argv[])	//������,������ڵ�
{
	int nRole;
	int db_exists = access("db", 0);	//�ж��ļ����Ƿ����
	int bill_exists = access("bill", 0);
	if(db_exists != 0)	//���ļ��в������򴴽�֮
	{
		_mkdir("db");
	}
	if(bill_exists != 0)
	{
		_mkdir("bill");
	}
	do
	{
		nRole = SERVER_login();	//��¼
	}
	while(SERVER_fuc_choice(nRole));	//����ѡ��

	//getch();
	return 0;
}