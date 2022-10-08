#include "Desk.h"
#include "BTimer.h"

Desk::Desk(DeskView* view, QObject* parent)
	: QObject(parent),
	m_deskView(view)
{
	m_timerServ = new BTimer(this);
	connect(m_timerServ, &QTimer::timeout, this, [&]()
		{
			if (m_peopleCount > 0)
			{
				DeltaPeopleCount(-1);
			}
		});
	//StartTimer();
}

Desk::Desk(const Desk& d)
{
	m_peopleCount = d.m_peopleCount;
}

void Desk::SetPeopleCount(const int quantity)
{
	m_peopleCount = quantity;
	changed_people(m_peopleCount);
}

void Desk::DeltaPeopleCount(const int delta)
{
	m_peopleCount += delta;
	changed_people(m_peopleCount);
	if (m_peopleCount > 0)
	{
		StartTimerRandom();
	}
}
void Desk::SetRunning(const bool running)
{
	m_running = running;
	if (running)
		m_timerServ->resume();
	else
		m_timerServ->pause();
}

void Desk::StartTimerRandom()
{
	if (m_running)
	{
		const int min = m_deskView->GetMinServTime();
		const int max = m_deskView->GetMaxServTime();
		m_timerServ->start(min, max);
	}
}

Desk::~Desk()
{}
