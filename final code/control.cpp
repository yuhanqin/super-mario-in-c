#include "control.h"
#include"graphics.h"
#include"conio.h"
#include"mydefine.h"

control::control(void)
{
	key=0;
}
control::~control(void)
{
}
int control::getKey()
{
	if(_kbhit())
		key = GetCommand();//获取键盘按键信息
	if(key & CMD_ESC)//如果按了暂停键
		pauseClick();//暂停游戏
	return key;
}
int control::GetCommand()//实现上下左右发射操作
{
	int c = 0;

	if (GetAsyncKeyState('A') & 0x8000)
		c |= CMD_LEFT;
	if (GetAsyncKeyState('D') & 0x8000)
    	c |= CMD_RIGHT;
	if ((GetAsyncKeyState('W') & 0x8000)||(GetAsyncKeyState('K') & 0x8000))
    	c |= CMD_UP;
	if (GetAsyncKeyState('S') & 0x8000)
    	c |= CMD_DOWN;
	if (GetAsyncKeyState('J') & 0x8000)
    	c |= CMD_SHOOT;
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    	c |= CMD_ESC;
	return c;
}
void control::pauseClick()//updated by liangjunzhao at 13:00 3-11
{
	BeginBatchDraw();//绘制游戏暂停界面
	POINT points[8]={{XSIZE/2-45,YSIZE/3}, {XSIZE/2+45,YSIZE/3}, {XSIZE/2+45,YSIZE/3+120}, {XSIZE/2-45,YSIZE/3+120}};//设定各个按钮矩形四个顶点的坐标
	setfillcolor(GREEN);//设置背景颜色为绿色
	fillpolygon(points, 4);//绘制填充颜色的矩形
	setbkmode(TRANSPARENT);
	setfont(20,0,"方正舒体");//设置字体字号
	RECT r2={XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30};rectangle(XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30);//绘制矩形与文字
	drawtext("BACK", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3={XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60};rectangle(XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60);//绘制矩形与文字
    drawtext("RESTART", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    RECT r4={XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90};rectangle(XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90);//绘制矩形与文字
	drawtext("MENU", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    RECT r5={XSIZE/2-45,YSIZE/3+90,XSIZE/2+45,YSIZE/3+120};rectangle(XSIZE/2-45,YSIZE/3+90,XSIZE/2+45,YSIZE/3+120);//绘制矩形与文字
	drawtext("SHOP",&r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	FlushBatchDraw();

	FlushMouseMsgBuffer();//清空鼠标消息队列，否则会出错
	while(true)
	{
		BeginBatchDraw();
		MOUSEMSG m=GetMouseMsg();//获取鼠标信息
		switch(m.uMsg)
        {
		case WM_LBUTTONDOWN:// updated by liangjunzhao at 13:00 3-11 当鼠标左键按下时进入本case
			EndBatchDraw();
			if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3&&m.y<YSIZE/3+30)//如果选择“回到游戏”，则返回VIR_RETURN
			{
	     	    key=VIR_RETURN;
				return;
			}
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+30&&m.y<YSIZE/3+60)//如果选择“重新开始”，则返回VIR_RESTART
			{
				key=VIR_RESTART;
				return;
 			}
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+60&&m.y<YSIZE/3+90)//如果选择“主菜单”，则返回VIR_HOME
			{
				key=VIR_HOME;
				return;
			}
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+90&&m.y<YSIZE/3+120)//如果选择“商店”，则输出文字
			{
				outtextxy(130,260,"Cannot shop in the process!");
			}
		case WM_MOUSEMOVE: //updated by liangjunzhao at 13:00 3-11
			RECT r;
			int i;
			for(i=0;i<4;i++)//创建按钮矩形，并作出鼠标移动到矩形上矩形框变红的动画
			{
			    if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+i*30&&m.y<YSIZE/3+30+i*30)//判断鼠标坐标信息
			    {
				    r.left=XSIZE/2-45;//矩形四条边的坐标
				    r.top=YSIZE/3+i*30;
				    r.right=XSIZE/2+45;
				    r.bottom=YSIZE/3+30+i*30;
					POINT points[8]={{r.left,r.top}, {r.right,r.top}, {r.right,r.bottom}, {r.left,r.bottom}};
				    setfillcolor(RED);//将背景颜色设置为红色
					fillpolygon(points, 4);
					setbkmode(TRANSPARENT);
					switch(i)
					{
					case 0:
					    drawtext("BACK", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//根据15行之前的for循环填入文字
					    break;
					case 1:
					    drawtext("RESTART", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//根据18行之前的for循环填入文字
						break;
					case 2:
					    drawtext("MENU", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//根据21行之前的for循环填入文字
						break;
					case 3:
						drawtext("SHOP",&r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//根据24行之前的for循环填入文字
						break;
					}
				}
			    else
			    {
					if(getpixel(XSIZE/2-45+1,YSIZE/3+i*30+1)==RED)//鼠标移动到指定矩形上后矩形变红
					{
			       	    r.left=XSIZE/2-45;
			            r.top=YSIZE/3+i*30;
			       	    r.right=XSIZE/2+45;
			       	    r.bottom=YSIZE/3+30+i*30;
						POINT points[8]={{r.left,r.top}, {r.right,r.top}, {r.right,r.bottom}, {r.left,r.bottom}};
		   		        setfillcolor(GREEN);
		       			fillpolygon(points, 4);
		       			setbkmode(TRANSPARENT);
		        		switch(i)
					    {
			    		case 0:
			    		    drawtext("BACK", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			    			break;
			    		case 1:
			    			drawtext("RESTART", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			    			break;
			    		case 2:
			    			drawtext("MENU", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			    			break;
						case 3:
							drawtext("SHOP",&r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						}						
					}
					FlushBatchDraw();
				}
			}
		}
	}
}// updated by liangjunzhao at 13:00 3-11
void control::gameStart()//游戏启动界面
{
	cleardevice();
	setfont(50,0,"方正舒体");//设置字体字号
	RECT r1 = {0, 0, XSIZE, YSIZE/3};
	drawtext("EMOJI ALLIANCE", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setfont(10,0,"方正舒体");
	RECT r2={XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30};rectangle(XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30);//绘制矩形与文字
	drawtext("START", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3={XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60};rectangle(XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60);//绘制矩形与文字
    drawtext("INTRODUCTION", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r4={XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90};rectangle(XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90);//绘制矩形与文字
	drawtext("DIRECTION", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r5={XSIZE/2-45,YSIZE/3+90,XSIZE/2+45,YSIZE/3+120};rectangle(XSIZE/2-45,YSIZE/3+90,XSIZE/2+45,YSIZE/3+120);//绘制矩形与文字
	drawtext("EXIT", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	bool _HOME=true,_INTRODUCTION=false,_OPERATION=false;//判断游戏界面停留在主页面，未进入游戏操作界面
	MOUSEMSG m;
	while(_HOME)//设置死循环开始无限不停刷新
	{
		BeginBatchDraw();
		m=GetMouseMsg();//获取鼠标信息
		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN://若鼠标按下
			EndBatchDraw();
		    if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3&&m.y<YSIZE/3+30&&_HOME==1&&_INTRODUCTION==0&&_OPERATION==0)//如果选择“开始游戏”
		    {
				_HOME=false;
				break;
			}
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+30&&m.y<YSIZE/3+60&&_HOME==1&&_OPERATION==0)//如果选择“游戏介绍”
			{
			    _INTRODUCTION=true;//进入游戏介绍
				cleardevice();
				rectangle(50,50,213,220);//绘制矩形与文字
				outtextxy(52,52,"INTRODUCTION ：");//绘制矩形与文字
				outtextxy(52,82,"EMOJI ALLIANCE");
				outtextxy(52,102,"A GAME ABOUT FUNNY'S LOVE");
				outtextxy(52,132,"DESINERS: ");
				outtextxy(52,152,"A MYSTEROUS TEAM");
				outtextxy(52,182,"THANKS FOR MUZINIANNIAN");
				RECT R1={XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2};rectangle(XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2);//绘制矩形与文字
	            drawtext("BACK", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+60&&m.y<YSIZE/3+90&&_HOME==1&&_INTRODUCTION==0)//如果选择“操作说明”
			{
				_OPERATION=true;
				cleardevice();
				rectangle(50,50,213,220);//绘制矩形与文字
				outtextxy(52,52,"DIRECTION：");//绘制矩形与文字
				outtextxy(52,72,"MOVE LEFT：THE KEY A");
				outtextxy(52,92,"MOVE RIGHT：THE KEY D");
				outtextxy(52,112,"SHOOT：THE KEY J");
				outtextxy(52,132,"JUMP ：THE KEY W/K");
				outtextxy(52,152,"PAUSE:Esc");
				RECT R2={XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2};rectangle(XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2);//绘制矩形与文字
	            drawtext("BACK", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+90&&m.y<YSIZE/3+120&&_HOME==1&&_INTRODUCTION==0&&_OPERATION==0)//如果选择“退出游戏”
			    exit(0);
			else if(m.x>XSIZE-46&&m.x<XSIZE-3&&m.y>YSIZE-26&&m.y<YSIZE-3&&(_INTRODUCTION==1||_OPERATION==1))//如果选择“返回”
			{
			    cleardevice();
				_HOME=false,_INTRODUCTION=false,_OPERATION=false;//进入到一个三无界面
				gameStart();//随即立刻开始
			}
			else
			    break;
		case WM_MOUSEMOVE://判断鼠标移动信息
			RECT r;
			if(_INTRODUCTION==1||_OPERATION==1)//若游戏界面位于游戏介绍或游戏进行
			{
			    if(m.x>XSIZE-46&&m.x<XSIZE-3&&m.y>YSIZE-26&&m.y<YSIZE-3)//设置返回键
				{
				    r.left=XSIZE-46;//返回按钮矩形的四个顶点
				    r.top=YSIZE-26;
			        r.right=XSIZE-2;
					r.bottom=YSIZE-2;
					POINT points[8]={{r.left,r.top}, {r.right,r.top}, {r.right,r.bottom}, {r.left,r.bottom}};
				    setfillcolor(RED);
					fillpolygon(points, 4);
					setbkmode(TRANSPARENT);
					drawtext("BACK", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//绘制矩形与文字
				}
				else
				{
					if(getpixel(XSIZE-46+1,YSIZE-26+1)==RED)//鼠标移动到上面变红效果
					{
					    r.left=XSIZE-46;
			         	r.top=YSIZE-26;
			            r.right=XSIZE-2;
			        	r.bottom=YSIZE-2;
						POINT points[8]={{r.left,r.top}, {r.right,r.top}, {r.right,r.bottom}, {r.left,r.bottom}};
						setfillcolor(BLACK);
					    fillpolygon(points, 4);
					    setbkmode(TRANSPARENT);
					    drawtext("BACK", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
				}
			}
			else//若游戏界面没有位于游戏介绍或游戏进行，则绘制主菜单按钮
			{
			    for(int i=0;i<4;i++)//主菜单按钮一共有4个，开始循环
				{
				    if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+i*30&&m.y<YSIZE/3+30+i*30)//通过i的递增实现上下矩形相连
				    {
					    r.left=XSIZE/2-45;
					    r.top=YSIZE/3+i*30;
					    r.right=XSIZE/2+45;
					    r.bottom=YSIZE/3+30+i*30;
						POINT points[8]={{r.left,r.top}, {r.right,r.top}, {r.right,r.bottom}, {r.left,r.bottom}};
					    setfillcolor(RED);
						fillpolygon(points, 4);
						setbkmode(TRANSPARENT);
						switch(i)//通过switch绘制文字
						{
						case 0:
						    drawtext("START", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						    break;
						case 1:
						    drawtext("INTRODUCTION", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 2:
						    drawtext("DIRECTION", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
					   	case 3:
							drawtext("EXIT", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						}
					}
				    else
				    {
						if(getpixel(XSIZE/2-45+1,YSIZE/3+i*30+1)==RED)//鼠标移动到上面变红效果
						{
				       	    r.left=XSIZE/2-45;
				            r.top=YSIZE/3+i*30;
				       	    r.right=XSIZE/2+45;
				       	    r.bottom=YSIZE/3+30+i*30;
							POINT points[4]={{r.left,r.top}, {r.right,r.top}, {r.right,r.bottom}, {r.left,r.bottom}};
			   		        setfillcolor(BLACK);
			       			fillpolygon(points, 4);
			       			setbkmode(TRANSPARENT);
			        		switch(i)
						    {
				    		case 0:
				    		    drawtext("START", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
				    		case 1:
				    			drawtext("INTRODUCTION", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
				    		case 2:
				    			drawtext("DIRECTION", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
				    	   	case 3:
				    			drawtext("EXIT", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
							}
						}
					}
				}
			}
			FlushBatchDraw();
			break;
			default:
			    break;
		 }
	}
}
void control::showScore(int score)//在游戏地图上端显示得分与关卡
{
	setfont(0,0,"宋体");
	char s1[20]="MONEY:  ";
	char s2[5];//存储金钱信息
	itoa(score,s2,10);
	strcat(s1,s2);//数组合并
	setbkmode(TRANSPARENT);
	outtextxy(10,10,s1);//数组输出
	setbkmode(OPAQUE);
}
void control::showLevel(int level)
{
	setfont(0,0,"宋体");
	char s1[20]="LEVEL:  ";
	char s2[2];//存储关卡 信息
	itoa(level,s2,10);
	strcat(s1,s2);
	setbkmode(TRANSPARENT);
	outtextxy(XSIZE-90,10,s1);
	setbkmode(OPAQUE);
}
void control::showDied(int life)//本关失败后动画
{
	cleardevice();
	char s1[20]="Your life left:  ";
	char s2[2];//存储剩余生命信息
	itoa(life,s2,10);
	outtextxy(XSIZE/2-43,YSIZE/3,s1);
	outtextxy(XSIZE/2,YSIZE/2-20,s2);
	Sleep(2000);
}
void control::showGameOver()//游戏结束动画
{
	IMAGE img;
	loadimage(&img,"res\\home.bmp",XSIZE,5*YSIZE);//其实就是一张图
	putimage(0,-YSIZE,&img);
	Sleep(6500);//而且需要过6.5秒才能出这张图
}
void control::showPassed(int world)//通关动画
{
	cleardevice();
	char s1[20]="LEVEL:  ";//显示下一关关卡数
	char s2[2];
	itoa(world,s2,10);
	outtextxy(XSIZE/2-20,YSIZE/3,s1);
	outtextxy(XSIZE/2,YSIZE/2-20,s2);
	Sleep(1000);
}
void control::showPassedAll()
{
	IMAGE img;
	loadimage(&img,"res\\home.bmp",XSIZE,5*YSIZE);//通关图片
	putimage(0,-3*YSIZE,&img);
	Sleep(7800);//这把等待的时间更长
}