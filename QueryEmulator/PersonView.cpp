#include "PersonView.h"
#include "ui_PersonView.h"

PersonView::PersonView(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::PersonView())
{
	ui->setupUi(this);
}

PersonView::~PersonView()
{
	delete ui;
}
