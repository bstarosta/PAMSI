#include "pch.h"
#include "Graf_lista.h"


void Graf_lista::iniciuj_graf(int Vd, int Ed)
{
	int p, k, w;

	V = Vd;
	E = Ed;

	LS = new Lista<int>*[V];
	for (int i = 0; i < V; ++i)
	{
		LS[i] = new Lista<int>;
	}
}

void Graf_lista::stworz_graf_losowo(int Vd, int Ed, int start)
{
	int p, k, w, pom = 0;

	iniciuj_graf(Vd, Ed);
	S = start;

	srand(time(NULL));

	if (E == V * (V - 1) / 2)
	{
		for (int i = 0; i < V; ++i)
		{
			for (int j = pom; j < V; ++j)
			{
				if (i != j)
				{
					w = (std::rand() % 10) + 1;
					LS[i]->dodaj(j, w);
					LS[j]->dodaj(i, w);
				}
			}
			++pom;
		}
	}
	else
	{
		for (int l = 0; l < E; ++l)
		{
			do
			{
				p = std::rand() % V;
				k = std::rand() % V;
			} while ((LS[p]->wyszukaj(k) != 1000) || (p == k));

			w = (std::rand() % 10) + 1;
			LS[p]->dodaj(k, w);
			LS[k]->dodaj(p, w);
		}
	}

}

bool Graf_lista::wczytaj_z_pliku(std::string nazwa)
{
	std::ifstream plik;
	plik.open(nazwa);
	int p, k, w;
	if (plik.good() == true)
	{
		plik >> E >> V >> S;
		iniciuj_graf(V, E);
		for (int i = 0; i < E; ++i)
		{
			plik >> p >> k >> w;
			LS[p]->dodaj(k, w);
			LS[k]->dodaj(p, w);
		}
	}
	else
		return false;

	plik.close();
	return true;
}

void Graf_lista::wypisz()
{
	for (int i = 0; i < V; ++i)
	{
		std::cout << i << " ";
		LS[i]->wypisz();
		std::cout << std::endl;
	}
}

void Graf_lista::wypisz_droge(int droga[], int i)
{
	if (droga[i] == -1)
		return;
	wypisz_droge(droga, droga[i]);
	std::cout << i << " ";
}

void Graf_lista::wypisz_droge_do_pliku(int droga[], int i, std::ofstream& plik)
{
	if (droga[i] == -1)
		return;
	wypisz_droge_do_pliku(droga, droga[i], plik);
	plik << i << " ";
}

void Graf_lista::wypisz_rozwiazanie(Lista<int>** droga, int odleglosc[])
{
	for (int i = 0; i < V; ++i)
	{
		if (odleglosc[i] == INF)
		{
			std::cout << i << "\t" << "brak" << "\t| ";
		}
		else
			std::cout << i << "\t" << odleglosc[i] << "\t| ";
		droga[i]->wypisz();
		std::cout << std::endl;
	}
}

bool Graf_lista::zapisz_sciezke_do_pliku(int droga[], int odleglosc[], int i, std::string nazwa)
{
	std::ofstream plik;
	plik.open(nazwa);

	if (plik.good() == true)
	{
		if (odleglosc[i] == INF)
		{
			plik << i << "\t" << "brak" << "\t| ";
		}
		else
		{
			plik << i << "\t" << odleglosc[i] << "\t| ";
			wypisz_droge_do_pliku(droga, i, plik);
		}
		plik << std::endl;
	}
	else
		return false;

	plik.close();
	return true;
}

bool Graf_lista::zapisz_do_pliku(int droga[], int odleglosc[], std::string nazwa)
{
	std::ofstream plik;
	plik.open(nazwa);

	if (plik.good() == true)
	{
		for (int i = 0; i < V; ++i)
		{
			if (odleglosc[i] == INF)
			{
				plik << i << "\t" << "brak" << "\t| ";
			}
			else
			{
				plik << i << "\t" << odleglosc[i] << "\t| ";
				wypisz_droge_do_pliku(droga, i, plik);
			}
			plik << std::endl;
		}
	}
	else
		return false;

	plik.close();
	return true;
}

int Graf_lista::znajdz_najkrotsza(bool odwiedzone[], int odleglosc[])
{
	int minimalny_koszt = INF;
	int wierzcholek;

	for (int i = 0; i < V; ++i)
	{
		if (odwiedzone[i] == false && odleglosc[i] <= minimalny_koszt)
		{
			minimalny_koszt = odleglosc[i];
			wierzcholek = i;
		}
	}

	return wierzcholek;
}

void Graf_lista::dijkstra(int koniec)
{
	bool* odwiedzone = new bool[V];
	int* odleglosc = new int[V];
	int w;
	int* droga = new int[V];
	Element<int>* pom;


	for (int i = 0; i < V; ++i)
	{
		odleglosc[i] = INF;
		odwiedzone[i] = false;
		droga[i] = -1;
	}

	odleglosc[S] = 0;

	for (int j = 0; j < V - 1; ++j)
	{
		w = znajdz_najkrotsza(odwiedzone, odleglosc);
		odwiedzone[w] = true;
		pom = LS[j]->poczatek();
		while(pom)
		{
			if (odwiedzone[pom->pole] == false && odleglosc[w] != INF && odleglosc[w] + pom->waga < odleglosc[pom->pole])
			{
				droga[pom->pole] = w;
				odleglosc[pom->pole] = odleglosc[w] + pom->waga;

			}
			pom = pom->nastepny;
		}
	}

	if (koniec < 0)
		zapisz_do_pliku(droga, odleglosc, "wynik.txt");
	else
		zapisz_sciezke_do_pliku(droga, odleglosc, koniec, "wynik.txt");

	for (int l = 0; l < V; ++l)
	{
		LS[l]->usun_wszystko();
		delete LS[l];
	}
	delete[] odwiedzone;
	delete[] odleglosc;
	delete[] droga;
}

void Graf_lista::dijkstra_test(int wierz, int kraw)
{
	auto start = std::chrono::high_resolution_clock::now();
	auto suma = std::chrono::duration_cast<std::chrono::microseconds>(start - start);

	bool* odwiedzone = new bool[wierz];
	int* odleglosc = new int[wierz];
	int w;
	int* droga = new int[wierz];
	Element<int>* pom;

	for (int t = 0; t < 100; ++t)
	{
		stworz_graf_losowo(wierz, kraw, 0);

		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < V; ++i)
		{
			odleglosc[i] = INF;
			odwiedzone[i] = false;
			droga[i] = -1;
		}

		odleglosc[S] = 0;

		for (int j = 0; j < V - 1; ++j)
		{
			w = znajdz_najkrotsza(odwiedzone, odleglosc);
			odwiedzone[w] = true;
			pom = LS[j]->poczatek();
			while (pom)
			{
				if (odwiedzone[pom->pole] == false && odleglosc[w] != INF && odleglosc[w] + pom->waga < odleglosc[pom->pole])
				{
					droga[pom->pole] = w;
					odleglosc[pom->pole] = odleglosc[w] + pom->waga;

				}
				pom = pom->nastepny;
			}
		}

		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		suma = suma + duration;

		for (int l = 0; l < V; ++l)
		{
			LS[l]->usun_wszystko();
			delete LS[l];
		}
	}
	zapisz_do_pliku(droga, odleglosc, "wynik.txt");
	std::cout << "Czas wykonania zadania: " << suma.count() << " mikrosekund" << std::endl;
	delete[] odwiedzone;
	delete[] odleglosc;
	delete[] droga;
}