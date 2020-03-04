#pragma once

template<typename T>
class Sortowanie
{
public:

	void static zamien(T *a, T *b);
	void static scal(T tablica[], int start, int srodek, int koniec);
	void static sortowanie_przez_scalanie(T tablica[], int pierwszy, int ostatni);
	int static podzial(T tablica[], int pierwszy, int ostatni);
	int static podzial2(T tablica[], int pierwszy, int ostatni);
	void static quicksort(T tablica[], int pierwszy, int ostatni);
	void static kopcowanie(T tablica[], int rodzic, int pierwszy, int ostatni);
	void static heapsort(T tablica[], int pierwszy, int ostatni);
	void static insertion_sort(T tablica[], int pierwszy, int ostatni);
	void static introsort(T tablica[], int pierwszy, int ostatni, int glebokosc);

};

template<typename T>
void Sortowanie<T>::zamien(T *a , T *b)
{
	T pomocniczna;
	pomocniczna = *a;
	*a = *b;
	*b = pomocniczna;
}

template<typename T>
void Sortowanie<T>::scal(T tablica[], int start, int srodek, int koniec)
{
	T *tab_d = new T[koniec - start + 1];
	int i = start;
	int j = srodek + 1;
	int k = 0;

	while (i <= srodek && j <= koniec)
	{
		if (tablica[i] < tablica[j])
		{
			tab_d[k] = tablica[i];
			++i;
		}
		else
		{
			tab_d[k] = tablica[j];
			++j;
		}
		++k;
	}
	
	while (i <= srodek)
	{
		tab_d[k] = tablica[i];
		++i;
		++k;
	}

	while (j <= koniec)
	{
		tab_d[k] = tablica[j];
		++j;
		++k;
	}

	for (i = 0; i <= koniec - start; ++i)
		tablica[start + i] = tab_d[i];

	delete tab_d;
}

template<typename T>
void Sortowanie<T>::sortowanie_przez_scalanie(T tablica[], int pierwszy, int ostatni)
{
	if (pierwszy != ostatni)
	{
		int srodek = (pierwszy+ostatni) / 2;
		sortowanie_przez_scalanie(tablica, pierwszy, srodek);
		sortowanie_przez_scalanie(tablica, srodek + 1, ostatni);
		scal(tablica, pierwszy, srodek, ostatni);
	}
}

template<typename T>
int Sortowanie<T>::podzial2(T tablica[], int pierwszy, int ostatni)
{
	int srodek = (ostatni + pierwszy) / 2;
	T p = tablica[srodek];
	T pomocniczna;
	int i = pierwszy - 1;
	int j;

	pomocniczna = tablica[srodek];
	tablica[srodek] = tablica[ostatni];
	tablica[ostatni] = pomocniczna;

	for (j = pierwszy; j < ostatni; ++j)
	{
		if (tablica[j] < p)
		{
			++i;
			pomocniczna = tablica[i];
			tablica[i] = tablica[j];
			tablica[j] = pomocniczna;
		}
	}

	++i;
	pomocniczna = tablica[i];
	tablica[i] = tablica[ostatni];
	tablica[ostatni] = pomocniczna;
	return i;
}

template<typename T>
int Sortowanie<T>::podzial(T tablica[], int pierwszy, int ostatni)
{
	T p = tablica[(pierwszy + ostatni) / 2];
	T pomocniczna;
	int i = pierwszy;
	int j = ostatni;

	while (true)
	{
		while (tablica[i] < p)
			i++;
		while (tablica[j] > p)
			j--;

		if (i < j)
		{
			pomocniczna =tablica[i];
			tablica[i] = tablica[j];
			tablica[j] = pomocniczna;
			--j;
			++i;
		}
		else
			return j;
	}
	
}

template<typename T>
void Sortowanie<T>::quicksort(T tablica[], int pierwszy, int ostatni)
{
	int granica;
	if (pierwszy < ostatni)
	{
		granica = podzial2(tablica, pierwszy, ostatni);
		quicksort(tablica, pierwszy, granica-1);
		quicksort(tablica, granica + 1, ostatni);
	}
}

template<typename T>
void Sortowanie<T>::kopcowanie(T tablica[], int rodzic, int pierwszy, int ostatni)
{
	int wiekszy;
	T pomocnicza;
	int l = 2 * rodzic + 1;
	int p = 2 * rodzic + 2;

	if (l<=ostatni && tablica[l]>tablica[rodzic])
		wiekszy = l;
	else
		wiekszy = rodzic;
	if (p<=ostatni && tablica[p]>tablica[wiekszy])
		wiekszy = p;
	if (wiekszy != rodzic)
	{
		pomocnicza = tablica[rodzic];
		tablica[rodzic] = tablica[wiekszy];
		tablica[wiekszy] = pomocnicza;
		kopcowanie(tablica, wiekszy, pierwszy, ostatni);
	}
}

template<typename T>
void Sortowanie<T>::heapsort(T tablica[], int pierwszy, int ostatni)
{
	T pomocnicza;

	for (int i = (pierwszy+ostatni-1)/2; i>=pierwszy; --i)
		kopcowanie(tablica, i, pierwszy, ostatni);

	for (int j = ostatni; j>=pierwszy; --j)
	{
		pomocnicza = tablica[pierwszy];
		tablica[pierwszy] = tablica[j];
		tablica[j] = pomocnicza;
		kopcowanie(tablica, pierwszy, pierwszy, j-1);
	}
}

template<typename T>
void Sortowanie<T>::insertion_sort(T tablica[], int pierwszy, int ostatni)
{
	int i, j, element;
	
	for (i = pierwszy+1; i < ostatni+1; ++i)
	{
		element = tablica[i];
		j = i - 1;

		while (element<tablica[j] && j>=pierwszy)
		{
			tablica[j + 1] = tablica[j];
			--j;
		}
		tablica[j + 1] = element;
	}
}

template<typename T>
void Sortowanie<T>::introsort(T tablica[], int pierwszy, int ostatni, int glebokosc)
{
	int granica;


	if ((ostatni - pierwszy)<16)
		insertion_sort(tablica, pierwszy, ostatni);
	else if (pierwszy < ostatni)
			{
				if (0 >= glebokosc && (ostatni - pierwszy) >= 16)
				{
					heapsort(tablica, pierwszy, ostatni);
					std::cout << "heapsort" << std::endl;
					return;
				}
				
				else
				{
					granica = podzial(tablica, pierwszy, ostatni);
					introsort(tablica, pierwszy, granica, glebokosc - 1);
					introsort(tablica, granica + 1, ostatni, glebokosc - 1);
				}

			}
			else
				return;
	
}