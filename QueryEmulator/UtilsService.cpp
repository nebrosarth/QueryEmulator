#include "UtilsService.h"

UtilsService::UtilsService(QObject *parent)
	: QObject(parent)
{}

UtilsService::~UtilsService()
{}

int UtilsService::GetRandomInt(const int min, const int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}
