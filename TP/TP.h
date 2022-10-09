#pragma once

#include "Worker.h"
#include "Tasks.h"

typedef std::vector<CTaskBase*> CTaskVector;
typedef std::vector<HANDLE> HandleVector;

typedef struct
{
	int nQuantity;
	HandleVector vectorStoreHandles;

}StoreHandleStruct, *pStoreHandleStruct;