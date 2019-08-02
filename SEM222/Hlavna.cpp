#include "Hlavna.h"

//komparatory,musia byt aj pre int aj pre double 
// sluzia na rozhodovaniu quick sortu ci bude roztriedenie vzostupne alebo zostupne
// cize podla coho ma triedit udaje
int vzostupnyKomparator(TableItem<string,int> &a,TableItem<string,int> &b) {
	if (a.getData() > b.getData()) { return -1; } // tu vymienam ked lave mansie ako prave 
	if (a.getData() < b.getData()) { return 1; }// nerobi nic 
	if (a.getData() == b.getData()) { return 0; } // nic neurobi 
};
int zostupnyKomparator(TableItem<string, int> &a, TableItem<string, int> &b) {
	if (a.getData() > b.getData()) { return 1; } // nevymien ide od najvacsieho po najmansie 
	if (a.getData() < b.getData()) { return -1; } // vymienam 
	if (a.getData() == b.getData()) { return 0; }
};
int vzostupnyKomparatorDouble(TableItem<string, double> &a, TableItem<string, double> &b) {
	if (a.getData() > b.getData()) { return -1; }
	if (a.getData() < b.getData()) { return 1; }
	if (a.getData() == b.getData()) { return 0; }
};
int zostupnyKomparatorDouble(TableItem<string, double> &a, TableItem<string, double> &b) {
	if (a.getData() > b.getData()) { return 1; }
	if (a.getData() < b.getData()) { return -1; }
	if (a.getData() == b.getData()) { return 0; }
};


Hlavna::Hlavna()
{
	// tabulky pre ukldanie dat o obci okresu a kraja
	// musia byt sortnute koli tomu aby bolo vyhladavanie mensie ako O(n)
	// metoda bisekcie tusim
	zoznamObci = new Table_ArrayList_Sorted<string, Obec*>(functionCompare<string>);
	zoznamOkresov = new Table_ArrayList_Sorted<string, Okres*>(functionCompare<string>);// tabulka okresov
	zoznamKrajov = new Table_ArrayList_Sorted<string, Kraj*>(functionCompare<string>);
}


Hlavna::~Hlavna()
{
	
	for (TableItem<string,Obec*> *to : * zoznamObci) {
		delete to->getData();
	}
	delete zoznamObci;
	
	for (TableItem<string,Okres*> *t : *zoznamOkresov) {
		delete t->getData();

	}
	/**/
	for (TableItem<string, Kraj*> *t : *zoznamKrajov) {
		delete t->getData();
	}

	delete zoznamOkresov;
	delete zoznamKrajov;
}

