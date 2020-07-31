// 2048.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

/*#include <iostream>
#include<easyx.h>
#include<conio.h>


#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#include<time.h>
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
using namespace std;

namespace
{
	IMAGE image[12];
	int imageIndex[12];
	int map[4][4] = { 2 };
	bool isOver = true;
	bool gameOver = false;
	enum direction
	{
		Up, Down, Left, Right
	};
};

void SetImageIndex();//设置图片编号
void loadResource();
void drawMap();
void randIntNum();
void keyDownAndDraw();
bool TurnLeft(int s[4][4]);
void ChangeOnKeyDown(direction Direction);



int main()
{
	SetImageIndex();
	loadResource();
	initgraph(60 * 4, 60 * 4 + 120);//游戏界面大小
	drawMap();
	keyDownAndDraw();
	system("pause");//防止闪屏
	//closegraph();
	//system("pause");
	return 0;
}
void SetImageIndex()
{
	imageIndex[0] = 0;
	for (int i = 1; i < 12; i++)
	{
		imageIndex[i] = int(pow(2, i));
	}
}
void loadResource()//加载图片
{
	for (int i = 0; i < 12; i++)
	{
		char fileName[20] = "";
		sprintf(fileName, "%d.bmp", imageIndex[i]);//拼接
		loadimage(image + i, fileName, 60, 60);
	}
}

//画地图
void drawMap()
{
	string out;
	int HistryHighlyScore = 0;
	ifstream IScore("Score.txt");//创建文件读取历史最高分
	if (!IScore)
	{
		ofstream OScore("Score.txt");
		IScore.open("Score.txt");
	}
	getline(IScore, out);
	char Score[10];
	char HighlyScore[100];
	int Sum = 0;
	setbkcolor(RGB(244, 215, 215));
	cleardevice();
	settextcolor(WHITE);//设置文字颜色
	settextstyle(35, 0, "楷体");//设置文字格式
	outtextxy(50, 10, "2048游戏");
	settextcolor(YELLOW);//设置文字颜色
	settextstyle(25, 0, "楷体");//设置文字格式
	for (int i = 0; i < 4; i++)//计算分数
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] > 4)
			{
				Sum += map[i][j] * sqrt(map[i][j]);
			}
		}
	}
	sprintf(Score, "分数:%d", Sum);
	outtextxy(10, 300, Score);
	for (int i = 0; i < out.length(); i++)
	{
		HighlyScore[i] = out[i];
	}
	stringstream mid;
	mid << out;
	mid >> HistryHighlyScore;
	if (HistryHighlyScore > Sum)
	{
		HighlyScore[out.length()] = '\0';
		settextcolor(RED);//设置文字颜色
		settextstyle(25, 0, "楷体");//设置文字格式
		outtextxy(10, 330, "历史最高:");
		outtextxy(130, 330, HighlyScore);
	}
	else
	{
		char Score1[20];
		settextcolor(RED);//设置文字颜色
		settextstyle(25, 0, "楷体");//设置文字格式
		sprintf(Score1, "历史最高:%d", Sum);
		outtextxy(10, 330, Score1);
		ofstream OScore1;
		OScore1.open("Score.txt");
		OScore1 << Sum;
		OScore1.close();
	}
	IScore.close();
	//根据二维数组去画图
	int x, y, k;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			x = 60 * j;
			y = 60 * i + 55;
			for (k = 0; k < 12; k++)
			{
				if (imageIndex[k] == map[i][j])
				{
					break;
				}
			}
			putimage(x, y, image + k);
		}
	}
	isOver = true;
}

//随机产生2或者4;
void randIntNum()
{
	bool haszero = false;
	bool isOk = false;
	srand((unsigned)time(NULL)); //随机函数种子
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] == 0)
			{
				haszero = true;
				map[i][j] = (rand() % 3) * 2;
				if (map[i][j] == 0)
				{
					continue;
				}
				isOk = true;
				break;
			}
		}
		if (isOk)
		{
			break;
		}
	}
	if (!isOk)
	{
		isOk = false;
		if (haszero)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (map[i][j] == 0)
					{
						map[i][j] = 2;
						isOk = true;
						break;
					}
				}
				if (isOk)
				{
					break;
				}
			}
		}
	}
	for (int i = 0; i < 4; i++)//检测最后一步是否留有空位，若全满游戏结束
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] == 0)
			{
				drawMap();
				return;
			}
		}
	}
	for (int i = 0; i < 4; i++)//游戏失败则重置
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == 0 && j == 0)
			{
				map[i][j] = 2;
				continue;
			}
			map[i][j] = 0;
		}
	}
	drawMap();
}

//按键响应
void keyDownAndDraw()
{
	while (true)
	{
		char key = _getch();//接收用户按键
		if (isOver)
		{
			isOver = false;
			switch (key)
			{
			case 'W':
			case'w':
			case 72:
				ChangeOnKeyDown(Up);
				break;
			case 'S':
			case's':
			case 80:
				ChangeOnKeyDown(Down);
				break;
			case 'a':
			case'A':
			case 75:
				ChangeOnKeyDown(Left);
				break;
			case 'D':
			case'd':
			case 77:
				ChangeOnKeyDown(Right);
				break;
			default:
				isOver = true;
				break;
			}
		}
	}
}
void ChangeOnKeyDown(direction Direction)
{
	int Map[4][4] = { 0 };
	bool CanMove;
	switch (Direction)//将所有方向改为向左方向，并利用向左算法计算各个方向
	{
	case Up:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Map[j][i] = map[i][j];
			}
		}
		break;
	case Down:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Map[j][3 - i] = map[i][j];
			}
		}
		break;
	case Left:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Map[i][j] = map[i][j];
			}
		}
		break;
	case Right:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Map[i][3 - j] = map[i][j];
			}
		}
		break;
	default:
		break;
	}
	//向左算法
	CanMove = TurnLeft(Map);
	//将向左改回各自方向
	switch (Direction)
	{
	case Up:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				map[j][i] = Map[i][j];
			}
		}
		break;
	case Down:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				map[3 - j][i] = Map[i][j];
			}
		}
		break;
	case Left:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				map[i][j] = Map[i][j];
			}
		}
		break;
	case Right:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				map[i][3 - j] = Map[i][j];
			}
		}
		break;
	default:
		break;
	}
	if (CanMove)
	{
		randIntNum();
		drawMap();
	}
	else
	{
		isOver = true;
	}
};
//算法
bool TurnLeft(int Map[4][4])//按向左键进行合并
{
	int k;
	int len;
	int Save[4];
	int Move[4][4];
	bool CanMove = false;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Move[i][j] = Map[i][j];
		}
	}
	for (int i = 0; i < 4; i++)
	{
		k = 0;
		len = 0;
		for (int j = 0; j < 4; j++)
		{
			if (Map[i][j] == 0)
			{
				continue;
			}
			for (k = j + 1; k < 4; k++)
			{
				if (Map[i][k] != 0)
				{
					if (Map[i][j] == Map[i][k])
					{
						Map[i][j] *= 2;
						Map[i][k] = 0;
					}
					break;
				}
			}
		}
		for (int j = 0; j < 4; j++)
		{
			if (Map[i][j] != 0)
			{
				Save[len] = Map[i][j];
				len++;
			}
		}
		for (int j = 0; j < 4; j++)
		{
			if (j < len)
			{
				Map[i][j] = Save[j];
			}
			else
			{
				Map[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (Move[i][j] != Map[i][j])
			{
				CanMove = true;
			};
		}
	}
	return CanMove;
}
*/