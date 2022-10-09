#pragma once
#include <atomic>



class CWorkerDummy
{
public:
	CWorkerDummy();
	typedef DWORD_PTR RequestType;
public:
	virtual BOOL Initialize(void* pvParam);
	virtual void Terminate(void* pvParam = nullptr);
	void Execute(RequestType dw, void* pvParam, OVERLAPPED* pOverlapped) throw();

protected:
	std::atomic<DWORD> m_dwExecs;//count the execution
	std::atomic<LONG> m_lId;//thread id
};