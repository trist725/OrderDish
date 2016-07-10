/***
*
*globle.h - 1.包含本系统结构体类型声明
*			2.包含本系统本系统用到的其它全局宏
*
****/

#ifndef _GLOBLE_H_
#define _GLOBLE_H_

#define COL 80	//一行的列数
#define MAX_INPUT 10	//最长输入字符数


/////////////////////员工信息模板////////////////////////
struct stEmp
{
	int nRole;	//角色,0--管理员,1--服务员,2--经理
	char acNum[11];	//工号
	char acPw[11];	//密码
	char acName[21];	//姓名
};

/////////////////////菜模板/////////////////////////////
struct stMenu
{
	int nNum;	//菜编号
	int iStat;	//是否已点,0--未点,1--已点
	char acName[20];	//菜名
	float fPrice;	//价格
};

/////////////////////台桌模板///////////////////////////
struct stDesk
{
	int nNum;	//桌号
	int iStat; //台桌状态 0--不可用,1--可用
	int iOrder;	//该桌是否已经点菜,0--未点,1--已点,用户不可见,点菜时用
	char acInfo[20]; //台桌描述
};

/////////////////////临时点菜模板///////////////////////////
struct stOrder
{
	struct stMenu Menu_T;	//菜模板
	int nNum;	//份数
};

/////////////////////订单模板///////////////////////////
struct stBill
{
	char nEmpNum[MAX_INPUT + 1];	//服务员工号
	int DeskNum;	//桌号
	char acDate[9];	//日期
	char acTime[15];	//单号(日期时间) 精确到s
	int iPay;	//是否买单 0--否, 1--是
	float sum;	//总金额
};

/////////////////////订单模板///////////////////////////
struct stIncome
{
	char acDate[9];
	char acEmpNum[MAX_INPUT];
	float fSum;
};

#endif _GLOBLE_H_