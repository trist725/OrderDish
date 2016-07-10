/***
*SERVER_emp_data.h - 人员基础信息的增,删,查,改
*		
*
*
* 函数体:定义于SERVER_emp_data.cpp
*
*
*
****/

#ifndef _SERVER_EMP_DATA_H_
#define _SERVER_EMP_DATA_H_


///////////////////////////////////////////////////////////////////////
//函数名：SERVER_emp_choice
//
//函数功能：人员信息管理
//			
//函数参数说明：无
//
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_emp_choice();

////////////////////////////////////////////////////////////////////////
//函数名：SERVER_emp_index
//
//函数功能：人员信息查询
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_emp_index();

////////////////////////////////////////////////////////////////////////
//函数名：SERVER_emp_add
//
//函数功能：人员信息增加
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_emp_add();

///////////////////////////////////////////////////////////////////////
//函数名：SERVER_emp_update
//
//函数功能：人员信息修改
//
//函数参数说明:
//
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_emp_update();

///////////////////////////////////////////////////////////////////////
//函数名：SERVER_emp_del
//
//函数功能：人员信息删除
//			
//函数参数说明:
//					 
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_emp_del();








#endif