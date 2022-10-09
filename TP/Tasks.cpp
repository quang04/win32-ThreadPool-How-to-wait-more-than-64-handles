#include "pch.h"
#include "Tasks.h"


CTaskBase::CTaskBase()
	: m_hWaitTaskComplete(CreateEvent(NULL, FALSE, FALSE, NULL))
{
}

CTaskBase::~CTaskBase()
{
}

CTaskBase::CTaskBase(const CTaskBase& other)
{
	m_hWaitTaskComplete = other.m_hWaitTaskComplete;
}

constexpr CTaskBase& CTaskBase::operator=(const CTaskBase& other)
{
	m_hWaitTaskComplete = other.m_hWaitTaskComplete;
	return *this;
}

CTaskBase::CTaskBase(CTaskBase&& other) noexcept
{
	m_hWaitTaskComplete = other.m_hWaitTaskComplete;
	other.m_hWaitTaskComplete = INVALID_HANDLE_VALUE;
}

CTaskBase& CTaskBase::operator=(CTaskBase&& other) noexcept
{
	m_hWaitTaskComplete = other.m_hWaitTaskComplete;
	other.m_hWaitTaskComplete = INVALID_HANDLE_VALUE;
	return *this;
}


void CTask1::DoTask(void* pvPara, OVERLAPPED* pOverlapped)
{
	std::cout << std::format("{}: CTask1:DoTask\n", GetCurrentThreadId());
	std::cout << "Task 1 completed. Signed wait event \n";
	SetEvent(m_hWaitTaskComplete);
}

void CTask2::DoTask(void* pvPara, OVERLAPPED* pOverlapped)
{
	std::cout << std::format("{}: CTask2:DoTask\n", GetCurrentThreadId());
	std::cout << "Task 2 completed. Signed wait event \n";
	SetEvent(m_hWaitTaskComplete);
}
