// LargeShoot.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <concurrentqueue.h>
#include <future>
#include <iostream>

int main()
{
	std::atomic<int> res[10000];
	for (int i = 0; i < 10000; ++i)
	{
		res[i] = 0;
	}

	moodycamel::ConcurrentQueue<int> queue;
	for (int i = 0; i < 10000; ++i)
	{
		queue.enqueue(i);
	}

	auto t1 = std::async([&]()
	{
		int i;
		while (queue.size_approx() > 0)
			if (queue.try_dequeue(i))
			{
				std::cout << "id: " << std::this_thread::get_id() << "\tvalue: " << i << std::endl;
				++res[i];
			}
	});


	auto t2 = std::async([&]()
	{
		int i;
		while (queue.size_approx() > 0)
			if (queue.try_dequeue(i))
			{
				std::cout << "id: " << std::this_thread::get_id() << "\tvalue: " << i << std::endl;
				++res[i];
			}
	});

	t1.get();
	t2.get();

	int i;
	std::cin >> i;
	return 0;
}

