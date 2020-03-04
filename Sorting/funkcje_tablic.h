#pragma once
#include <ctime>

template<typename T>
class Funkcje_tablic
{
public:

	void static wypisz_tablice(T tablica[], int rozmiar);
	int static sprawdz(T tablica[], int rozmiar);
	void static czy_posortowana(T tablica[], int rozmiar);
	static T* stworz_tablice(int rozmiar, int posortowanie, char typ);

};

template<typename T>
void Funkcje_tablic<T>::wypisz_tablice(T tablica[], int rozmiar)
{
	int i;

	for (i = 0; i < rozmiar; ++i)
	{
		std::cout << tablica[i] << " ";
	}
}

template<typename T>
int Funkcje_tablic<T>::sprawdz(T tablica[], int rozmiar)
{
	int i = 0;
	int j = 1;
	while (j <= rozmiar - 1)
	{
		if (tablica[i] > tablica[j])
			return i;
		++j;
		++i;
	}

	return -1;
}

template<typename T>
void Funkcje_tablic<T>::czy_posortowana(T tablica[], int rozmiar)
{
	if (sprawdz(tablica, rozmiar) != -1)
		std::cout << "Tablica jest posortowana do " << sprawdz(tablica, rozmiar) << "elemetu" << std::endl;
}

template<typename T>
T* Funkcje_tablic<T>::stworz_tablice(int rozmiar, int posortowanie, char typ)
{
	T* tablica = new T[rozmiar];
	int i = 0;
	int j = 1;

	if (typ=='o')
	{
		for (i; i >= 0; --i)
		{
			tablica[i] = j++;
		}
	}

	if (typ=='p')
	{
		for (i; i < posortowanie; ++i)
		{
			tablica[i] = i;
		}
		srand(time(NULL));
		for (i = posortowanie; i < rozmiar; ++i)
		{

			tablica[i] = rand();
		}
	}


	return tablica;
}
