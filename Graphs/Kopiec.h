#pragma once

template<typename T, int N> class Kopiec
{
	T **tablica=new T* [2];
	tablica[0] = new T[N];
	tablica[1] = new T[N];
	int rozmiar;

public:
	void kopcowanie(int rodzic, int pierwszy, int ostatni);
	T usun_korzen();
};

template<typename T, int N>
void Kopiec<T, N>::kopcowanie(int rodzic, int pierwszy, int ostatni)
{
	int mniejszy;
	T pomocnicza;
	int l = 2 * rodzic + 1;
	int p = 2 * rodzic + 2;

	if (l <= ostatni && tablica[1][l] < tablica[1][rodzic])
		mniejszy = l;
	else
		wiekszy = rodzic;
	if (p <= ostatni && tablica[1][p] < tablica[1][mniejszy])
		mniejszy = p;
	if (mniejszy != rodzic)
	{
		pomocnicza = tablica[rodzic];
		tablica[rodzic] = tablica[mniejszy];
		tablica[mniejszy] = pomocnicza;
		kopcowanie(mniejszy, pierwszy, ostatni);
	}
}

template<typename T, int N>
T Kopiec<T,N>::usun_korzen()
{
	T pom;
	tablica[0] = pom;
	tablica[0] = tablica[rozmiar];
	tablica[rozmiar] = pom;
	--rozmiar;
	kopcowanie(0, 0, rozmiar);

	return pom;
}