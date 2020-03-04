#pragma once
template<typename T> class Element
{
public:
	T pole;
	int waga;
	Element* nastepny;

	Element(T wartosc, int wartosc2) { pole = wartosc; waga = wartosc2; }
};

template<typename T> class Lista
{
	Element<T>* header;

public:

	Lista() { header = nullptr; }
	void dodaj(T wartosc, int wartosc2);
	void wypisz();
	int wyszukaj(T wartosc);
	bool usun(Element<T>* wsk);
	void usun_wszystko();
	Element<T>* poczatek();
};

template<typename T>
void Lista<T>::dodaj(T wartosc, int wartosc2) 
{
	Element<T> *nowy=new Element<T>(wartosc, wartosc2);
	if (header == nullptr)
		header = nowy;
	else
	{
		Element<T> *pomocnicza=header;
		while (pomocnicza->nastepny)
		{
			pomocnicza = pomocnicza->nastepny;
		}
		pomocnicza->nastepny = nowy;
		nowy->nastepny = nullptr;
	}

}

template<typename T>
void Lista<T>::wypisz()
{
	Element<T>* pomocnicza=header;

	while (pomocnicza)
	{
		std::cout << pomocnicza->pole <<" ";
		pomocnicza = pomocnicza->nastepny;
	}
}

template<typename T>
int Lista<T>::wyszukaj(T wartosc)
{
	Element<T>* pomocnicza = header;

	while (pomocnicza)
	{
		if (pomocnicza->pole == wartosc)
			return pomocnicza->waga;
		pomocnicza = pomocnicza->nastepny;
	}

	return 1000;
}

template<typename T>
bool Lista<T>::usun(Element<T>* wsk)
{
	Element<T>* pomocnicza = header;

	if (wsk == header)
	{
		header = pomocnicza->nastepny;
		delete pomocnicza;
		return true;

	}

	while (pomocnicza->nastepny!=wsk)
	{
		pomocnicza = pomocnicza->nastepny;
	}

	if (wsk->nastepny==nullptr)
	{
		pomocnicza->nastepny = nullptr;
		delete wsk;
		return true;
	}

	if ((wsk->nastepny!= nullptr)&&(wsk!=nullptr))
	{
		pomocnicza->nastepny = wsk->nastepny;
		delete wsk;
		return true;
	}

	return false;
}

template<typename T>
void Lista<T>::usun_wszystko()
{
	while (header != nullptr)
	{
		Element<T> *pomocnicza = header;
		while (pomocnicza->nastepny)
		{
			pomocnicza = pomocnicza->nastepny;
		}

		usun(pomocnicza);
	}
}

template<typename T>
Element<T>* Lista<T>::poczatek()
{
	return header;
}