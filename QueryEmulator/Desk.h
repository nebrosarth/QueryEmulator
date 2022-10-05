#pragma once

#include <QObject>
#include "DeskView.h"

class Desk  : public QObject
{
	Q_OBJECT

public:
	Desk(DeskView* view, QObject *parent=nullptr);
	Desk(const Desk& d);
	void UpdateQuantity(const int quantity);

	auto operator<=>(const Desk& d2) const
	{
		return this->people_count <=> d2.people_count;
	}
	bool operator==(const Desk& d2) const
	{
		return this->people_count == d2.people_count;
	}
	Desk& operator=(const Desk& DeskView)
	{
		people_count = DeskView.people_count;
		/*...*/
		return *this;
	}

	~Desk();

private:
	int people_count = 0;
};
