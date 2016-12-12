// CPUInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CPUInfo.h"
#include "windows.h"
//�����洢eax,ebx,ecx,edx�ĸ��Ĵ�������Ϣ
DWORD deax;
DWORD debx;
DWORD decx;
DWORD dedx;
// CCPUInfo

IMPLEMENT_DYNAMIC(CCPUInfo, CWnd)

CCPUInfo::CCPUInfo()
{

}

CCPUInfo::~CCPUInfo()
{
}


BEGIN_MESSAGE_MAP(CCPUInfo, CWnd)
END_MESSAGE_MAP()



// CCPUInfo ��Ϣ�������

void CCPUInfo::ExeCPUID(DWORD veax)  //��ʼ��CPU
{
	__asm
	{
		mov eax, veax
		cpuid
			mov deax, eax
			mov debx, ebx
			mov decx, ecx
			mov dedx, edx
	}
}
/*    ��Intel Pentium���ϼ����CPU�У���һ����Ϊ��ʱ�����Time Stamp�����Ĳ�����
����64λ�޷����������ĸ�ʽ����¼����CPU�ϵ�������������ʱ����������
����Ŀǰ��CPU��Ƶ���ǳ��ߣ��������������Դﵽ���뼶�ļ�ʱ���ȡ�
�����ȷ�����������ַ������޷�����ġ�
��Pentium���ϵ�CPU�У��ṩ��һ������ָ��RDTSC��Read Time Stamp Counter��
����ȡ���ʱ��������֣������䱣����EDX:EAX�Ĵ�������
*/
long CCPUInfo::GetCPUFreq()       //��ȡCPUƵ��,��λ: MHZ
{
	int start, over;
	_asm
	{
		RDTSC
		mov start, eax
	}
	Sleep(50);
	_asm
	{
		RDTSC
		mov over, eax
	}
	return (over - start) / 50000;
}



/*   ��eax = 0��Ϊ������������Եõ�CPU����������Ϣ��
cpuidָ��ִ���Ժ󣬻᷵��һ��12�ַ�����������Ϣ��
ǰ�ĸ��ַ���ASC�밴��λ����λ����ebx���м��ĸ�����edx������ĸ��ַ�����ecx��
*/
CString CCPUInfo::GetManID()   //��ȡ��������Ϣ
{
	char ID[25];
	memset(ID, 0, sizeof(ID));

	ExeCPUID(0);          //��ʼ��
	memcpy(ID + 0, &debx, 4); //��������Ϣ���Ƶ�����
	memcpy(ID + 4, &dedx, 4);
	memcpy(ID + 8, &decx, 4);

	return CString(ID);
}


/*  ���ҵĵ����ϵ���Ҽ���ѡ�����ԣ������ڴ��ڵ����濴��һ��CPU����Ϣ��
�����CPU���̱��ַ�����CPU���̱��ַ���Ҳ��ͨ��cpuid�õ��ġ�
�����̱���ַ����ܳ�(48���ַ�)�����Բ�����һ��cpuidָ��ִ��ʱȫ���õ���
����intel�����ֳ���3��������eax����������ֱ���0x80000002,0x80000003,0x80000004��
ÿ�η��ص�16���ַ������մӵ�λ����λ��˳�����η���eax, ebx, ecx, edx��
��ˣ�������ѭ���ķ�ʽ��ÿ��ִ�����Ժ󱣴�����Ȼ��ִ����һ��cpuid��
*/
CString CCPUInfo::GetCPUType()
{
	const DWORD id = 0x80000002; //��0x80000002��ʼ,��0x80000004����
	char CPUType[49];//�����洢CPU�ͺ���Ϣ
	memset(CPUType, 0, sizeof(CPUType));//��ʼ������

	for (DWORD t = 0; t < 3; t++)
	{
		ExeCPUID(id + t);
		//ÿ��ѭ������,������Ϣ������
		memcpy(CPUType + 16 * t + 0, &deax, 4);
		memcpy(CPUType + 16 * t + 4, &debx, 4);
		memcpy(CPUType + 16 * t + 8, &decx, 4);
		memcpy(CPUType + 16 * t + 12, &dedx, 4);
	}

	return CString(CPUType);
}
