#include "scene.h"
#include"graphics.h"
#include"math.h"
#include"role.h"
#include"mydefine.h"

scene::scene(int world)
{
	loadimage(&img_bg,"res\\mapsky.bmp",XSIZE,4*YSIZE);//载入图片
	loadimage(&img_map,"res\\map.bmp");//载入图片
	loadimage(&img_scenery,"res\\scenery.bmp");//载入图片
	loadimage(&img_coin,"res\\ani.bmp");//载入图片
	loadimage(&img_food,"res\\ani.bmp");//载入图片
	xBg=0;//初始化各项地图参数，是块的就定义为0，是图的就定义为第1帧
	yBg=0;
	xMap=0;
	yMap=0;
	scenery_iframe=1;//初始化各项地图参数，是块的就定义为0，是图的就定义为第1帧
	coin_iframe=1;
	food_iframe=1;
	for(int i=0;i<MAP_NUMBER;i++)//初始化各项地图参数，是块的就定义为0，是图的就定义为第1帧
	{
		map[i].x=0;
		map[i].y=0;
		map[i].id=0;
		map[i].u=0;
		map[i].xAmount=0;
		map[i].yAmount=0;
	}
	for(int j=0;j<COINS_NUMBER;j++)//初始化各项地图参数，是块的就定义为0，是图的就定义为第1帧
	{
		coins[j].x=0;
		coins[j].y=0;
	}
	for(int k=0;k<SCORE_NUMBER;k++)//初始化各项地图参数，是块的就定义为0，是图的就定义为第1帧
	{
		score[k].x=0;
		score[k].y=0;
		score_iframe[k]=0;
	}
	for(int l=0;l<FOOD_NUMBER;l++)//初始化各项地图参数，是块的就定义为0，是图的就定义为第1帧
	{
		food[l].x=0;
		food[l].y=0;
	}
	this->world=world;
	createCoin();
	createFood();	
	createMap(world);
}
scene::~scene(void)
{
}
bool scene::isEnding(int distance)
{
	switch(world)//设置每关地图的长度，第三关终极300块
	{
	case 1:
		if(distance>100*WIDTH)
			return true;
		return false;
	case 2:
		if(distance>104*WIDTH)
			return true;
		return false;
	case 3:
		if(distance>300*WIDTH)
			return true;
		return false;
	}
	return false;
}
void scene::createMap(int world)
{
	if(world==1)
	{
		//编辑地图，第一位坐标表示横坐标，第二位5坐标表示纵坐标，第三位坐标表示地块类型，第四位坐标表示横向延伸距离，第五位表示纵向扩张距离 左上起为00
		// 第三位 1表示黄色地块，2表示灰色石块 10是绿色柱子1即横向三格 11是棕色的草高两格 12是WIN,13是水且1延伸三格   张子晗 2018.3.11 15；45
		Map m[]={{0,9,1,10,3},{13,9,1,26,3},{42,9,1,7,3},{52,9,1,6,3},{60,8,1,1,5},{63,9,1,8,3},{74,9,1,8,3},{95,9,1,19,3},
		         {4,6,2,3,1},{8,5,2,3,1},{19,6,2,4,1},{20,5,2,3,1},{21,4,2,2,1},{22,3,2,1,1},{25,3,2,1,1},{25,4,2,2,1},{25,5,2,3,1},{25,6,2,4,1},
				 {36,5,2,3,1},{42,8,2,3,1},{42,7,2,2,1},{42,6,2,1,1},{46,5,2,3,1},{50,10,2,1,1},{54,6,2,3,1},{67,5,2,3,1},{84,7,2,1,1},{86,6,2,1,1},{88,5,2,1,1},
				 {90,3,2,1,1},{92,5,2,1,1},{94,7,12,1,1},
		         {15,7,10,1,1},{33,7,10,1,1},{64,7,10,1,1},{76,7,10,1,1},
		         {10,10,13,1,1},{39,10,13,1,1},{49,11,13,1,1},{71,10,13,1,1},{82,10,13,11,1}
				};
		int i=0;
		while(m[i].id>0&&m[i].id<15&&i<MAP_NUMBER)//???存在问题
		{
			switch(m[i].id)
			{
			case 1:
			case 3:
			case 4:
			case 5:
			case 6:
				m[i].u=(V_MAX/T1)/G;//每一关对应的摩擦系数降速的效果均不同
				break;
			case 2:
				m[i].u=(V_MAX/T2)/G;
				break;
			default:
				m[i].u=(V_MAX/T3)/G;
				break;
			}
			map[i]=m[i];
			i++;
		}
	}
	else if(world==2)
	{
		//编辑地图
		Map m[]={/*{18,9,2,4,1},{23,6,2,6,1},{25,3,2,3,1},{31,10,2,2,1},{39,7,2,1,1},{39,4,2,1,1},{96,7,2,2,1},{99,5,2,2,1},{102,3,2,12,1},
				 {0,10,4,15,2},{38,10,4,10,2},{50,10,4,1,2},{53,10,4,1,2},{56,10,4,1,2},{61,10,4,10,2},{75,10,4,3,2},{82,10,4,11,2},
				 {67,9,8,1,1},{68,8,8,1,2},{69,7,8,1,3},{70,6,8,1,4},{75,6,8,1,4,},{76,7,8,1,3},{77,8,8,1,2},
				 {42,8,11,1,1},
				 {111,1,12,1,1},
			     {4,8,14,1,1},{9,8,14,1,1},{83,8,14,1,1},{89,8,14,1,1},*///此处为草稿，楼下为新地图
			
			
				{ 0, 11, 1, 200, 1 }, { 0, 0, 1, 200, 1 },
				{ 15, 1, 2, 1, 4 }, { 14, 10, 2, 1, 1 },
				{ 20, 1, 2, 1, 2 }, { 19, 8, 2, 1, 3 },
				{ 23, 1, 2, 1, 3 }, { 23, 9, 2, 2, 2 },
				{ 27, 1, 2, 1, 3 }, { 28, 10, 2, 1, 1 },
				{ 29, 1, 2, 1, 4 }, { 29, 10, 2, 1, 0 },
				{ 32, 1, 2, 2, 2 }, { 32, 10, 2, 1, 1 },
				{ 34, 1, 2, 1, 0 }, { 35, 10, 2, 1, 1 },
				{ 37, 1, 1, 1, 5 }, { 40, 8, 2, 1, 3 },//
				{ 41, 1, 2, 1, 3 }, { 42, 10, 2, 1, 0 },
				{ 44, 1, 2, 1, 6 }, { 45, 10, 2, 1, 1 },
				{ 48, 1, 2, 2, 4 }, { 49, 9, 2, 1, 2 },
				{ 51, 1, 2, 1, 5 }, { 54, 8, 2, 1, 3 },
				{ 54, 1, 2, 1, 3 },
				{ 58, 1, 1, 2, 3 }, { 59, 9, 2, 1, 2 },//
				{ 61, 1, 2, 1, 0 }, { 62, 7, 2, 1, 4 },
				{ 65, 1, 2, 1, 5 }, { 66, 10, 2, 2, 1 },
				{ 69, 1, 2, 1, 6 }, { 67, 10, 2, 1, 1 },
				{ 72, 1, 2, 1, 3 }, { 72, 9, 2, 1, 2 },
				{ 74, 1, 2, 1, 4 }, { 76, 10, 2, 1, 2 },
				{ 79, 1, 2, 1, 3 }, { 81, 7, 2, 1, 4 },
				{ 84, 1, 2, 1, 5 }, { 83, 11, 2, 1, 0 },
				{ 86, 1, 2, 1, 3 }, { 86, 10, 2, 1, 1 },
				{ 89, 1, 2, 1, 2 }, { 89, 8, 2, 1, 3 },
				{ 91, 1, 2, 1, 2 }, { 91, 1, 1, 1, 2 }, //
				{ 93, 1, 2, 1, 0 }, { 93, 6, 2, 1, 5 },
				{ 96, 1, 2, 1, 3 }, { 96, 10, 2, 1, 0 },



				/*{X + 5, 1, 2, 1, Y}, {X+5,7+Y,2,1,4-Y}*/
			};

				
		int i=0;
		while(m[i].id>0&&m[i].id<15&&i<MAP_NUMBER)//???存在问题
		{
			switch(m[i].id)
			{
			case 1:
			case 3:
			case 4:
			case 5:
			case 6:
				m[i].u=(V_MAX/T1)/G;
				break;
			case 2:
				m[i].u=(V_MAX/T2)/G;
				break;
			default:
				m[i].u=(V_MAX/T3)/G;
				break;
			}
			map[i]=m[i];
			i++;
		}
	}
	else if(world==3)
	{
		//编辑地图
		Map m[] = { 
		{0,0,2,310,1},{24,5,2,4,1},{9,6,2,3,4},{19,6,2,3,4},{30,6,2,3,4},{14,6,2,3,1},{0,10,2,43,2},{47,2,2,3,1},{66,2,2,4,2},{98,2,2,8,1},{57,7,2,3,3},{62,5,2,3,5},{78,8,2,7,2},{79,7,2,6,1},{80,6,2,5,1},{81,5,2,4,1},{82,4,2,3,1},{86,4,2,2,2},{90,4,2,7,1},{99,5,2,1,1},{109,11,2,38,1},{112,5,2,5,1},{118,5,2,5,1},{117,8,2,2,3},{120,7,2,1,4},{125,3,2,5,1},{125,5,2,5,1},{125,7,2,5,4},{132,5,2,6,1},{133,4,2,5,1},{134,3,2,4,1},{135,2,2,3,1},{141,2,2,3,1},{141,3,2,4,1},{141,4,2,5,1},{141,5,2,6,1},{154,8,2,7,1},{162,5,2,7,7},{166,3,2,7,1},{175,2,2,7,1},{183,10,2,13,2},{188,5,2,3,5},{195,7,2,4,1},{200,2,2,9,1},{207,6,2,6,1},{215,10,2,20,2},{216,8,2,1,1},{218,6,2,3,4},{221,2,2,8,1},{229,6,2,6,1},{238,10,2,1,1},{240,8,2,1,1},{242,6,2,1,1},{244,4,2,1,1},{246,1,2,10,1},{256,5,2,7,1},{265,10,2,19,2},{266,7,2,1,1},{268,5,2,1,1},{270,2,2,6,1},{276,7,2,3,3},{281,7,2,3,3},{283,2,2,9,1},{283,4,2,9,1},{293,9,2,1,1},{295,7,2,1,1},{298,5,2,12,1},{57,10,2,40,2},{28,2,2,14,2},{90,2,2,7,1},{288,6,2,4,2}};
		int i=0;
		while(m[i].id>0&&m[i].id<15&&i<MAP_NUMBER)//???存在问题
		{
			switch(m[i].id)
			{
			case 1:
			case 3:
			case 4:
			case 5:
			case 6:
				m[i].u=(V_MAX/T1)/G;
				break;
			case 2:
				m[i].u=(V_MAX/T2)/G;
				break;
			default:
				m[i].u=(V_MAX/T3)/G;
				break;
			}
			map[i]=m[i];
			i++;
		}
	}
}
void scene::createCoin()//创建金币，在此不做过多注释
{
	if(world==1)
	{
		POINT p[]={{8,4},{9,4},{10,4},{36,4},{37,4},{38,4},{40,2},{60,7},{54,5},{55,5},
		{56,5},{67,4},{68,4},{69,4},{98,8},{99,8},{100,8},{101,8},{102,8},{103,8}};//updated by 张子晗 2018.3.11.17:30
		int i=0;
		while(i<=sizeof(p)/sizeof(p[0]))
		{
			coins[i].x=p[i].x;
			coins[i].y=p[i].y;
			i++;
		}
	}
	else if(world==2)
	{
		POINT p[]={{16,7},{17,6},{18,7},{32,4},{32,5},{32,6},{32,7},
		           {32,8},{43,5},{50,6},{53,6},{56,6},{61,4},{62,3},{63,4},{64,7},
		           {65,8},{66,9},{75,6},{76,7},{83,7},{84,8},{85,9},
		};//updated by 张子晗 2018.3.15.18:49
		int i=0;
		while(i<=sizeof(p)/sizeof(p[0]))
		{
			coins[i].x=p[i].x;
			coins[i].y=p[i].y;
			i++;
		}
	}
	else if(world==3)
	{
		POINT p[]={{9,5},{10,5},{11,5},{13,1},{14,1},{15,1},{16,1},{17,1},{18,1},{19,1},{20,1},{21,1},{22,1},{23,1},{24,1},{25,1},{26,1},{27,1},{36,9},{36,8},{36,7},{36,6},{38,9},{38,8},{38,7},{38,6},{40,9},{40,8},{40,7},{40,6},{57,6},{58,6},{59,6},{62,4},{63,4},{64,4},{65,9},{66,9},{67,9},{68,9},{69,9},{70,9},{71,9},{72,9},{73,9},{74,9},{75,9},{76,9},{77,9},{78,7},{79,6},{80,5},{81,4},{90,5},{91,5},{92,5},{93,5},{94,5},{95,5},{96,5},{112,6},{113,6},{114,6},{115,6},{116,6},{138,4},{138,5},{138,6},{138,7},{138,8},{138,9},{139,4},{139,5},{139,6},{139,7},{139,8},{139,9},{140,4},{140,5},{140,6},{140,7},{140,8},{140,9},{166,2},{167,2},{168,2},{169,2},{170,2},{171,2},{172,2},{188,4},{189,4},{190,4},{200,3},{201,3},{202,3},{203,3},{204,3},{205,3},{206,3},{207,3},{208,3},{221,3},{222,3},{223,3},{224,3},{225,3},{226,3},{227,3},{228,3},{246,2},{247,3},{248,2},{249,3},{250,2},{251,3},{252,2},{253,3},{254,2},{255,3},{266,3},{266,4},{266,5},{266,6},{268,1},{268,2},{268,3},{268,4}
				  };
		int i=0;
		while(i<=sizeof(p)/sizeof(p[0]))
		{
			coins[i].x=p[i].x;
			coins[i].y=p[i].y;
			i++;
		}
	}
}
void scene::createFood()//创建食物，不做注释
{
	if(world==1)
	{
		POINT p[]={{36*WIDTH,8*HEIGHT+HEIGHT/5}};
		int i=0;
		while(i<=sizeof(p)/sizeof(p[0]))
		{
			food[i].x=p[i].x;
			food[i].y=p[i].y;
			i++;
		}
	}
	else if(world==2)
	{
		POINT p[]={{39*WIDTH-WIDTH/3,3*HEIGHT+HEIGHT/5}};
		int i=0;
		while(i<=sizeof(p)/sizeof(p[0]))
		{
			food[i].x=p[i].x;
			food[i].y=p[i].y;
			i++;
		}
	}
/*	else if(world==3)
	{
		POINT p[]={{41*WIDTH,5*HEIGHT+HEIGHT/5}};
		int i=0;
		while(i<=sizeof(p)/sizeof(p[0]))
		{
			food[i].x=p[i].x;
			food[i].y=p[i].y;
			i++;
		}
	}*/
}
void scene::setScorePos(int x,int y)
{
	for(int i=0;i<SCORE_NUMBER;i++)
	{
		if(score[i].x==0&&score[i].y==0)
		{
			score[i].x=x;
			score[i].y=y;
			score_iframe[i]=1;
			break;
		}
	}
}
void scene::setFood(int x,int y)
{
	for(int i=0;i<FOOD_NUMBER;i++)
	{
		if(food[i].x==0&&food[i].y==0)
		{
			food[i].x=x;
			food[i].y=y;
			break;
		}
	}
}
void scene::action(role *myRole)
{
	//由主人公的坐标改变背景和地图的坐标，使主人公有向前运动的感觉
	int xmap=xMap;
	xMap=(int)(myRole->getHero())->x0;//获取role里面的原点坐标;
	double bgStep=abs((myRole->getHero())->vX)*TIME*UNREAL_HEIGHT/REAL_HEIGHT/K_MAP_BG;
	if((myRole->getHero())->x==XRIGHT&&(myRole->getHero())->vX>0&&xmap!=xMap)//如果主人公已经到达右边界限且正在向右运动
		xBg-=bgStep;//背景向后移动
}
void scene::show()
{
	//控制背景移动
	if(xBg<=-img_bg.getwidth())
    		xBg=0;
	yBg=-(world-1)*YSIZE;
	putimage((int)xBg,(int)yBg,&img_bg);
    putimage(img_bg.getwidth()+(int)xBg,(int)yBg,&img_bg);
	//控制地图移动
	int i=0;
	while(map[i].id>0&&i<MAP_NUMBER)//map[i]中有数据才参与运算
	{
		for(int j=0;j<map[i].xAmount;j++)
			for(int k=0;k<map[i].yAmount;k++)
	     	{
	    		int x=xMap+map[i].x*WIDTH+j*WIDTH;
	    		int y=yMap+map[i].y*HEIGHT+k*HEIGHT;
	    		int x0=0;
	    		int y0=(map[i].id-1)*HEIGHT;
				if(map[i].id>9)//如果地图标号大于9则可能出现一块占多块的情况
				{
					if(map[i].id==10)
						putimage(x,y,2*WIDTH,2*HEIGHT,&img_map,x0,y0);
					else
					{
						y0=(map[i].id-11)*4*HEIGHT;
						putimage(x,y,3*WIDTH,2*HEIGHT,&img_scenery,((int)scenery_iframe-1)*3*WIDTH,y0+2*HEIGHT,SRCAND);
						putimage(x,y,3*WIDTH,2*HEIGHT,&img_scenery,((int)scenery_iframe-1)*3*WIDTH,y0,SRCPAINT);
						scenery_iframe+=F;
						if(scenery_iframe>=3)
							scenery_iframe=1;
					}
				}
				else
					putimage(x,y,WIDTH,HEIGHT,&img_map,x0,y0);
	    	}
	    i++;
	}
	//控制硬币
	coin_iframe+=TIME*7;
	if((int)coin_iframe==5)
		coin_iframe=1;
	int j=0;
	while(j<COINS_NUMBER)//硬币随着地图一块向前运动
	{
		if(coins[j].x!=0)
		{
	     	int x=coins[j].x*WIDTH;
    		int y=coins[j].y*HEIGHT;
    		putimage(xMap+x,y,WIDTH,HEIGHT,&img_coin,((int)coin_iframe-1)*WIDTH,9*HEIGHT,SRCAND);
    		putimage(xMap+x,y,WIDTH,HEIGHT,&img_coin,((int)coin_iframe-1)*WIDTH,8*HEIGHT,SRCPAINT);
		}
		j++;
	}
	//下面代码用于控制吃到硬币的效果
	for(int k=0;k<SCORE_NUMBER;k++)
	{
		if(score[k].x!=0&&score[k].y!=0)
		{
			score_iframe[k]+=TIME*8;
			if((int)score_iframe[k]==5)
			{
				score_iframe[k]=1;
				score[k].x=0;
				score[k].y=0;
			}
			else
			{
				int x=(int)xMap+score[k].x*WIDTH;
				int y=score[k].y*HEIGHT;
	    		putimage(x,y,WIDTH,HEIGHT,&img_coin,((int)score_iframe[k]-1)*WIDTH,11*HEIGHT,SRCAND);
             	putimage(x,y,WIDTH,HEIGHT,&img_coin,((int)score_iframe[k]-1)*WIDTH,10*HEIGHT,SRCPAINT);
			}
		}
	}
	//控制食物
	food_iframe+=TIME*7;
	if((int)food_iframe==3)
		food_iframe=1;
	int l=0;
	while(l<FOOD_NUMBER)
	{
		if(food[l].x!=0)
		{
	     	int x=food[l].x;
    		int y=food[l].y;
			putimage(xMap+x,y,3*WIDTH/2+4,HEIGHT*4/5,&img_food,((int)food_iframe-1)*(3*WIDTH/2+4),12*HEIGHT+HEIGHT*4/5,SRCAND);
			putimage(xMap+x,y,3*WIDTH/2+4,HEIGHT*4/5,&img_food,((int)food_iframe-1)*(3*WIDTH/2+4),12*HEIGHT,SRCPAINT);
		}
		l++;
	}
}