void Hlavna::nacitaj()
{
	// pomocny array list pre obce,nemozem este dat do tabulky lebo tam mi ich utriedi a nebudem
	//vediet priradit data
	ArrayList<Obec*> *zo = new ArrayList<Obec*>();
	//nacitaj obce
	ifstream subor("obceN.txt"); // iba nazvy vsetkych obci
	while (!subor.eof()) {
		string aa;
		subor >> aa;
		
		Obec *o = new Obec(aa); // vytvorim smernik na obec, a dam do arraylist a vytvorim obec s parametrom nazvom 
		zo->add(o);
	}


	// nacitanie vymery so spravnym poctom riadkov
	ifstream subor3("vymerav2.txt");
	bool koniec = false;
	while (!koniec) {
		int celkova;	
		string riadok1 = "";
		int a = 0, b = 0;
		for (Obec *o : *zo) {
			string nazov;
			//pre prvu obec 
			if (a == 0) {
				getline(subor3, riadok1); // nacitam jeden riadok 
				stringstream ss(riadok1); // stringstream to pomocou suboru 
				ss >> nazov;
				for (int i = 1996; i < 2018; i++) {
					ss >> celkova;
					// vytovrim zaznam s celkovou vymerou a zvysne docastne nastavim na 0 a nastavim
					//rok ako kluc v tabulke zaznamom pre danu obec
					o->vlozZaznam(new ZaznamObce(celkova, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), i);
					a++;
				}
			}
			// pre 2.+obce
			else if (riadok1.compare("") != 0) {
				stringstream ss(riadok1);
				ss >> nazov;
				for (int i = 1996; i < 2018; i++) {
					ss >>  celkova;
					o->vlozZaznam(new ZaznamObce(celkova, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), i);
				}
			}
			// cyklus kde si zistim ake data nacitam a podla toho setnem hodnotu
			// ak najdem celkovu vymeru znamena to ze pokracujem dalsou obcou
			while (1) {
				getline(subor3, riadok1);
				stringstream ss(riadok1);
				ss >> nazov;
				if (nazov.compare("Celkovavymerauzemiaobce-mesta(vm2)") == 0) {
					break;
				}
				else if (nazov.compare("Polnohospodarskapoda-spolu(vm2)") == 0) {
					for (int i = 1996; i < 2018; i++) {
						ss >> b;
						o->getZaznam(i)->setPolnohospoPoda(b);
					}
				}
				else if (nazov.compare("Polnohospodarskapoda-ornapoda(vm2)") == 0) {
					for (int i = 1996; i < 2018; i++) {
						ss >> b;
						o->getZaznam(i)->setOrnaPoda(b);
					}
				}
				else if (nazov.compare("Polnohospodarskapoda-chmelnica(vm2)") == 0) {
					for (int i = 1996; i < 2018; i++) {
						ss >> b;
						o->getZaznam(i)->setChmelnica(b);
					}
				}
				else if (nazov.compare("Polnohospodarskapoda-vinica(vm2)") == 0) {
					for (int i = 1996; i < 2018; i++) {
						ss >> b;
						o->getZaznam(i)->setVinica(b);
					}
				}
				else if (nazov.compare("Polnohospodarskapoda-zahrada") == 0) {
					for (int i = 1996; i < 2018; i++) {
						ss >> b;
						o->getZaznam(i)->setZahrada(b);
					}
				}
				else if (nazov.compare("Polnohospodarskapoda-ovocnysad(vm2)") == 0) {
					for (int i = 1996; i < 2018; i++) {
						ss >> b;
						o->getZaznam(i)->setOvocnysad(b);
					}
				}
				else if (nazov.compare("Polnohospodarskapoda-trvalytravnyporast(vm2)") == 0) {
					for (int i = 1996; i < 2018; i++) {
						ss >> b;
						o->getZaznam(i)->setTrvalyTravnaty(b);
					}
				}
				else if (nazov.compare("Nepolnohospodarskapoda-spolu") == 0) {
					for (int i = 1996; i < 2018; i++) {
						ss >> b;
						o->getZaznam(i)->setNepolno(b);
					}
				}
				else if (nazov.compare("Nepolnohospodarskapoda-lesnypozemok(vm2)") == 0) {
					for (int i = 1996; i < 2018; i++) {
						ss >> b;
						o->getZaznam(i)->setLesny(b);
					}
				}
				else if (nazov.compare("Nepolnohospodarskapoda-vodnaplocha(vm2)") == 0) {
					for (int i = 1996; i < 2018; i++) {
						ss >> b;
						o->getZaznam(i)->setVodny(b);
					}
				}
				else if (nazov.compare("Nepolnohospodarskapoda-zastavanaplochaanadvorie(vm2)") == 0) {
					for (int i = 1996; i < 2018; i++) {
						ss >> b;
						o->getZaznam(i)->setZastavany(b);
					}
				}
				else if (nazov.compare("Nepolnohospodarskapoda-ostatnaplocha(vm2)") == 0) {
					for (int i = 1996; i < 2018; i++) {
						ss >> b;
						o->getZaznam(i)->setOstatna(b);
					}
					//chcem skoncit cyklus po poslednej obci lebo dalsia celkova vymera uz nie je
					if (o->getNazov().compare("ZemplinskyBranc") == 0) {
						koniec = true;
						break;
					}
				}



			}
		}
	}
	//vsetky obce uz so setnutymi datami vlozim do utriedenej tabulky
	ifstream subor4("okresy-kraje.txt");
	for (Obec *o : *zo) {
		string riadok = "", obec, okres, kraj;
		bool existujeOkress = true;
		bool existujeKrajj = true;
		int kodOkresu, kodObce, kodKraja;
		getline(subor4, riadok);
		if (riadok.compare("") == 0) break;
		stringstream ss(riadok);
		ss >> kodObce>>obec >>kodOkresu >> okres >> kodKraja>> kraj;
		// obci setujem aj id kraja a okresu koli lahsiemu vzhladavaniu v 6+
		o->setId(kodObce);
		o->setIdOkresu(kodOkresu);
		o->setIdKraja(kodKraja);
		// ak neexistuje okres vytvorim novy
		if (!existujeOkres(okres)) {
			Okres *ok = new Okres(okres);
			ok->setId(kodOkresu);
			ok->vlozObec(o);
			vlozOkres(ok);
			existujeOkress = false;
		}
		else {
			zoznamOkresov->operator[](okres)->vlozObec(o);
		}
		// to iste co s okresmi
		if (!existujeKraj(kraj)) {
			Kraj *k = new Kraj(kraj);
			k->setId(kodKraja);
			k->vlozOkres(vratOkres(okres));
			vlozKraj(k);
			existujeKrajj = false;

		}
		if (!existujeOkress && existujeKrajj) {
			zoznamKrajov->operator[](kraj)->vlozOkres(vratOkres(okres));
		}

		vlozObec(o);
	}

		// kazdej obci ktoru som uz nacital vlozim zaznam oby 
		ifstream subor5("oby2.txt");
		while (!subor5.eof()) {
			string riadok,nazov;
			getline(subor5,riadok);
			stringstream ss(riadok);
			ss >> nazov;
			int spolu, zeny, muzi,nezistene;
			if (existujeObec(nazov)) {
				for (int vek = 0; vek < 110; vek += 5) {
					ss >> spolu >> muzi >> zeny>>nezistene;
					zoznamObci->operator[](nazov)->vlozZaznamObyvatelstva(new ZaznamObyvatelstva(spolu, zeny, muzi), vek);
				}

			}
			
		}
	
	
	
		delete zo;


	
}

