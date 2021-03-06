/***
*server.h - 1.包含本系统登录模块和功能选单模块
*		
*
*
* 函数体:定义于server.cpp
*
*
*
****/

#ifndef _SERVER_H_
#define _SERVER_H_

/////////////////////////////////////////////////////////////////////////
//函数名：SERVER_login
//
//函数功能：登录模块,控制用户输入工号和密码,并根据不同账号进入其相应功能选单
//			
//函数参数说明：无
//
//返回值：0 -- 管理员
//		  1 -- 服务员
//		  2 -- 经理/Boss
///////////////////////////////////////////////////////////////////////
int SERVER_login();

/////////////////////////////////////////////////////////////////////////
//函数名：SERVER_fuc_choice
//
//函数功能：人员管理
//			
//函数参数说明：Role: 0 -- 管理员功能菜单
//					  1 -- 服务员功能菜单
//					  2 -- 经理/Boss功能菜单
//返回值：0 -- 结束 1 -- 注销登录,回到登录界面
///////////////////////////////////////////////////////////////////////
int SERVER_fuc_choice(int nRole);

/////////////////////////////////////////////////////////////////////////
//函数名：SERVER_emp_choice
//
//函数功能：人员信息管理
//			
//函数参数说明：无
//
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_emp_choice();

/////////////////////////////////////////////////////////////////////////
//函数名：SERVER_fuc0_choice
//
//函数功能：管理员功能选单
//			
//函数说明：		  0 -- 台桌数据管理
//					  1 -- 菜谱数据管理
//					  2 -- 人员数据管理
//					  3 -- 注销
//					  4 -- 退出
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_fuc0_choice();

///////////////////////////////////////////////////////////////////////
//函数名：SERVER_fuc1_choice
//
//函数功能：服务员功能选单
//			
//函数说明：		  1 -- 开桌/点菜
//					  2 -- 营业额查询
//					  3 -- 已买/未买单查询
//					  4 -- 注销
//					  5 -- 退出
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_fuc1_choice();

///////////////////////////////////////////////////////////////////////
//函数名：SERVER_fuc2_choice
//
//函数功能：经理/Boss功能选单
//			
//函数说明：		  1 -- 营收统计
//					  2 -- 注销
//					  3 -- 退出
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
int SERVER_fuc2_choice();

///////////////////////////////////////////////////////////////////////
//函数名：SERVER_order_dish
//
//函数功能：人员信息修改
//
//函数参数说明:
//
//返回值：0 -- 结束 1 -- 返回
///////////////////////////////////////////////////////////////////////
//int SERVER_order_dish();





#endif _SERVER_H_