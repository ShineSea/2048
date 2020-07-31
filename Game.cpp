#include "Game.h"

#include<iostream>
#include <cstdlib> 
#include <ctime>

using std::cout;
using std::endl;
Game::Game()
{
	initmap();
	initgraph(width,height);//游戏界面大小
	//setbkcolor(0xffb99d);
	cleardevice();//清空绘图设备	
	setbkmode(TRANSPARENT); //设置当前设备图案填充和文字输出时的背景模式。
	//设置图片背景
	loadimage(&img, L"C:\\Users\\82719\\Pictures\\壁纸\\background.jpg");//加载图片
	putimage(0, 0, &img);//放置图片

	// 在屏幕中央输出字符串
	settextcolor(WHITE);//设置文本颜色
	settextstyle(20, 0, _T("Consolas"));//设置当前字体为高 16 像素的"Consolas"
	RECT r = { 0, 0,width-1,height-1};
	drawtext(_T("按任意键开始游戏"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

Game::~Game()
{
	closegraph();//关闭窗口
}


void Game::play()
{
	refresh();
	while (!isWin&&!isFail) {
		isMerge = false;//重置是否合并过
		char key = _getch();//接收用户按键
		check_key(key);
		if (isFull())
		{
			check_fail();
		}
		else {
			int i = rand() % (size << 2);
			while (map[i / size][i % size])//如果不为0，说明有数字了
			{
					i = rand() % (size << 2);
			}
			if (isMerge)//上一回合有合并数字，则这回合出现的数字为4
				map[i / size][i % size] = 4;
			else
				map[i / size][i % size] = 2;
			refresh();//更新界面
		}
	}
	if (isWin)
	{
		cleardevice();
		//设置图片背景
		putimage(0, 0, &img);//放置图片
		outtextxy(100, height/2-50, _T("分数:"));
		TCHAR s[10];
		_stprintf_s(s, _T("%d"), score);
		outtextxy(200, height/2-50, s);
		outtextxy(110, height / 2, _T("你赢了！"));

	}
	if (isFail)
	{
		cleardevice();
		//设置图片背景
		putimage(0, 0, &img);//放置图片
		outtextxy(100, height / 2 - 50, _T("分数:"));
		TCHAR s[10];
		_stprintf_s(s, _T("%d"), score);
		outtextxy(200, height / 2 - 50, s);
		outtextxy(110, height / 2, _T("你输了！"));

	}
	
}


void Game::refresh() const
{
	cleardevice();
	settextstyle(40, 0, _T("Consolas"));//设置当前字体为高 16 像素的"Consolas"
	//设置图片背景
	putimage(0, 0, &img);//放置图片
	//显示分数
	outtextxy(80, height - 60, _T("分数:"));
	TCHAR s[10];
	_stprintf_s(s, _T("%d"), score);	
	outtextxy(180, height - 60, s);

	
	//显示地图
	int i, j;
	for (i = 0; i != size; ++i)
	{
		for (j = 0; j != size; ++j)
		{	
			if (i == 0)
			{
				line(j * 100, 0,j*100 , height - 101);
			}
			
			if(map[i][j]!=0)
			{ 
				TCHAR s[4];
				_stprintf_s(s, _T("%d"), map[i][j]);
				// 在屏幕中央输出字符串
				RECT r = { j*100, i*100, (j+1)*100-1, (i+1)*100-1 };//注意X,Y轴对应的啥
				drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
		line(0,i * 100 , width - 1,i * 100 );

	}
	line(0, i * 100, width - 1, i * 100);
}

void Game::initmap() 
{
	srand((unsigned)time(NULL)); //随机函数种子

	//随机生成两个位置放2
	int i = rand() % (size<<2) ;
	int j = rand() % (size<<2) ;
	while (i == j)
		j = rand() % (size << 2);
	map[i / 4][i % 4] = 2;
	map[j / 4][j % 4] = 2;
}

void Game::check_key(const char key)//检测按键
{
	switch (key)
	{
	case 'W':case'w'://上case 72:
		up();
		break;
	case 'S':case's'://下case 80:
		down();
		break;
	case 'A':case'a'://左case 75:
		left();
		break;
	case 'D':case'd'://右case 77: 32空格是暂停
		right();
		break;
	default://最好有提醒
		
		break;
	}
}

void Game::up()
{
	for (int j = 0; j != size; ++j)
	{
		int flag = 0;//记录可合并的行
		for (int i = 1; i != size; ++i)
		{
			if (map[i][j] == 0 || i==flag)//不含数字不计算 或者 flag标志和i重合
				continue;
			if (map[flag][j] == 0)//flag为0就交换
			{
				map[flag][j] = map[i][j];
				map[i][j] = 0;
				continue;
			}
			int sum = map[flag][j] + map[i][j];
			if (sum == 4 || sum == 8 || sum == 16 || sum == 32 || sum == 64 || sum == 128 || sum == 256 || sum == 512 || sum == 1024 || sum == 2048)
			{
				if (sum == 2048)//赢了
					isWin = true;
				map[flag][j] = sum;
				map[i][j] = 0;
				score += sum;
				isMerge = true;
				++flag;
			}
			else {
				map[++flag][j] = map[i][j];
				if(i!=flag)
					map[i][j] = 0;
			}	
		}
	}
}

void Game::down()
{

	for (int j = 0; j != size; ++j)
	{
		int flag = size-1;//记录可合并的行
		for (int i = size-2; i != -1; --i)
		{
			if (map[i][j] == 0 || i == flag)
				continue;
			if (map[flag][j] == 0)
			{
				map[flag][j] = map[i][j];
				map[i][j] = 0;
				continue;
			}
			int sum = map[flag][j] + map[i][j];
			if (sum == 4 || sum == 8 || sum == 16 || sum == 32 || sum == 64 || sum == 128 || sum == 256 || sum == 512 || sum == 1024|| sum == 2048)
			{
				if (sum==2048)//赢了
					isWin = true;
				map[flag][j] = sum;
				map[i][j] = 0;
				score += sum;
				isMerge = true;
				--flag;
			}
			else {
				map[--flag][j] = map[i][j];
				if (i != flag)
					map[i][j] = 0;
			}
		}
	}
}

void Game::left()
{
	for (int i = 0; i != size; ++i)
	{
		int flag =0;//记录可合并的行
		for (int j=1; j !=  size ; ++j)
		{
			if (map[i][j] == 0 || j == flag)
				continue;
			if (map[i][flag] == 0)
			{
				map[i][flag] = map[i][j];
				map[i][j] = 0;
				continue;
			}
			int sum = map[i][flag] + map[i][j];
			if (sum == 4 || sum == 8 || sum == 16 || sum == 32 || sum == 64 || sum == 128 || sum == 256 || sum == 512 || sum == 1024 || sum == 2048)
			{
				if (sum == 2048)//赢了
					isWin = true;
				map[i][flag] = sum;
				map[i][j] = 0;
				score += sum;
				isMerge = true;
				++flag;
			}
			else {
				map[i][++flag] = map[i][j];
				if (j != flag)
					map[i][j] = 0;
			}
		}
	}
}

void Game::right()
{
	for (int i = 0; i != size; ++i)
	{
		int flag = size-1;//记录可合并的行
		for (int j = size-2; j != -1; --j)
		{
			if (map[i][j] == 0 || j == flag)
				continue;
			if (map[i][flag] == 0)
			{
				map[i][flag] = map[i][j];
				map[i][j] = 0;
				continue;
			}
			int sum = map[i][flag] + map[i][j];
			if (sum == 4 || sum == 8 || sum == 16 || sum == 32 || sum == 64 || sum == 128 || sum == 256 || sum == 512 || sum == 1024 || sum == 2048)
			{
				if (sum == 2048)//赢了
					isWin = true;
					map[i][flag] = sum;
				map[i][j] = 0;
				score += sum;
				isMerge = true;
				--flag;
			}
			else {
				map[i][--flag] = map[i][j];
				if (j != flag)
					map[i][j] = 0;
			}
		}
	}
}

bool Game::isFull()
{
	for (auto& i : map)
	{
		for (auto& j : i)
			if (j==0)//找到为0的数字
				return false;
	}
	return true;
}

void Game::check_fail()
{
	for (int i = 0; i != size; ++i)
	{
		for (int j = 0; j != size; ++j)
		{
			if (j != size - 1 && map[i][j] == map[i][j + 1])
				return;
			if (i != size - 1 && map[i][j] == map[i + 1][j])
				return;
		}
	}
	isFail = true;
}