void Hlavna::vlozObec(Obec * o)
{
	zoznamObci->insert(o->getNazov(), o);
}

void Hlavna::vlozOkres(Okres * o)
{
	zoznamOkresov->insert(o->getNazov(),o);
}

void Hlavna::vlozKraj(Kraj * k)
{
	zoznamKrajov->insert(k->getNazov(),k);
}

bool Hlavna::existujeObec(string o)
{
	for (TableItem<string, Obec*> *tt : *zoznamObci) {
		if (tt->getKey().compare(o) == 0) {
			return true;
		}
	}
	return false;
}

bool Hlavna::existujeOkres(string o)
{
	for (TableItem<string,Okres*> *tt : *zoznamOkresov) {
		if (tt->getKey().compare(o)==0) {
			return true;
		}
	}
	return false;
}

bool Hlavna::existujeKraj(string k)
{
	for (TableItem<string,Kraj*> *tt : *zoznamKrajov) {
		if (tt->getKey().compare(k) == 0) {
			return true;
		}
	}
	return false;
}



Obec * Hlavna::vratObec(string nazov)
{
	return zoznamObci->operator[](nazov);
}

Okres * Hlavna::vratOkres(string nazov)
{
	return zoznamOkresov->operator[](nazov);
}
//1
void Hlavna::vypisInformcieOObci(string nazov, int rok,int rok2)
{
	// pre kazdy rok z rozpatia rokov si vratim dany zaznam a vytiahnem si z neho konkretne informacie
	Obec *o = zoznamObci-> operator[](nazov);// z tabulky vyberam podla kluca, snerniku priradim obec ktoru som vybral 
	if (o != nullptr)
	{
		for (int i = rok; i < rok2 + 1; i++) {
			ZaznamObce *z = o->getZaznam(i);
			int vymera = z->getCelkovaVymera();
			int orna = z->getornaPoda();
			int ovocnesady = z->getovocnysad();
			int vodnaPlocha = z->getvodnaPlocha();
			int lesnnaPlocha = z->getlesnyPozemok();
			int zastavana = z->getzastavanaPlocha();
			double vodnaKuVymere = roundf(((double)((double)vodnaPlocha / (double)vymera) * 100) * 100) / 100; // roundf zaokruhluje nahor, vracia percenta
			double lesneKuVymere = roundf(((double)((double)lesnnaPlocha / (double)vymera) * 100) * 100) / 100;// prva stovka je na percenta a potom na dve desatine miesta *100 /100
			double zastavaneKuVymere = roundf(((double)((double)zastavana / (double)vymera) * 100) * 100) / 100;
			cout << "Rok : " << i << endl;
			cout << "Celkova vymera : " << vymera << "\nOrna poda : " << orna <<
				"\nOvocne sady : " << ovocnesady << "\nPodiel vodnej k celkovej : " << vodnaKuVymere <<
				"\nPodiel lesnej k celkovej : " << lesneKuVymere << "\nPodiel zastavanej k celkovej : " <<
				zastavaneKuVymere << endl;
			cout << endl;
		}
	}
	
}
//2a
void Hlavna::zoradPodlaCelkovejVymery(int rok, bool triedenie)
{
	//true triedenie znamena zostupny
	// docasna tabulka , potrebujem triedit ale nepotrebujem to triedit hned ako vlozim, potom utriedim
	Table_ArrayList_Unsorted_Sort<string, int> *docTabulka = new Table_ArrayList_Unsorted_Sort<string, int>(functionCompare<string>);
	// vytvorenie pomocnej tabulky a vlozenie dat,kluc bude nazov obci a data budu celkova vymera danej obce
	// potom budem mat tabulku kde bude nazov obce a celkova vymera
	for (TableItem<string,Obec*> *o : *zoznamObci) { //*o = table item, je to struktura kde mas nejaky kluc a nejake data
		docTabulka->insert(o->getKey(),o->getData()->getZaznam(rok)->getCelkovaVymera());// getKey() vrati kluc obce cize jej nazov
		// prejdem vsetky obce ktore mam v zozname obci a insertnem                      // o-> getData() vrati obec, komplet cela obec                                 
	}           
	                                                                                      //getZaznam(rok) vrati celkova vymera....(cely stlpec)

	//zotriedenie quickom pomocou komparatorov 
	if (triedenie) {
		docTabulka->sort(zostupnyKomparator); // komparator sa rozhoduje ci pri sortovani to ma prehodit alebo nie 
	}
	else {
		docTabulka->sort(vzostupnyKomparator);
	}
	// vypisat 3k obci na konzolu? 
	for (TableItem<string,int> *ti : *docTabulka) {
		cout << ti->getKey() << endl;
		cout << ti->getData() << endl;
	}
	delete docTabulka;
	
}
//2b
void Hlavna::zoradPodlaZastavenychKuCelkovej(int rok, bool triedenie)
{
	// to iste ako 2a
	//true triedenie znamena zostupny
	Table_ArrayList_Unsorted_Sort<string, double> *docTabulka = new Table_ArrayList_Unsorted_Sort<string, double>(functionCompare<string>);
	for (TableItem<string, Obec*> *o : *zoznamObci) {
		int celkova = o->getData()->getZaznam(rok)->getCelkovaVymera(); // zoberiem to co potrebujem // o-: getData() vrati obec, obec vrati data v danom roku
		int zastavana = o->getData()->getZaznam(rok)->getzastavanaPlocha();
		if (celkova != 0) { // niektore obce mali nulu tak preto tam je ta podmienka
			double pomer = (double)(((double)zastavana / (double)celkova)*100); // doublelebo je tam pomer 
			docTabulka->insert(o->getKey(), pomer); // a hotovy pomer insertnem do tabulky 
		}

	}


	if (triedenie) {
		docTabulka->sort(zostupnyKomparatorDouble);
	}
	else {
		docTabulka->sort(vzostupnyKomparatorDouble);
	}
	// vypisat 3k obci na konzolu? 
	for (TableItem<string, double> *ti : *docTabulka) {
		cout << ti->getKey() << endl;
		cout << ti->getData() << endl;
	}
	delete docTabulka;
}
//2c
void Hlavna::zoradPodlaZmenyOrnejKCelkovej(int rok1, int rok2, bool triedenie)
{
	//uplne rovanky princip ako 2a
	//true triedenie znamena zostupny
	Table_ArrayList_Unsorted_Sort<string, double> *docTabulka = new Table_ArrayList_Unsorted_Sort<string, double>(functionCompare<string>);
	for (TableItem<string, Obec*> *o : *zoznamObci) {
		double pomer1 = 0.0, pomer2=0.0;
		// vypocitam si pomer,moze byt aj v obci a potom staci vracat getter ale je to to iste
		// moze sa stat ze celkova vymera moze byt 0 preto tie ify
		if(o->getData()->getZaznam(rok1)->getCelkovaVymera() !=0)
		pomer1 = (double)((double)o->getData()->getZaznam(rok1)->getornaPoda()/(double)o->getData()->getZaznam(rok1)->getCelkovaVymera())*100; // zoberiem z obce v konkretnom roku data ale chcem iba
		if (o->getData()->getZaznam(rok2)->getCelkovaVymera() != 0)                                                                            // ornu podu a celkovu vymeru, je to v percentach 
		pomer2 = (double)((double)o->getData()->getZaznam(rok2)->getornaPoda() / (double)o->getData()->getZaznam(rok2)->getCelkovaVymera()) * 100; // to iste ale pre druhy rok
		docTabulka->insert(o->getKey(),(pomer1-pomer2)); // odpocitam a insertnem do tabulky 
	}

	
	if (triedenie) {
		docTabulka->sort(zostupnyKomparatorDouble);
	}
	else {
		docTabulka->sort(vzostupnyKomparatorDouble);
	}
	// vypisat 3k obci na konzolu? 
	for (TableItem<string, double> *ti : *docTabulka) {
		cout << ti->getKey() << endl;
		cout << ti->getData() << endl;
	}
	delete docTabulka;
}
//3a
void Hlavna::najOkresOvocneSady(int rok)
{
	// v okresoch si scitam pre vsetky obce ovocne sady a vlozim do tabulky s klucom nazvom okresu
	Table_ArrayList_Unsorted<string, int> *doc = new Table_ArrayList_Unsorted<string, int>(functionCompare<string>); // kluc je nazov okresu
	// v tom to pripade usorted lebo ju nebude sortovat ani nic
	for (TableItem<string,Okres*> *tt : *zoznamOkresov) { 
		doc->insert(tt->getKey(),tt->getData()->getOvocneSady(rok)); // getData() je okres ale chcem to pre konkretny rok
	}
	int najmensi = INT_MAX;
	int najvacsi = 0;
	string najv, najm;
	// prejdem vsetky data najdem max a min hodnotu zapisem si nazvy do pomocnych stringov a na konci vypisem
	for (TableItem<string,int > *tt : *doc) { // int je co som poscitaval ovocne sady a dal do tabulky 
		if (najmensi > tt->getData()) {
			najmensi = tt->getData();
			najm = tt->getKey(); // aby som vedel ktory okres tak preto kluc
		}
		if (najvacsi  < tt->getData()) {// to iste ale pre najvacsie
			najvacsi = tt->getData();
			najv = tt->getKey();
		}
	}
	cout << "Najviac ovocnych sadov ma " << najv << " v pocte " << najvacsi << endl;
	cout << "Najmenej ovocnych sadov ma " << najm << " v pocte " << najmensi << endl;
	delete doc;
}
//3b
void Hlavna::najOrnaKuOvocnej(int rok)
{
	//to iste ako 3a
	Table_ArrayList_Unsorted<string,  double> *doc = new Table_ArrayList_Unsorted<string,  double>(functionCompare<string>);
	for (TableItem<string, Okres*> *tt : *zoznamOkresov) {
		if (tt->getKey(), tt->getData()->pomerOrnejkOvocnym(rok) != -1)
		{
			doc->insert(tt->getKey(), tt->getData()->pomerOrnejkOvocnym(rok)); 
		} // do tabulky vkladam uz hotovy pomer, kolko okresov, tolko zaznamov
	
	}
	double najmensi = DBL_MAX;
    double najvacsi = 0;
	string najv, najm;
	for (TableItem<string,  double > *tt : *doc) {  // to iste ako minule
		if (najmensi > tt->getData()) {
			najmensi = tt->getData();
			najm = tt->getKey();
		}
		if (najvacsi  < tt->getData()) {
			najvacsi = tt->getData();
			najv = tt->getKey();
		}
	}
	cout << "Najvacsi pomer ma " << najv << " v pocte " << najvacsi << endl;
	cout << "Najmensi pomer ma " << najm << " v pocte " << najmensi << endl;
	delete doc;
}
// 3c
void Hlavna::najLesKuCelkovej(int rok)
{
	//to iste ako 3a
	Table_ArrayList_Unsorted<string, double> *doc = new Table_ArrayList_Unsorted<string, double>(functionCompare<string>);
	for (TableItem<string, Okres*> *tt : *zoznamOkresov) {
		doc->insert(tt->getKey(), tt->getData()->podielLesuKVymere(rok));
	}
	double najmensi = DBL_MAX;
	double najvacsi = 0;
	string najv, najm;
	for (TableItem<string, double > *tt : *doc) {
		if (najmensi > tt->getData()) {
			najmensi = tt->getData();
			najm = tt->getKey();
		}
		if (najvacsi  < tt->getData()) {
			najvacsi = tt->getData();
			najv = tt->getKey();
		}
	}
	cout << "Najvacsi pomer ma " << najv << " v pocte " << najvacsi << endl;
	cout << "Najmensi pomer ma " << najm << " v pocte " << najmensi << endl;
	delete doc;
}
//4a
void Hlavna::zoradOkresyPodlaOvocnychKCelkovej(int rok1, int rok2,bool zoradenie)
{
	// v okrese si zistim rozdiel medzi rokmi vlozim do tabulky a pomocou komparatorov roztriedim
	// metoda na najdeneie rozdielu je v okrese
	Table_ArrayList_Unsorted_Sort<string, double> *doc = new Table_ArrayList_Unsorted_Sort<string, double>(functionCompare<string>);
	for (TableItem<string,Okres*> *tt :*zoznamOkresov) {
		doc->insert(tt->getKey(), tt->getData()->zmenaOvocnychKCelkovej(rok1, rok2)); // do tabulky vlozim udaje pre vsetky okresy, uz hotovu zmenu pomerov
	}
	if (zoradenie) {
		doc->sort(zostupnyKomparatorDouble);
	}
	else {
		doc->sort(vzostupnyKomparatorDouble);
	}
	for (TableItem<string,double> *tt : *doc) {
		cout << tt->getKey() << " " << tt->getData() << endl;// sortnutu tabulku vypisem
	}
	delete doc;
}
//4b
void Hlavna::zoradOkresyPodlaOrnejKCelkovej(int rok1, int rok2, bool zoradenie)
{// to iste
	// v okrese si zistim rozdiel medzi rokmi vlozim do tabulky a pomocou komparatorov roztriedim
	// metoda na najdeneie rozdielu je v okrese
	Table_ArrayList_Unsorted_Sort<string, double> *doc = new Table_ArrayList_Unsorted_Sort<string, double>(functionCompare<string>);
	for (TableItem<string, Okres*> *tt : *zoznamOkresov) {
		doc->insert(tt->getKey(), tt->getData()->zmenaOrnejKCelkovej(rok1, rok2));
	}
	if (zoradenie) {
		doc->sort(zostupnyKomparatorDouble);
	}
	else {
		doc->sort(vzostupnyKomparatorDouble);
	}
	for (TableItem<string, double> *tt : *doc) {
		cout << tt->getKey() << " " << tt->getData() << endl;
	}
	delete doc;
}
//4c
void Hlavna::zoradOkresyPodlaLesovKCelkovej(int rok1, int rok2, bool zoradenie)
{// to iste
	// v okrese si zistim rozdiel medzi rokmi vlozim do tabulky a pomocou komparatorov roztriedim
	// metoda na najdeneie rozdielu je v okrese
	Table_ArrayList_Unsorted_Sort<string, double> *doc = new Table_ArrayList_Unsorted_Sort<string, double>(functionCompare<string>);
	for (TableItem<string, Okres*> *tt : *zoznamOkresov) {
		doc->insert(tt->getKey(), tt->getData()->zmenaLesnychKCelkovej(rok1, rok2));
	}
	if (zoradenie) {
		doc->sort(zostupnyKomparatorDouble);
	}
	else {
		doc->sort(vzostupnyKomparatorDouble);
	}
	for (TableItem<string, double> *tt : *doc) {
		cout << tt->getKey() << " " << tt->getData() << endl;
	}
	delete doc;
}


