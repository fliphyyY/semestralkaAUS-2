#include "ZaznamObce.h"
#include "DS/heap_monitor.h"



// vymera, uzemia, vyuzitie pody
// toto je iba pre jeden rok 
// pre kazdy rok jedna tabulka

ZaznamObce::ZaznamObce(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, int a12, int a13)
{
	celkovaVymera = a1;
	celkovaPolnohospodarskaPoda = a2;
	ornaPoda = a3;
	chmelnica = a4;
	vinica = a5;
	zahrada = a6;
	ovocnysad = a7;
	trvalyTravnyPorast = a8;
	nepolnospolu = a9;
	lesnyPozemok = a10;
	vodnaPlocha = a11;
	zastavanaPlocha = a12;
	ostatnaPlocha = a13;

}

ZaznamObce::~ZaznamObce()
{
}

int ZaznamObce::getCelkovaVymera()
{
	return celkovaVymera;
}

int ZaznamObce::getcelkovaPolnohospodarskaPoda()
{
	return celkovaPolnohospodarskaPoda;
}

int ZaznamObce::getornaPoda()
{
	return ornaPoda;
}

int ZaznamObce::getchmelnica()
{
	return chmelnica;
}

int ZaznamObce::getvinica()
{
	return 	vinica;
}


int ZaznamObce::getzahrada()
{
	return zahrada;
}

int ZaznamObce::getovocnysad()
{
	return ovocnysad;
}

int ZaznamObce::gettrvalyTravnyPorast()
{
	return trvalyTravnyPorast;
}

int ZaznamObce::getnepolnospolu()
{
	return nepolnospolu;
}

int ZaznamObce::getlesnyPozemok()
{
	return lesnyPozemok;
}

int ZaznamObce::getvodnaPlocha()
{
	return vodnaPlocha;
}

int ZaznamObce::getzastavanaPlocha()
{
	return zastavanaPlocha;
}

int ZaznamObce::getostatnaPlocha()
{
	return ostatnaPlocha;
}

void ZaznamObce::setCelkovaVymera(int a)
{
	this->celkovaVymera = a;
}

void ZaznamObce::setPolnohospoPoda(int a)
{
	celkovaPolnohospodarskaPoda = a;
}

void ZaznamObce::setOrnaPoda(int a)
{
	ornaPoda = a;
}

void ZaznamObce::setChmelnica(int a)
{
	chmelnica = a;
}

void ZaznamObce::setVinica(int a)
{
	vinica = a;
}

void ZaznamObce::setZahrada(int a)
{
	zahrada = a;
}

void ZaznamObce::setOvocnysad(int a)
{
	ovocnysad = a;
}

void ZaznamObce::setTrvalyTravnaty(int a)
{
	trvalyTravnyPorast = a;
}

void ZaznamObce::setNepolno(int a)
{
	nepolnospolu = a;
}

void ZaznamObce::setLesny(int a)
{
	lesnyPozemok = a;
}

void ZaznamObce::setVodny(int a)
{
	vodnaPlocha = a;
}

void ZaznamObce::setZastavany(int a)
{
	zastavanaPlocha = a;
}

void ZaznamObce::setOstatna(int a)
{
	ostatnaPlocha = a;
}
