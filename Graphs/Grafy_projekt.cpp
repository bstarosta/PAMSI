#include "pch.h"
#include <iostream>
#include "Graf_lista.h"
#include "Graf_macierz.h"

using namespace std;

int main()
{
	char wybor, typ;
	Graf_macierz graf_m;
	Graf_lista graf_l;
	string nazwa;
	int lv, le;

	cout << " 1. Program" << endl;
	cout << " 2. Lista sasiedztwa - test" << endl;
	cout << " 3. Macierz sasiedztwa - test" << endl;
	cin >> wybor;
	while (cin.fail() || (wybor != '1' && wybor != '2' && wybor != '3'))
	{
		cout << "Podana wartosc jest niepoprawna. Sprobuj jeszcze raz: " << endl;
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> wybor;
	}
	cout << endl;

	switch (wybor)
	{
	case '3':
		cout << "Podaj liczbe wierzcholkow i liczbe krawedzi: ";
		cin >> lv >> le;
		while (cin.fail() || (lv<=0 ||le<=0||le>(lv*(lv-1))/2))
		{
			cout << "Podane wartosci sa niepoprawne. Sprobuj jeszcze raz: " << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			cin >>lv>>le;
		}
		cout << endl;
		graf_m.dijkstra_test(lv, le);
		break;
	case '2':
		cout << "Podaj liczbe wierzcholkow i liczbe krawedzi: ";
		cin >> lv >> le;
		while (cin.fail() || (lv <= 0 || le <= 0 || le > (lv*(lv - 1)) / 2))
		{
			cout << "Podane wartosci sa niepoprawne. Sprobuj jeszcze raz: " << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> lv >> le;
		}
		cout << endl;
		graf_l.dijkstra_test(lv, le);
		break;
	case '1':
		cout << "Wybierz sposob reprezentacji grafu"<<endl;
		cout << " 1.Macierz sasiedztwa" << endl;
		cout << " 2.Lista sasiedztwa" << endl;
		cin >> typ;
		while (cin.fail() || (typ != '1' && typ != '2'))
		{
			cout << "Podana wartosc jest niepoprawna. Sprobuj jeszcze raz: " << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> typ;
		}
		cout << endl;

		cout << "1. Wczytaj graf z pliku." << endl;
		cout << "2. Wygeneruj losowy graf." << endl;
		cin >> wybor;
		while (cin.fail() || (wybor != '1' && wybor != '2'))
		{
			cout << "Podana wartosc jest niepoprawna. Sprobuj jeszcze raz: " << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> wybor;
		}

		if (wybor == '1')
		{
			cout << "Podaj nazwe pliku ktory chcesz wczytac: ";
			cin >> nazwa;
			if (typ == '1')
				graf_m.wczytaj_z_pliku(nazwa);
			else
				graf_l.wczytaj_z_pliku(nazwa);
		}
		if (wybor == '2')
		{
			int p;
			cout << "Podaj liczbe wierzcholkow, liczbe krawedzi i wierzcholek poczatkowy: ";
			cin >> lv>>le>>p;
			while (cin.fail() || (lv <= 0 || le <= 0 || le > (lv*(lv - 1)) / 2 || p < 0 || p>lv-1))
			{
				cout << "Podane wartosci sa niepoprawne. Sprobuj jeszcze raz: " << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> lv >> le>>p;
			}
			if (typ=='1')
				graf_m.stworz_graf_losowo(lv, le, p);
			else
				graf_l.stworz_graf_losowo(lv, le, p);

		}
		cout << endl;
		cout << "1.Znajdz droge do wszystkich wierzcholkow" << endl;
		cout << "2.Znajdz droge do wybranego wierzcholka" << endl;
		cin >> wybor;
		if (wybor=='1')
		{
			if (typ == '1')
				graf_m.dijkstra(-1);
			else
				graf_l.dijkstra(-1);
		}
		else
		{
			int k;
			cout << endl;
			cout << "Podaj wierzcholek koncowy:";
			cin >> k;
			while (cin.fail() || k<0 || k>=lv)
			{
				cout << "Podana wartosc jest niepoprawna. Sprobuj jeszcze raz: " << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> wybor;
			}
			if (typ == '1')
				graf_m.dijkstra(k);
			else
				graf_l.dijkstra(k);
		}
		break;
	default:
		break;
	}
}

