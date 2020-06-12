#pragma once
#include"graphics.h"
#include"mydefine.h"

const int MAP_NUMBER=1000;
const int COINS_NUMBER=1000;
const int SCORE_NUMBER=5;
const int FOOD_NUMBER=5;
class role;//超前说明（可以避免重复包含头文件）
#ifndef _MAP
#define _MAP
struct Map//地图的结构体
{
	int x;
	int y;
	int id;	
	int xAmount;//横向地图块的个数
	int yAmount;//纵向地图块的个数
	double u;//摩擦因数
};
#endif
class scene
{	
private:
	double xBg;//背景坐标
	double yBg;
	int xMap;//地图坐标
	int yMap;	
	Map map[MAP_NUMBER];
	POINT coins[COINS_NUMBER];//金币
	POINT score[SCORE_NUMBER];//得分
	POINT food[FOOD_NUMBER];//食物
	IMAGE img_bg;//背景图
	IMAGE img_map;//地图
	IMAGE img_scenery;//场景图
	IMAGE img_coin;//金币图
	IMAGE img_food;//食物图
	double scenery_iframe;//背景帧数
	double coin_iframe;//金币帧数
	double score_iframe[SCORE_NUMBER];
	double food_iframe;//食物帧数
	int world;//第world关
public:
	scene(int world);//第world关场景
	~scene(void);//清内存
	Map *getMap(){return map;}//抓取地图指针
	POINT *getCoins(){return coins;}
	POINT *getFood(){return food;}
	void setScorePos(int x,int y);//设置显示金钱的位置
	void setFood(int x,int y);//设置食物
	void createMap(int world);//创造第world关的地图	
	void createCoin();//在地图中绘制金币
	void createFood();//在地图中绘制食物
	void action(role *myRole);//主人公动作
	void show();
	bool isEnding(int distance);
};
