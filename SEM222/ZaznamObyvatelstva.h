#pragma once
#include "DS/heap_monitor.h"
class ZaznamObyvatelstva
{
public:
	ZaznamObyvatelstva(int spolu,int muzi,int zeny);
	~ZaznamObyvatelstva();
	int getSpolu();
	int getMuzi();
	int getZeny();
private:
	int zeny;
	int muzi;
	int spolu;
};

