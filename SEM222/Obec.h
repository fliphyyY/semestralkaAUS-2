#pragma once
#include "DS/heap_monitor.h"
#include "ZaznamObce.h"
#include <string>
#include "DS\Table_ArrayList_Sorted.h"
#include "ZaznamObyvatelstva.h"

using namespace std;
using namespace DS;
class Obec
{

	// obec si pamata v ktorom je okrese a v ktorom je kraji
	// kazda obec si pamata svoje id kvoli siestej funkcionalite
	// kazda obec vie do ktoreho okresu patri
public:
	Obec(string nazov);
	~Obec();
	string getNazov();
	void vlozZaznam(ZaznamObce *z, int rok);
	void vlozZaznamObyvatelstva(ZaznamObyvatelstva*z,int vek);
	ZaznamObyvatelstva *getZaznamObyvatelstva(int vek);
	ZaznamObce *getZaznam(int rok);
	void setId(int a);
	int getId();
	double getPodielLesuKCelkovej(int rok);
	int getPocetEkonomickyAktivnych(int volba);
	void setIdOkresu(int a);
	void setIdKraja(int a);
	int getIdOkresu();
	int getIdKraja();
	double getPercentaEOA();
	double getPercentaOrnejPody(int rok);
	double getPercentaZahrady(int rok);
	int getOrnu(int rok);
	int getOvocnySad(int rok);

private:
	int id; // id obce kvoli tomu aby mi to vybralo iba obce z toho kraja
	int idOkresu;
	int idKraja;
	string nazov;
	Table_ArrayList_Sorted<int, ZaznamObce*> *udaje; // rok je kluc, pre kazdy rok jeden zaznam, jeden stlpec z excelu
	Table_ArrayList_Sorted<int, ZaznamObyvatelstva*> *obyvatelstvo;
};  // to iste ale pre obyvatelstvo, ale kluc je minimum z toho rozpatia

