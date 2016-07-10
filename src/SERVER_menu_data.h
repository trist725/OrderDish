/***
*SERVER_menu_data.h - 菜谱基础信息的增,删,查,改
*		
*
*
* 函数体:定义于SERVER_menu_data.cpp
*
*
*
****/

#ifndef _SERVER_MENU_DATA_H_
#define _SERVER_MENU_DATA_H_

/////////////////////////////////////////////////////////////////////////
//函数名：SERVER_reread_menu
//
//函数功能：重读菜谱信息文件到通用链表
//			
//函数参数说明：无
//
//返回值：无
//说明:调用该函数后该链表数据域仍为void*型,使用前请强转为实际类型
///////////////////////////////////////////////////////////////////////
//void SERVER_reread_menu();

///////////////////////////////////////////////////////////////////////
//函数名：SERVER_menu_choice
//
//函数功能：菜谱信息管理
//			
//函数参数说明：无
//
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_menu_choice();

////////////////////////////////////////////////////////////////////////
//函数名：SERVER_menu_index
//
//函数功能：菜谱信息查询
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_menu_index();

////////////////////////////////////////////////////////////////////////
//函数名：SERVER_menu_add
//
//函数功能：菜谱信息增加
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_menu_add();

///////////////////////////////////////////////////////////////////////
//函数名：SERVER_menu_update
//
//函数功能：菜谱信息修改
//
//函数参数说明:
//
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_menu_update();

///////////////////////////////////////////////////////////////////////
//函数名：SERVER_menu_del
//
//函数功能：菜谱信息删除
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_menu_del();








#endif