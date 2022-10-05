#include "DeskView.h"
#include "ui_DeskView.h"
#include "Queue.h"

DeskView::DeskView(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::DeskView())
{
	ui->setupUi(this);
}

void DeskView::UpdateQuantity(const int quantity)
{
	const int delta = quantity - ui->QueuesLayout->children().count();
	if (delta > 0)
	{
		for (int i = 0; i < delta; ++i)
		{
			Queue* queue = new Queue(this);
			ui->QueuesLayout->addWidget(queue);
		}
	}
	else
	{
		for (int i = 0; i < -delta; ++i)
		{
			auto q = ui->QueuesLayout->children().end()[0];
			delete q;
		}
	}
}

DeskView::~DeskView()
{
	delete ui;
}
