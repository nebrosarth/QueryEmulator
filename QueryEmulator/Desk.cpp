#include "Desk.h"
#include "ui_Desk.h"

Desk::Desk(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::DeskClass())
{
	ui->setupUi(this);
}

Desk::Desk(const Desk& d)
{
	ui->setupUi(this);
	queues = d.queues;
}

void Desk::UpdateQuantity(const int quantity)
{
	const int delta = quantity - queues.size();
	if (delta > 0)
	{
		for (int i = 0; i < delta; ++i)
		{
			Queue* queue = new Queue(this);
			ui->QueuesLayout->addWidget(queue);
			queues.push_back(queue);
		}
	}
	else
	{
		for (int i = queues.size() + delta; i < queues.size(); ++i)
			delete queues[i];
		queues.erase(queues.end() + delta, queues.end());
		auto c = ui->QueuesLayout->children();
	}
}

Desk::~Desk()
{
	delete ui;
}
