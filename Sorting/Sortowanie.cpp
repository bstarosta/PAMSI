#include "pch.h"
#include <iostream>
#include <chrono>
#include <math.h>
#include "funkcje_sortowania.h"
#include "funkcje_tablic.h"


using namespace std;



int main()
{
	int rozmiar, sort, ile_tablic;
	double posortowanie;
	char typ;
	cout << "Wybierz typ sortowania:" << endl;
	cout << "   1.Mergesort" << endl;
	cout << "   2.Quicksort" << endl;
	cout << "   3.Introsort" << endl;
	cin >> sort;
	while (cin.fail()||(sort != 1 && sort != 2 && sort!=3))
	{
		cout << "Podana wartosc jest niepoprawna. Sprobuj jeszcze raz: " << endl;
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> sort;
	}
	cout << endl;

	cout << "Podaj liczbe tablic do posortowania: ";
	cin >> ile_tablic;
	while (cin.fail() || ile_tablic < 0 || ile_tablic > 1000)
	{
		cout << "Podana wartosc jest niepoprawna. Sprobuj jeszcze raz: " << endl;
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> ile_tablic;
	}
	cout << endl;

	cout << "Podaj parametry tablicy: ";
	cin >> rozmiar>>posortowanie>>typ;
	while (cin.fail()||rozmiar<0||posortowanie>100||(typ!='o' && typ != 'p'))
	{
		cout << "Podana wartosc jest niepoprawna. Sprobuj jeszcze raz: " << endl;
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> rozmiar>>posortowanie>>typ;
	}
	cout << endl;

	int do_ktorego = (rozmiar*posortowanie) / 100;
	int* tab;
	int max_glebokosc = 4*log2(rozmiar);
	auto start = chrono::high_resolution_clock::now();
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	auto suma = chrono::duration_cast<chrono::microseconds>(start-start);

	if (sort == 1)
	{
		for (int k = 0; k < ile_tablic; ++k)
		{
			tab = Funkcje_tablic<int>::stworz_tablice(rozmiar, do_ktorego, typ);
			start = chrono::high_resolution_clock::now();
			Sortowanie<int>::sortowanie_przez_scalanie(tab, 0, rozmiar - 1);
			stop = chrono::high_resolution_clock::now();
			duration = chrono::duration_cast<chrono::microseconds>(stop - start);
			suma = suma + duration;
			Funkcje_tablic<int>::czy_posortowana(tab, rozmiar);
			delete[] tab;
		}
	}

	else if (sort == 2)
	{
		for (int k = 0; k < ile_tablic; ++k)
		{
			tab = Funkcje_tablic<int>::stworz_tablice(rozmiar, do_ktorego, typ);
			start = chrono::high_resolution_clock::now();
			Sortowanie<int>::quicksort(tab, 0, rozmiar - 1);
			stop = chrono::high_resolution_clock::now();
			duration = chrono::duration_cast<chrono::microseconds>(stop - start);
			suma = suma + duration;
			Funkcje_tablic<int>::czy_posortowana(tab, rozmiar);
			delete[] tab;
		}
	}

	else if (sort == 3)
	{
		for (int k = 0; k < ile_tablic; ++k)
		{
			tab = Funkcje_tablic<int>::stworz_tablice(rozmiar, do_ktorego, typ);
			start = chrono::high_resolution_clock::now();
			Sortowanie<int>::introsort(tab, 0, rozmiar - 1, max_glebokosc);
			stop = chrono::high_resolution_clock::now();
			duration = chrono::duration_cast<chrono::microseconds>(stop - start);
			suma = suma + duration;
			Funkcje_tablic<int>::czy_posortowana(tab, rozmiar);
			delete[] tab;
		}
	}
	
	cout << "Czas sortowania: " << suma.count() << " mikrosekund" << endl;
	
	cin >> rozmiar;
	return 0;
}


