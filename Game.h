#pragma once
#include<easyx.h>
#include<conio.h>
#include<array>
#include<set>
constexpr int size=4;
class Game
{
public:
	Game();//构造函数
	void refresh() const;//刷新界面
	void play();
	~Game();
private:
	std::array<std::array<int, size>,size> map = {};//2048游戏界面
	int score=0;//分数
	const int width= 100 * size;
	const int height = 100 * size + 100;
	bool isWin=false;//是否赢了
	bool isMerge=false;//是否上一回合消掉了数字
	bool isFail = false;//是否失败
	IMAGE img;
	//随机生成初始地图
	void initmap();

	//按键对应的动作
	void check_key(const char key);//检测按键，是否赢了
	void up();
	void down();
	void left();
	void right();


	//检验是否失败	
	void check_fail();
	bool isFull();
};

