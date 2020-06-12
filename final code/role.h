#pragma once
#include"graphics.h"
#include"mydefine.h"

const int ENEMY_TOTE=100;
const int BOMB_NUMBER=5;
const int BULLET_NUMBER=30;
const int BULLET_INTERVAL=WIDTH;
const int LEHGTH_INTERVAL_BULLET=4;//��ֵԽ���Զ����ٶ�Խ�� 
const double TIME_INTERVAL_BULLET=0.2;//��ֵԽ��Ҫ���ӵ�����ļ��ʱ��Խ��

class scene;//��ǰ˵��

struct Hero
{
	int x;//���˹��ĵ�ǰ���꣨����Ļ�ϵ����꣩
    int y;
	double xx;//���˹������꣨double�ͣ�
	double yy;
	double x0;//ԭ������
	double vX;//�ٶ�
	double vY;
	int turn;//���˹��˶��ķ���
	POINT direction;
	bool isFly;//���˹��Ƿ��ڿ���
	bool isShoot;//���˹��Ƿ�������
	bool died;//���˹��Ƿ�����
	bool ending;//���˹��Ƿ����Ͼ�Ҫ����
	bool passed;//���˹��Ƿ����
	int jump; //updated by qinyuhan at 23:00 3-10
	int hiddentime;//updated by qinyuhan at 22:30 3-18
};
struct Enemy
{
	int x;
	int y;
	int turn;//���˵��˶�����
};
struct Bullet
{
	int x;
	int y;
	int turn;
};
#ifndef _MAP
#define _MAP
struct Map//��ͼ�Ľṹ��
{
	int x;//��ͼ�ĺ�����
	int y;//��ͼ��������
	int id;	//��ͼ�����ʽ
	int xAmount;//�����ͼ��ĸ���
	int yAmount;//�����ͼ��ĸ���
	double u;//Ħ������
};
#endif
class role
{
public:	
	Hero myHero;//����һ�����˹�
	scene *myScene;
	Enemy myEnemy[ENEMY_TOTE];//�������ɵ���
	POINT bombs[BOMB_NUMBER];//�������ɱ�ը��
	Bullet bullets[BULLET_NUMBER];//���������ӵ�
	IMAGE img_hero;//���˹�ͼƬ
	IMAGE img_enemy;//����ͼƬ
	IMAGE img_showBomb;
	IMAGE img_bullet;//�ӵ�ͼƬ
	bool shootButtonDown;//���ڼ�¼������Ƿ���
	double shootTimeInterval;//�����Զ�ˢ�µ����ʱ������ʱ��
	int hero_iframe;//���ڿ������˹������˺ͱ�ը�ļ���֡�����صڼ�������ͼ�����������þ��鿴��ȥ�������ˣ�
	double enemy_iframe;//���˶���֡ͼ
	double bomb_iframe[BOMB_NUMBER];
	double bullet_iframe[BULLET_NUMBER];
	int score;
private:
	Map *touchMap(int x,int y,scene *myScene);//ָ����������Ч���������
	POINT *touchCoins(int x,int y,scene *myScene);//�񵽽��ָ��
	POINT *touchFood(int x,int y,scene *myScene);//�Ե�ʳ��ָ��
	Enemy *touchEnemy(int x,int y,Enemy *emy);//��ײ����ָ��
	bool isTouch(POINT *p1,POINT *p2);
	void setBomb(int x,int y);
	void setBullet(int x,int y);//�����ӵ�
	void bullteFlying(Bullet *p,scene *myScene);//�ӵ��ڷɺ���
public:
	role(int world);
	~role(void);
	Hero *getHero(){return &myHero;}//�������ݿɸ��ݱ��������ж�
	bool isDied(){return myHero.died;}
	bool isPassed(){return myHero.passed;}
	void createEnemy(int world);//�������ݿɸ��ݱ��������ж�
	void show();
	void action(int KEY,scene *myScene);
	int getScore(){return score;}//�������ݿɸ��ݱ��������ж�
};
