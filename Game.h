#pragma once
#include<easyx.h>
#include<conio.h>
#include<array>
#include<set>
constexpr int size=4;
class Game
{
public:
	Game();//���캯��
	void refresh() const;//ˢ�½���
	void play();
	~Game();
private:
	std::array<std::array<int, size>,size> map = {};//2048��Ϸ����
	int score=0;//����
	const int width= 100 * size;
	const int height = 100 * size + 100;
	bool isWin=false;//�Ƿ�Ӯ��
	bool isMerge=false;//�Ƿ���һ�غ�����������
	bool isFail = false;//�Ƿ�ʧ��
	IMAGE img;
	//������ɳ�ʼ��ͼ
	void initmap();

	//������Ӧ�Ķ���
	void check_key(const char key);//��ⰴ�����Ƿ�Ӯ��
	void up();
	void down();
	void left();
	void right();


	//�����Ƿ�ʧ��	
	void check_fail();
	bool isFull();
};

