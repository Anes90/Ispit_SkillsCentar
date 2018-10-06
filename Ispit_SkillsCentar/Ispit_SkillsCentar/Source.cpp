#include <iostream>
using namespace std;
//narednu liniju code-a ignorisite, osim u slucaju da vam bude predstavljala smetnje u radu
#pragma warning(disable:4996)

enum enumKursevi { HtmlCSSJavaScript, SoftwareEngeneeringFundamentals, MasteringSQL, WindowsSecurity };
char *crt = "\n--------------------------------------------\n";
char *Kursevi_[] = { "HtmlCSSJavaScript", "SoftwareEngeneeringFundamentals", "MasteringSQL", "WindowsSecurity" };

struct Datum {
	int * _dan, *_mjesec, *_godina;
	void Unos(int d, int m, int g) {
		_dan = new int(d);
		_mjesec = new int(m);
		_godina = new int(g);
	}
	void Ispis() { cout << *_dan << "/" << *_mjesec << "/" << *_godina << endl; }
	void Dealociraj() { delete _dan; delete _mjesec; delete _godina; }
	bool ProvjeraDatuma(Datum datum) {
		if (*datum._godina > *_godina)
			return true;
		else if (*datum._godina == *_godina && *datum._mjesec > *_mjesec)
			return true;
		else if (*datum._mjesec == *_mjesec && *datum._dan > *_dan)
			return true;
		else
			return false;
	}
	bool ProvjeraDatuma5dana(Datum datum) {
		if (*datum._godina > *_godina)
			return true;
		else if (*datum._godina == *_godina && *datum._mjesec > *_mjesec)
			return true;
		else if (*datum._mjesec == *_mjesec && *datum._dan - *_dan >5)
			return true;
		else
			return false;
	}
};

