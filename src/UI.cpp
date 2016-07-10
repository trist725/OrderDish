
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globle.h"
#include "public.h"
#include "UI.h"


/////////////////////////////////////////////////////////////////////////
//函数名：Main_Menu
//
//函数功能：打印主菜单
//			
//函数参数说明：无
//
//返回值：无
///////////////////////////////////////////////////////////////////////
void UI_main()	
{
	char c1[] = {"欢迎使用餐馆点菜管理系统!"};
	char c2[] = {"工号:"};
	char c3[] = {"密码:"};

	system("cls");
	printf("\n\n");
	Print_Str_Center(c1);
	printf("\n\n");
	Print_Str_Center(c2);
	printf("\n");
	Print_Str_Center(c3);
	printf("\n\n");
	printf("    *工号和密码最长均不能超过%d位,只能输入英文字母(区分大小写)和阿拉伯数字*", MAX_INPUT);
	Gotoxy((COL - strlen(c2)) / 2 + strlen(c2) + 1, 6);	//光标定位
}

/////////////////////////////////////////////////////////////////////////
//函数名：UI_sub
//
//函数功能：1.根据角色不同输出不同功能子菜单
//			
//函数参数说明：Role:0 -- 输出管理员功能子菜单
//					 1 -- 输出服务员功能子菜单
//					 2 -- 输出BOSS/经理功能子菜单
//
//返回值：无
///////////////////////////////////////////////////////////////////////
void UI_sub(int Role)
{
	char c4[] = {"1.台桌管理"};
	char c5[] = {"2.菜谱管理"};
	char c6[] = {"3.人员管理"};
	char c7[] = {"4.注销"};
	char c8[] = {"5.退出"};

	char c9[] = {"1.开桌"};
	char c10[] = {"2.点菜"};
	char c11[] = {"3.已买/未买单查询"};
	char c17[] = {"4.营业额查询"};
	char c18[] = {"5.注销"};
	char c19[] = {"6.退出"};

	char c16[] = {"1.营收统计"};
	char c20[] = {"2.注销"};
	char c21[] = {"3.退出"};

	char c12[] = {"请输入您要选择的功能:"};
	char c13[] = {"管理员界面"};
	char c14[] = {"服务员界面"};
	char c15[] = {"Boss/经理界面"};

	system("cls");
	printf("\n\n");
	switch(Role)	//功能选单开关
	{
	case 0:	//输出管理员功能子菜单
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
	case 1:	//输出服务员功能子菜单
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
	case 2:	//输出Boss/经理功能子菜单
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
		printf("传参错误!\n");
		break;
	}
}

