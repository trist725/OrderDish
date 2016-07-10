
//#include <stdio.h>
//#include <stdlib.h>
#include <conio.h>
#include <direct.h>		//创建文件夹_mkdir()
#include <io.h>	//判断文件是否存在access()
//#include "globle.h"
//#include "public.h"
#include "server.h"


int main(int argc, char *argv[])	//主函数,程序入口点
{
	int nRole;
	int db_exists = access("db", 0);	//判断文件夹是否存在
	int bill_exists = access("bill", 0);
	if(db_exists != 0)	//若文件夹不存在则创建之
	{
		_mkdir("db");
	}
	if(bill_exists != 0)
	{
		_mkdir("bill");
	}
	do
	{
		nRole = SERVER_login();	//登录
	}
	while(SERVER_fuc_choice(nRole));	//功能选择

	//getch();
	return 0;
}