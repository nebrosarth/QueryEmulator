#include "Worker.h"
#include "QueueEmulator.h"
#include "Desk.h"

Worker::Worker(QueueEmulator* parent)
	: QObject(parent), m_view(parent)
{

}

void Worker::PendDeskQuantity(const int quantity)
{
	const int current_size = m_desks.size();
	if (quantity > current_size)
	{
		for (int i = 0; i < quantity - current_size; ++i)
		{
			DeskView* deskView = m_view->CreateDeskView();
			Desk* desk = new Desk(deskView);
			connect(this, QOverload<int>::of(&Worker::changed_p), desk, &Desk::SetPeopleIncome);
			connect(this, QOverload<int>::of(&Worker::changed_t), desk, &Desk::SetTimeInterval);
			connect(desk, QOverload<int>::of(&Desk::changed_people), deskView, &DeskView::SetPeopleCount);
			Add(desk);
		}
	}
	else
	{
		for (int i = 0; i < current_size - quantity; ++i)
		{
			m_view->DeleteLastDeskView();
			DeleteLast();
		}
	}
}

void Worker::Add(Desk* desk)
{
	m_desks.push_back(desk);
	m_isSorted = false;
}

void Worker::DeleteLast()
{
	m_desks.pop_back();
}

void Worker::Sort()
{
	std::sort(m_desks.begin(), m_desks.end());
}

void Worker::SetP(const int val)
{
	m_p = val;
	changed_p(val);
}

int Worker::GetP() const
{
	return m_p;
}

void Worker::SetT(const int val)
{
	m_t = val;
	changed_t(val);
}

int Worker::GetT() const
{
	return m_t;
}

Worker::~Worker()
{

}
