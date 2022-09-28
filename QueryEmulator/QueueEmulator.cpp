#include "QueueEmulator.h"
#include "ui_QueueEmulator.h"
#include <qspinbox.h>

QueueEmulator::QueueEmulator(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::QueueEmulator())
{
	ui->setupUi(this);

	connect(ui->sb_n, QOverload<int>::of(&QSpinBox::valueChanged), this, [this]()
		{
			UpdateQuantity(ui->sb_n->value());
		});
}

void QueueEmulator::UpdateQuantity(const int quantity)
{
	const int delta = quantity - desks.size();
	if (delta > 0)
	{
		for (int i = 0; i < delta; ++i)
		{
			Desk* desk = new Desk(this);
			desk->UpdateQuantity(quantity);
			ui->DesksLayout->addWidget(desk);
			desks.push_back(desk);
		}
	}
	else
	{
		for (int i = desks.size() + delta; i < desks.size(); ++i)
			delete desks[i];
		desks.erase(desks.end() + delta, desks.end());
		auto c = ui->DesksLayout->children();
	}
}

QueueEmulator::~QueueEmulator()
{
	for (int i = 0; i < desks.size(); ++i)
	{
		delete desks[i];
	}
	delete ui;
}
