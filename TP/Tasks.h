#pragma once



class CTaskBase
{
public:
	CTaskBase();
	virtual ~CTaskBase();
	CTaskBase(const CTaskBase& other);
	constexpr CTaskBase& operator=(const CTaskBase& other);
	CTaskBase(CTaskBase&& other) noexcept;
	CTaskBase& operator=(CTaskBase&& other) noexcept;
protected:
	HANDLE m_hWaitTaskComplete;
public:
	inline HANDLE& GetWaitTaskCompleteEvent()
	{
		return m_hWaitTaskComplete;
	}
	virtual void DoTask(void* pvParam, OVERLAPPED* pOverlapped) = 0;
};

class CTask1 : public CTaskBase
{
public:
	virtual void DoTask(void* pvPara, OVERLAPPED* pOverlapped) override;
};

class CTask2 : public CTaskBase
{
public:
	virtual void DoTask(void* pvPara, OVERLAPPED* pOverlapped) override;
};