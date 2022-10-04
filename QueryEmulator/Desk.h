#pragma once

#include <QWidget>
#include "Queue.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class DeskClass; };
QT_END_NAMESPACE

class Desk : public QWidget
{
	Q_OBJECT

public:
	Desk(QWidget *parent = nullptr);
	Desk(const Desk& d);
	void UpdateQuantity(const int quantity);

	auto operator<=>(const Desk& d2) const
	{
		return this->queues.size() <=> d2.queues.size();
	}
	bool operator==(const Desk& d2) const
	{
		return this->queues.size() == d2.queues.size();
	}

	~Desk();

private:
	Ui::DeskClass *ui;
	std::vector<Queue*> queues;
};
