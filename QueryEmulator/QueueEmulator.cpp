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
			Desk desk = Desk(this);
			desk.UpdateQuantity(quantity);
			ui->DesksLayout->addWidget(&desk);
			desks.insert(std::move(desk));
		}
	}
	else
	{
		auto it = desks.end();
		for (int i = 0; i < -delta; ++i)
		{
			it = desks.erase(it);
		}
		auto c = ui->DesksLayout->children();
	}
}

QueueEmulator::~QueueEmulator()
{
	delete ui;
}