struct Kurs {
	enumKursevi _kurs;
	Datum _pocetak;
	Datum _kraj;
	char * _imePredavaca;
	bool _aktivan;//SVAKI KURS JE NA POCETKU AKTIVAN
	void Unos(enumKursevi Kurs, Datum prvi, Datum drugi, char* naziv) {
		_kurs = Kurs;
		_pocetak.Unos(*prvi._dan, *prvi._mjesec, *prvi._godina);
		_kraj.Unos(*drugi._dan, *drugi._mjesec, *drugi._godina);
		int size = strlen(naziv) + 1;
		_imePredavaca = new char[size];
		strcpy_s(_imePredavaca, size, naziv);
		_aktivan = true;
	}
	void Dealociraj() {
		_pocetak.Dealociraj();
		_kraj.Dealociraj();
		delete[] _imePredavaca; _imePredavaca = nullptr;
	}
	void Ispis() {
		cout << "Naziv kursa : " << Kursevi_[_kurs] << endl;
		cout << "Datum pocetka kursa : ";
		_pocetak.Ispis();
		cout << "Datum zavrsetka kursa : ";
		_kraj.Ispis();
		cout << "Ime predavaca : " << _imePredavaca << endl;
	}
};
struct Polaznik {
	int _polaznikID;
	char * _imePrezime;
	void Unos(int polaznikID, char * imePrezime) {
		_polaznikID = polaznikID;
		int size = strlen(imePrezime) + 1;
		_imePrezime = new char[size];
		strcpy_s(_imePrezime, size, imePrezime);
	}
	void Ispis() { cout << "ID polaznika " << _polaznikID << " " << "Ime prezime polaznika : " << _imePrezime << endl; }
	void Dealociraj() {
		delete[] _imePrezime; _imePrezime = nullptr;
	}
};
struct Polaganja {
	Polaznik _polaznik;
	Kurs _kurs;
	Datum _datumPolaganja;
	float _ostvareniUspjeh;
	bool Uspjeh;
	void Unos(Polaznik polaznik, Kurs kurs, Datum datum, float uspjeh) {
		_polaznik.Unos(polaznik._polaznikID, polaznik._imePrezime);
		_kurs.Unos(kurs._kurs, kurs._pocetak, kurs._kraj, kurs._imePredavaca);
		_datumPolaganja.Unos(*datum._dan, *datum._mjesec, *datum._godina);
		_ostvareniUspjeh = uspjeh;
		if (_ostvareniUspjeh >= 55)
			Uspjeh = true;
		else
			Uspjeh = false;
	}
	void Dealociraj() {
		_polaznik.Dealociraj();
		_kurs.Dealociraj();
		_datumPolaganja.Dealociraj();
	}
	void Ispis() {
		_polaznik.Ispis();
		_kurs.Ispis();
		cout << "Datum polaganja : ";
		_datumPolaganja.Ispis();
		cout << "Ostvareni uspjeh : " << _ostvareniUspjeh << endl;
	}
};
struct SkillsCentar {
	char * _nazivCentra;
	Kurs * _kursevi[50];//JEDAN EDUKACIJSKI CENTAR MOZE NUDITI NAJVISE 50 KURSEVA
	int _trenutnoKurseva;
	Polaganja * _polaganja;
	int _trenutnoPolaganja;
	void Unos(char *naziv) {
		int size = strlen(naziv) + 1;
		_nazivCentra = new char[size];
		strcpy_s(_nazivCentra, size, naziv);
		_trenutnoKurseva = 0;
		_trenutnoPolaganja = 0;
	}
	bool DodajKurs(Kurs kurs) {
		if (_trenutnoKurseva >= 50)
			return false;
		for (int i = 0; i < _trenutnoKurseva; i++) {
			if (_kursevi[i]->_kurs == kurs._kurs && _kursevi[i]->_kraj.ProvjeraDatuma(kurs._pocetak) == false)
				return false;
		}
		_kursevi[_trenutnoKurseva] = new Kurs;
		_kursevi[_trenutnoKurseva]->Unos(kurs._kurs, kurs._pocetak, kurs._kraj, kurs._imePredavaca);
		(_trenutnoKurseva)++;
		return true;
	}
	bool DodajPolaganje(Polaganja polaganje) {
		if (polaganje._kurs._aktivan == false)
			return false;
		for (int i = 0; i < _trenutnoPolaganja; i++) {
			if (polaganje._kurs._kurs != _polaganja[i]._kurs._kurs)
				return false;
			else if (polaganje._kurs._kurs == _polaganja[i]._kurs._kurs && _polaganja[i]._kurs._kraj.ProvjeraDatuma5dana(polaganje._kurs._pocetak) == false)
				return false;
			else if (strcmp(polaganje._polaznik._imePrezime, _polaganja[i]._polaznik._imePrezime) == 0 && polaganje._ostvareniUspjeh>_polaganja[i]._ostvareniUspjeh) {
				_polaganja[i]._ostvareniUspjeh = polaganje._ostvareniUspjeh;
				return true;
			}
		}
		Polaganja* temp = new Polaganja[_trenutnoPolaganja + 1];
		for (int i = 0; i < _trenutnoPolaganja; i++) {
			temp[i].Unos(_polaganja[i]._polaznik, _polaganja[i]._kurs, _polaganja[i]._datumPolaganja, _polaganja[i]._ostvareniUspjeh);
		}
		temp[_trenutnoPolaganja] = polaganje;
		if (_trenutnoPolaganja > 0) {
			for (int i = 0; i < _trenutnoPolaganja; i++) {
				_polaganja[i].Dealociraj();
			}
			delete[]_polaganja;
			_polaganja = nullptr;
		}
		_polaganja = temp;
		(_trenutnoPolaganja)++;
		return true;
	}
	Polaganja* PolaganjaByDatum(Datum prvi, Datum drugi, int&Broj) {
		for (int i = 0; i < _trenutnoPolaganja; i++) {
			if (prvi.ProvjeraDatuma(_polaganja[i]._datumPolaganja) == true && drugi.ProvjeraDatuma(_polaganja[i]._datumPolaganja) == false)
				Broj++;
		}
		Polaganja*temp = new Polaganja[Broj + 1];
		for (int i = 0; i < Broj; i++) {
			temp[i].Unos(_polaganja[i]._polaznik, _polaganja[i]._kurs, _polaganja[i]._datumPolaganja, _polaganja[i]._ostvareniUspjeh);
		}
		return temp;
	}
	void Ispis() {
		cout << "Naziv centra : " << _nazivCentra << endl;
		int i, j;
		Kurs *pom = new Kurs;
		for (i = 0; i < _trenutnoKurseva; i++) {
			j = i;
			while (j > 0 && _kursevi[j - 1]->_pocetak.ProvjeraDatuma(_kursevi[j]->_pocetak) == false) {
				pom = _kursevi[j];
				_kursevi[j] = _kursevi[j - 1];
				_kursevi[j - 1] = pom;
				j--;
			}
		}
		cout << "Kursevi : " << endl;
		for (int i = 0; i < _trenutnoKurseva; i++) {
			_kursevi[i]->Ispis();
		}
		cout << "Polaganja : " << endl;
		for (int i = 0; i < _trenutnoPolaganja; i++) {
			_polaganja[i].Ispis();
		}
	}
	void Dealociraj() {
		delete[]_nazivCentra;
		_nazivCentra = nullptr;
		for (int i = 0; i < _trenutnoKurseva; i++) {
			_kursevi[i]->Dealociraj();
			delete _kursevi[i];
			_kursevi[i] = nullptr;
		}
		for (int i = 0; i < _trenutnoPolaganja; i++) {
			_polaganja[i].Dealociraj();
		}
	}
};
//float PretragaRekurzivno(SkillsCentar Centar, enumKursevi Kurs, int broj, int pozicija) {
//  float suma = 0;
//  if (broj == Centar._trenutnoPolaganja - 1)
//      return suma/pozicija;
//  else if (Centar._polaganja[broj]._kurs._kurs == Kurs) {
//      pozicija++;
//      suma += Centar._polaganja[broj]._ostvareniUspjeh;
//  }
//  broj++;
//  return PretragaRekurzivno(Centar, Kurs, broj, pozicija);
//}
void main() {

	/*
	1. BROJ I TIPOVI PARAMETARA MORAJU BITI IDENTICNI ONIMA U TESTNOM CODE-U (OSIM UKOLIKO IMATE OPRAVDANU POTREBU ZA MODIFIKACIJOM). U SUPROTNOM SE RAD NEÆE BODOVATI
	2. KREIRAJTE .DOC FAJL SA VAŠIM BROJEM INDEKSA ( NPR. IB130030.DOC BEZ IMENA I PREZIMENA), TE NA KRAJU ISPITA U NJEGA KOPIRAJTE RJEŠENJA VAŠIH ZADATAKA. NE PREDAVATI .TXT ILI .CPP FAJLOVE. TAKOÐER, UKLONITE SVE DIJELOVE CODE-A KOJI NISU IMPLEMENTIRANI
	3. TOKOM IZRADE ISPITA NIJE DOZVOLJENO KORIŠTENJE HELP-A
	4. TOKOM IZRADE ISPITA MOGU BITI POKRENUTA SAMO TRI PROGRAMA: PDF READER (ISPITNI ZADACI), MS VISUAL STUDIO, MS WORD (U KOJI ÆETE KOPIRATI VAŠA RJEŠENJA)
	5. BEZ OBZIRA NA TO DA LI SU ISPITNI ZADACI URAÐENI, SVI STUDENTI KOJI SU PRISTUPILI ISPITU MORAJU PREDATI SVOJ RAD
	*/

	Datum datum1, datum2, datum3, datum4, datum5, datum6;
	datum1.Unos(26, 11, 2015);
	datum2.Unos(29, 5, 2016);
	datum3.Unos(5, 6, 2016);
	datum4.Unos(15, 8, 2016);
	datum5.Unos(13, 7, 2016);
	datum6.Unos(22, 9, 2016);

	Kurs softverski, html, sql, security;
	softverski.Unos(SoftwareEngeneeringFundamentals, datum1, datum2, "Emina Junuz");
	html.Unos(HtmlCSSJavaScript, datum2, datum3, "Larisa Tipura");
	sql.Unos(MasteringSQL, datum3, datum4, "Jasmin Azemovic");
	security.Unos(WindowsSecurity, datum3, datum4, "Adel Handzic");

	Polaznik denis, zanin, indira;
	denis.Unos(1, "Denis Music");
	zanin.Unos(2, "Zanin Vejzovic");
	indira.Unos(3, "Indira Hamulic");

	Polaganja denisHtml, zaninHtml, indiraSql;
	denisHtml.Unos(denis, html, datum5, 61);
	//61 predstavlja ostvareni uspjeh/procenat, a uspjesno polozenim se smatra svaki kurs na kome je polaznik ostvari vise od 55%
	zaninHtml.Unos(zanin, html, datum5, 93);

	SkillsCentar mostar;
	mostar.Unos("Skills Center Mostar");
	//jedan edukacijski centar moze nuditi vise istih kurseva (npr. MasteringSQL), ali se oni moraju realizovati u razlictim periodima (pocetak-kraj) tj. ne smiju se preklapati
	//novi kurs istog tipa (npr. MasteringSQL) se mora realizovati nakon prethodno dodanog npr. ako prethodni kurs MasteringSQL traje 01.03.2016 - 01.04.2016, onda se novi kurs MasteringSQL moze dodati jedino ako pocinje nakon 01.04.2016
	if (mostar.DodajKurs(softverski)) {
		cout << crt << "KURS USPJESNO REGISTROVAN" << crt;
		softverski.Ispis();
		cout << crt;
	}
	//nije moguce dodati polaganje onog kursa koji nije evidentiran (registrovan, ponudjen) u tom edukacijskom centru
	//moguce je polagati samo aktivne kurseve i to najkasnije 5 dana od dana zavrsetka (kraja) posljednje dodanog (aktivnog) kursa iste vrste (npr. MasteringSQL)
	//jedan polaznik moze vise puta polagati isti kurs, ali novi procenat mora biti veci od prethodno dodanog (na istom kursu)
	if (mostar.DodajPolaganje(denisHtml)) {
		cout << crt << "POLAGANJE EVIDENTIRANO" << crt;
		denisHtml.Ispis();
		cout << crt;//Dodano zbog preglednosti
	}
	Datum OD, DO;
	int brojPolaganja = 0;
	OD.Unos(1, 6, 2016);
	DO.Unos(1, 8, 2016);
	//PolaganjaByDatum – vraca niz polaganja koja su uspjesno realizovana u periodu OD-DO
	Polaganja * polaganjaByDatum = mostar.PolaganjaByDatum(OD, DO, brojPolaganja);
	cout << "U periodu od ";
	OD.Ispis();
	cout << " do ";
	DO.Ispis();
	cout << " uspjesno je realizovano " << brojPolaganja << " polaganja--->>>";
	for (size_t i = 0; i < brojPolaganja; i++)
		polaganjaByDatum[i].Ispis();
	cout << crt;//Dodano zbog preglednosti

				////PretragaRekurzivno - rekurzivna funkcija pronalazi prosjecni uspjeh koji su polaznici tokom godine (npr.2016) ostvarili na odredjenom kursu (npr. MasteringSQL)
				/*cout << "Prosjecan uspjeh na kursu MasteringSQL u 2016 godini je " << PretragaRekurzivno(mostar, MasteringSQL, 0, 0) << endl;*/
				////Ispis - ispisuje sve informacije o edukacijskom centru. prije ispisa sortirati sve kurseve na osnovu pocetka odrzavanja kursa
	mostar.Ispis();
	mostar.Dealociraj();//izvrsiti potrebne dealokacije
	system("pause>0");
}