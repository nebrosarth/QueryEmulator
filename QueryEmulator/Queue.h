#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class QueryClass; };
QT_END_NAMESPACE

class Queue : public QWidget
{
	Q_OBJECT

public:
	Queue(QWidget *parent = nullptr);
	~Queue();

private:
	Ui::QueryClass *ui;
};
