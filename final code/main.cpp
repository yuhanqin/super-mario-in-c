/////////////////////////////////////////////////////////
// �������ƣ�Emoji Alliance
// ����ο�������Ģ��2 http://www.easyx.cn/samples/view.aspx?id=146
// Դ���д��ľ������ <www.baidu.com/p/taozi24>
// �����Ż���������(Team Leader) ������(Tech Leader) ������(CIO) ���ں� �ź��� ��Ȫ
// �޸�ʱ�䣺2018-2-28����
//
#include"graphics.h"
#include"conio.h"
#include"MyTimer.h"
#include"mydefine.h"
#include"control.h"
#include"role.h"
#include"scene.h"
#pragma comment(lib,"Winmm.lib")   //����Ϸ�������Ҫ�õ�


//ȫ�ֱ���
int life=LIFE;   //���˹���life������
int world=1;     //�����ǵ�world��

void main()
{
	initgraph(XSIZE,YSIZE);		//����ͷ�ļ����ڳ��򴰿ڴ�С�Ķ���

	control myCtrl;   //����һ����Ϸ����
	Hero myHero;	//�������˹�״̬
	role myRole(world);    //�����ɫ
	scene myScene(world);  //������Ϸ����

	myCtrl.gameStart();//��Ϸ�Ŀ�ʼ����

	//�����Ϸ����
	mciSendString("open res\\��������.mp3 alias music_bg", NULL, 0, NULL);
	mciSendString("open res\\ʤ��.mp3 alias music_win", NULL, 0, NULL);
	mciSendString("open res\\ͨ��.mp3 alias music_passedAll", NULL, 0, NULL);
	mciSendString("open res\\��Ϸ����.mp3 alias music_end",NULL,0,NULL);
	mciSendString("play music_bg repeat", NULL, 0, NULL);
	mciSendString("open res\\�̵�.mp3 alias music_shop", NULL, 0, NULL);
	
	MyTimer mytimer;//��ȷ�ӳ�
	while(true)
	{

		int key=myCtrl.getKey(); //��ȡ��Ұ��µļ�                              
		if(key==VIR_RESTART)     //�����Ϸ������ѡ���ˡ����¿�ʼ��
		{
			myScene=scene(world);mciSendString("play music_bg from 0", NULL, 0, NULL);//���²��ű������֣����Ʊ��س���������
			myRole=role(world);			
		}
		else if(key==VIR_HOME)   //�����Ϸ������ѡ���ˡ����˵���
		{
			mciSendString("stop music_bg", NULL, 0, NULL);//ͣ�Ͳ�����Ϸ����
			life=LIFE;//���������ص�5��
			world=1;//�ӵ�1�ؿ�ʼ
			myRole=role(world);//������world�س���
			myScene=scene(world);
			myCtrl.gameStart();
			mciSendString("play music_bg from 0", NULL, 0, NULL);
		}
		else if(key==VIR_SHOP)   //�����Ϸ������ѡ���ˡ��̵ꡱ********************************************** uodated by liangjunzhao at around 20:00 3-9
		{
			
		}

		myRole.action(key,&myScene);  

		myScene.action(&myRole);  

		if(myRole.isDied())     //������˹�����
		{
			mciSendString("stop music_bg", NULL, 0, NULL);//ֹͣ���֣������������
			BeginBatchDraw();
			myScene.show();
			myRole.show();
			myCtrl.showScore(myRole.getScore());
			myCtrl.showLevel(world);
			EndBatchDraw();

			mytimer.Sleep(1000); //updated by liangjunzhao at around 20:00 3-9
			life--;//����-1
			if(life==0)//��������Ϸ����
			{
				mciSendString("play music_end from 0",NULL,0,NULL);//������Ϸ��������
				myCtrl.showGameOver();//����Ϊ��Ϸ����
				life=LIFE;//�ص����˵���������������������
				world=1;
				myCtrl.gameStart();
				myRole=role(world);//���ƶ�Ӧ����
				myScene=scene(world);				
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
			else//�������-1
			{
				myCtrl.showDied(life);
				myRole=role(world);//�ӵ�ǰ�ؿ����¿�ʼ
				myScene=scene(world);		
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
		}
		if(myRole.isPassed())   //������˹����� updated by liangjunzhao at 16:00 3-10
		{
			if(world==1||world==2)//��û��ͨ�أ�������̵�
			{
				loadimage(NULL, "res\\����.jpg");//�������ͼƬ
				rectangle(295,36,440,131);//������Ʒ��������ľ���
				rectangle(90,36,220,131);
				rectangle(XSIZE-45,YSIZE-30,XSIZE-2,YSIZE-2);
				outtextxy(XSIZE-45,YSIZE-25,"����");
				int point=myRole.getScore();//��role.h���õ÷��ļ�
				int ljz=1;//��������Ա㿪ʼѭ��
				k:
					MOUSEMSG m=GetMouseMsg();
					while(ljz!=0)
						{
						switch(m.uMsg)
						{
						case WM_LBUTTONDOWN:
							if(m.x>90&&m.y>36&&m.x<220&&m.y<131)//�����ӵ�
							{
							if(point>=100)//����Ǯ�㹻
							{
							point-=100;
							myHero.isShoot=true;//�����������
							goto k;//goto���Ǹ��ö�����������лл�����������ϴ��Ĵ����ñ��δ���������������������ָ�л��������
							}
							else 
							{
							outtextxy(55,150,"You do not have");
							outtextxy(55,180,"enough money!");
							goto k;//goto���Ǹ��ö�����������лл�����������ϴ��Ĵ����ñ��δ���������������������ָ�л��������
							}
							}
							if(m.x>295&&m.y>36&&m.x<440&&m.y<131)
							{
							if(point>=200)//����Ǯ�㹻
							{
							point-=200;
							life++;
							goto k;//goto���Ǹ��ö�����������лл�����������ϴ��Ĵ����ñ��δ���������������������ָ�л��������
							}
							else
							{
							outtextxy(300,150,"You do not have");
							outtextxy(300,180,"enough money!");
							goto k;//goto���Ǹ��ö�����������лл�����������ϴ��Ĵ����ñ��δ���������������������ָ�л��������
							}
							}
							else if(m.x>XSIZE-45&&m.y>YSIZE-30)//����갴��ָ����ť�����˳��̵꣬������һ�� uodated by  liangjunzhao at 18:30 3-10
							{//���ذ�ťλ����Ļ���½�
							cleardevice();
							world++;//����+1����ʾͨ��������������һ�س���
							myCtrl.showPassed(world);
							myRole=role(world);
							myScene=scene(world);
							mciSendString("stop music_bg", NULL, 0, NULL);
							break;//ֻ�а��·��ذ�ť��������whileѭ��
							}
							default: goto k;//goto���Ǹ��ö�����������лл�����������ϴ��Ĵ��룡������
							}
							ljz=0;
						}
			}
			
			else if(world==3)//������˹�ͨ��
			{
				mciSendString("play music_win from 0", NULL, 0, NULL);//��Ӯ��/б��Ц
				mytimer.Sleep(1000); // updated by liangjunzhao at 16:00 3-10
			    mciSendString("play music_passedAll from 0",NULL,0,NULL);//����ͨ������
				myCtrl.showPassedAll();
				life=LIFE;//������Ϸ
				world=1;
				myRole=role(world);
				myScene=scene(world);
				myCtrl.gameStart();
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
		}
		
		BeginBatchDraw();
		myScene.show();
		myRole.show();
		myCtrl.showScore(myRole.getScore());
		myCtrl.showLevel(world);
		EndBatchDraw();

		mytimer.Sleep((int)(TIME*1000));
	}
	mciSendString("clase all",NULL,0,NULL);//�ر����������ļ�
	closegraph();
}
