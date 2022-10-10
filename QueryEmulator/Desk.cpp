#include "Desk.h"
#include "BTimer.h"
#include "ui_DeskView.h"

Desk::Desk(DeskView* view, QObject* parent)
	: QObject(view),
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
		m_avgTime = (m_avgTime * m_passedClients + m_timerServ->m_time) / (m_passedClients + 1);
		m_passedClients++;
		auto deskView = GetView();
		if (deskView)
		{
			deskView->GetUI()->l_avgTime->setText(u8"Среднее время: " + QString::number(m_avgTime));
			deskView->GetUI()->l_qLength->setText(u8"Длина очереди: " + QString::number(m_peopleCount));
		}
	}
}

DeskView* Desk::GetView() const
{
	return m_deskView;
}

Desk::~Desk()
{
	m_timerServ->stop();
	onDelete_givePeople(m_peopleCount);
}
