#include "Thread.h"
#include <windows.h>


TThread::TThread()
{
	FThreadID = 0;
	FHandle = 0;
};


unsigned long __stdcall TThread::Wrapper(void * arg)
{  
	TThread * Thd;
	Thd = ((TThread *) arg);
	//Sleep(2000);
	Thd->Execute();	
	ExitThread(Thd->FReturnValue);
	return Thd->FReturnValue;
};

bool TThread::Run()
{  
	FHandle = CreateThread(NULL, 0, Wrapper, this, 0, &FThreadID);
	if (FHandle == 0)
		FThreadID = 0;
	return FHandle != 0; 
};

TThread::~TThread()
{ 
	if (FThreadID != 0)  { 
		WaitFor(); 
		CloseHandle(FHandle);
	}	
};

void TThread::WaitFor(){ 
	if (FThreadID == 0)    return; 
	WaitForSingleObject(FHandle, INFINITE);
};

int TThread::GetThreadID()
{  
	return FThreadID;
};

HANDLE TThread::GetHandle()
{
	return FHandle;
};
