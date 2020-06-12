// 程序名称：精确到微秒的延时类（基于多媒体定时器）
// 程序编写：yangw80 <yw80@qq.com>
// 最后修改：2011-5-4
//
#pragma once
#include <windows.h>

class MyTimer
{
private:
	LARGE_INTEGER m_clk;
	
	// 保存时钟信息
	LONGLONG m_oldclk;
	
	
	// 保存开始时钟和结束时钟
	int m_freq;
	
	
	
	
	// 时钟频率(时钟时间换算率)，时间差

public:
	MyTimer();
	void Sleep(int ms);//屏幕静止等待函数
	void Reset();//重置计时器
};
