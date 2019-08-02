#include "Obec.h"
#include <iostream>
#include "DS/heap_monitor.h"




Obec::Obec(string nazov)
{
	this->nazov = nazov;
	//tabulka udajov o vymere,kluc je rok 
	udaje = new Table_ArrayList_Sorted<int, ZaznamObce*>(functionCompare<int>);
	// tabulka udajov o eoa obyvatelstve,kluc je min vek,pre 0-4 je 0 pre 5-9 je 5 atd
	obyvatelstvo = new Table_ArrayList_Sorted<int, ZaznamObyvatelstva*>(functionCompare<int>);
}

Obec::~Obec()
{
	for (TableItem<int, ZaznamObce*> *tt : *udaje) {
		delete tt->getData();
		
	}
	for (TableItem<int,ZaznamObyvatelstva*> *tt : *obyvatelstvo) {
		delete tt->getData();
	}
	delete udaje;
	delete obyvatelstvo;
}

string Obec::getNazov()
{
	return this->nazov;
}
//vkladanie zaznamov do tabulky
void Obec::vlozZaznam(ZaznamObce * z, int rok)
{
	udaje->insert(rok, z);
}

void Obec::vlozZaznamObyvatelstva(ZaznamObyvatelstva * z, int vek)
{
	obyvatelstvo->insert(vek,z);
}
//vratenie zaznamu s danym klucom/rokom
ZaznamObyvatelstva * Obec::getZaznamObyvatelstva(int vek)
{
	return obyvatelstvo->operator[](vek);
}

ZaznamObce * Obec::getZaznam(int rok)
{
	return udaje->operator[](rok);
}

void Obec::setId(int a)
{
	id = a;
}

int Obec::getId()
{
	return id;
}

double Obec::getPodielLesuKCelkovej(int rok)
{//pre konkretnu obec vypocitam 
	double lesna = (double)udaje->operator[](rok)->getlesnyPozemok();// operator [] vyberam data z tabulky kluc ktory je rok 
	double celkova = (double)udaje->operator[](rok)->getCelkovaVymera();
	if(celkova == 0) return -1;
	double a = roundf(((lesna / celkova) * 100) * 100) / 100; // vypocitam percenta
	return a;
	// na dve desatine miesta to zaokruhlim, cim zvacsim tym zmansim a ostanu dve desatinu
}

int Obec::getPocetEkonomickyAktivnych(int volba)
{
	int a = 0;
	for (TableItem<int,ZaznamObyvatelstva*> *tt : *obyvatelstvo) {
		if (tt->getKey() >= 20 && tt->getKey() <= 60) { // 60-64 beriem minimum
			switch (volba) {
			case 0:
				a += tt->getData()->getSpolu();
				break;
			case 1:
				a += tt->getData()->getMuzi();
				break;
			case 2:
				a += tt->getData()->getZeny();
				break;
			}
		}
	}
	return a;
}

void Obec::setIdOkresu(int a)
{
	idOkresu = a;
}

void Obec::setIdKraja(int a)
{
	idKraja = a;
}

int Obec::getIdOkresu()
{
	return idOkresu;
}

int Obec::getIdKraja()
{
	return idKraja;
}

double Obec::getPercentaEOA()
{
	int celkove = 0;
	int aktivne = 0;
	for (TableItem<int,ZaznamObyvatelstva*> *t : *obyvatelstvo) {
		if (t->getKey() >= 20 && t->getKey() <= 60) {
			aktivne += t->getData()->getSpolu();
		}
		celkove += t->getData()->getSpolu();
	}
	double vysledok = roundf(((double)((double)aktivne / (double)celkove) * 100) * 100) / 100;
	return vysledok;
}

double Obec::getPercentaOrnejPody(int rok)
{
	return  roundf(((double)((double)udaje->operator[](rok)->getornaPoda() / (double)udaje->operator[](rok)->getCelkovaVymera()) * 100) * 100) / 100;
}

double Obec::getPercentaZahrady(int rok)
{
	return  roundf(((double)((double)udaje->operator[](rok)->getovocnysad() / (double)udaje->operator[](rok)->getCelkovaVymera()) * 100) * 100) / 100;

}

int Obec::getOrnu(int rok)
{
	return udaje->operator[](rok)->getornaPoda();
}

int Obec::getOvocnySad(int rok)
{
	return udaje->operator[](rok)->getovocnysad();
}