/*//////////////////////////////////////////////////////////////////////
函数名：UI_sub_emp

函数功能：1.根据角色不同输出不同功能子菜单
			
函数参数说明：n:	 1 -- 增加人员信息
					 2 -- 删除人员信息
					 3 -- 修改人员信息
					 4 -- 查询人员信息
					 5 -- 返回
返回值：无
////////////////////////////////////////////////////////////////////*/
void UI_sub0_emp()
{
	char c1[] = {"1.增加人员信息"};
	char c2[] = {"2.删除人员信息"};
	char c3[] = {"3.修改人员信息"};
	char c4[] = {"4.查询人员信息"};
	char c5[] = {"5.返回"};
	char c6[] = {"人员信息管理"};
	char c7[] = {"请输入您要选择的功能:"};

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
函数名：UI_sub0_menu

函数功能：1.根据角色不同输出不同功能子菜单
			
函数参数说明：n:	 1 -- 添加菜到菜谱
					 2 -- 删除菜谱中的菜
					 3 -- 修改菜谱中的菜
					 4 -- 查询菜谱信息
					 5 -- 返回
返回值：无
////////////////////////////////////////////////////////////////////*/
void UI_sub0_menu()
{
	char c1[] = {"1.添加菜到菜谱"};
	char c2[] = {"2.删除菜谱中的菜"};
	char c3[] = {"3.修改菜谱中的菜"};
	char c4[] = {"4.查询菜谱信息"};
	char c5[] = {"5.返回"};
	char c6[] = {"菜谱信息管理"};
	char c7[] = {"请输入您要选择的功能:"};

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
函数名：UI_sub0_desk

函数功能：1.根据角色不同输出不同功能子菜单
			
函数参数说明：n:	 1 -- 增加台桌信息
					 2 -- 删除台桌信息
					 3 -- 修改台桌信息
					 4 -- 查询台桌信息
					 5 -- 返回
返回值：无
////////////////////////////////////////////////////////////////////*/
void UI_sub0_desk()
{
	char c1[] = {"1.增加台桌信息"};
	char c2[] = {"2.删除台桌信息"};
	char c3[] = {"3.修改台桌信息"};
	char c4[] = {"4.查询台桌信息"};
	char c5[] = {"5.返回"};
	char c6[] = {"台桌信息管理"};
	char c7[] = {"请输入您要选择的功能:"};

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
//函数名：UI_emp_index
//
//函数功能：员工信息查询
//			
//函数参数说明：无
//					  
//返回值：无
///////////////////////////////////////////////////////////////////////
void UI_emp_index()
{
	char c1[] = {"1.按工号查询"};
	char c2[] = {"2.按姓名查询"};
	char c3[] = {"3.按用户权限查询"};
	char c4[] = {"查询员工信息"};
	char c5[] = {"4.返回"};
	char c7[] = {"请输入您要选择的功能:"};

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
//函数名：UI_menu_index
//
//函数功能：菜谱信息查询
//			
//函数参数说明：无
//					  
//返回值：无
///////////////////////////////////////////////////////////////////////
void UI_menu_index()
{
	char c1[] = {"1.按菜编号查询"};
	char c2[] = {"2.按菜名查询"};
	char c3[] = {"3.按价格查询"};
	char c4[] = {"查询菜谱信息"};
	char c5[] = {"4.返回"};
	char c7[] = {"请输入您要选择的功能:"};

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
//函数名：UI_desk_index
//
//函数功能：员工信息查询
//			
//函数参数说明：无
//					  
//返回值：无
///////////////////////////////////////////////////////////////////////
void UI_desk_index()
{
	char c1[] = {"1.按桌号查询"};
	char c2[] = {"2.按状态查询"};
	char c4[] = {"查询台桌信息"};
	char c5[] = {"3.返回"};
	char c7[] = {"请输入您要选择的功能:"};

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
//函数名：UI_menu_del
//
//函数功能：菜谱信息删除
//			
//函数参数说明：无
//					  
//返回值：无
///////////////////////////////////////////////////////////////////////
void UI_menu_del()
{
	char c1[] = {"1.按菜编号删除"};
	char c2[] = {"2.按菜名删除"};
	char c3[] = {"3.按价格删除"};
	char c4[] = {"查询菜谱信息"};
	char c5[] = {"4.返回"};
	char c7[] = {"请输入您要选择的功能:"};

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
//函数名：UI_emp_del
//
//函数功能：员工信息删除
//			
//函数参数说明：无
//					  
//返回值：无
///////////////////////////////////////////////////////////////////////
void UI_emp_del()
{
	char c1[] = {"1.按工号删除"};
	char c2[] = {"2.按姓名删除"};
	char c3[] = {"3.按用户角色删除"};
	char c4[] = {"删除员工信息"};
	char c5[] = {"4.返回"};
	char c7[] = {"请输入您要选择的功能:"};

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
//函数名：UI_desk_del
//
//函数功能：台桌信息删除
//			
//函数参数说明：无
//					  
//返回值：无
///////////////////////////////////////////////////////////////////////
void UI_desk_del()
{
	char c1[] = {"1.按桌号删除"};
	char c2[] = {"2.按状态删除"};
	char c4[] = {"删除台桌信息"};
	char c5[] = {"3.返回"};
	char c7[] = {"请输入您要选择的功能:"};

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
//函数名：UI_emp_update
//
//函数功能：员工信息修改
//			
//函数参数说明：无
//					  
//返回值：无
///////////////////////////////////////////////////////////////////////
void UI_emp_update()
{
	char c1[] = {"1.按工号修改"};
	char c2[] = {"2.按姓名修改"};
	char c3[] = {"3.按用户角色修改"};
	char c4[] = {"修改员工信息"};
	char c5[] = {"4.返回"};
	char c7[] = {"请输入您要选择的功能:"};

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
//函数名：UI_menu_update
//
//函数功能：菜谱信息修改
//			
//函数参数说明：无
//					  
//返回值：无
///////////////////////////////////////////////////////////////////////
void UI_menu_update()
{
	char c1[] = {"1.按菜编号修改"};
	char c2[] = {"2.按菜名修改"};
	char c3[] = {"3.按价格修改"};
	char c4[] = {"查询菜谱信息"};
	char c5[] = {"4.返回"};
	char c7[] = {"请输入您要选择的功能:"};

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
//函数名：UI_desk_update
//
//函数功能：员工信息修改
//			
//函数参数说明：无
//					  
//返回值：无
///////////////////////////////////////////////////////////////////////
void UI_desk_update()
{
	char c1[] = {"1.按桌号修改"};
	char c2[] = {"2.按状态修改"};
	char c4[] = {"修改台桌信息"};
	char c5[] = {"3.返回"};
	char c7[] = {"请输入您要选择的功能:"};

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