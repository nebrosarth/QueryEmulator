#pragma once

#include <QObject>
#include "DeskView.h"

class BTimer;

class Desk  : public QObject
{
	Q_OBJECT

public:
	Desk(DeskView* view, QObject *parent=nullptr);
	Desk(const Desk& d);
	void SetPeopleCount(const int quantity);
	void DeltaPeopleCount(const int delta);
	void SetRunning(const bool running);
	void StartTimerRandom();

	auto operator<=>(const Desk& d2) const
	{
		return this->m_peopleCount <=> d2.m_peopleCount;
	}
	bool operator==(const Desk& d2) const
	{
		return this->m_peopleCount == d2.m_peopleCount;
	}
	Desk& operator=(const Desk& DeskView)
	{
		m_peopleCount = DeskView.m_peopleCount;
		/*...*/
		return *this;
	}

	~Desk();

signals:
	void changed_people(const int val);

private:
	DeskView* m_deskView;
	BTimer* m_timerServ;
	int timer_increment = 0;
	int m_peopleCount = 0;
	bool m_running = true;
};
