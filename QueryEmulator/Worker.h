#pragma once

#include <QObject>
#include <vector>

class Desk;
class QueueEmulator;
class BTimer;

class Worker : public QObject
{
	Q_OBJECT

public:
	Worker(QueueEmulator* parent = nullptr);
	void PendDeskQuantity(const int quantity); //онопняхрэ хглемхрэ йнк-бн йюяя
	void Add(Desk* desk);
	void AddPeople(Desk* desk, const int quantity);
	void SetRunning(const bool running);
	void DeleteLast();
	void Sort();
	void StartTimerRandom();

	void SetP(const int val);
	int GetP() const;
	void SetT(const int val);
	int GetT() const;
	~Worker();

signals:
	void changed_running(const bool running);

private:
	QueueEmulator* m_view;
	BTimer* m_timerSpawn;
	std::vector<Desk*> m_desks;
	bool m_isSorted = false;
	int m_p = 0;
	int m_t = 1;
	bool m_running;
};
