#pragma once
#include "Obec.h"
#include "DS\Table_ArrayList_Sorted.h"
#include "DS/Table_ArrayList_Unsorted_Sort.h"
#include "Okres.h"
#include "Kraj.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <algorithm>
#include "DS\Array.h"

using namespace std;
class Hlavna
{
public:
	Hlavna();
	~Hlavna();
	void nacitaj();
	void vlozObec(Obec *o);
	void vlozOkres(Okres *o);
	void vlozKraj(Kraj *k);
	bool existujeObec(string o);
	bool existujeOkres(string o);
	bool existujeKraj(string k);
	Obec *vratObec(string nazov);
	Okres *vratOkres(string nazov);
	void vypisInformcieOObci(string nazov,int rok,int rok2);
	void zoradPodlaCelkovejVymery(int rok,bool triedenie);
	void zoradPodlaZastavenychKuCelkovej(int rok,bool triedenie);
	void zoradPodlaZmenyOrnejKCelkovej(int rok1,int rok2,bool triedenie);
	void najOkresOvocneSady(int rok);
	void najOrnaKuOvocnej(int rok);
	void najLesKuCelkovej(int rok);
	void zoradOkresyPodlaOvocnychKCelkovej(int rok1,int rok2,bool zoradenie);
	void zoradOkresyPodlaOrnejKCelkovej(int rok1, int rok2, bool zoradenie);
	void zoradOkresyPodlaLesovKCelkovej(int rok1, int rok2, bool zoradenie);
	void krajSNajviacAnajmenejObcami(int rok,double percenta);
	void asponXOkresovLesKuCelkovej(int pocet,int rok,double percenta);
	void podielCelkovejKLesupreKraj(int rok,double percenta);
	void lesnaKuCelkovejKraj(int rok,double percenta);
	void ekonomickyAktivniiObyPohlavie(int volba, bool zoradenie);
	void ekonomickyAktovnyVKraji(string kraj,string okres,int volba,bool zoradenie);
	void zapisDoTextaku(string nazov,string kraj,string okres,int volba,int rok);
	void vyberObce(int jablone,int zemiaky,double percentaJ,double percentaZem,double eoa,string okres,string kraj,int rok);


private:
	Table_ArrayList_Sorted<string, Obec*> *zoznamObci;
	Table_ArrayList_Sorted<string, Okres*> *zoznamOkresov;
	Table_ArrayList_Sorted<string, Kraj*> *zoznamKrajov;


};

