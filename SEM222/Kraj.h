#pragma once
#include "Okres.h"
#include "DS/Table_ArrayList_Sorted.h"
#include "DS/Table_ArrayList_Unsorted.h"
#include <iostream>
using namespace std;
class Kraj
{
public:
	Kraj(string nazov);
	~Kraj();
	void vlozOkres(Okres *o);
	string getNazov();
	void najdiObce(int rok,double percenta);
	int getPocetObciKtoreSplnaju();
	int getPocetOkresovSplnujucich(double percenta,int rok);
	double podielLesnejKCelkovej(int rok);
	void vypisObce();
	void vypisOkresy();
	void setId(int a);
	int getId();
	int pocetObciSlesKuCelkovej(int rok,double percenta);
private:
	int id;
	string nazov;
	Table_ArrayList_Sorted<string, Okres*> *zoznamOkresov;
	Table_ArrayList_Unsorted<string, double> *zoznamObciVlesKuCelkova;
	Table_ArrayList_Unsorted<string, double> *zoznamOkresovSplnujucich;
};

