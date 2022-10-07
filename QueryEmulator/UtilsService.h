#pragma once

#include <QObject>
#include <random>

class UtilsService  : public QObject
{
	Q_OBJECT

public:
	UtilsService(QObject *parent);
	~UtilsService();
	static int GetRandomInt(const int min, const int max);

private:
	std::mt19937 m_randomGenerator;
};
