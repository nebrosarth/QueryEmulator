#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class PersonView; };
QT_END_NAMESPACE

class PersonView : public QWidget
{
	Q_OBJECT

public:
	PersonView(QWidget *parent = nullptr);
	~PersonView();

private:
	Ui::PersonView *ui;
};
