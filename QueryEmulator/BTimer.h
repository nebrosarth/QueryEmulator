#pragma once

#include <QTimer>

class BTimer  : public QTimer
{
	Q_OBJECT

public:
	BTimer(QObject *parent);
	~BTimer();
	void pause();
	void resume();
	void start(const int min, const int max);
	void start(const int msec);

private:
	int m_remainingTime;
};
