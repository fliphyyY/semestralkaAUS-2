#include "DS/heap_monitor.h"
#include "DS/ArrayList.h"
#include "Hlavna.h"

using namespace DS;
int main() {
	initHeapMonitor();
	Hlavna *h = new Hlavna();
	cout << "nacitavam data" << endl;
	h->nacitaj();
	cout << "uspesne nacitane" << endl;
	char klavesnica = '0';
	while (klavesnica != 'k') {

		if (klavesnica == '0') {

			cout << "1----------------------Vyhladanie obce---------------------------------1" << endl;
			cout << "2----------------------Zoradenie vsetkych obci-------------------------2" << endl;
			cout << "3----------------------Vyhladanie okresu-------------------------------3" << endl;
			cout << "4----------------------Zoradenie okresov na zaklade--------------------4" << endl;
			cout << "5----------------------Vyhladanie krajov-------------------------------5" << endl;
			cout << "6----------------------Zoradenie obci podla EAO------------------------6" << endl;
			cout << "7----------------------Zapis do textoveho suboru-----------------------7" << endl;
			cout << "8----------------------Rozhodnutie Biofarmara--------------------------8" << endl;


		}


		if (klavesnica == '1')
		{
			int rok1, rok2;
			string nazov;
			cout << "Zadavajte roky z rozpatia 1996 az 2017 !!!" << endl;
			int rokP = 0;
			while (rokP < 1996 || rokP > 2017)
			{
				
				cout << "Zadaj prvy rok z rozpatia: ";
				cin >> rokP;
			}
			rok1 = rokP;
			cout << "Druhy rok z rozpatia musi byt vacsi ako prvy rok z rozpatia !!!" << endl;
			cout << "Zadaj druhy rok z rozpatia: ";
			cin >> rok2;
			cout << "Zadaj nazov obce: ";
			cin >> nazov;
			cout << endl;
			h->vypisInformcieOObci(nazov, rok1, rok2);

		}

		if (klavesnica == '2')
		{
			int rok1, rok2;
			char volba;
			bool zostupne;
			cout << "Vyber moznost:" << endl;
			cout << "Zoradenie obci podla celkovej vymery(a)" << endl;
			cout << "Zoradenie podla pomeru zastavanej k celkovej(b) " << endl;
			cout << "Podla zmeny podielu  vymery ornej pody k celkovej(c) " << endl;
			cin >> volba;
			if (volba == 'a') {
				cout << "Ak zostupne(0) inak (1): ";
				cin >> zostupne;
				cout << endl;
				cout << "Zadavajte roky z rozpatia 1996 az 2017 !!!" << endl;
				cout << "V ktorom roku: ";
				cin >> rok1;
				h->zoradPodlaCelkovejVymery(rok1, zostupne);
			}
			else if (volba == 'b') {
				cout << "Ak zostupne(0) inak (1): " << endl;
				cin >> zostupne;
				cout << "Zadavajte roky z rozpatia 1996 az 2017 !!!" << endl;
				cout << "V ktorom roku: ";
				cin >> rok1;
				h->zoradPodlaZastavenychKuCelkovej(rok1, zostupne);
			}
			else if (volba == 'c') {
				cout << "Ak zostupne(0) inak (1): ";
				cin >> zostupne;
				cout << "V ktorom roku: ";
				cout << "Zadavajte roky z rozpatia 1996 az 2017 !!!" << endl;
				cin >> rok1;
				cout << "Zadajte rok 2: ";
				cin >> rok2;
				h->zoradPodlaZmenyOrnejKCelkovej(rok1, rok2, zostupne);
			}

		}

		if (klavesnica == '3')
		{
			int rok;
			char volba;
			cout << "Zadavajte roky z rozpatia 1996 az 2017 !!!" << endl;
			cout << "Zadaj rok: ";
			cin >> rok;
			cout << "(a) Najvacsia a najmensia celkova vymera ovocny sadov" << endl;
			cout << "(b) Najvacsi a najmensi podiel celkovej vymeri ornej pody okresu voci celkovej vymere ovocnych sadov okresu" << endl;
			cout << "(c) Najvacsi a najmensi podiel vymery lesov voci celkovej vymere okresu" << endl;
			cin >> volba;
			if (volba == 'a') {
				h->najOkresOvocneSady(rok);
			}
			else if (volba == 'b') {
				h->najOrnaKuOvocnej(rok);
			}
			else if (volba == 'c') {
				h->najLesKuCelkovej(rok);
			}


		}

		if (klavesnica == '4')
		{
			int rok1, rok2;
			char volba;
			bool zostupne;
			cout << "Zadavajte roky z rozpatia 1996 az 2017 !!!" << endl;
			cout << "Zadaj prvy rok z rozpatia: ";
			cin >> rok1;
			cout << "Druhy rok z rozpatia musi byt vacsi ako prvy rok z rozpatia !!!" << endl;
			cout << "Zadaj druhy rok z rozpatia: ";
			cin >> rok2;
			cout << "Ak zostupne(1) inak (0)" << endl;
			cin >> zostupne;
			cout << "Volba a - ovocne k celkovej, b - orna k celkovej,c - lesy k celkovej" << endl;
			cin >> volba;
			if (volba == 'a') {
				h->zoradOkresyPodlaOvocnychKCelkovej(rok1, rok2, zostupne);
			}
			else if (volba == 'b') {
				h->zoradOkresyPodlaOrnejKCelkovej(rok1, rok2, zostupne);
			}
			else if (volba == 'c') {
				h->zoradOkresyPodlaLesovKCelkovej(rok1, rok2, zostupne);
			}

		}

		if (klavesnica == '5')
		{// pre kazdu obec v okrese zistim hodnotu pomeru, ak splna tak zvacsim pocet obci ktore splnaju
			// v tom okrese 
			int rok, pocet;
			char volba;
			double percenta;
			cout << "Zadaj volbu: " << endl;
			cin >> volba;
			cout << "Zadaj rok: " << endl;
			cin >> rok;
			if (volba == 'a') {
				cout << "Zadaj percenta" << endl;
				cin >> percenta;
				h->podielCelkovejKLesupreKraj(rok, percenta);
			}
			else if (volba == 'b') {
				cout << "Zadaj pocet okresov" << endl;
				cin >> pocet;
				cout << "Zadaj percenta" << endl;
				cin >> percenta;
				h->asponXOkresovLesKuCelkovej(pocet, rok, percenta);
			}
			else if (volba == 'c') {
				cout << "Zadaj percenta" << endl;
				cin >> percenta;
				h->lesnaKuCelkovejKraj(rok, percenta);
			}

		}

		if (klavesnica == '6')
		{
			char vstup;
			cout << "Zoradenie obci na zaklade poctu EAO: ";
			cin >> vstup;
			if (vstup == 'a')
			{


				int volba;
				bool zoradenie;
				cout << "Vyber pohlavie 0-oboje,1-muzi,2-zeny" << endl;
				cin >> volba;
				cout << "Vyber zoradenie 0 zostupne,1 vzostupne" << endl;
				cin >> zoradenie;
				h->ekonomickyAktivniiObyPohlavie(volba, zoradenie);
			}

			else if (vstup == 'b')
			{

				string kraj = "a", okres = "a";// nic nezadavam a
				int volba;
				bool zoradenie;
				cout << "Zadaj kraj" << endl;
				cin >> kraj;
				cout << "Zadaj okres" << endl;
				cin >> okres;
				cout << "Zadaj volbu" << endl;
				cin >> volba;
				cout << "Zadaj zoradenie" << endl;
				cin >> zoradenie;
				if (kraj.compare("a") == 0) kraj = "";
				if (okres.compare("a") == 0) okres = "";
				h->ekonomickyAktovnyVKraji(kraj, okres, volba, zoradenie);

			}







		}



		if (klavesnica == '7')
		{



			string nazov, okres = "a", kraj = "a";
			int volba, rok;
			cout << "Zadaj nazov suboru " << endl;
			cin >> nazov;
			cout << "Zadaj nazov kraja" << endl;
			cin >> kraj;
			cout << "Zadaj nazov okresu" << endl;
			cin >> okres;
			cout << "0 - vsetci eko , 1 - muzi,2 - zeny" << endl;
			cin >> volba;
			cout << "Rok" << endl;
			cin >> rok;
			if (okres.compare("a") == 0) okres = "";
			if (kraj.compare("a") == 0) kraj = "";
			h->zapisDoTextaku(nazov, kraj, okres, volba, rok);


		}


		if (klavesnica == '8')
		{


			string kraj, okres;
			double percentaJ, percentaZ, eao;
			int orna, ovocny, rok;
			cout << "Zadaj kraj" << endl;
			cin >> kraj;
			cout << "Zadaj okres" << endl;
			cin >> okres;
			cout << "Kolko potrebuje ornej" << endl;
			cin >> orna;
			cout << "Kolko potrebuje sadov" << endl;
			cin >> ovocny;
			cout << "Percenta jabloni" << endl;
			cin >> percentaJ;
			cout << "Percenta zemiakov" << endl;
			cin >> percentaZ;
			cout << "Percenta eao" << endl;
			cin >> eao;
			cout << "Rok" << endl;
			cin >> rok;
			if (kraj.compare("a") == 0) kraj = "";
			if (okres.compare("a") == 0) okres = "";
			h->vyberObce(ovocny, orna, percentaJ, percentaZ, eao, okres, kraj, rok);

		}
		cin >> klavesnica;
	}


	delete h;
	return 0;
}
