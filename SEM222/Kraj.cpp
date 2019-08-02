#include "Kraj.h"
#include <iostream>
#include "DS/heap_monitor.h"




Kraj::Kraj(string nazov)
{
	this->nazov = nazov;
	zoznamOkresov = new Table_ArrayList_Sorted<string, Okres*>(functionCompare<string>);
	zoznamObciVlesKuCelkova = new Table_ArrayList_Unsorted<string, double>(functionCompare<string>);
	zoznamOkresovSplnujucich = new Table_ArrayList_Unsorted<string, double>(functionCompare<string>); // 5b, pomocna tabulka kde su nazvy okresov a ich hodnoty ktore splnaju kriteria
}                                                                                                            

Kraj::~Kraj()
{
	
	delete zoznamOkresov;
	delete zoznamOkresovSplnujucich;
	delete zoznamObciVlesKuCelkova;
}

void Kraj::vlozOkres(Okres * o)
{
	zoznamOkresov->insert(o->getNazov(),o);
}

string Kraj::getNazov()
{
	return this->nazov;
}

void Kraj::najdiObce(int rok, double percenta)
{
	for (TableItem<string,Okres*> *tt1 :*zoznamOkresov) {
		for (TableItem<string,Obec*> *tt2 : *tt1->getData()->getZoznamObci()) {
			double p = (double)((double)(tt2->getData()->getZaznam(rok)->getlesnyPozemok() * 100) / (double)tt2->getData()->getZaznam(rok)->getCelkovaVymera());
			if (p >= percenta)
				zoznamObciVlesKuCelkova->insert(tt2->getKey(),p);
		}
	}
}

int Kraj::getPocetObciKtoreSplnaju()
{
	return zoznamObciVlesKuCelkova->size();
}

int Kraj::getPocetOkresovSplnujucich( double percenta, int rok)
{
	int pocet = 0;
	for (TableItem<string,Okres*> *tt1 : *zoznamOkresov) {
		if (tt1->getData()->percentaLesnejKCelkovej(rok)>=percenta) { // porovnam to s kriteriom ktore som zadal 
			pocet++; // ak to je splnene tak potom inkrementnem
			zoznamOkresovSplnujucich->insert(tt1->getKey(), tt1->getData()->podielLesuKVymere(rok));
		} // vytvoril som si pomocnu tabulku, kazdy okres ktory to splna tak vlozim do tej tabulky 
	}      // s pomerom a s jeho nazvom 
	return pocet;
}

double Kraj::podielLesnejKCelkovej(int rok)
{ 
	long long celkova = 0; 
	long long lesna = 0;
	for (TableItem<string,Okres*>*tt1 : *zoznamOkresov) {
		celkova += tt1->getData()->getCelkovu(rok);//v kazdom okrese som nascitaval v kazdej obci celkovu vymeru
		lesna += tt1->getData()->getLesnu(rok); // a to iste pre lesnu 
	}
	double vysledok = roundf(((double)((double)lesna /(double)celkova) * 100) * 100) / 100;
	return vysledok;  // a urobil som pomer 
}

void Kraj::vypisObce()
{
	for (TableItem<string,double> *tt1 : *zoznamObciVlesKuCelkova) {
		cout << tt1->getKey() << endl;
		cout << tt1->getData() << endl;
	}
}

void Kraj::vypisOkresy()
{
	for (TableItem<string,double> *tt1 : *zoznamOkresovSplnujucich) {
		cout << tt1->getKey() << endl;
		cout << tt1->getData() << endl;
	}
}

void Kraj::setId(int a)
{
	id = a;
}

int Kraj::getId()
{
	return id;
}

int Kraj::pocetObciSlesKuCelkovej(int rok, double percenta)
{ // pocet obci ktore splnaju kriterium v okrese, konkretne obce scitavam
	// okres si pamata obce a v kraji prejdem kazdy okres 
	// v kazdom okrese zistim kolko podmienok splna pozadovane kriterium 
	//scitavam teraz obce vo vsetkych okresoch ktore splnaju podmienku
	int pocet = 0;
	for (TableItem<string,Okres*> *tt : *zoznamOkresov) {
		pocet += tt->getData()->getPocetSlesnouKcelkovej(rok,percenta);
	}
	return pocet;
}






