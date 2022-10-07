#include "Desk.h"
#include "qtimer.h"
#include "UtilsService.h"

Desk::Desk(DeskView* view, QObject *parent)
	: QObject(parent)
{
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, [&]()
		{
			const int nextTime = UtilsService::GetRandomInt(0, m_maxTimeInterval);
			timer->start(nextTime);
			const int increment = UtilsService::GetRandomInt(0, m_maxPeopleIncome);
			SetPeopleCount(m_peopleCount + increment);
		});
	timer->start(m_maxTimeInterval);
}

Desk::Desk(const Desk& d)
{
	m_peopleCount = d.m_peopleCount;
}

void Desk::SetPeopleCount(const int quantity)
{
	m_peopleCount = quantity;
	changed_people(quantity);
}

void Desk::SetPeopleIncome(const int val)
{
	m_peopleCount = val;
}

void Desk::SetTimeInterval(const int val)
{
	m_maxTimeInterval = val;
}

Desk::~Desk()
{}
