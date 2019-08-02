#include "ZaznamObyvatelstva.h"
#include "DS/heap_monitor.h"



ZaznamObyvatelstva::ZaznamObyvatelstva(int spolu, int muzi, int zeny)
{
	this->spolu = spolu;
	this->muzi = muzi;
	this->zeny = zeny;
}

ZaznamObyvatelstva::~ZaznamObyvatelstva()
{
}

int ZaznamObyvatelstva::getSpolu()
{
	return spolu;
}

int ZaznamObyvatelstva::getMuzi()
{
	return muzi;
}

int ZaznamObyvatelstva::getZeny()
{
	return zeny;
}
