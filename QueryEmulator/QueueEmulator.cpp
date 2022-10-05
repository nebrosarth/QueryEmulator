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
	worker = new Worker(this);
	QThread* thread = new QThread();
	worker->moveToThread(thread);
	//connect(ui->pb_PauseResume, SIGNAL(clicked()), worker, SLOT(zaloopa()));
	//connect(ui->pb_PauseResume, &QPushButton::clicked, worker, &Worker::zaloopa);
	//thread->start();
	connect(ui->sb_n, QOverload<int>::of(&QSpinBox::valueChanged), this, [this]()
		{
			//UpdateQuantity(ui->sb_n->value());
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
	auto view = *ui->DesksLayout->children().end();
	delete view;
}

QueueEmulator::~QueueEmulator()
{
	delete ui;
}
