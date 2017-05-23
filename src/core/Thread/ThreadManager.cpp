#include "stdafx.h"

#include "thread.h"

LargeShoot::ThreadManager::ThreadManager(const LargeShoot::Id id, int threadNumber)
	:Object(id)
{
	for(int i =0; i < threadNumber; i++)
	{
		_threads.push_back(Thread(Id()));
	}
}