//5 b
void Hlavna::asponXOkresovLesKuCelkovej(int pocet, int rok, double percenta)
{
	// prejdem kraj ,najdem kolko okresov splna a ak viac ako zadane tak vypisem
	for (TableItem<string, Kraj*>*tt1 : *zoznamKrajov) {
		int a = tt1->getData()->getPocetOkresovSplnujucich(percenta, rok);
		if (a>= pocet) { // zavolam metodu a overim ci to splna dane kriterium ak ano tak to vypisem
			tt1->getData()->vypisOkresy(); // vypisem kazdy kraj ktory to splna a aj pocet okresov v kraji ktore to splnaju
		}

	}

}
//5a
void Hlavna::podielCelkovejKLesupreKraj(int rok, double percenta)
{
	// prejdem vsetky kraje a najdem ten s najvacsim poctom obci splnujucom kriterium 
	int pocet = 0,idKraja, pocet2 = INT_MAX, idKraja2;
	for (TableItem<string,Kraj*> *tt : *zoznamKrajov) {
		// v krajoch prejdem okresy a z toho zistim pocet obci, a prejdem vsetky kraje a viem kolko obci to splna hladam kraj kde to je najviac
		int a = tt->getData()->pocetObciSlesKuCelkovej(rok,percenta);// pocet je kolko v obci v kraji splna to kriterium 
		if (tt->getData()->pocetObciSlesKuCelkovej(rok,percenta) > pocet) {
			idKraja = tt->getData()->getId(); // tu zistim ktory kraj to bol 
			pocet = a;
		}

		if (tt->getData()->pocetObciSlesKuCelkovej(rok, percenta) < pocet2) { // pre kazdy kraj si zistim kolko obci splna kriterium a hladam taky kraj kde je obci najmenej
			idKraja2 = tt->getData()->getId();
			pocet2 = a;
		}


	}

	cout << "Najviac obci v kraji ktore splnaju kriteria" << endl;
	// vypisme obce v kraji ktore splnaju
	for (TableItem<string,Obec*> *tt : *zoznamObci) { // mam zoznam obci a kazda obec si pamata id obce a id kraja
		if (tt->getData()->getIdKraja() == idKraja && percenta <= tt->getData()->getPodielLesuKCelkovej(rok)) {
			cout << tt->getKey() << "  " << tt->getData()->getPodielLesuKCelkovej(rok) << endl;
		}
	}// prejdem vsetky obce a ak sa zhoduje id kraja ktore som nasiel pred tym a potom 
	// pre kazdu obec zistim to kriterium a ak je mansie tak vypisem aj s pomerom  

	cout << endl;
	cout << "Najmenej obci v kraji ktore splnaju kriteria" << endl;

	for (TableItem<string, Obec*> *tt : *zoznamObci) { // prejdem vsetky obce porovnam id z kraja s tym kde je najviac obci a ak ta obec splna kriteriom tak ju vypisem s tym pomerom 
		if (tt->getData()->getIdKraja() == idKraja2 && percenta <= tt->getData()->getPodielLesuKCelkovej(rok)) {
			cout << tt->getKey() << "  " << tt->getData()->getPodielLesuKCelkovej(rok) << endl;
		}
	}

}
//5c
void Hlavna::lesnaKuCelkovejKraj(int rok, double percenta)
{
	// prejdem celkove pre kraj a ak viac ako percenta vypisem
	for (TableItem<string,Kraj*> *tt : *zoznamKrajov) {
		double p = tt->getData()->podielLesnejKCelkovej(rok);
		if (p >= percenta) {
			cout << tt->getKey() << "  " << p << endl;
		}
	}
}
//6 prvy filter
void Hlavna::ekonomickyAktivniiObyPohlavie(int volba, bool zoradenie) // 0 nezadane1 muzi 2 zeny
{    // v obci mam tabulku ktora si pamata EAO obyvatelstva
	
	//tabulka s klucom nazvom obce,obec ma metodu kde vrati pocet eoa oby 20-65 a uz to len pomocou komparatora sortnem
	Table_ArrayList_Unsorted_Sort<string, int> *doc = new Table_ArrayList_Unsorted_Sort<string, int>(functionCompare<string>);
	// tabulka si pamata pre vsetky obce EAO, kluc je nazov obce a datu su EAO
	for (TableItem<string,Obec*> *tt : *zoznamObci) {
		doc->insert(tt->getKey(), tt->getData()->getPocetEkonomickyAktivnych(volba));
		// v obci mam metodu ktora podla volby vyberie 
	}

	if (zoradenie) {
		doc->sort(zostupnyKomparator); // zoradim 
	}
	else {
		doc->sort(vzostupnyKomparator);
	}
	for (TableItem<string,int> *tt : *doc) {// vypisem
		cout << tt->getKey() << "   " << tt->getData() << endl;
	}
	delete doc;
}
//6 druhy filter
void Hlavna::ekonomickyAktovnyVKraji(string kraj, string okres, int volba, bool zoradenie)
{
	// zistim ci sa zadal nejaky kraj/okres ak nie prejdem vsetky inak najdem id konkretneho
	int idKraja = -1, idOkresu = -1;
	if (kraj.compare("") != 0) idKraja = zoznamKrajov->operator[](kraj)->getId(); // ak je zadany kraj tak si zistim id toho kraja, vyberam kraj s klucom, zistim a potom s tym pracujem 
	if (okres.compare("") != 0) idOkresu = zoznamOkresov->operator[](okres)->getId(); // tak isto 
	// povkladam do tabulky obce ktore splnaju podmienky
	// obce si mapataju aj id svojho okresu a kraja
	Table_ArrayList_Unsorted_Sort<string, int> *doc = new Table_ArrayList_Unsorted_Sort<string, int>(functionCompare<string>);
	for (TableItem<string,Obec*> *tt : *zoznamObci) {
		if (idKraja == -1 && idOkresu == -1) { // nezadal som ani kraj ani okres a vlozim vsetky obce SR
			doc->insert(tt->getKey(),tt->getData()->getPocetEkonomickyAktivnych(volba));
		}
		else if (idKraja != -1 && idOkresu == -1) {// zadal som kraj a nezadal som okres tak vsetky obce kraja
			if (idKraja == tt->getData()->getIdKraja()) {
				doc->insert(tt->getKey(), tt->getData()->getPocetEkonomickyAktivnych(volba));
			}
		}
		else if (idKraja != -1 && idOkresu != -1) {// ak zadam aj kraj aj okres tak vlozim iba obce z toho okresu 
			if (idKraja == tt->getData()->getIdKraja() && idOkresu == tt->getData()->getIdOkresu()) {// obec si pamata aj svoj kraj aj svoj okres 
				doc->insert(tt->getKey(), tt->getData()->getPocetEkonomickyAktivnych(volba)); // ak najdem obec ktora zodpoveda kraju aj okresu tak vtedy ju tam vlozim 
			}
		}
	}


	if (zoradenie) {
		doc->sort(zostupnyKomparator);
	}else{
		doc->sort(vzostupnyKomparator);
	}
	for (TableItem<string,int> *tt :*doc) {
		cout << tt->getKey() << "   " << tt->getData() << endl;
	}
	delete doc;
	
}
//7
void Hlavna::zapisDoTextaku(string nazov, string kraj, string okres,int volba,int rok)
{

	
	// rovnaky princip ako v 6ke druhom filtri
	int idKraja = -1, idOkresu = -1;
	if (kraj.compare("") != 0) {
	   idKraja = zoznamKrajov->operator[](kraj)->getId(); // najdem id kraja
	}
	if (okres.compare("") != 0) {
		 idOkresu = zoznamOkresov->operator[](okres)->getId();// najdem id okresu 
	}
	// vytvoim textak s nazvom aky sa zada v parametri
	nazov += ".txt";
	ofstream subor(nazov);
	// vyhladam obec podla okresu,kraja
	for (TableItem<string,Obec*> *tt : *zoznamObci) {
		Obec *o = nullptr; // dal som null pointer, presiel som vsetky obce a ak splna podmienky tak som priradil do o
		if (idKraja == -1 && idOkresu == -1) { // ak nebol null pointer tak som to zapisal, preto aby som vedel ze ci to zapisat 
			o = tt->getData();
		}
		else if (idKraja != - 1 && idOkresu == -1) {
			if (tt->getData()->getIdKraja() == idKraja) {
				o = tt->getData();
			}
		}
		else if (idKraja != -1 && idOkresu != -1) { // zadal som aj kraj aj okres, tak vypisem obce z toho kraja
			if (tt->getData()->getIdKraja() == idKraja && tt->getData()->getIdOkresu() == idOkresu) {
				o = tt->getData();
			}
		}
		// zapisem udaje o obci do suboru v danom formate
		if (o != nullptr) {
			subor << o->getId() << ";" << o->getIdOkresu() << ";" << o->getIdKraja() << ";"
				<< o->getPocetEkonomickyAktivnych(volba) << ";" << o->getNazov() << ";" <<
				o->getZaznam(rok)->getornaPoda() << ";" << o->getZaznam(rok)->getovocnysad() << endl;
		}
	}
	subor.close();



}



