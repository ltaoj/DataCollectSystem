#pragma once


// CCPUInfo

class CCPUInfo : public CWnd
{
	DECLARE_DYNAMIC(CCPUInfo)

public:
	CCPUInfo();
	virtual ~CCPUInfo();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CString GetCPUType();
	CString GetManID();
	long GetCPUFreq();
	void ExeCPUID(DWORD veax);
};


