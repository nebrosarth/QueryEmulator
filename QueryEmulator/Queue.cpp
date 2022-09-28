#include "Queue.h"
#include "ui_Queue.h"

Queue::Queue(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::QueryClass())
{
	ui->setupUi(this);
}

Queue::~Queue()
{
	delete ui;
}
