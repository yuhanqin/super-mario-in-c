#pragma once
#include"graphics.h"

class control
{
private:
	int key;
private:
    int GetCommand();
	void pauseClick();
public:
	control(void);
	~control(void);
	int getKey();//��ȡ��Ұ��µļ�	
	void gameStart();//��Ϸ��ʼ����
	void showScore(int score);//��ʾ��Ǯ���÷֣�
	void showLevel(int level);//��ʾ�ؿ�
	void showDied(int life);     //���˹�����ʱ�Ķ���
	void showGameOver();         //��Ϸ����ʱ�Ķ���
	void showPassed(int word);   //���˹�����ʱ�Ķ���
	void showPassedAll();        //ͨ��ʱ�Ķ���
};
