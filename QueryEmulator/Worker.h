#pragma once

#include <QObject>
#include <vector>

class Desk;
class QueueEmulator;
class BTimer;
class DeskView;

class Worker : public QObject
{
	Q_OBJECT

public:
	Worker(QueueEmulator* parent = nullptr);
	void PendDeskQuantity(const int quantity); //онопняхрэ хглемхрэ йнк-бн йюяя
	void Add(Desk* desk);
	void AddPeople(const int val);
	void AddPeople2Desk(Desk* desk, const int quantity);
	void SetRunning(const bool running);
	void DeleteLast();
	void Sort();
	void StartTimerRandom();
	void UpdateMostFreeCrowded();

	void SetP(const int val);
	int GetP() const;
	void SetT(const int val);
	int GetT() const;
	~Worker();

signals:
	void changed_running(const bool running);

private:
	QueueEmulator* m_view = nullptr;
	BTimer* m_timerSpawn = nullptr;
	std::vector<Desk*> m_desks;
	DeskView* m_mostFree = nullptr;
	DeskView* m_mostCrowded = nullptr;
	bool m_isSorted = false;
	int m_p = 0;
	int m_t = 1;
	bool m_running;
	int m_sparePeople = 0;
};
