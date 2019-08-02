#include "Okres.h"
#include <iostream>
#include "DS/heap_monitor.h"






Okres::Okres(string nazov)
{
	this->nazov = nazov;
	zoznamObci = new Table_ArrayList_Sorted<string, Obec*>(functionCompare<string>);
	// kazdy okres si pamata zoznam obci ktore ho tvoria
}

Okres::~Okres()
{
	delete zoznamObci;
}

void Okres::vlozObec(Obec * o)
{
	zoznamObci->insert(o->getNazov(),o);
}

string Okres::getNazov()
{
	return this->nazov;
}

int Okres::getOvocneSady(int rok)
{
	int celkova = 0; // v pre kazdu dedinu vo vsetkych okresoch scitam ovocne sady 
	for (TableItem<string,Obec*> *tt : *zoznamObci) {// kazdy okres ma vsetky svoje obce tak to scitam 
		celkova += tt->getData()->getZaznam(rok)->getovocnysad();
	}
	return celkova; // vysledna hodnota ovocnych sadov v okrese 
}

double Okres::pomerOrnejkOvocnym(int rok)
{
	double celkovaOrna = 0.0;
	double celkoveOvocne = 0.0;
	for (TableItem<string,Obec*>*tt:*zoznamObci) { // v kazdom okrese spocitam ornu podu a ovocne sady pre konkretny rok 
		celkovaOrna += tt->getData()->getZaznam(rok)->getornaPoda();
	
		celkoveOvocne += tt->getData()->getZaznam(rok)->getovocnysad();
	
	}

	if (celkoveOvocne == 0)
	{
		return -1;
		
	}
	double vysledok = celkovaOrna * 100 / celkoveOvocne; // spravim z toho pomer a ten pomer je pre jeden konkretny okres
	return vysledok;
}

double Okres::podielLesuKVymere(int rok)
{
	double celkovaLesna = 0.0;
	double celkova = 0.0;
	for (TableItem<string, Obec*>*tt : *zoznamObci) { // to iste len ine data
		celkovaLesna += tt->getData()->getZaznam(rok)->getlesnyPozemok();
		celkova += tt->getData()->getZaznam(rok)->getCelkovaVymera();
	}
	double vysledok = celkovaLesna * 100 / celkova;
	return vysledok;
}

double Okres::zmenaOvocnychKCelkovej(int rok1, int rok2)
{// 4a
	
	double zmena = 0,a,b;
	for (TableItem<string,Obec*> *tt :*zoznamObci) {
		if (tt->getData()->getZaznam(rok1)->getCelkovaVymera() == 0 || tt->getData()->getZaznam(rok2)->getCelkovaVymera() == 0) continue; // aby som nedelil 0
		a= (double)((double)tt->getData()->getZaznam(rok1)->getovocnysad()/(double)tt->getData()->getZaznam(rok1)->getCelkovaVymera()); // toto je pomer pre jeden rok
		b= (double)((double)tt->getData()->getZaznam(rok2)->getovocnysad() / (double)tt->getData()->getZaznam(rok2)->getCelkovaVymera()); // toto pre druhy
		zmena += (a - b); //tu odcitam
	}// toto je pre kazdy okres
	return zmena;

}

double Okres::zmenaOrnejKCelkovej(int rok1, int rok2)
{//4b   to iste 
	double zmenaVR1 = 0.0, zmenaVR2 = 0.0;
	for (TableItem<string, Obec*> *tt : *zoznamObci) {
		if (tt->getData()->getZaznam(rok1)->getornaPoda() == 0 || tt->getData()->getZaznam(rok2)->getovocnysad() == 0) continue;
		zmenaVR1 += (double)((double)tt->getData()->getZaznam(rok1)->getornaPoda() / (double)tt->getData()->getZaznam(rok1)->getovocnysad());
		zmenaVR1 += (double)((double)tt->getData()->getZaznam(rok2)->getornaPoda() / (double)tt->getData()->getZaznam(rok2)->getovocnysad());

	}
	return zmenaVR1 - zmenaVR2;
}

double Okres::zmenaLesnychKCelkovej(int rok1, int rok2)
{//4c    to iste 
	double zmenaVR1 = 0.0, zmenaVR2 = 0.0;
	for (TableItem<string, Obec*> *tt : *zoznamObci) {
		if (tt->getData()->getZaznam(rok1)->getlesnyPozemok() == 0 || tt->getData()->getZaznam(rok2)->getovocnysad() == 0) continue;
		zmenaVR1 += (double)((double)tt->getData()->getZaznam(rok1)->getlesnyPozemok() / (double)tt->getData()->getZaznam(rok1)->getovocnysad());
		zmenaVR1 += (double)((double)tt->getData()->getZaznam(rok2)->getlesnyPozemok() / (double)tt->getData()->getZaznam(rok2)->getovocnysad());

	}
	return zmenaVR1 - zmenaVR2;
}

Table_ArrayList_Sorted<string, Obec*>* Okres::getZoznamObci()
{
	return zoznamObci;
}

long Okres::getCelkovu(int rok)
{
	long celkova = 0;
	for (TableItem<string,Obec*> *tt1 : *zoznamObci) {
		celkova += tt1->getData()->getZaznam(rok)->getCelkovaVymera();
	}
 	return celkova;
}

long Okres::getLesnu(int rok)
{
	long celkova = 0;
	for (TableItem<string, Obec*> *tt1 : *zoznamObci) {
		celkova += tt1->getData()->getZaznam(rok)->getlesnyPozemok();
	}
	return celkova;
}

void Okres::setId(int a)
{
	id = a;
}

int Okres::getId()
{
	return id;
}

int Okres::getPocetSlesnouKcelkovej(int rok, double percenta)
{ //prejdem vsetky obce a pre tu obec pre ktoru plati ze splna hodnotu pomeru tak zvacsim pocet
	int pocet = 0;
	for (TableItem<string,Obec*> *tt : *zoznamObci) {
		if (tt->getData()->getPodielLesuKCelkovej(rok) >= percenta) {
			pocet++;
		}
	}
	return pocet;
}

double Okres::percentaLesnejKCelkovej(int rok)
{// v okrese prejdem vsetky obce, z obce zistim lesny pozemok a postupne pre kazdu obec z okresu to takto
	double lesna = 0.0;                        // urobim a tak ziskam celkovu rozlohu lesnych pozemkov pre okres a to iste pre celkovu rozlohu 
	double celkova = 0.0;
	for (TableItem<string,Obec*> *tt : *zoznamObci) {
		lesna += tt->getData()->getZaznam(rok)->getlesnyPozemok();
		celkova += tt->getData()->getZaznam(rok)->getCelkovaVymera();
	}
	double vysledok = roundf(((lesna/celkova) * 100) * 100) / 100;
	return vysledok;

}


