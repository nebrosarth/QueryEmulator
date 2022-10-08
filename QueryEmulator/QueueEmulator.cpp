#include "QueueEmulator.h"
#include "ui_QueueEmulator.h"
#include <qspinbox.h>
#include <qthread.h>
#include "Worker.h"
#include "DeskView.h"

QueueEmulator::QueueEmulator(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::QueueEmulator())
{
	ui->setupUi(this);
	m_Worker = new Worker(this);
	m_Worker->SetP(ui->sb_p->value());
	m_Worker->SetT(ui->sb_t->value() * 1000);
	QThread* thread = new QThread();
	m_Worker->moveToThread(thread);
	connect(ui->sb_n, QOverload<int>::of(&QSpinBox::valueChanged), m_Worker, [this]()
		{
			m_Worker->PendDeskQuantity(ui->sb_n->value());
		});
	connect(ui->sb_p, QOverload<int>::of(&QSpinBox::valueChanged), m_Worker, [this]()
		{
			m_Worker->SetP(ui->sb_p->value());
		});
	connect(ui->sb_t, QOverload<int>::of(&QSpinBox::valueChanged), m_Worker, [this]()
		{
			m_Worker->SetT(ui->sb_t->value() * 1000);
		});
	connect(ui->pb_PauseResume, QOverload<bool>::of(& QPushButton::toggled), m_Worker, &Worker::SetRunning);
	connect(ui->pb_PauseResume, QOverload<bool>::of(&QPushButton::toggled), this, [this](const bool running)
		{
			QString text = running ? u8"Остановить" : u8"Продолжить";
			ui->pb_PauseResume->setText(text);
		});
}

DeskView* QueueEmulator::CreateDeskView()
{
	DeskView* view = new DeskView(this);
	ui->DesksLayout->addWidget(view);
	return view;
}

void QueueEmulator::DeleteLastDeskView()
{
	const int items_count = ui->DesksLayout->count();
	auto item = ui->DesksLayout->itemAt(items_count - 1)->widget();
	if(item)
		delete item;
}

QueueEmulator::~QueueEmulator()
{
	delete ui;
}
