#include "DS/heap_monitor.h"
#pragma once
class ZaznamObce
{
public:
	ZaznamObce(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, int a12, int a13);
	~ZaznamObce();

	int getCelkovaVymera();
	int getcelkovaPolnohospodarskaPoda();
	int getornaPoda();
	int getchmelnica();
	int getvinica();
	int getzahrada();
	int getovocnysad();
	int gettrvalyTravnyPorast();
	int getnepolnospolu();
	int getlesnyPozemok();
	int getvodnaPlocha();
	int getzastavanaPlocha();
	int getostatnaPlocha();
	void setCelkovaVymera(int a);
	void setPolnohospoPoda(int a);
	void setOrnaPoda(int a);
	void setChmelnica(int a);
	void setVinica(int a);
	void setZahrada(int a);
	void setOvocnysad(int a);
	void setTrvalyTravnaty(int a);
	void setNepolno(int a);
	void setLesny(int a);
	void setVodny(int a);
	void setZastavany(int a);
	void setOstatna(int a);

private:
	int celkovaVymera;
	int celkovaPolnohospodarskaPoda;
	int ornaPoda;
	int chmelnica;
	int vinica;
	int zahrada;
	int ovocnysad;
	int trvalyTravnyPorast;
	int nepolnospolu;
	int lesnyPozemok;
	int vodnaPlocha;
	int zastavanaPlocha;
	int ostatnaPlocha;

};

