#include "Worker.h"
#include "QueueEmulator.h"
#include "Desk.h"
#include "BTimer.h"
#include "UtilsService.h"

Worker::Worker(QueueEmulator* parent)
	: QObject(parent), m_view(parent)
{
	m_timerSpawn = new BTimer(this);
	connect(m_timerSpawn, &QTimer::timeout, this, [&]()
		{
			if (!m_isSorted)
				Sort();
			StartTimerRandom();
		});
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
			connect(desk, QOverload<int>::of(&Desk::changed_people), deskView, &DeskView::SetPeopleCount);
			connect(this, QOverload<bool>::of(&Worker::changed_running), desk, &Desk::SetRunning);
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
	if (m_desks.size() > 0)
	{
		StartTimerRandom();
	}
	else
		m_timerSpawn->stop();
}

void Worker::Add(Desk* desk)
{
	m_desks.push_back(desk);
	m_isSorted = false;
}

void Worker::AddPeople(Desk* desk, const int quantity)
{
	if (desk)
	{
		desk->DeltaPeopleCount(quantity);
	}
}

void Worker::SetRunning(const bool running)
{
	m_running = running;
	if (running)
		m_timerSpawn->resume();
	else
		m_timerSpawn->pause();
	changed_running(running);
}

void Worker::DeleteLast()
{
	m_desks.pop_back();
}

void Worker::Sort()
{
	std::sort(m_desks.begin(), m_desks.end());
}

void Worker::StartTimerRandom()
{
	if (m_running)
	{
		const int new_people = UtilsService::GetRandomInt(0, m_p);
		AddPeople(*m_desks.begin(), new_people);
		m_timerSpawn->start(1, m_t);
	}
}

void Worker::SetP(const int val)
{
	m_p = val;
}

int Worker::GetP() const
{
	return m_p;
}

void Worker::SetT(const int val)
{
	m_t = val;
}

int Worker::GetT() const
{
	return m_t;
}

Worker::~Worker()
{

}
