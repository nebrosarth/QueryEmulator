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
	void PendDeskQuantity(const int quantity); //онопняхрэ хглемхрэ йнк-бн йюяя
	void Add(Desk* desk);
	void DeleteLast();
	void Sort();
	void SetP(const int val);
	int GetP() const;
	void SetT(const int val);
	int GetT() const;
	~Worker();

signals:
	void quantityChanged(int quantity);
	void changed_p(const int val);
	void changed_t(const int val);

private:
	QueueEmulator* m_view;
	std::vector<Desk*> m_desks;
	bool m_isSorted = false;
	int m_p;
	int m_t;
};
