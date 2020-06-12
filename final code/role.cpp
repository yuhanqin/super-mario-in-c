#include "role.h"
#include"graphics.h"
#include"mydefine.h"
#include"math.h"
#include"rule.h"
#pragma comment(lib,"Winmm.lib")   //����Ϸ�������Ҫ�õ���

extern int world;

role::role(int world)
{
	myHero.x=X0;//�������˹��ĳ�ʼλ��
	myHero.y=X0;
	myHero.xx=myHero.x;
	myHero.yy=myHero.y;
	myHero.x0=0;
	myHero.vX=0;
	myHero.vY=0;
	myHero.turn=1;//1Ϊ����-1Ϊ����
	myHero.direction.x=0;
	myHero.direction.y=0;
	myHero.isFly=true;//�ж������Ƿ��ڿ���
	myHero.isShoot=false;//�ж������Ƿ����
	myHero.died=false;//�Ƿ�����-1
	myHero.ending=false;//�Ƿ񼴽�ͨ��
	myHero.passed=false;//�Ƿ�ͨ��
	myHero.jump=0;//updated by qinyuhan at 10:00 3-11
	myHero.hiddentime=0;//updated by qinyuhan at 22:30 3-18
	myScene=0;
	hero_iframe=1;//���˹���ͼƬΪ��1֡
	enemy_iframe=1;//���˵�ͼƬΪ��1֡
	shootButtonDown=false;//�ر����˹��������
	shootTimeInterval=0;//�����ʱ������
	score=0;
	loadimage(&img_hero,"res\\role.bmp");//����ͼƬ
	loadimage(&img_enemy,"res\\ani.bmp");
	loadimage(&img_showBomb,"res\\ani.bmp");
	loadimage(&img_bullet,"res\\ani.bmp");
	for(int i=0;i<ENEMY_TOTE;i++)//��ʼ������
	{
		myEnemy[i].x=0;
		myEnemy[i].y=0;
		myEnemy[i].turn=0;
	}
	for(int j=0;j<BOMB_NUMBER;j++)//��ʼ���ӵ�
	{
		bombs[j].x=0;
	    bombs[j].y=0;
		bomb_iframe[j]=0;
	}
	for(int k=0;k<BULLET_NUMBER;k++)//��ʼ������
	{
		bullets[k].x=0;
		bullets[k].y=0;
		bullets[k].turn=0;
		bullet_iframe[k]=0;
	}
	createEnemy(world);//������world�ص���
	mciSendString("open res\\����1.mp3 alias music_died", NULL, 0, NULL);//�������ֱ���
	mciSendString("open res\\��.mp3 alias music_jump", NULL, 0, NULL);
	mciSendString("open res\\���.mp3 alias music_coin", NULL, 0, NULL);
	mciSendString("open res\\�ȵ���.mp3 alias music_tread", NULL, 0, NULL);
	mciSendString("open res\\�Ե�����.mp3 alias music_getWeapon", NULL, 0, NULL);
	mciSendString("open res\\�ӵ�.mp3 alias music_bullet", NULL, 0, NULL);
	mciSendString("open res\\�ӵ�ײǽ.mp3 alias music_boom", NULL, 0, NULL);
	mciSendString("open res\\�ӵ��򵽵���.mp3 alias music_boom2", NULL, 0, NULL);
	
}
role::~role(void)
{
}
void role::createEnemy(int world)//��������
{
	if(world==1)
	{
		Enemy emy[]={{3,8,1},{18,8,-1},{36,8,-1},{47,4,1},{47,8,1},{57,8,-1},{68,4,1},{66,8,-1},{79,8,1}};//��1λΪx���꣬��2λΪy���꣬��3λΪ�˶�����
		int i=0;
		while(i<=sizeof(emy)/sizeof(emy[0]))//ͨ������*��λ���ӿ��32�����ڵ�ͼ�л��ƶ�Ӧ�ĵ���
		{
			myEnemy[i].x=emy[i].x*WIDTH;
			myEnemy[i].y=emy[i].y*HEIGHT;
			myEnemy[i].turn=emy[i].turn;
			i++;
		}
	}
	else if(world==2)
	{
		Enemy emy[]={{17,4,1},{24,5,1},{28,7,-1},{32,12,1},{44,9,1},{56,7,1},{64,8,1},{77,6,1},{89,4,1}};//��1λΪx���꣬��2λΪy���꣬��3λΪ�˶�����
		int i=0;
		while(i<=sizeof(emy)/sizeof(emy[0]))//ͨ������*��λ���ӿ��32�����ڵ�ͼ�л��ƶ�Ӧ�ĵ���
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
		};//��1λΪx���꣬��2λΪy���꣬��3λΪ�˶����� ���Ǿ�����Ƶĵ����س�����ͼ
		int i=0;
		while(i<=sizeof(emy)/sizeof(emy[0]))//ͨ������*��λ���ӿ��32�����ڵ�ͼ�л��ƶ�Ӧ�ĵ���
		{
			myEnemy[i].x=emy[i].x*WIDTH;
			myEnemy[i].y=emy[i].y*HEIGHT;
			myEnemy[i].turn=emy[i].turn;
			i++;
		}
	}
}//updated by ������ 2018.3.15 20:55
void role::setBomb(int x,int y)//�����ӵ�����
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
void role::bullteFlying(Bullet *p,scene *myScene)//�ӵ��ڿ��з�
{
	if(p->x==0&&p->y==0)//���ӵ�Խ������Ч
		return;
	if(p->x>XSIZE||p->x<-WIDTH)//���ӵ�Խ������Ч��Խ�����Խ����Ļ��Χ��
	{
		p->x=0;
		p->y=0;
		p->turn=0;
		return;
	}
	Enemy *emy=touchEnemy(p->x,p->y,myEnemy);//���е���ָ��
	Map *map=touchMap(p->x,p->y,myScene);//����ǽָ��
	if(emy!=NULL||map!=NULL)//����ӵ��򵽵��˻���ǽ
	{
		if(emy!=NULL)
		{mciSendString("play music_boom2 from 0", NULL, 0, NULL);score+=5;}
		else
			mciSendString("play music_boom from 0", NULL, 0, NULL);
		
		//���±�ը�������
		int x,y;
		if(emy!=NULL)//���������
		{
			x=emy->x;//������Ľ���������¼����
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
		setBomb(x,y);//��ը
	}
	else
		p->x+=LEHGTH_INTERVAL_BULLET*p->turn;
}
bool role::isTouch(POINT *p1,POINT *p2)//�ж��Ƿ��нӴ�
{
	for(int i=0;i<4;i++)//������˹�4��������һ�������ڵ�ͼ�ڣ����ж�Ϊ�Ӵ�����ͼ
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
	//����˼·���ж����˹����ĸ������Ƿ�������һ���ڵ�ͼ�ڣ��У����ж�Ϊ���˹���ײ����ͼ
	int xmap=(int)myHero.x0;
	POINT r[4];//���˹�4����������꣨�����˹�СһȦ���˴����˹����۳�����ζ���һ��Բ������ǰ��������Ҫ����ĵ�������
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
		&&i<MAP_NUMBER)//��������ͼ������Ϊǰ13�ֵ�ͼ
	{
		POINT m[2];//��ͼ���ϽǶ�������½Ƕ��������

		m[0].x=myScene->getMap()[i].x*WIDTH;
		m[0].y=myScene->getMap()[i].y*HEIGHT;

		if(myScene->getMap()[i].id==10)//idΪ10�ĵ�ͼҪ��Щ
		{
			m[1].x=myScene->getMap()[i].x*WIDTH+myScene->getMap()[i].xAmount*2*WIDTH;
	        m[1].y=myScene->getMap()[i].y*HEIGHT+myScene->getMap()[i].yAmount*2*HEIGHT;
		}
		else
		{
			m[1].x=myScene->getMap()[i].x*WIDTH+myScene->getMap()[i].xAmount*WIDTH;
    	    m[1].y=myScene->getMap()[i].y*HEIGHT+myScene->getMap()[i].yAmount*HEIGHT;
		}
		if(isTouch(r,m))//������������ཻ������ײ
			return &(myScene->getMap()[i]);
		i++;
	}
	return NULL;
}
POINT *role::touchCoins(int x,int y,scene *myScene)
{
	//����˼·���ж����˹����ĸ������Ƿ�������һ����Ӳ���ڣ��У����ж�Ϊ���˹����Ե�Ӳ��
	int xmap=(int)myHero.x0;
	POINT r[4];//���˹�4����������꣨�����˹�СһȦ����ͬ��
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
		POINT m[2];//Ӳ�����ϽǶ�������½Ƕ��������

		m[0].x=myScene->getCoins()[i].x*WIDTH;
		m[0].y=myScene->getCoins()[i].y*HEIGHT;
		m[1].x=m[0].x+WIDTH;
    	m[1].y=m[0].y+HEIGHT;
		if(isTouch(r,m))//������������ཻ������ײ
			return &(myScene->getCoins()[i]);
		i++;
	}
	return NULL;
}
POINT *role::touchFood(int x,int y,scene *myScene)
{
	//����˼·���ж����˹����ĸ������Ƿ�������һ����ʳ���ڣ��У����ж�Ϊ���˹����Ե�ʳ��
	int xmap=(int)myHero.x0;
	POINT r[4];//���˹�4����������꣨�����˹�СһȦ����ͬ��
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
		POINT m[2];//ʳ�����ϽǶ�������½Ƕ��������

		m[0].x=myScene->getFood()[i].x;
		m[0].y=myScene->getFood()[i].y;
		m[1].x=m[0].x+3*WIDTH/2+4;
    	m[1].y=m[0].y+4*HEIGHT/5;
		if(isTouch(r,m))//������������ཻ������ײ
			return &(myScene->getFood()[i]);
		i++;
	}
	return NULL;
}
Enemy *role::touchEnemy(int x,int y,Enemy *emy)
{
	//����˼·���ж����˹����ĸ������Ƿ�������һ���ڵ�ͼ�ڣ��У����ж�Ϊ���˹���ײ������
	int xmap=(int)myHero.x0;
	POINT r[8];//�������˹���ͼ����Բ�Σ��ʽ����ĸ����䶨λ���˹���λ�ý�Ϊ����ȷ�����Բ��ð˱��θ�Բ��ʹ���ܸ��Ӿ�ȷ
	r[0].x=-xmap+x+10;r[0].y=y+1;
	r[1].x=-xmap+x+24;r[1].y=y+1;
	r[2].x=-xmap+x+1;r[2].y=y+10;
	r[3].x=-xmap+x+WIDTH-1;r[3].y=y+10;
	r[4].x=-xmap+x+1;r[4].y=y+24;
	r[5].x=-xmap+x+WIDTH-1;r[5].y=y+24;
	r[6].x=-xmap+x+10;r[6].y=y+HEIGHT-1;
	r[7].x=-xmap+x+24;r[7].y=y+HEIGHT-1;
	int i=0;
	while(i<ENEMY_TOTE)//�����ڵ��������ѭ��
	{
		if(emy[i].turn!=0)//ͬ���ж�
		{
    		POINT m[2];//�������ϽǶ�������½Ƕ��������

    	 	m[0].x=emy[i].x;
    		m[0].y=emy[i].y;
    		m[1].x=m[0].x+WIDTH;
    	    m[1].y=m[0].y+HEIGHT;
   	    	
			if(world==1)
			{
			if(isTouch(r,m))//������������ཻ������ײ
    		{
				return &emy[i];
	    	}
			}

				if(world==2)
			{
			if(isTouch(r,m))//������������ཻ������ײ
    		{
				return &emy[i];
	    	}
			}

					if(world==3)
			{
				if((GetAsyncKeyState('H')&0x8000)&&myHero.hiddentime<1000)//����H����������
				{
					myHero.hiddentime++;
				}
				else
				{

			if(isTouch(r,m))//������������ཻ������ײ
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
	//����������ڿ������˹���ת�������˸������
	//�ı����˹�����ͼƬ�ĵڼ�֡
	int rolePos=-(int)myHero.x0+myHero.x;//���˹���λ��
	if(rolePos/STEP%2==0&&rolePos/STEP%4!=0)
		hero_iframe=2;
	else if(rolePos/STEP%4==0)
		hero_iframe=1;
	//�������˹��ķ���
	if(myHero.direction.x==1)
		myHero.turn=1;
	else if(myHero.direction.x==-1)
		myHero.turn=-1;
	if(myHero.died==true)//������˹��ҵ���
	{
		putimage(myHero.x,myHero.y,WIDTH,HEIGHT,&img_hero,2*WIDTH,HEIGHT,SRCAND);//����ͼƬ����sleep��϶�����
		putimage(myHero.x,myHero.y,WIDTH,HEIGHT,&img_hero,2*WIDTH,0,SRCPAINT);
	}
	else//���û��
	{
		if(myHero.turn==1)//�������
		{
			putimage(myHero.x,myHero.y,WIDTH,HEIGHT,&img_hero,(hero_iframe-1)*WIDTH,HEIGHT,SRCAND);//������һ֡��ʹ���˹�������
   			putimage(myHero.x,myHero.y,WIDTH,HEIGHT,&img_hero,(hero_iframe-1)*WIDTH,0,SRCPAINT);

		}
		else
		{
			putimage(myHero.x,myHero.y,WIDTH,HEIGHT,&img_hero,(hero_iframe-1)*WIDTH+3*WIDTH,HEIGHT,SRCAND);
   			putimage(myHero.x,myHero.y,WIDTH,HEIGHT,&img_hero,(hero_iframe-1)*WIDTH+3*WIDTH,0,SRCPAINT);
		}
	}

	//�ı���˼���ͼƬ�ĵڼ�֡��ͬ�ϣ������ٹ���ע��
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
	//����������ڿ��Ʊ�ըЧ�������뷽ʽͬ��
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
	//����������ڿ����ӵ�����ʾ�����뷽ʽͬ��
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
	myHero.direction.x=0;//���˹���������ĳһ������
	myHero.direction.y=0;
    double a=0;//���˹��˶��ļ��ٶȺ�Ħ��������ļ��ٶ�
	double a1=0;
	Map *map=NULL;
	

	if(world==1)
 {
	
	if((KEY&CMD_UP)/*&&myHero.isFly==false*/&&myHero.jump<1&&myHero.ending==false)//ֻ�е����˹�û���ڿ��������˹�û���ص�ʱ������������
	{
		mciSendString("play music_jump from 0", NULL, 0, NULL);
		myHero.isFly=true;//���˹��ڿ���
		myHero.vY=-sqrt(2*G*REAL_HEIGHT);//��ʼ�ù�ʽ���ٶ�
		myHero.jump++;
	}	
	if(myHero.isFly==true)// updated by qinyuhan at 10:00 3-11
	{		
		myHero.yy=myHero.yy-(-rule::move(myHero.vY,TIME,G)*UNREAL_HEIGHT/REAL_HEIGHT);//move�������ص�λʱ�䣨T���ڣ����˹��������½��ĸ߶�
		myHero.y=(int)myHero.yy;
		map=touchMap(myHero.x,myHero.y+1,myScene);

		if((KEY&CMD_UP)/*&&myHero.isFly==false*/&&myHero.jump<9&&myHero.ending==false)//ֻ�е����˹�û���ڿ��������˹�û���ص�ʱ������������
	{
		mciSendString("play music_jump from 0", NULL, 0, NULL);
		myHero.isFly=true;//��ʾ���˹��ڿ���
		myHero.vY=-sqrt(2*G*REAL_HEIGHT);//��ʼ�ù�ʽ���ٶ�
		myHero.jump++;
		

		if(myHero.isFly==true)//������˹������Ϸ�
		myHero.yy=myHero.yy-(-rule::move(myHero.vY,TIME,G)*UNREAL_HEIGHT/REAL_HEIGHT);//move�������ص�λʱ�䣨T���ڣ����˹��������½��ĸ߶�
		myHero.y=(int)myHero.yy;
		map=touchMap(myHero.x,myHero.y+1,myScene);}


		if(map!=NULL)// updated by qinyuhan at 10:00 3-11
		{
			if(myHero.vY>0)//��ʾ�����˹��Ӵ�����ʱ
				{myHero.isFly=false;
			myHero.jump=0;}
			myHero.vY=0;
			myHero.y=(myHero.y+HEIGHT/2)/HEIGHT*HEIGHT;//�����ˡ�+HEIGHT/2������ʾ���˹�������
			myHero.yy=myHero.y;
		    myHero.direction.y+=1;
		
		}
		if(myHero.vY>0)
		{
			Enemy *emy=touchEnemy(myHero.x,myHero.y,myEnemy);
			if(emy!=NULL)//������˹���������
			{
				mciSendString("play music_tread from 0", NULL, 0, NULL);
				score+=5;//��Ǯ+5
				//���±�ը�������
				setBomb(emy->x,emy->y);
				emy->x=0;
	    		emy->y=0;
	    		emy->turn=0;
			}
			if(myHero.y>YSIZE)
			{
				myHero.died=true;//���˹�-1s
				mciSendString("play music_died from 0", NULL, 0, NULL);
			}
		}
	}
	else
	{
		map=touchMap(myHero.x,myHero.y+1,myScene);
		if(map==NULL)//������˹�û��������ͼ�����ڿ���
    	{
    		myHero.isFly=true;
    	}
	}
  }

	if(world==2)
 {
	
	if((KEY&CMD_UP)&&myHero.ending==false)//ֻ�е����˹�û���ڿ��������˹�û���ص�ʱ������������
	{
		mciSendString("play music_jump from 0", NULL, 0, NULL);
		myHero.isFly=true;//���˹��ڿ���
		myHero.vY=-sqrt(2*G*REAL_HEIGHT);//��ʼ�ù�ʽ���ٶ�
		myHero.jump++;
	}	
	if(myHero.isFly==true)// updated by qinyuhan at 10:00 3-11
	{		
		myHero.yy=myHero.yy-(-rule::move(myHero.vY,TIME,G)*UNREAL_HEIGHT/REAL_HEIGHT);//move�������ص�λʱ�䣨T���ڣ����˹��������½��ĸ߶�
		myHero.y=(int)myHero.yy;
		map=touchMap(myHero.x,myHero.y+1,myScene);

		if((KEY&CMD_UP)/*&&myHero.isFly==false*/&&myHero.jump<9&&myHero.ending==false)//ֻ�е����˹�û���ڿ��������˹�û���ص�ʱ������������
	{
		mciSendString("play music_jump from 0", NULL, 0, NULL);
		myHero.isFly=true;//��ʾ���˹��ڿ���
		myHero.vY=-sqrt(2*G*REAL_HEIGHT);//��ʼ�ù�ʽ���ٶ�
		myHero.jump++;
		

		if(myHero.isFly==true)//������˹������Ϸ�
		myHero.yy=myHero.yy-(-rule::move(myHero.vY,TIME,G)*UNREAL_HEIGHT/REAL_HEIGHT);//move�������ص�λʱ�䣨T���ڣ����˹��������½��ĸ߶�
		myHero.y=(int)myHero.yy;
		map=touchMap(myHero.x,myHero.y+1,myScene);}


		if(map!=NULL)// updated by qinyuhan at 10:00 3-11
		{
			if(myHero.vY>0)//��ʾ�����˹��Ӵ�����ʱ
				{myHero.isFly=false;
			myHero.jump=0;}
			myHero.vY=0;
			myHero.y=(myHero.y+HEIGHT/2)/HEIGHT*HEIGHT;//�����ˡ�+HEIGHT/2������ʾ���˹�������
			myHero.yy=myHero.y;
		    myHero.direction.y+=1;
		
		}
		if(myHero.vY>0)
		{
			Enemy *emy=touchEnemy(myHero.x,myHero.y,myEnemy);
			if(emy!=NULL)//������˹���������
			{
				mciSendString("play music_tread from 0", NULL, 0, NULL);
				score+=5;//��Ǯ+5
				//���±�ը�������
				setBomb(emy->x,emy->y);
				emy->x=0;
	    		emy->y=0;
	    		emy->turn=0;
			}
			if(myHero.y>YSIZE)
			{
				myHero.died=true;//���˹�-1s
				mciSendString("play music_died from 0", NULL, 0, NULL);
			}
		}
	}
	else
	{
		map=touchMap(myHero.x,myHero.y+1,myScene);
		if(map==NULL)//������˹�û��������ͼ�����ڿ���
    	{
    		myHero.isFly=true;
    	}
	}
  }


	if(world==3)
 {
	
	if((KEY&CMD_UP)/*&&myHero.isFly==false*/&&myHero.jump<2&&myHero.ending==false)//ֻ�е����˹�û���ڿ��������˹�û���ص�ʱ������������
	{
		mciSendString("play music_jump from 0", NULL, 0, NULL);
		myHero.isFly=true;//���˹��ڿ���
		myHero.vY=-sqrt(2*G*REAL_HEIGHT);//��ʼ�ù�ʽ���ٶ�
		myHero.jump++;
	}	
	if(myHero.isFly==true)// updated by qinyuhan at 10:00 3-11
	{		
		myHero.yy=myHero.yy-(-rule::move(myHero.vY,TIME,G)*UNREAL_HEIGHT/REAL_HEIGHT);//move�������ص�λʱ�䣨T���ڣ����˹��������½��ĸ߶�
		myHero.y=(int)myHero.yy;
		map=touchMap(myHero.x,myHero.y+1,myScene);

		if((KEY&CMD_UP)/*&&myHero.isFly==false*/&&myHero.jump<9&&myHero.ending==false)//ֻ�е����˹�û���ڿ��������˹�û���ص�ʱ������������
	{
		mciSendString("play music_jump from 0", NULL, 0, NULL);
		myHero.isFly=true;//��ʾ���˹��ڿ���
		myHero.vY=-sqrt(2*G*REAL_HEIGHT);//��ʼ�ù�ʽ���ٶ�
		myHero.jump++;
		

		if(myHero.isFly==true)//������˹������Ϸ�
		myHero.yy=myHero.yy-(-rule::move(myHero.vY,TIME,G)*UNREAL_HEIGHT/REAL_HEIGHT);//move�������ص�λʱ�䣨T���ڣ����˹��������½��ĸ߶�
		myHero.y=(int)myHero.yy;
		map=touchMap(myHero.x,myHero.y+1,myScene);}


		if(map!=NULL)// updated by qinyuhan at 10:00 3-11
		{
			if(myHero.vY>0)//��ʾ�����˹��Ӵ�����ʱ
				myHero.isFly=false;
			
			myHero.vY=0;
			myHero.jump=0;
			myHero.y=(myHero.y+HEIGHT/2)/HEIGHT*HEIGHT;//�����ˡ�+HEIGHT/2������ʾ���˹�������
			myHero.yy=myHero.y;
		    myHero.direction.y+=1;
		
		}
		if(myHero.vY>0)
		{
			Enemy *emy=touchEnemy(myHero.x,myHero.y,myEnemy);
			/*if(emy!=NULL)//������˹���������
			{
				mciSendString("play music_tread from 0", NULL, 0, NULL);
				score+=5;//��Ǯ+5
				//���±�ը�������
				setBomb(emy->x,emy->y);
				emy->x=0;
	    		emy->y=0;
	    		emy->turn=0;
			}*/
			if(myHero.y>YSIZE)
			{
				myHero.died=true;//���˹�-1s
				mciSendString("play music_died from 0", NULL, 0, NULL);
			}
		}
	}
	else
	{
		map=touchMap(myHero.x,myHero.y+1,myScene);
		if(map==NULL)//������˹�û��������ͼ�����ڿ���
    	{
    		myHero.isFly=true;
    	}
	}
  }



	if(KEY&CMD_DOWN)//��Ұ��¼���û��ʲô��
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
	//���´��봦�����˹�ˮƽ�����ϵ��˶�
	if(myHero.vX*a<=0&&myHero.vX!=0)
	{
		int k=-(int)(myHero.vX/abs(myHero.vX));//k������ٶȵķ���
		if(map==NULL)
			a1=0;
		else
			a1=k*G*map->u;//������ʽa=mg*u/g�ó�
	}
	double tmp=myHero.vX;
	double H=rule::move(myHero.vX,TIME,a+a1)*UNREAL_HEIGHT/REAL_HEIGHT;//��δ��뿴����������ͷ������ʵ���Ͼ�����߶�[̯��]
	if(tmp*myHero.vX<0)
		myHero.vX=0;
	myHero.xx=myHero.xx+H;
	myHero.x=(int)myHero.xx;
	if(myScene->isEnding(-(int)myHero.x0+myHero.x))//������˹����Ϲ������Զ������ƽ�
	{
		myHero.ending=true;
	}
	if(myHero.x>XSIZE)//������˹��Ѿ����������ұ߽����ѹ���
		myHero.passed=true;
	if(touchMap(myHero.x,myHero.y,myScene)!=NULL)
	{
		if(myHero.x>XRIGHT)//�������˹���λ�ò����ܹ�ͷ��
			myHero.x=XRIGHT;
		else
			myHero.x=(int)(myHero.xx-H);
		myHero.xx=myHero.x;
		myHero.vX=0;
	    a=0;
		a1=0;
	}
	if(abs(myHero.vX)>V_MAX)//�������˹����ٶȲ��ܴ��ͷ��
		myHero.vX=myHero.vX/abs(myHero.vX)*V_MAX;
	if(KEY&CMD_ESC)
	{
	}
	if(KEY&CMD_SHOOT&&myHero.isShoot==true)
	{
		//xΪ�ӵ��ĺ�����
		int x=myHero.x+WIDTH/2;
		if(myHero.turn==-1)
			x=myHero.x-WIDTH;

		//���´�������ӵ����˶�
		//��һֱ��ס�����ʱ���ӵ���һ��ʱ���ڲ��ܷ��䣻���߿�����ʱ�����ӵ�
		if(shootButtonDown==false)
		{
			mciSendString("play music_bullet from 0", NULL, 0, NULL);
			setBullet(x,myHero.y);
		}
		else
		{
			if(shootTimeInterval==0)//�������������Ϊ0

			{
				mciSendString("play music_bullet from 0", NULL, 0, NULL);
				setBullet(x,myHero.y);
			}
			shootTimeInterval+=TIME;//���ʱ�������Զ�ˢ��Ƶ����ƥ��
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
	//�жϳ����˹��Ƿ񳬳����ҽ���
    if(myHero.x<XLEFT)
	{
		myHero.x=XLEFT;//��������������
		myHero.xx=myHero.x;
		myHero.vX=0;
		a=0;
	}
   	else if(myHero.x>XRIGHT&&myHero.ending==false)//������˹����ҳ�����Ļ����������
	{
		myHero.x0-=(myHero.x-XRIGHT);
		myHero.x=XRIGHT;
		myHero.xx=myHero.x;
	}
	//���³�����Ƶ��˵��˶�
	int i=0;
	if((int)(enemy_iframe*100)%2==0)//���Ƶ����˶���ˢ��Ƶ��
 	{
    	while(i<ENEMY_TOTE)//�����˴���ʱ
    	{
			if(myEnemy[i].turn!=0)//������Ǹ�����
			{
        		myEnemy[i].x+=myEnemy[i].turn*ENEMY_STEP;//�����ڶ�
				int x1=(int)myHero.x0+myEnemy[i].x;
				int y1=myEnemy[i].y;
    			int x2=(int)myHero.x0+myEnemy[i].x+myEnemy[i].turn*WIDTH;
    			int y2=myEnemy[i].y+1;				
    			if(touchMap(x1,y1,myScene)!=NULL||touchMap(x2,y2,myScene)==NULL)//�����������ǽ�ڻ���û�в���½���ϣ���������෴�����˶�
    				myEnemy[i].turn*=-1;
			}
    		i++;
    	}
	}
	//���´����ж����˹��Ƿ�Ե���ң����Ե���ѽ�ҵ��������
	POINT *p=touchCoins(myHero.x,myHero.y,myScene);
	if(p!=NULL)
	{
		mciSendString("play music_coin from 0", NULL, 0, NULL);
		score+=10;
		myScene->setScorePos(p->x,p->y);
		p->x=0;
		p->y=0;
	}
	//���´����ж����˹��Ƿ�Ե�ʳ����Ե����ʳ����������
	POINT *q=touchFood(myHero.x,myHero.y,myScene);
	if(q!=NULL)
	{
		mciSendString("play music_getWeapon from 0", NULL, 0, NULL);
		myScene->setScorePos(q->x,q->y);
		q->x=0;
		q->y=0;
		myHero.isShoot=true;
	}
	//���´����ж����˹��Ƿ�ײ������
	Enemy *emy=touchEnemy(myHero.x,myHero.y,myEnemy);
	if(emy!=NULL&&myHero.vY<=0)//������˹����������ȵ�����
	{
		myHero.died=true;
		mciSendString("play music_died from 0", NULL, 0, NULL);
	}
}