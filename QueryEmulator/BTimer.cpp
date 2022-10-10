#include "BTimer.h"
#include "UtilsService.h"

BTimer::BTimer(QObject *parent)
	: QTimer(parent)
{}

BTimer::~BTimer()
{}

void BTimer::pause()
{
	m_remainingTime = this->remainingTime();
	this->stop();
}

void BTimer::resume()
{
	if(!this->isActive())
		this->start(m_remainingTime);
}

void BTimer::start(const int min, const int max)
{
	const int nextTime = UtilsService::GetRandomInt(min, max);
	this->start(nextTime);
}

void BTimer::start(const int msec)
{
	m_time = msec;
	QTimer::start(msec);
}
 