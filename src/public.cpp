
#include <windows.h> 
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include "public.h"
#include "globle.h"




/////////////////////////////////////////////////////////////////////////
//函数名：Gotoxy
//
//函数功能：在控制台上实现对光标的定位
//			
//函数参数说明：左上角为原点(0,0)
//				x--光标横坐标
//              y--光标纵坐标
//
//返回值：无
///////////////////////////////////////////////////////////////////////
void Gotoxy(int x, int y)
{   
	COORD pos;   
	pos.X = x - 1;   
	pos.Y = y - 1;   
	SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), pos);   
}     

/////////////////////////////////////////////////////////////////////////
//函数名：Print_Str_Center
//
//函数功能：根据字符串长度,打印空格,以便使该字符串居中打印
//			
//函数参数说明：Str[]--要居中打印的字符串
//
//返回值：无
///////////////////////////////////////////////////////////////////////
void Print_Str_Center(const char Str[])
{
	char c = 32;	//空格
	int nAlign = (COL - strlen(Str)) / 2;

	printf("%*c", nAlign, c);
	printf("%s\n", Str);
}


/////////////////////////////////////////////////////////////////////////
//函数名：GetStr
//
//函数功能：1.获取界面连续输入的字符;
//			2.能限制输入个数;
//			3.输入回删键（\b）能达到回删的效果;
//			4.输入合法字符为大小写英文字符和数字，其他字符无效;
//			5.输入为回车跳出.
//			
//函数参数说明：pcStr--从界面上获取的字符存放位置
//              nLen--限制输入字符的长度
//				nFlag--控制输入字符的显示,1为原样输出,0为用*号输出
//
//返回值：实际输入的有效字符个数
//注:1.在使用该函数之前必须要用memset把第一个参数全部初始化为0
//	 2.不支持获取中文字符串
///////////////////////////////////////////////////////////////////////
int GetStr(char pcStr[], int nLen,int nFlag)
{
	int flag = 1;
	int i;
	char ch;

	for(i = 0; (i < nLen) || flag; i++)
	{
		if(i < nLen)
		{
			ch = getch();
			if(ch == '\r')
			{
				break;
			}
			else
				if(ch == '\b' && (i > 0))
				{
					printf("\b \b");
					pcStr[i - 1] = 0;	//	把删掉的那个置0
					i -= 2;	//要减2,因为减1的话执行完该次循环又i++回去了
				}
				else
					if(ch == '\b' && (i <= 0))
					{
						Beep(800, 100);
						i--;
					}
					else
						if(((ch >= 'A') && (ch <= 'Z')) ||	//合法字符
							((ch >= 'a') && (ch <= 'z')) ||
							((ch >= '0') && (ch <= '9')))
						{
							if(nFlag)
							{
								pcStr[i] = ch;
								printf("%c", pcStr[i]);
							}
							else
							{
								pcStr[i] = ch;
								printf("*");
							}
						}
						else
						{
							Beep(900, 100);
							i--;
						}
		}
		else	//当输入完限定的最后一个字符,则只能回删或者回车
		{
			ch = getch();
			if(ch == '\r')
			{
				break;
			}
			else
				if(ch == '\b')
				{
					printf("\b \b");
					pcStr[i - 1] = 0;	//	把删掉的那个置0
					i -= 2;	//要减2,因为减1的话执行完该次循环又i++回去了
				}
				else
				{
					Beep(800, 100);
					i--;
				}
		}
	}
	return i;
}

