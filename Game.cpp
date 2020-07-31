#include "Game.h"

#include<iostream>
#include <cstdlib> 
#include <ctime>

using std::cout;
using std::endl;
Game::Game()
{
	initmap();
	initgraph(width,height);//��Ϸ�����С
	//setbkcolor(0xffb99d);
	cleardevice();//��ջ�ͼ�豸	
	setbkmode(TRANSPARENT); //���õ�ǰ�豸ͼ�������������ʱ�ı���ģʽ��
	//����ͼƬ����
	loadimage(&img, L"C:\\Users\\82719\\Pictures\\��ֽ\\background.jpg");//����ͼƬ
	putimage(0, 0, &img);//����ͼƬ

	// ����Ļ��������ַ���
	settextcolor(WHITE);//�����ı���ɫ
	settextstyle(20, 0, _T("Consolas"));//���õ�ǰ����Ϊ�� 16 ���ص�"Consolas"
	RECT r = { 0, 0,width-1,height-1};
	drawtext(_T("���������ʼ��Ϸ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

Game::~Game()
{
	closegraph();//�رմ���
}


void Game::play()
{
	refresh();
	while (!isWin&&!isFail) {
		isMerge = false;//�����Ƿ�ϲ���
		char key = _getch();//�����û�����
		check_key(key);
		if (isFull())
		{
			check_fail();
		}
		else {
			int i = rand() % (size << 2);
			while (map[i / size][i % size])//�����Ϊ0��˵����������
			{
					i = rand() % (size << 2);
			}
			if (isMerge)//��һ�غ��кϲ����֣�����غϳ��ֵ�����Ϊ4
				map[i / size][i % size] = 4;
			else
				map[i / size][i % size] = 2;
			refresh();//���½���
		}
	}
	if (isWin)
	{
		cleardevice();
		//����ͼƬ����
		putimage(0, 0, &img);//����ͼƬ
		outtextxy(100, height/2-50, _T("����:"));
		TCHAR s[10];
		_stprintf_s(s, _T("%d"), score);
		outtextxy(200, height/2-50, s);
		outtextxy(110, height / 2, _T("��Ӯ�ˣ�"));

	}
	if (isFail)
	{
		cleardevice();
		//����ͼƬ����
		putimage(0, 0, &img);//����ͼƬ
		outtextxy(100, height / 2 - 50, _T("����:"));
		TCHAR s[10];
		_stprintf_s(s, _T("%d"), score);
		outtextxy(200, height / 2 - 50, s);
		outtextxy(110, height / 2, _T("�����ˣ�"));

	}
	
}


void Game::refresh() const
{
	cleardevice();
	settextstyle(40, 0, _T("Consolas"));//���õ�ǰ����Ϊ�� 16 ���ص�"Consolas"
	//����ͼƬ����
	putimage(0, 0, &img);//����ͼƬ
	//��ʾ����
	outtextxy(80, height - 60, _T("����:"));
	TCHAR s[10];
	_stprintf_s(s, _T("%d"), score);	
	outtextxy(180, height - 60, s);

	
	//��ʾ��ͼ
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
				// ����Ļ��������ַ���
				RECT r = { j*100, i*100, (j+1)*100-1, (i+1)*100-1 };//ע��X,Y���Ӧ��ɶ
				drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
		line(0,i * 100 , width - 1,i * 100 );

	}
	line(0, i * 100, width - 1, i * 100);
}

void Game::initmap() 
{
	srand((unsigned)time(NULL)); //�����������

	//�����������λ�÷�2
	int i = rand() % (size<<2) ;
	int j = rand() % (size<<2) ;
	while (i == j)
		j = rand() % (size << 2);
	map[i / 4][i % 4] = 2;
	map[j / 4][j % 4] = 2;
}

void Game::check_key(const char key)//��ⰴ��
{
	switch (key)
	{
	case 'W':case'w'://��case 72:
		up();
		break;
	case 'S':case's'://��case 80:
		down();
		break;
	case 'A':case'a'://��case 75:
		left();
		break;
	case 'D':case'd'://��case 77: 32�ո�����ͣ
		right();
		break;
	default://���������
		
		break;
	}
}

void Game::up()
{
	for (int j = 0; j != size; ++j)
	{
		int flag = 0;//��¼�ɺϲ�����
		for (int i = 1; i != size; ++i)
		{
			if (map[i][j] == 0 || i==flag)//�������ֲ����� ���� flag��־��i�غ�
				continue;
			if (map[flag][j] == 0)//flagΪ0�ͽ���
			{
				map[flag][j] = map[i][j];
				map[i][j] = 0;
				continue;
			}
			int sum = map[flag][j] + map[i][j];
			if (sum == 4 || sum == 8 || sum == 16 || sum == 32 || sum == 64 || sum == 128 || sum == 256 || sum == 512 || sum == 1024 || sum == 2048)
			{
				if (sum == 2048)//Ӯ��
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
		int flag = size-1;//��¼�ɺϲ�����
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
				if (sum==2048)//Ӯ��
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
		int flag =0;//��¼�ɺϲ�����
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
				if (sum == 2048)//Ӯ��
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
		int flag = size-1;//��¼�ɺϲ�����
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
				if (sum == 2048)//Ӯ��
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
			if (j==0)//�ҵ�Ϊ0������
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