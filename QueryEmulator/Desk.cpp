#include "Desk.h"

Desk::Desk(DeskView* view, QObject *parent)
	: QObject(parent)
{}

Desk::Desk(const Desk& d)
{
	people_count = d.people_count;
}

void Desk::UpdateQuantity(const int quantity)
{
	people_count = quantity;
}

Desk::~Desk()
{}
