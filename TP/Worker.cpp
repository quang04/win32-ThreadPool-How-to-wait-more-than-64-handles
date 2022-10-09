#include "pch.h"
#include "Worker.h"
#include "Tasks.h"

static LONG g_lCurrId = -1;

CWorkerDummy::CWorkerDummy()
	: m_dwExecs(0)
{
	m_lId = ++g_lCurrId;
}

BOOL CWorkerDummy::Initialize(void* pvParam)
{
	std::cout << std::format("[{}]: CWorkerDummny Initialize.\n", GetCurrentThreadId());
	return TRUE;
}

void CWorkerDummy::Terminate(void* pvParam)
{
	std::cout << std::format("CWorkerDummy ID: {}. Execution {} times.\n",
		m_lId.load(), m_dwExecs.load());
}

void CWorkerDummy::Execute(RequestType dw, void* pvParam, OVERLAPPED* pOverlapped) throw()
{
	ASSERT(pvParam != nullptr);

	std::cout << std::format("[{}]: CWorkerDummny Execute.\n", GetCurrentThreadId());


	CTaskBase* pTask = reinterpret_cast<CTaskBase*>(dw);
	pTask->DoTask(pvParam, pOverlapped);

	m_dwExecs++;
}
