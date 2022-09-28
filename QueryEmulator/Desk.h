#pragma once

#include <QWidget>
#include "Queue.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class DeskClass; };
QT_END_NAMESPACE

class Desk : public QWidget
{
	Q_OBJECT

public:
	Desk(QWidget *parent = nullptr);
	void UpdateQuantity(const int quantity);
	~Desk();

private:
	Ui::DeskClass *ui;
	std::vector<Queue*> queues;
};
