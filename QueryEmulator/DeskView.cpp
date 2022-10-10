#include "DeskView.h"
#include "ui_DeskView.h"
#include "PersonView.h"

DeskView::DeskView(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::DeskView())
{
	ui->setupUi(this);
	connect(ui->sb_maxServTime, &QSpinBox::valueChanged, ui->sb_minServTime, [this]()
		{
			ui->sb_minServTime->setMaximum(ui->sb_maxServTime->value());
		});
	const int layoutSize = ui->QueuesLayout->count();
	ui->l_extra->setText("");
}

void DeskView::SetPeopleCount(const int quantity)
{
	const int layoutSize = ui->QueuesLayout->count();
	const int extra = quantity - m_maxClients > 0 ? quantity - m_maxClients : 0;
	const int delta = quantity - extra - layoutSize;

	if (delta > 0)
	{
		for (int i = 0; i < delta; ++i)
		{
			PersonView* person = new PersonView(this);
			ui->QueuesLayout->addWidget(person);
		}
	}
	else
	{
		for (int i = 0; i < -delta; ++i)
		{
			auto q = ui->QueuesLayout->itemAt(0)->widget();
			delete q;
		}
	}
	QString extra_text = extra ? "+" + QString::number(extra) : "";
	ui->l_extra->setText(extra_text);
}

int DeskView::GetMinServTime() const
{
	return ui->sb_minServTime->value() * 1000;
}

int DeskView::GetMaxServTime() const
{
	return ui->sb_maxServTime->value() * 1000;
}

Ui::DeskView* DeskView::GetUI() const
{
	return ui;
}

DeskView::~DeskView()
{
	delete ui;
}