void Hlavna::vyberObce(int jablone, int zemiaky, double percentaJ, double percentaZem,double eao ,string okres,string kraj,int rok)
{

	Table_ArrayList_Unsorted_Sort<string, int> *doc1 = new Table_ArrayList_Unsorted_Sort<string, int>(functionCompare<string>); // tabulka obci ktore splnaju podmienky pre zemiaky
	Table_ArrayList_Unsorted_Sort<string, int> *doc2 = new Table_ArrayList_Unsorted_Sort<string, int>(functionCompare<string>); // to iste ale pre sady 
	// to iste co v predchadzajucich 2 krokoch
	int idKraja = -1, idOkresu = -1;// nezadal kraj 
	if (kraj.compare("") != 0) { // toto znamena ze ci si chcem vybrat ze v ktorom kraji a v ktorom okrese 
		idKraja = zoznamKrajov->operator[](kraj)->getId(); // zistim id kraja z parametra co som zadal 
	}
	if (okres.compare("") != 0) {
		idOkresu = zoznamOkresov->operator[](okres)->getId();  // to iste ale s okresom 
	}
	// zistim ci je obec v danom kraji/okrese a ci eao splna zadane percenta
	for (TableItem<string, Obec*> *t : *zoznamObci) {
		Obec *o = nullptr;
		if (idKraja == -1 && idOkresu == -1 && t->getData()->getPercentaEOA() >= eao) { // v obci mam vyratane kolko ich je vsetkych EAO a vypocitam percenta
			o = t->getData(); // nezadal som kraj ani okres tak idem dalej 
		}
		else if (idKraja != -1 && idOkresu == -1) {
			if (idKraja == t->getData()->getIdKraja() && t->getData()->getPercentaEOA() >= eao) {
				o = t->getData();
			}
		}
		else if (idKraja != -1 && idOkresu != -1) {
			if (idKraja == t->getData()->getIdKraja() && idOkresu == t->getData()->getIdOkresu() &&
				t->getData()->getPercentaEOA() >= eao) {
				o = t->getData();
			}
		}
		// ak obec splna zistim ze ma dost percent pre EAO kriterium ktore som zadal
		if (o != nullptr) {
			if (o->getPercentaOrnejPody(rok) >= percentaZem) { // ak je pomer ornej pody k celkovej vacsi ako podiel ktory zadal biofarmar tak to vlozim do tabulky, je to pre zemiaky
				doc1->insert(o->getNazov(), o->getOrnu(rok)); // vzdy v ktorom roku 
			}
			if (o->getPercentaZahrady(rok) >= percentaJ) { // tato podmienka mi overuje ci pomer ovocnych sadov je vacsi ako zadane kriterium pre percentaJabloni
				doc2->insert(o->getNazov(), o->getOvocnySad(rok)); // to iste ale pre ovocny sad 
			}
		}
	}

	  if (doc1->size() > 0)
		// sortnem koli optimalizacii aby som vybral obec s najvacsou ornou/sadmi
	  {
		doc1->sort(zostupnyKomparator); // kvoli optimalizacii som to zaradil od najvacsej obce po najmansiu
		 


		cout << "Obce pre zemiaky" << endl;
		int orna = 0;// docasna premenna ktora znamena ze kolko uz biofarmar kupil od obci 
		for (TableItem<string, int> *t : *doc1) {
			int a = t->getData(); //  konkretne cislo ornej pody z tabulky pre zemiaky, kolko ma obec ornej pody 
			if (orna + a >= zemiaky) { 
				cout << t->getKey() << "  " << (zemiaky - orna) << endl;
				orna += (zemiaky - orna);
				break;
				// ak uz by som prekrocil s tou s ktorou kupujem tak kupim iba to co potrebujem 
				// aby som urobil optimalizaciu tak kupim vsetko co chcem kupit 
				

				// uz som kupil dost 
				
			}


			
			orna += t->getData();// kolko som kupil pody od jednej obce, a prechdzam vsetky obce foreachom az kym nemam dost  
			cout << t->getKey() << "  " << t->getData() << endl; // get key je nazov obce a get data kolko som kupil 

		}

		if (orna < zemiaky) {
			cout << "Nepodarilo sa nakupit dostatocne mnozstvo pre zemiaky " << endl;
		
		}
	  }

	  else {
		  cout << "Ziadna obec nesplna pozadovane kriteria pre nakup pody pre zemiaky" << endl;
	  }


	  if (doc2->size() > 0) {
		  doc2->sort(zostupnyKomparator); // to iste ale pre ovocny sad  
		  cout << "Obce pre jablone" << endl;
		  int ovocne = 0;
		  for (TableItem<string, int> *t : *doc2) {
			  int a = t->getData();
			  if (ovocne + a >= jablone) {
				  cout << t->getKey() << "   " << (jablone - ovocne) << endl;
				  ovocne += (jablone - ovocne);
				  break;


				 

				 
			  }

			 

			  ovocne += t->getData();
			  cout << t->getKey() << "   " << t->getData() << endl;

		  }


		  if (ovocne < jablone) {
			  cout << "Nepodarilo sa nakupit dostatocne mnozstvo pre jablone" << endl;
			
		  }

	  }

	  else
	  {
		  cout << "Ziadna obec nesplna pozadovane kriteria pre nakup pody pre ovocne sady" << endl;
	  }



		delete doc1;
		delete doc2;

}









