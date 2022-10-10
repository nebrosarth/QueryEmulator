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
			connect(desk, QOverload<int>::of(&Desk::onDelete_givePeople), this, [this](const int val)
				{
					m_sparePeople += val;
				});
			connect(desk, &Desk::destroyed, this, [this]()
				{
					if (!m_desks.empty())
					{
						AddPeople(m_sparePeople);
						m_sparePeople = 0;
					}
				});
			//connect(deskView, &QWidget::destroyed, desk, [&]()
			//	{
			//		desk->suicide();
			//	});
			Add(desk);
		}
	}
	else
	{
		for (int i = 0; i < current_size - quantity; ++i)
		{
			//m_view->DeleteLastDeskView();
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

void Worker::AddPeople(const int val)
{
	for (int i = 0; i < val; ++i)
	{
		if (!m_isSorted)
			Sort();
		AddPeople2Desk(m_desks.front(), 1);
	}
}

void Worker::AddPeople2Desk(Desk* desk, const int quantity)
{
	if (desk)
	{
		desk->DeltaPeopleCount(quantity);
		m_isSorted = false;
	}
}

void Worker::SetRunning(const bool running)
{
	m_running = running;
	if (running)
		if (m_timerSpawn->remainingTime() <= 0)
			StartTimerRandom();
		else
			m_timerSpawn->resume();
	else
		m_timerSpawn->pause();
	changed_running(running);
}

void Worker::DeleteLast()
{
	auto item = m_desks.back();
	auto deskView = item->GetView();
	m_desks.pop_back();
	if (deskView)
		delete deskView;
}

bool compareDesksPtr(Desk* d1, Desk* d2)
{
	return (*d1 < *d2);
}

void Worker::Sort()
{
	std::sort(m_desks.begin(), m_desks.end(), compareDesksPtr);
	m_isSorted = true;
}

void Worker::StartTimerRandom()
{
	if (m_running && m_desks.size() > 0)
	{
		const int new_people = UtilsService::GetRandomInt(0, m_p);
		AddPeople(new_people + m_sparePeople);
		m_sparePeople = 0;
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
