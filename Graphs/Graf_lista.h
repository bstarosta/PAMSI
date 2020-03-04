#pragma once
#include "Lista.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <chrono>

#define INF 10000

class Graf_lista
{
	Lista<int>** LS;
	int V;
	int E;
	int S;

public:

	void iniciuj_graf(int Vd, int Ed);
	void stworz_graf_losowo(int Vd, int Ed, int start);
	bool wczytaj_z_pliku(std::string nazwa);
	void wypisz();
	void wypisz_droge(int droga[], int i);
	void wypisz_droge_do_pliku(int droga[], int i, std::ofstream& plik);
	void wypisz_rozwiazanie(Lista<int>** droga, int odleglosc[]);
	bool zapisz_sciezke_do_pliku(int droga[], int odleglosc[], int i, std::string nazwa);
	bool zapisz_do_pliku(int droga[], int odleglosc[], std::string nazwa);
	int znajdz_najkrotsza(bool odwiedzone[], int odleglosc[]);
	void dijkstra(int koniec);
	void dijkstra_test(int wierz, int kraw);
};


