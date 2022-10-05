#pragma once

#include <QObject>
#include <vector>

class Desk;
class QueueEmulator;

class Worker : public QObject
{
	Q_OBJECT

public:
	Worker(QueueEmulator* parent = nullptr);
	void SetDeskQuantity(const int quantity); //хглемхрэ йнк-бн йюяя
	void Add(Desk& desk);
	void DeleteLast();
	void Sort();
	~Worker();

signals:
	void quantityChanged(int quantity);

private:
	QueueEmulator* emu;
	std::vector<Desk> desks;
	bool is_sorted = false;
};
