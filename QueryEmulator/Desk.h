#pragma once

#include <QObject>
#include "DeskView.h"

class Desk  : public QObject
{
	Q_OBJECT

public:
	Desk(DeskView* view, QObject *parent=nullptr);
	Desk(const Desk& d);
	void SetPeopleCount(const int quantity);
	void SetPeopleIncome(const int val);
	void SetTimeInterval(const int val);

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
	QTimer* timer;
	int m_peopleCount = 1;
	bool m_running = true;
	int m_maxPeopleIncome = 0;
	int m_maxTimeInterval = 1000;
};
