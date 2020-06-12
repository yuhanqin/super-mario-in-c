/////////////////////////////////////////////////////////
// 程序名称：Emoji Alliance
// 程序参考：超级蘑菇2 http://www.easyx.cn/samples/view.aspx?id=146
// 源码编写：木子念念 <www.baidu.com/p/taozi24>
// 升级优化：吕金秋(Team Leader) 梁君肇(Tech Leader) 张子晗(CIO) 秦钰涵 张鹤曦 刘泉
// 修改时间：2018-2-28至今
//
#include"graphics.h"
#include"conio.h"
#include"MyTimer.h"
#include"mydefine.h"
#include"control.h"
#include"role.h"
#include"scene.h"
#pragma comment(lib,"Winmm.lib")   //给游戏添加音乐要用到


//全局变量
int life=LIFE;   //主人公有life条生命
int world=1;     //现在是第world关

void main()
{
	initgraph(XSIZE,YSIZE);		//引用头文件对于程序窗口大小的定义

	control myCtrl;   //定义一个游戏控制
	Hero myHero;	//定义主人公状态
	role myRole(world);    //定义角色
	scene myScene(world);  //定义游戏场景

	myCtrl.gameStart();//游戏的开始界面

	//添加游戏音乐
	mciSendString("open res\\背景音乐.mp3 alias music_bg", NULL, 0, NULL);
	mciSendString("open res\\胜利.mp3 alias music_win", NULL, 0, NULL);
	mciSendString("open res\\通关.mp3 alias music_passedAll", NULL, 0, NULL);
	mciSendString("open res\\游戏结束.mp3 alias music_end",NULL,0,NULL);
	mciSendString("play music_bg repeat", NULL, 0, NULL);
	mciSendString("open res\\商店.mp3 alias music_shop", NULL, 0, NULL);
	
	MyTimer mytimer;//精确延迟
	while(true)
	{

		int key=myCtrl.getKey(); //获取玩家按下的键                              
		if(key==VIR_RESTART)     //如果游戏过程中选择了“重新开始”
		{
			myScene=scene(world);mciSendString("play music_bg from 0", NULL, 0, NULL);//重新播放背景音乐，绘制本关场景与人物
			myRole=role(world);			
		}
		else if(key==VIR_HOME)   //如果游戏过程中选择了“主菜单”
		{
			mciSendString("stop music_bg", NULL, 0, NULL);//停滞播放游戏音乐
			life=LIFE;//生命数量回到5条
			world=1;//从第1关开始
			myRole=role(world);//创建第world关场景
			myScene=scene(world);
			myCtrl.gameStart();
			mciSendString("play music_bg from 0", NULL, 0, NULL);
		}
		else if(key==VIR_SHOP)   //如果游戏过程中选择了“商店”********************************************** uodated by liangjunzhao at around 20:00 3-9
		{
			
		}

		myRole.action(key,&myScene);  

		myScene.action(&myRole);  

		if(myRole.isDied())     //如果主人公死亡
		{
			mciSendString("stop music_bg", NULL, 0, NULL);//停止音乐，定格各项数据
			BeginBatchDraw();
			myScene.show();
			myRole.show();
			myCtrl.showScore(myRole.getScore());
			myCtrl.showLevel(world);
			EndBatchDraw();

			mytimer.Sleep(1000); //updated by liangjunzhao at around 20:00 3-9
			life--;//生命-1
			if(life==0)//如果玩家游戏结束
			{
				mciSendString("play music_end from 0",NULL,0,NULL);//播放游戏结束音乐
				myCtrl.showGameOver();//控制为游戏结束
				life=LIFE;//回到主菜单，重置生命数量、关数
				world=1;
				myCtrl.gameStart();
				myRole=role(world);//绘制对应场景
				myScene=scene(world);				
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
			else//玩家生命-1
			{
				myCtrl.showDied(life);
				myRole=role(world);//从当前关卡重新开始
				myScene=scene(world);		
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
		}
		if(myRole.isPassed())   //如果主人公过关 updated by liangjunzhao at 16:00 3-10
		{
			if(world==1||world==2)//若没能通关，则进入商店
			{
				loadimage(NULL, "res\\货架.jpg");//载入货架图片
				rectangle(295,36,440,131);//绘制商品所在区域的矩形
				rectangle(90,36,220,131);
				rectangle(XSIZE-45,YSIZE-30,XSIZE-2,YSIZE-2);
				outtextxy(XSIZE-45,YSIZE-25,"返回");
				int point=myRole.getScore();//从role.h调用得分文件
				int ljz=1;//定义变量以便开始循环
				k:
					MOUSEMSG m=GetMouseMsg();
					while(ljz!=0)
						{
						switch(m.uMsg)
						{
						case WM_LBUTTONDOWN:
							if(m.x>90&&m.y>36&&m.x<220&&m.y<131)//购买子弹
							{
							if(point>=100)//若金钱足够
							{
							point-=100;
							myHero.isShoot=true;//开启射击功能
							goto k;//goto真是个好东西！！！！谢谢嘉轩大佬组上传的代码让本段代码起死回生！！！！万分感谢！！！！
							}
							else 
							{
							outtextxy(55,150,"You do not have");
							outtextxy(55,180,"enough money!");
							goto k;//goto真是个好东西！！！！谢谢嘉轩大佬组上传的代码让本段代码起死回生！！！！万分感谢！！！！
							}
							}
							if(m.x>295&&m.y>36&&m.x<440&&m.y<131)
							{
							if(point>=200)//若金钱足够
							{
							point-=200;
							life++;
							goto k;//goto真是个好东西！！！！谢谢嘉轩大佬组上传的代码让本段代码起死回生！！！！万分感谢！！！！
							}
							else
							{
							outtextxy(300,150,"You do not have");
							outtextxy(300,180,"enough money!");
							goto k;//goto真是个好东西！！！！谢谢嘉轩大佬组上传的代码让本段代码起死回生！！！！万分感谢！！！！
							}
							}
							else if(m.x>XSIZE-45&&m.y>YSIZE-30)//若鼠标按下指定按钮，则退出商店，进入下一关 uodated by  liangjunzhao at 18:30 3-10
							{//返回按钮位于屏幕右下角
							cleardevice();
							world++;//关数+1，显示通过动画，进入下一关场景
							myCtrl.showPassed(world);
							myRole=role(world);
							myScene=scene(world);
							mciSendString("stop music_bg", NULL, 0, NULL);
							break;//只有按下返回按钮才能跳出while循环
							}
							default: goto k;//goto真是个好东西！！！！谢谢嘉轩大佬组上传的代码！！！！
							}
							ljz=0;
						}
			}
			
			else if(world==3)//如果主人公通关
			{
				mciSendString("play music_win from 0", NULL, 0, NULL);//你赢了/斜眼笑
				mytimer.Sleep(1000); // updated by liangjunzhao at 16:00 3-10
			    mciSendString("play music_passedAll from 0",NULL,0,NULL);//播放通关音乐
				myCtrl.showPassedAll();
				life=LIFE;//重置游戏
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
	mciSendString("clase all",NULL,0,NULL);//关闭所有音乐文件
	closegraph();
}
