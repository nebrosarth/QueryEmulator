#include "Worker.h"
#include "QueueEmulator.h"
#include "Desk.h"

Worker::Worker(QueueEmulator* parent)
	: QObject(parent), emu(parent)
{

}

void Worker::SetDeskQuantity(const int quantity)
{
	const int current_size = desks.size();
	if (!is_sorted)
		Sort();
	if (quantity > current_size)
	{
		for (int i = 0; i < quantity - current_size; ++i)
		{
			auto view = emu->CreateDeskView();
			Desk desk(view);
			Add(desk);
		}
	}
	else
	{
		for (int i = 0; i < current_size - quantity; ++i)
		{
			emu->DeleteLastDeskView();
			DeleteLast();
		}
	}
}

void Worker::Add(Desk& desk)
{
	desks.push_back(std::move(desk));
	is_sorted = false;
}

void Worker::DeleteLast()
{
	desks.pop_back();
	is_sorted = false;
}

void Worker::Sort()
{
	std::sort(desks.begin(), desks.end());
}

Worker::~Worker()
{

}
