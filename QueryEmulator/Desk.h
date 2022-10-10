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
	void suicide() { delete this; }

	auto operator<=>(const Desk& d2) const
	{
		return this->m_peopleCount <=> d2.m_peopleCount;
	}
	//bool operator<(const Desk& d2) const
	//{
	//	return this->m_peopleCount < d2.m_peopleCount;
	//}

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
	DeskView* GetView() const;
	~Desk();

signals:
	void changed_people(const int val);
	void onDelete_givePeople(const int val);

private:
	DeskView* m_deskView = nullptr;
	BTimer* m_timerServ = nullptr;
	int timer_increment = 0;
	int m_peopleCount = 0;
	bool m_running = true;
	double m_avgTime = 0;
	long m_passedClients = 0;
};
