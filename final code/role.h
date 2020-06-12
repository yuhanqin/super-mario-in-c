#pragma once
#include"graphics.h"
#include"mydefine.h"

const int ENEMY_TOTE=100;
const int BOMB_NUMBER=5;
const int BULLET_NUMBER=30;
const int BULLET_INTERVAL=WIDTH;
const int LEHGTH_INTERVAL_BULLET=4;//数值越大，自动的速度越快 
const double TIME_INTERVAL_BULLET=0.2;//数值越大，要求子弹发射的间隔时间越长

class scene;//超前说明

struct Hero
{
	int x;//主人公的当前坐标（在屏幕上的坐标）
    int y;
	double xx;//主人公的坐标（double型）
	double yy;
	double x0;//原点坐标
	double vX;//速度
	double vY;
	int turn;//主人公运动的方向
	POINT direction;
	bool isFly;//主人公是否在空中
	bool isShoot;//主人公是否可以射击
	bool died;//主人公是否死亡
	bool ending;//主人公是否马上就要过关
	bool passed;//主人公是否过关
	int jump; //updated by qinyuhan at 23:00 3-10
	int hiddentime;//updated by qinyuhan at 22:30 3-18
};
struct Enemy
{
	int x;
	int y;
	int turn;//敌人的运动方向
};
struct Bullet
{
	int x;
	int y;
	int turn;
};
#ifndef _MAP
#define _MAP
struct Map//地图的结构体
{
	int x;//地图的横坐标
	int y;//地图的纵坐标
	int id;	//地图块的样式
	int xAmount;//横向地图块的个数
	int yAmount;//纵向地图块的个数
	double u;//摩擦因数
};
#endif
class role
{
public:	
	Hero myHero;//定义一个主人公
	scene *myScene;
	Enemy myEnemy[ENEMY_TOTE];//定义若干敌人
	POINT bombs[BOMB_NUMBER];//定义若干爆炸点
	Bullet bullets[BULLET_NUMBER];//定义若干子弹
	IMAGE img_hero;//主人公图片
	IMAGE img_enemy;//敌人图片
	IMAGE img_showBomb;
	IMAGE img_bullet;//子弹图片
	bool shootButtonDown;//用于记录射击键是否按下
	double shootTimeInterval;//用于自动刷新的射击时间间隔计时器
	int hero_iframe;//用于控制主人公、敌人和爆炸的加载帧（加载第几副精灵图，这样就能让精灵看上去动起来了）
	double enemy_iframe;//敌人动画帧图
	double bomb_iframe[BOMB_NUMBER];
	double bullet_iframe[BULLET_NUMBER];
	int score;
private:
	Map *touchMap(int x,int y,scene *myScene);//指针做参数后，效率明显提高
	POINT *touchCoins(int x,int y,scene *myScene);//捡到金币指针
	POINT *touchFood(int x,int y,scene *myScene);//吃到食物指针
	Enemy *touchEnemy(int x,int y,Enemy *emy);//碰撞敌人指针
	bool isTouch(POINT *p1,POINT *p2);
	void setBomb(int x,int y);
	void setBullet(int x,int y);//设置子弹
	void bullteFlying(Bullet *p,scene *myScene);//子弹在飞函数
public:
	role(int world);
	~role(void);
	Hero *getHero(){return &myHero;}//以下内容可根据变量名称判断
	bool isDied(){return myHero.died;}
	bool isPassed(){return myHero.passed;}
	void createEnemy(int world);//以下内容可根据变量名称判断
	void show();
	void action(int KEY,scene *myScene);
	int getScore(){return score;}//以下内容可根据变量名称判断
};
