// �������ƣ���ȷ��΢�����ʱ�ࣨ���ڶ�ý�嶨ʱ����
// �����д��yangw80 <yw80@qq.com>
// ����޸ģ�2011-5-4
//
#pragma once
#include <windows.h>

class MyTimer
{
private:
	LARGE_INTEGER m_clk;
	
	// ����ʱ����Ϣ
	LONGLONG m_oldclk;
	
	
	// ���濪ʼʱ�Ӻͽ���ʱ��
	int m_freq;
	
	
	
	
	// ʱ��Ƶ��(ʱ��ʱ�任����)��ʱ���

public:
	MyTimer();
	void Sleep(int ms);//��Ļ��ֹ�ȴ�����
	void Reset();//���ü�ʱ��
};
