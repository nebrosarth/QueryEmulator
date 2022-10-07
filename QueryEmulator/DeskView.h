#pragma once

#include <QWidget>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class DeskView; };
QT_END_NAMESPACE

class DeskView : public QWidget
{
	Q_OBJECT

public:
	DeskView(QWidget *parent = nullptr);
	void SetPeopleCount(const int quantity); //хглемхрэ йнк-бн йюяя

	~DeskView();

private:
	Ui::DeskView *ui;
};
