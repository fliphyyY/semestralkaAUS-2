#pragma once
#include "DS/heap_monitor.h"
#include "Obec.h"
#include "DS/Table_ArrayList_Sorted.h"
#include "DS/Table_ArrayList_Unsorted_Sort.h"

class Okres
{
public:
	Okres(string nazov);
	~Okres();
	void vlozObec(Obec *o);
	string getNazov();
	int getOvocneSady(int rok);
	double pomerOrnejkOvocnym(int rok);
	double podielLesuKVymere(int rok);
	double zmenaOvocnychKCelkovej(int rok1,int rok2);
	double zmenaOrnejKCelkovej(int rok1,int rok2);
	double zmenaLesnychKCelkovej(int rok1,int rok2);
	Table_ArrayList_Sorted<string, Obec*> *getZoznamObci();
	long getCelkovu(int rok);
	long getLesnu(int rok);
	void setId(int a);
	int getId();
	int getPocetSlesnouKcelkovej(int rok,double percenta);
	double percentaLesnejKCelkovej(int rok);

private:
	int id;
	string nazov;
	Table_ArrayList_Sorted<string, Obec*> *zoznamObci;
};

