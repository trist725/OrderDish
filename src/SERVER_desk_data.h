/***
*SERVER_desk_data.h - 台桌基础信息的增,删,查,改
*		
*
*
* 函数体:定义于SERVER_desk_data.cpp
*
*
*
****/

#ifndef _SERVER_DESK_DATA_H_
#define _SERVER_DESK_DATA_H_

/////////////////////////////////////////////////////////////////////////
//函数名：SERVER_reread_desk
//
//函数功能：重读台桌信息文件到通用链表
//			
//函数参数说明：无
//
//返回值：无
//说明:调用该函数后该链表数据域仍为void*型,使用前请强转为实际类型
///////////////////////////////////////////////////////////////////////
//void SERVER_reread_desk();

///////////////////////////////////////////////////////////////////////
//函数名：SERVER_desk_choice
//
//函数功能：台桌信息管理
//			
//函数参数说明：无
//
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_desk_choice();

////////////////////////////////////////////////////////////////////////
//函数名：SERVER_desk_index
//
//函数功能：台桌信息查询
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_desk_index();

////////////////////////////////////////////////////////////////////////
//函数名：SERVER_desk_add
//
//函数功能：台桌信息增加
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_desk_add();

///////////////////////////////////////////////////////////////////////
//函数名：SERVER_desk_update
//
//函数功能：台桌信息修改
//
//函数参数说明:
//
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_desk_update();

///////////////////////////////////////////////////////////////////////
//函数名：SERVER_desk_del
//
//函数功能：台桌信息删除
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_desk_del();








#endif