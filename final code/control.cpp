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
		key = GetCommand();//��ȡ���̰�����Ϣ
	if(key & CMD_ESC)//���������ͣ��
		pauseClick();//��ͣ��Ϸ
	return key;
}
int control::GetCommand()//ʵ���������ҷ������
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
	BeginBatchDraw();//������Ϸ��ͣ����
	POINT points[8]={{XSIZE/2-45,YSIZE/3}, {XSIZE/2+45,YSIZE/3}, {XSIZE/2+45,YSIZE/3+120}, {XSIZE/2-45,YSIZE/3+120}};//�趨������ť�����ĸ����������
	setfillcolor(GREEN);//���ñ�����ɫΪ��ɫ
	fillpolygon(points, 4);//���������ɫ�ľ���
	setbkmode(TRANSPARENT);
	setfont(20,0,"��������");//���������ֺ�
	RECT r2={XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30};rectangle(XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30);//���ƾ���������
	drawtext("BACK", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3={XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60};rectangle(XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60);//���ƾ���������
    drawtext("RESTART", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    RECT r4={XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90};rectangle(XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90);//���ƾ���������
	drawtext("MENU", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    RECT r5={XSIZE/2-45,YSIZE/3+90,XSIZE/2+45,YSIZE/3+120};rectangle(XSIZE/2-45,YSIZE/3+90,XSIZE/2+45,YSIZE/3+120);//���ƾ���������
	drawtext("SHOP",&r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	FlushBatchDraw();

	FlushMouseMsgBuffer();//��������Ϣ���У���������
	while(true)
	{
		BeginBatchDraw();
		MOUSEMSG m=GetMouseMsg();//��ȡ�����Ϣ
		switch(m.uMsg)
        {
		case WM_LBUTTONDOWN:// updated by liangjunzhao at 13:00 3-11 ������������ʱ���뱾case
			EndBatchDraw();
			if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3&&m.y<YSIZE/3+30)//���ѡ�񡰻ص���Ϸ�����򷵻�VIR_RETURN
			{
	     	    key=VIR_RETURN;
				return;
			}
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+30&&m.y<YSIZE/3+60)//���ѡ�����¿�ʼ�����򷵻�VIR_RESTART
			{
				key=VIR_RESTART;
				return;
 			}
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+60&&m.y<YSIZE/3+90)//���ѡ�����˵������򷵻�VIR_HOME
			{
				key=VIR_HOME;
				return;
			}
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+90&&m.y<YSIZE/3+120)//���ѡ���̵ꡱ�����������
			{
				outtextxy(130,260,"Cannot shop in the process!");
			}
		case WM_MOUSEMOVE: //updated by liangjunzhao at 13:00 3-11
			RECT r;
			int i;
			for(i=0;i<4;i++)//������ť���Σ�����������ƶ��������Ͼ��ο���Ķ���
			{
			    if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+i*30&&m.y<YSIZE/3+30+i*30)//�ж����������Ϣ
			    {
				    r.left=XSIZE/2-45;//���������ߵ�����
				    r.top=YSIZE/3+i*30;
				    r.right=XSIZE/2+45;
				    r.bottom=YSIZE/3+30+i*30;
					POINT points[8]={{r.left,r.top}, {r.right,r.top}, {r.right,r.bottom}, {r.left,r.bottom}};
				    setfillcolor(RED);//��������ɫ����Ϊ��ɫ
					fillpolygon(points, 4);
					setbkmode(TRANSPARENT);
					switch(i)
					{
					case 0:
					    drawtext("BACK", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//����15��֮ǰ��forѭ����������
					    break;
					case 1:
					    drawtext("RESTART", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//����18��֮ǰ��forѭ����������
						break;
					case 2:
					    drawtext("MENU", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//����21��֮ǰ��forѭ����������
						break;
					case 3:
						drawtext("SHOP",&r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//����24��֮ǰ��forѭ����������
						break;
					}
				}
			    else
			    {
					if(getpixel(XSIZE/2-45+1,YSIZE/3+i*30+1)==RED)//����ƶ���ָ�������Ϻ���α��
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
void control::gameStart()//��Ϸ��������
{
	cleardevice();
	setfont(50,0,"��������");//���������ֺ�
	RECT r1 = {0, 0, XSIZE, YSIZE/3};
	drawtext("EMOJI ALLIANCE", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setfont(10,0,"��������");
	RECT r2={XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30};rectangle(XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30);//���ƾ���������
	drawtext("START", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3={XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60};rectangle(XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60);//���ƾ���������
    drawtext("INTRODUCTION", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r4={XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90};rectangle(XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90);//���ƾ���������
	drawtext("DIRECTION", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r5={XSIZE/2-45,YSIZE/3+90,XSIZE/2+45,YSIZE/3+120};rectangle(XSIZE/2-45,YSIZE/3+90,XSIZE/2+45,YSIZE/3+120);//���ƾ���������
	drawtext("EXIT", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	bool _HOME=true,_INTRODUCTION=false,_OPERATION=false;//�ж���Ϸ����ͣ������ҳ�棬δ������Ϸ��������
	MOUSEMSG m;
	while(_HOME)//������ѭ����ʼ���޲�ͣˢ��
	{
		BeginBatchDraw();
		m=GetMouseMsg();//��ȡ�����Ϣ
		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN://����갴��
			EndBatchDraw();
		    if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3&&m.y<YSIZE/3+30&&_HOME==1&&_INTRODUCTION==0&&_OPERATION==0)//���ѡ�񡰿�ʼ��Ϸ��
		    {
				_HOME=false;
				break;
			}
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+30&&m.y<YSIZE/3+60&&_HOME==1&&_OPERATION==0)//���ѡ����Ϸ���ܡ�
			{
			    _INTRODUCTION=true;//������Ϸ����
				cleardevice();
				rectangle(50,50,213,220);//���ƾ���������
				outtextxy(52,52,"INTRODUCTION ��");//���ƾ���������
				outtextxy(52,82,"EMOJI ALLIANCE");
				outtextxy(52,102,"A GAME ABOUT FUNNY'S LOVE");
				outtextxy(52,132,"DESINERS: ");
				outtextxy(52,152,"A MYSTEROUS TEAM");
				outtextxy(52,182,"THANKS FOR MUZINIANNIAN");
				RECT R1={XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2};rectangle(XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2);//���ƾ���������
	            drawtext("BACK", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+60&&m.y<YSIZE/3+90&&_HOME==1&&_INTRODUCTION==0)//���ѡ�񡰲���˵����
			{
				_OPERATION=true;
				cleardevice();
				rectangle(50,50,213,220);//���ƾ���������
				outtextxy(52,52,"DIRECTION��");//���ƾ���������
				outtextxy(52,72,"MOVE LEFT��THE KEY A");
				outtextxy(52,92,"MOVE RIGHT��THE KEY D");
				outtextxy(52,112,"SHOOT��THE KEY J");
				outtextxy(52,132,"JUMP ��THE KEY W/K");
				outtextxy(52,152,"PAUSE:Esc");
				RECT R2={XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2};rectangle(XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2);//���ƾ���������
	            drawtext("BACK", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+90&&m.y<YSIZE/3+120&&_HOME==1&&_INTRODUCTION==0&&_OPERATION==0)//���ѡ���˳���Ϸ��
			    exit(0);
			else if(m.x>XSIZE-46&&m.x<XSIZE-3&&m.y>YSIZE-26&&m.y<YSIZE-3&&(_INTRODUCTION==1||_OPERATION==1))//���ѡ�񡰷��ء�
			{
			    cleardevice();
				_HOME=false,_INTRODUCTION=false,_OPERATION=false;//���뵽һ�����޽���
				gameStart();//�漴���̿�ʼ
			}
			else
			    break;
		case WM_MOUSEMOVE://�ж�����ƶ���Ϣ
			RECT r;
			if(_INTRODUCTION==1||_OPERATION==1)//����Ϸ����λ����Ϸ���ܻ���Ϸ����
			{
			    if(m.x>XSIZE-46&&m.x<XSIZE-3&&m.y>YSIZE-26&&m.y<YSIZE-3)//���÷��ؼ�
				{
				    r.left=XSIZE-46;//���ذ�ť���ε��ĸ�����
				    r.top=YSIZE-26;
			        r.right=XSIZE-2;
					r.bottom=YSIZE-2;
					POINT points[8]={{r.left,r.top}, {r.right,r.top}, {r.right,r.bottom}, {r.left,r.bottom}};
				    setfillcolor(RED);
					fillpolygon(points, 4);
					setbkmode(TRANSPARENT);
					drawtext("BACK", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//���ƾ���������
				}
				else
				{
					if(getpixel(XSIZE-46+1,YSIZE-26+1)==RED)//����ƶ���������Ч��
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
			else//����Ϸ����û��λ����Ϸ���ܻ���Ϸ���У���������˵���ť
			{
			    for(int i=0;i<4;i++)//���˵���ťһ����4������ʼѭ��
				{
				    if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+i*30&&m.y<YSIZE/3+30+i*30)//ͨ��i�ĵ���ʵ�����¾�������
				    {
					    r.left=XSIZE/2-45;
					    r.top=YSIZE/3+i*30;
					    r.right=XSIZE/2+45;
					    r.bottom=YSIZE/3+30+i*30;
						POINT points[8]={{r.left,r.top}, {r.right,r.top}, {r.right,r.bottom}, {r.left,r.bottom}};
					    setfillcolor(RED);
						fillpolygon(points, 4);
						setbkmode(TRANSPARENT);
						switch(i)//ͨ��switch��������
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
						if(getpixel(XSIZE/2-45+1,YSIZE/3+i*30+1)==RED)//����ƶ���������Ч��
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
void control::showScore(int score)//����Ϸ��ͼ�϶���ʾ�÷���ؿ�
{
	setfont(0,0,"����");
	char s1[20]="MONEY:  ";
	char s2[5];//�洢��Ǯ��Ϣ
	itoa(score,s2,10);
	strcat(s1,s2);//����ϲ�
	setbkmode(TRANSPARENT);
	outtextxy(10,10,s1);//�������
	setbkmode(OPAQUE);
}
void control::showLevel(int level)
{
	setfont(0,0,"����");
	char s1[20]="LEVEL:  ";
	char s2[2];//�洢�ؿ� ��Ϣ
	itoa(level,s2,10);
	strcat(s1,s2);
	setbkmode(TRANSPARENT);
	outtextxy(XSIZE-90,10,s1);
	setbkmode(OPAQUE);
}
void control::showDied(int life)//����ʧ�ܺ󶯻�
{
	cleardevice();
	char s1[20]="Your life left:  ";
	char s2[2];//�洢ʣ��������Ϣ
	itoa(life,s2,10);
	outtextxy(XSIZE/2-43,YSIZE/3,s1);
	outtextxy(XSIZE/2,YSIZE/2-20,s2);
	Sleep(2000);
}
void control::showGameOver()//��Ϸ��������
{
	IMAGE img;
	loadimage(&img,"res\\home.bmp",XSIZE,5*YSIZE);//��ʵ����һ��ͼ
	putimage(0,-YSIZE,&img);
	Sleep(6500);//������Ҫ��6.5����ܳ�����ͼ
}
void control::showPassed(int world)//ͨ�ض���
{
	cleardevice();
	char s1[20]="LEVEL:  ";//��ʾ��һ�عؿ���
	char s2[2];
	itoa(world,s2,10);
	outtextxy(XSIZE/2-20,YSIZE/3,s1);
	outtextxy(XSIZE/2,YSIZE/2-20,s2);
	Sleep(1000);
}
void control::showPassedAll()
{
	IMAGE img;
	loadimage(&img,"res\\home.bmp",XSIZE,5*YSIZE);//ͨ��ͼƬ
	putimage(0,-3*YSIZE,&img);
	Sleep(7800);//��ѵȴ���ʱ�����
}