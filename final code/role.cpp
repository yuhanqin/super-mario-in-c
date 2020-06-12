#include "role.h"
#include"graphics.h"
#include"mydefine.h"
#include"math.h"
#include"rule.h"
#pragma comment(lib,"Winmm.lib")   //给游戏添加音乐要用到它

extern int world;

role::role(int world)
{
	myHero.x=X0;//定义主人公的初始位置
	myHero.y=X0;
	myHero.xx=myHero.x;
	myHero.yy=myHero.y;
	myHero.x0=0;
	myHero.vX=0;
	myHero.vY=0;
	myHero.turn=1;//1为向右-1为向左
	myHero.direction.x=0;
	myHero.direction.y=0;
	myHero.isFly=true;//判定人物是否在空中
	myHero.isShoot=false;//判定人物是否射击
	myHero.died=false;//是否生命-1
	myHero.ending=false;//是否即将通关
	myHero.passed=false;//是否通关
	myHero.jump=0;//updated by qinyuhan at 10:00 3-11
	myHero.hiddentime=0;//updated by qinyuhan at 22:30 3-18
	myScene=0;
	hero_iframe=1;//主人公的图片为第1帧
	enemy_iframe=1;//敌人的图片为第1帧
	shootButtonDown=false;//关闭主人公射击技能
	shootTimeInterval=0;//射击计时器清零
	score=0;
	loadimage(&img_hero,"res\\role.bmp");//载入图片
	loadimage(&img_enemy,"res\\ani.bmp");
	loadimage(&img_showBomb,"res\\ani.bmp");
	loadimage(&img_bullet,"res\\ani.bmp");
	for(int i=0;i<ENEMY_TOTE;i++)//初始化敌人
	{
		myEnemy[i].x=0;
		myEnemy[i].y=0;
		myEnemy[i].turn=0;
	}
	for(int j=0;j<BOMB_NUMBER;j++)//初始化子弹
	{
		bombs[j].x=0;
	    bombs[j].y=0;
		bomb_iframe[j]=0;
	}
	for(int k=0;k<BULLET_NUMBER;k++)//初始化道具
	{
		bullets[k].x=0;
		bullets[k].y=0;
		bullets[k].turn=0;
		bullet_iframe[k]=0;
	}
	createEnemy(world);//创建第world关敌人
	mciSendString("open res\\死亡1.mp3 alias music_died", NULL, 0, NULL);//载入音乐备用
	mciSendString("open res\\跳.mp3 alias music_jump", NULL, 0, NULL);
	mciSendString("open res\\金币.mp3 alias music_coin", NULL, 0, NULL);
	mciSendString("open res\\踩敌人.mp3 alias music_tread", NULL, 0, NULL);
	mciSendString("open res\\吃到武器.mp3 alias music_getWeapon", NULL, 0, NULL);
	mciSendString("open res\\子弹.mp3 alias music_bullet", NULL, 0, NULL);
	mciSendString("open res\\子弹撞墙.mp3 alias music_boom", NULL, 0, NULL);
	mciSendString("open res\\子弹打到敌人.mp3 alias music_boom2", NULL, 0, NULL);
	
}
role::~role(void)
{
}
void role::createEnemy(int world)//创建敌人
{
	if(world==1)
	{
		Enemy emy[]={{3,8,1},{18,8,-1},{36,8,-1},{47,4,1},{47,8,1},{57,8,-1},{68,4,1},{66,8,-1},{79,8,1}};//第1位为x坐标，第2位为y坐标，第3位为运动方向
		int i=0;
		while(i<=sizeof(emy)/sizeof(emy[0]))//通过坐标*单位格子宽度32像素在地图中绘制对应的敌人
		{
			myEnemy[i].x=emy[i].x*WIDTH;
			myEnemy[i].y=emy[i].y*HEIGHT;
			myEnemy[i].turn=emy[i].turn;
			i++;
		}
	}
	else if(world==2)
	{
		Enemy emy[]={{17,4,1},{24,5,1},{28,7,-1},{32,12,1},{44,9,1},{56,7,1},{64,8,1},{77,6,1},{89,4,1}};//第1位为x坐标，第2位为y坐标，第3位为运动方向
		int i=0;
		while(i<=sizeof(emy)/sizeof(emy[0]))//通过坐标*单位格子宽度32像素在地图中绘制对应的敌人
		{
			myEnemy[i].x=emy[i].x*WIDTH;
			myEnemy[i].y=emy[i].y*HEIGHT;
			myEnemy[i].turn=emy[i].turn;
			i++;
		}
	}
	else if(world==3)
	{
		Enemy emy[]={{4,9,1},{24,4,1},{30,5,1},{47,1,1},
{60,9,1},{66,1,1},{82,3,1},{90,3,1},{96,3,-1},
{98,1,1},{109,10,1},{120,6,1},{125,2,1},{125,4,1},
{129,2,1},{129,6,-1},{135,1,1},{143,1,-1},{154,7,1},
{160,7,-1},{162,4,1},{168,4,-1},{175,1,1},{183,9,1},
{187,9,-1},{195,6,1},{208,5,1},{213,5,-1},{229,5,1},
{238,9,1},{240,7,1},{242,5,1},{244,3,1},{256,4,1},
{265,9,1},{275,9,-1},{270,1,1},{276,6,1},{278,6,-1},
{279,9,1},{281,6,1},{283,6,-1},{283,1,1},{283,3,1},
{288,5,1},{291,5,-1},{293,8,1},{295,6,1},{130,10,1},
{142,10,1},{221,9,1},{234,9,-1},{228,9,1},{28,1,1},
{95,1,1},{90,1,1},{112,4,1},{122,4,-1},{200,1,1},{208,1,-1},{203,1,-1},{221,1,1},{85,9,1},{90,9,1},{96,9,-1},{130,10,1},{136,10,1},{147,10,-1},{191,9,1},{195,9,-1}
		};//第1位为x坐标，第2位为y坐标，第3位为运动方向 这是精心设计的第三关超长地图
		int i=0;
		while(i<=sizeof(emy)/sizeof(emy[0]))//通过坐标*单位格子宽度32像素在地图中绘制对应的敌人
		{
			myEnemy[i].x=emy[i].x*WIDTH;
			myEnemy[i].y=emy[i].y*HEIGHT;
			myEnemy[i].turn=emy[i].turn;
			i++;
		}
	}
}//updated by 张子晗 2018.3.15 20:55
void role::setBomb(int x,int y)//创建子弹道具
{
	for(int i=0;i<BOMB_NUMBER;i++)
	{
		if(bombs[i].x==0&&bombs[i].y==0)
		{
			bombs[i].x=x;
			bombs[i].y=y;
			bomb_iframe[i]=1;
			break;
		}
	}
}
void role::setBullet(int x,int y)
{
	for(int i=0;i<BULLET_NUMBER;i++)
	{
		if(bullets[i].x==0&&bullets[i].y==0)
		{
			bullets[i].x=x;
			bullets[i].y=y;
			bullets[i].turn=myHero.turn;
			bullet_iframe[i]=1;
			break;
		}
	}
}
void role::bullteFlying(Bullet *p,scene *myScene)//子弹在空中飞
{
	if(p->x==0&&p->y==0)//若子弹越界则无效
		return;
	if(p->x>XSIZE||p->x<-WIDTH)//若子弹越界则无效（越界代表越过屏幕范围）
	{
		p->x=0;
		p->y=0;
		p->turn=0;
		return;
	}
	Enemy *emy=touchEnemy(p->x,p->y,myEnemy);//打中敌人指针
	Map *map=touchMap(p->x,p->y,myScene);//打中墙指针
	if(emy!=NULL||map!=NULL)//如果子弹打到敌人或者墙
	{
		if(emy!=NULL)
		{mciSendString("play music_boom2 from 0", NULL, 0, NULL);score+=5;}
		else
			mciSendString("play music_boom from 0", NULL, 0, NULL);
		
		//记下爆炸点的坐标
		int x,y;
		if(emy!=NULL)//如果打中了
		{
			x=emy->x;//最基础的交换操作记录坐标
			y=emy->y;
			emy->x=0;
			emy->y=0;
			emy->turn=0;
			p->x=0;
			p->y=0;
			p->turn=0;
		}
		else
		{
			x=(-(int)myHero.x0+p->x)/WIDTH*WIDTH;
			if(p->turn==-1)
				x=(-(int)myHero.x0+p->x+WIDTH)/WIDTH*WIDTH;
			y=p->y;
			p->x=0;
			p->y=0;
			p->turn=0;
		
		}
		setBomb(x,y);//爆炸
	}
	else
		p->x+=LEHGTH_INTERVAL_BULLET*p->turn;
}
bool role::isTouch(POINT *p1,POINT *p2)//判定是否有接触
{
	for(int i=0;i<4;i++)//如果主人公4个顶点有一个顶点在地图内，则判断为接触到地图
	{
		if(p1[i].x>=p2[0].x&&p1[i].y>=p2[0].y&&p1[i].x<=p2[1].x&&p1[i].y<=p2[1].y)
		{
			return true;
		}
	}
	return false;
}
Map *role::touchMap(int x,int y,scene *myScene)
{
	//总体思路是判断主人公的四个顶点是否至少有一个在地图内，有，则判断为主人公碰撞到地图
	int xmap=(int)myHero.x0;
	POINT r[4];//主人公4个顶点的坐标（比主人公小一圈）此处主人公无论朝向如何都是一个圆形在向前进，不需要过多的点来描述
	r[0].x=-xmap+x+1;
	r[0].y=y+1;
	r[1].x=-xmap+x+WIDTH-1;
	r[1].y=y+1;
	r[2].x=-xmap+x+1;
	r[2].y=y+HEIGHT-1;
	r[3].x=-xmap+x+WIDTH-1;
	r[3].y=y+HEIGHT-1;
	int i=0;
	while(myScene->getMap()[i].id>0&&myScene->getMap()[i].id<13
		&&i<MAP_NUMBER)//条件：地图存在且为前13种地图
	{
		POINT m[2];//地图左上角顶点和右下角顶点的坐标

		m[0].x=myScene->getMap()[i].x*WIDTH;
		m[0].y=myScene->getMap()[i].y*HEIGHT;

		if(myScene->getMap()[i].id==10)//id为10的地图要大些
		{
			m[1].x=myScene->getMap()[i].x*WIDTH+myScene->getMap()[i].xAmount*2*WIDTH;
	        m[1].y=myScene->getMap()[i].y*HEIGHT+myScene->getMap()[i].yAmount*2*HEIGHT;
		}
		else
		{
			m[1].x=myScene->getMap()[i].x*WIDTH+myScene->getMap()[i].xAmount*WIDTH;
    	    m[1].y=myScene->getMap()[i].y*HEIGHT+myScene->getMap()[i].yAmount*HEIGHT;
		}
		if(isTouch(r,m))//如果两个矩形相交，则碰撞
			return &(myScene->getMap()[i]);
		i++;
	}
	return NULL;
}
POINT *role::touchCoins(int x,int y,scene *myScene)
{
	//总体思路是判断主人公的四个顶点是否至少有一个在硬币内，有，则判断为主人公碰吃到硬币
	int xmap=(int)myHero.x0;
	POINT r[4];//主人公4个顶点的坐标（比主人公小一圈），同理
	r[0].x=-xmap+x+1;
	r[0].y=y+1;
	r[1].x=-xmap+x+WIDTH-1;
	r[1].y=y+1;
	r[2].x=-xmap+x+1;
	r[2].y=y+HEIGHT-1;
	r[3].x=-xmap+x+WIDTH-1;
	r[3].y=y+HEIGHT-1;
	int i=0;
	while(i<COINS_NUMBER)
	{
		POINT m[2];//硬币左上角顶点和右下角顶点的坐标

		m[0].x=myScene->getCoins()[i].x*WIDTH;
		m[0].y=myScene->getCoins()[i].y*HEIGHT;
		m[1].x=m[0].x+WIDTH;
    	m[1].y=m[0].y+HEIGHT;
		if(isTouch(r,m))//如果两个矩形相交，则碰撞
			return &(myScene->getCoins()[i]);
		i++;
	}
	return NULL;
}
POINT *role::touchFood(int x,int y,scene *myScene)
{
	//总体思路是判断主人公的四个顶点是否至少有一个在食物内，有，则判断为主人公碰吃到食物
	int xmap=(int)myHero.x0;
	POINT r[4];//主人公4个顶点的坐标（比主人公小一圈），同理
	r[0].x=-xmap+x+1;
	r[0].y=y+1;
	r[1].x=-xmap+x+WIDTH-1;
	r[1].y=y+1;
	r[2].x=-xmap+x+1;
	r[2].y=y+HEIGHT-1;
	r[3].x=-xmap+x+WIDTH-1;
	r[3].y=y+HEIGHT-1;
	int i=0;
	while(i<FOOD_NUMBER)
	{
		POINT m[2];//食物左上角顶点和右下角顶点的坐标

		m[0].x=myScene->getFood()[i].x;
		m[0].y=myScene->getFood()[i].y;
		m[1].x=m[0].x+3*WIDTH/2+4;
    	m[1].y=m[0].y+4*HEIGHT/5;
		if(isTouch(r,m))//如果两个矩形相交，则碰撞
			return &(myScene->getFood()[i]);
		i++;
	}
	return NULL;
}
Enemy *role::touchEnemy(int x,int y,Enemy *emy)
{
	//总体思路是判断主人公的四个顶点是否至少有一个在地图内，有，则判断为主人公碰撞到敌人
	int xmap=(int)myHero.x0;
	POINT r[8];//由于主人公的图形是圆形，故仅用四个角落定位主人公的位置较为不精确，所以采用八边形割圆，使其能更加精确
	r[0].x=-xmap+x+10;r[0].y=y+1;
	r[1].x=-xmap+x+24;r[1].y=y+1;
	r[2].x=-xmap+x+1;r[2].y=y+10;
	r[3].x=-xmap+x+WIDTH-1;r[3].y=y+10;
	r[4].x=-xmap+x+1;r[4].y=y+24;
	r[5].x=-xmap+x+WIDTH-1;r[5].y=y+24;
	r[6].x=-xmap+x+10;r[6].y=y+HEIGHT-1;
	r[7].x=-xmap+x+24;r[7].y=y+HEIGHT-1;
	int i=0;
	while(i<ENEMY_TOTE)//若存在敌人则进入循环
	{
		if(emy[i].turn!=0)//同样判断
		{
    		POINT m[2];//敌人左上角顶点和右下角顶点的坐标

    	 	m[0].x=emy[i].x;
    		m[0].y=emy[i].y;
    		m[1].x=m[0].x+WIDTH;
    	    m[1].y=m[0].y+HEIGHT;
   	    	
			if(world==1)
			{
			if(isTouch(r,m))//如果两个矩形相交，则碰撞
    		{
				return &emy[i];
	    	}
			}

				if(world==2)
			{
			if(isTouch(r,m))//如果两个矩形相交，则碰撞
    		{
				return &emy[i];
	    	}
			}

					if(world==3)
			{
				if((GetAsyncKeyState('H')&0x8000)&&myHero.hiddentime<1000)//按下H键可以隐身
				{
					myHero.hiddentime++;
				}
				else
				{

			if(isTouch(r,m))//如果两个矩形相交，则碰撞
    		{
				return &emy[i];
	    	}
			myHero.hiddentime=0;
				}
			}


		}
		i++;
	}
	return NULL;
}
void role::show()
{
	//下面代码用于控制主人公的转动，令人更加舒服
	//改变主人公加载图片的第几帧
	int rolePos=-(int)myHero.x0+myHero.x;//主人公的位置
	if(rolePos/STEP%2==0&&rolePos/STEP%4!=0)
		hero_iframe=2;
	else if(rolePos/STEP%4==0)
		hero_iframe=1;
	//控制主人公的方向
	if(myHero.direction.x==1)
		myHero.turn=1;
	else if(myHero.direction.x==-1)
		myHero.turn=-1;
	if(myHero.died==true)//如果主人公挂掉了
	{
		putimage(myHero.x,myHero.y,WIDTH,HEIGHT,&img_hero,2*WIDTH,HEIGHT,SRCAND);//定格图片，与sleep配合定格画面
		putimage(myHero.x,myHero.y,WIDTH,HEIGHT,&img_hero,2*WIDTH,0,SRCPAINT);
	}
	else//如果没挂
	{
		if(myHero.turn==1)//如果向右
		{
			putimage(myHero.x,myHero.y,WIDTH,HEIGHT,&img_hero,(hero_iframe-1)*WIDTH,HEIGHT,SRCAND);//载入下一帧，使主人公滚起来
   			putimage(myHero.x,myHero.y,WIDTH,HEIGHT,&img_hero,(hero_iframe-1)*WIDTH,0,SRCPAINT);

		}
		else
		{
			putimage(myHero.x,myHero.y,WIDTH,HEIGHT,&img_hero,(hero_iframe-1)*WIDTH+3*WIDTH,HEIGHT,SRCAND);
   			putimage(myHero.x,myHero.y,WIDTH,HEIGHT,&img_hero,(hero_iframe-1)*WIDTH+3*WIDTH,0,SRCPAINT);
		}
	}

	//改变敌人加载图片的第几帧，同上，并不再过多注释
	enemy_iframe+=TIME*5;
	if((int)enemy_iframe==3)
		enemy_iframe=1;
	int i=0;
	while(i<ENEMY_TOTE)
	{
		if(myEnemy[i].turn!=0)
		{
    		putimage((int)myHero.x0+myEnemy[i].x,myEnemy[i].y,WIDTH,HEIGHT,&img_enemy,((int)enemy_iframe-1)*WIDTH,HEIGHT,SRCAND);
       	    putimage((int)myHero.x0+myEnemy[i].x,myEnemy[i].y,WIDTH,HEIGHT,&img_enemy,((int)enemy_iframe-1)*WIDTH,0,SRCPAINT);
		}
		i++;
	}
	//下面代码用于控制爆炸效果，载入方式同上
	for(int j=0;j<BOMB_NUMBER;j++)
	{
		if(bombs[j].x!=0&&bombs[j].y!=0)
		{
			bomb_iframe[j]+=TIME*10;
			if((int)bomb_iframe[j]==5)
			{
				bomb_iframe[j]=1;
				bombs[j].x=0;
				bombs[j].y=0;
			}
			else
			{
	    		putimage((int)myHero.x0+bombs[j].x-WIDTH/2,bombs[j].y-HEIGHT/2,2*WIDTH,2*HEIGHT,&img_showBomb,((int)bomb_iframe[j]-1)*2*WIDTH,6*HEIGHT,SRCAND);
             	putimage((int)myHero.x0+bombs[j].x-WIDTH/2,bombs[j].y-HEIGHT/2,2*WIDTH,2*HEIGHT,&img_showBomb,((int)bomb_iframe[j]-1)*2*WIDTH,4*HEIGHT,SRCPAINT);
			}
		}
	}
	//下面代码用于控制子弹的显示。载入方式同上
	for(int k=0;k<BULLET_NUMBER;k++)
	{
		if(bullets[k].x!=0&&bullets[k].y!=0)
		{
			bullet_iframe[k]+=TIME*10;
			if((int)bullet_iframe[k]==3)
			{
				bullet_iframe[k]=1;
			}
			else
			{
	    		putimage(bullets[k].x,bullets[k].y,WIDTH,HEIGHT,&img_bullet,((int)bullet_iframe[k]-1)*WIDTH,3*HEIGHT,SRCAND);
             	putimage(bullets[k].x,bullets[k].y,WIDTH,HEIGHT,&img_bullet,((int)bullet_iframe[k]-1)*WIDTH,2*HEIGHT,SRCPAINT);
			}
			bullteFlying(&bullets[k],myScene);
		}
	}
}
void role::action(int KEY,scene *myScene)
{
	this->myScene=myScene;
	myHero.direction.x=0;//主人公并不朝向某一个方向
	myHero.direction.y=0;
    double a=0;//主人公运动的加速度和摩擦力给予的加速度
	double a1=0;
	Map *map=NULL;
	

	if(world==1)
 {
	
	if((KEY&CMD_UP)/*&&myHero.isFly==false*/&&myHero.jump<1&&myHero.ending==false)//只有当主人公没有在空中且主人公没过关的时候允许按上升键
	{
		mciSendString("play music_jump from 0", NULL, 0, NULL);
		myHero.isFly=true;//主人公在空中
		myHero.vY=-sqrt(2*G*REAL_HEIGHT);//开始用公式算速度
		myHero.jump++;
	}	
	if(myHero.isFly==true)// updated by qinyuhan at 10:00 3-11
	{		
		myHero.yy=myHero.yy-(-rule::move(myHero.vY,TIME,G)*UNREAL_HEIGHT/REAL_HEIGHT);//move函数返回单位时间（T）内，主人公上升或下降的高度
		myHero.y=(int)myHero.yy;
		map=touchMap(myHero.x,myHero.y+1,myScene);

		if((KEY&CMD_UP)/*&&myHero.isFly==false*/&&myHero.jump<9&&myHero.ending==false)//只有当主人公没有在空中且主人公没过关的时候允许按上升键
	{
		mciSendString("play music_jump from 0", NULL, 0, NULL);
		myHero.isFly=true;//表示主人公在空中
		myHero.vY=-sqrt(2*G*REAL_HEIGHT);//开始用公式算速度
		myHero.jump++;
		

		if(myHero.isFly==true)//如果主人公在天上飞
		myHero.yy=myHero.yy-(-rule::move(myHero.vY,TIME,G)*UNREAL_HEIGHT/REAL_HEIGHT);//move函数返回单位时间（T）内，主人公上升或下降的高度
		myHero.y=(int)myHero.yy;
		map=touchMap(myHero.x,myHero.y+1,myScene);}


		if(map!=NULL)// updated by qinyuhan at 10:00 3-11
		{
			if(myHero.vY>0)//表示当主人公接触地面时
				{myHero.isFly=false;
			myHero.jump=0;}
			myHero.vY=0;
			myHero.y=(myHero.y+HEIGHT/2)/HEIGHT*HEIGHT;//巧用了“+HEIGHT/2”，表示主人公的中心
			myHero.yy=myHero.y;
		    myHero.direction.y+=1;
		
		}
		if(myHero.vY>0)
		{
			Enemy *emy=touchEnemy(myHero.x,myHero.y,myEnemy);
			if(emy!=NULL)//如果主人公踩死敌人
			{
				mciSendString("play music_tread from 0", NULL, 0, NULL);
				score+=5;//金钱+5
				//记下爆炸点的坐标
				setBomb(emy->x,emy->y);
				emy->x=0;
	    		emy->y=0;
	    		emy->turn=0;
			}
			if(myHero.y>YSIZE)
			{
				myHero.died=true;//主人公-1s
				mciSendString("play music_died from 0", NULL, 0, NULL);
			}
		}
	}
	else
	{
		map=touchMap(myHero.x,myHero.y+1,myScene);
		if(map==NULL)//如果主人公没有碰到地图，及在空中
    	{
    		myHero.isFly=true;
    	}
	}
  }

	if(world==2)
 {
	
	if((KEY&CMD_UP)&&myHero.ending==false)//只有当主人公没有在空中且主人公没过关的时候允许按上升键
	{
		mciSendString("play music_jump from 0", NULL, 0, NULL);
		myHero.isFly=true;//主人公在空中
		myHero.vY=-sqrt(2*G*REAL_HEIGHT);//开始用公式算速度
		myHero.jump++;
	}	
	if(myHero.isFly==true)// updated by qinyuhan at 10:00 3-11
	{		
		myHero.yy=myHero.yy-(-rule::move(myHero.vY,TIME,G)*UNREAL_HEIGHT/REAL_HEIGHT);//move函数返回单位时间（T）内，主人公上升或下降的高度
		myHero.y=(int)myHero.yy;
		map=touchMap(myHero.x,myHero.y+1,myScene);

		if((KEY&CMD_UP)/*&&myHero.isFly==false*/&&myHero.jump<9&&myHero.ending==false)//只有当主人公没有在空中且主人公没过关的时候允许按上升键
	{
		mciSendString("play music_jump from 0", NULL, 0, NULL);
		myHero.isFly=true;//表示主人公在空中
		myHero.vY=-sqrt(2*G*REAL_HEIGHT);//开始用公式算速度
		myHero.jump++;
		

		if(myHero.isFly==true)//如果主人公在天上飞
		myHero.yy=myHero.yy-(-rule::move(myHero.vY,TIME,G)*UNREAL_HEIGHT/REAL_HEIGHT);//move函数返回单位时间（T）内，主人公上升或下降的高度
		myHero.y=(int)myHero.yy;
		map=touchMap(myHero.x,myHero.y+1,myScene);}


		if(map!=NULL)// updated by qinyuhan at 10:00 3-11
		{
			if(myHero.vY>0)//表示当主人公接触地面时
				{myHero.isFly=false;
			myHero.jump=0;}
			myHero.vY=0;
			myHero.y=(myHero.y+HEIGHT/2)/HEIGHT*HEIGHT;//巧用了“+HEIGHT/2”，表示主人公的中心
			myHero.yy=myHero.y;
		    myHero.direction.y+=1;
		
		}
		if(myHero.vY>0)
		{
			Enemy *emy=touchEnemy(myHero.x,myHero.y,myEnemy);
			if(emy!=NULL)//如果主人公踩死敌人
			{
				mciSendString("play music_tread from 0", NULL, 0, NULL);
				score+=5;//金钱+5
				//记下爆炸点的坐标
				setBomb(emy->x,emy->y);
				emy->x=0;
	    		emy->y=0;
	    		emy->turn=0;
			}
			if(myHero.y>YSIZE)
			{
				myHero.died=true;//主人公-1s
				mciSendString("play music_died from 0", NULL, 0, NULL);
			}
		}
	}
	else
	{
		map=touchMap(myHero.x,myHero.y+1,myScene);
		if(map==NULL)//如果主人公没有碰到地图，及在空中
    	{
    		myHero.isFly=true;
    	}
	}
  }


	if(world==3)
 {
	
	if((KEY&CMD_UP)/*&&myHero.isFly==false*/&&myHero.jump<2&&myHero.ending==false)//只有当主人公没有在空中且主人公没过关的时候允许按上升键
	{
		mciSendString("play music_jump from 0", NULL, 0, NULL);
		myHero.isFly=true;//主人公在空中
		myHero.vY=-sqrt(2*G*REAL_HEIGHT);//开始用公式算速度
		myHero.jump++;
	}	
	if(myHero.isFly==true)// updated by qinyuhan at 10:00 3-11
	{		
		myHero.yy=myHero.yy-(-rule::move(myHero.vY,TIME,G)*UNREAL_HEIGHT/REAL_HEIGHT);//move函数返回单位时间（T）内，主人公上升或下降的高度
		myHero.y=(int)myHero.yy;
		map=touchMap(myHero.x,myHero.y+1,myScene);

		if((KEY&CMD_UP)/*&&myHero.isFly==false*/&&myHero.jump<9&&myHero.ending==false)//只有当主人公没有在空中且主人公没过关的时候允许按上升键
	{
		mciSendString("play music_jump from 0", NULL, 0, NULL);
		myHero.isFly=true;//表示主人公在空中
		myHero.vY=-sqrt(2*G*REAL_HEIGHT);//开始用公式算速度
		myHero.jump++;
		

		if(myHero.isFly==true)//如果主人公在天上飞
		myHero.yy=myHero.yy-(-rule::move(myHero.vY,TIME,G)*UNREAL_HEIGHT/REAL_HEIGHT);//move函数返回单位时间（T）内，主人公上升或下降的高度
		myHero.y=(int)myHero.yy;
		map=touchMap(myHero.x,myHero.y+1,myScene);}


		if(map!=NULL)// updated by qinyuhan at 10:00 3-11
		{
			if(myHero.vY>0)//表示当主人公接触地面时
				myHero.isFly=false;
			
			myHero.vY=0;
			myHero.jump=0;
			myHero.y=(myHero.y+HEIGHT/2)/HEIGHT*HEIGHT;//巧用了“+HEIGHT/2”，表示主人公的中心
			myHero.yy=myHero.y;
		    myHero.direction.y+=1;
		
		}
		if(myHero.vY>0)
		{
			Enemy *emy=touchEnemy(myHero.x,myHero.y,myEnemy);
			/*if(emy!=NULL)//如果主人公踩死敌人
			{
				mciSendString("play music_tread from 0", NULL, 0, NULL);
				score+=5;//金钱+5
				//记下爆炸点的坐标
				setBomb(emy->x,emy->y);
				emy->x=0;
	    		emy->y=0;
	    		emy->turn=0;
			}*/
			if(myHero.y>YSIZE)
			{
				myHero.died=true;//主人公-1s
				mciSendString("play music_died from 0", NULL, 0, NULL);
			}
		}
	}
	else
	{
		map=touchMap(myHero.x,myHero.y+1,myScene);
		if(map==NULL)//如果主人公没有碰到地图，及在空中
    	{
    		myHero.isFly=true;
    	}
	}
  }



	if(KEY&CMD_DOWN)//玩家按下键并没有什么用
	{
	}
	if(KEY&CMD_LEFT&&myHero.ending==false)
	{
		a-=A_ROLE;
		myHero.direction.x-=1;
	}
   	if(KEY&CMD_RIGHT||myHero.ending==true)
	{
		a+=A_ROLE;
		myHero.direction.x+=1;
	}
	//以下代码处理主人公水平方向上的运动
	if(myHero.vX*a<=0&&myHero.vX!=0)
	{
		int k=-(int)(myHero.vX/abs(myHero.vX));//k代表加速度的方向
		if(map==NULL)
			a1=0;
		else
			a1=k*G*map->u;//由物理公式a=mg*u/g得出
	}
	double tmp=myHero.vX;
	double H=rule::move(myHero.vX,TIME,a+a1)*UNREAL_HEIGHT/REAL_HEIGHT;//这段代码看起来令人挠头，但是实际上就是算高度[摊手]
	if(tmp*myHero.vX<0)
		myHero.vX=0;
	myHero.xx=myHero.xx+H;
	myHero.x=(int)myHero.xx;
	if(myScene->isEnding(-(int)myHero.x0+myHero.x))//如果主人公马上过关则自动向右推进
	{
		myHero.ending=true;
	}
	if(myHero.x>XSIZE)//如果主人公已经触及画布右边界则已过关
		myHero.passed=true;
	if(touchMap(myHero.x,myHero.y,myScene)!=NULL)
	{
		if(myHero.x>XRIGHT)//限制主人公的位置不能跑过头了
			myHero.x=XRIGHT;
		else
			myHero.x=(int)(myHero.xx-H);
		myHero.xx=myHero.x;
		myHero.vX=0;
	    a=0;
		a1=0;
	}
	if(abs(myHero.vX)>V_MAX)//限制主人公的速度不能大过头了
		myHero.vX=myHero.vX/abs(myHero.vX)*V_MAX;
	if(KEY&CMD_ESC)
	{
	}
	if(KEY&CMD_SHOOT&&myHero.isShoot==true)
	{
		//x为子弹的横坐标
		int x=myHero.x+WIDTH/2;
		if(myHero.turn==-1)
			x=myHero.x-WIDTH;

		//以下代码控制子弹的运动
		//当一直按住射击键时，子弹在一定时间内才能发射；否者可以随时发射子弹
		if(shootButtonDown==false)
		{
			mciSendString("play music_bullet from 0", NULL, 0, NULL);
			setBullet(x,myHero.y);
		}
		else
		{
			if(shootTimeInterval==0)//如果射击间隔参数为0

			{
				mciSendString("play music_bullet from 0", NULL, 0, NULL);
				setBullet(x,myHero.y);
			}
			shootTimeInterval+=TIME;//射击时间间隔与自动刷新频率相匹配
			if(shootTimeInterval>TIME_INTERVAL_BULLET)
	        	shootTimeInterval=0;
		}
		shootButtonDown=true;
	}
	else
	{
		shootButtonDown=false;
		shootTimeInterval=0.01;
	}
	//判断出主人公是否超出左右界限
    if(myHero.x<XLEFT)
	{
		myHero.x=XLEFT;//不让主角往回走
		myHero.xx=myHero.x;
		myHero.vX=0;
		a=0;
	}
   	else if(myHero.x>XRIGHT&&myHero.ending==false)//如果主人公向右超过屏幕则整体右移
	{
		myHero.x0-=(myHero.x-XRIGHT);
		myHero.x=XRIGHT;
		myHero.xx=myHero.x;
	}
	//以下程序控制敌人的运动
	int i=0;
	if((int)(enemy_iframe*100)%2==0)//控制敌人运动的刷新频率
 	{
    	while(i<ENEMY_TOTE)//当敌人存在时
    	{
			if(myEnemy[i].turn!=0)//这敌人是个活人
			{
        		myEnemy[i].x+=myEnemy[i].turn*ENEMY_STEP;//敌人在动
				int x1=(int)myHero.x0+myEnemy[i].x;
				int y1=myEnemy[i].y;
    			int x2=(int)myHero.x0+myEnemy[i].x+myEnemy[i].turn*WIDTH;
    			int y2=myEnemy[i].y+1;				
    			if(touchMap(x1,y1,myScene)!=NULL||touchMap(x2,y2,myScene)==NULL)//如果敌人碰到墙壁或者没有踩在陆地上，则敌人向相反方向运动
    				myEnemy[i].turn*=-1;
			}
    		i++;
    	}
	}
	//以下代码判断主人公是否吃到金币，若吃到则把金币的坐标记下
	POINT *p=touchCoins(myHero.x,myHero.y,myScene);
	if(p!=NULL)
	{
		mciSendString("play music_coin from 0", NULL, 0, NULL);
		score+=10;
		myScene->setScorePos(p->x,p->y);
		p->x=0;
		p->y=0;
	}
	//以下代码判断主人公是否吃到食物，若吃到则把食物的坐标记下
	POINT *q=touchFood(myHero.x,myHero.y,myScene);
	if(q!=NULL)
	{
		mciSendString("play music_getWeapon from 0", NULL, 0, NULL);
		myScene->setScorePos(q->x,q->y);
		q->x=0;
		q->y=0;
		myHero.isShoot=true;
	}
	//以下代码判断主人公是否撞到敌人
	Enemy *emy=touchEnemy(myHero.x,myHero.y,myEnemy);
	if(emy!=NULL&&myHero.vY<=0)//如果主人公碰到但不踩到敌人
	{
		myHero.died=true;
		mciSendString("play music_died from 0", NULL, 0, NULL);
	}
}