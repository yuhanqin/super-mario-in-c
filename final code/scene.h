#pragma once
#include"graphics.h"
#include"mydefine.h"

const int MAP_NUMBER=1000;
const int COINS_NUMBER=1000;
const int SCORE_NUMBER=5;
const int FOOD_NUMBER=5;
class role;//��ǰ˵�������Ա����ظ�����ͷ�ļ���
#ifndef _MAP
#define _MAP
struct Map//��ͼ�Ľṹ��
{
	int x;
	int y;
	int id;	
	int xAmount;//�����ͼ��ĸ���
	int yAmount;//�����ͼ��ĸ���
	double u;//Ħ������
};
#endif
class scene
{	
private:
	double xBg;//��������
	double yBg;
	int xMap;//��ͼ����
	int yMap;	
	Map map[MAP_NUMBER];
	POINT coins[COINS_NUMBER];//���
	POINT score[SCORE_NUMBER];//�÷�
	POINT food[FOOD_NUMBER];//ʳ��
	IMAGE img_bg;//����ͼ
	IMAGE img_map;//��ͼ
	IMAGE img_scenery;//����ͼ
	IMAGE img_coin;//���ͼ
	IMAGE img_food;//ʳ��ͼ
	double scenery_iframe;//����֡��
	double coin_iframe;//���֡��
	double score_iframe[SCORE_NUMBER];
	double food_iframe;//ʳ��֡��
	int world;//��world��
public:
	scene(int world);//��world�س���
	~scene(void);//���ڴ�
	Map *getMap(){return map;}//ץȡ��ͼָ��
	POINT *getCoins(){return coins;}
	POINT *getFood(){return food;}
	void setScorePos(int x,int y);//������ʾ��Ǯ��λ��
	void setFood(int x,int y);//����ʳ��
	void createMap(int world);//�����world�صĵ�ͼ	
	void createCoin();//�ڵ�ͼ�л��ƽ��
	void createFood();//�ڵ�ͼ�л���ʳ��
	void action(role *myRole);//���˹�����
	void show();
	bool isEnding(int distance);
};
