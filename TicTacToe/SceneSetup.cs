using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SceneSetup : MonoBehaviour
{

    int rozmiar=Getsettings.rozmiar;
    public GameObject pole;
    public GameObject Pionek_AI;
    int wygrana=Getsettings.do_wygranej;
    GameObject[,] model;
    public static bool tura_gracza;
    public static int ostatni_x=0;
    public static int ostatni_y=0;
    int AI_ostatni_x=0;
    int AI_ostatni_y=0; 
    public static int[,] plansza;
    int postep = 0;
    public GameObject OverPanel;
    public Text zwyciezca;
    public static bool koniec;
 
  


    // Start is called before the first frame update
    void Start()
    {
        plansza_nieparzysta();
        iniciuj_plansze();
    }

    // Update is called once per frame
    void Update()
    {
        
        if (tura_gracza == false && koniec==false)
        {
            koniec_gry();
            if (koniec == false)
            {
                ruch_AI();
                koniec_gry();
            }
        }

    }

    void plansza_nieparzysta()
    {
        float x = -2.2f * (rozmiar - 1)/2;
        float z = 2.2f * (rozmiar - 1)/2;

        model = new GameObject[rozmiar, rozmiar];

        for (int i = 0; i < rozmiar; ++i)
        {
            for (int j = 0; j < rozmiar; ++j)
            {
                model[i,j]=Instantiate(pole, new Vector3(x, 0, z), Quaternion.identity);
                model[i, j].GetComponent<SpawnCross>().x = j;
                model[i, j].GetComponent<SpawnCross>().y = i;
                x = x + 2.2f;
            }
            x = -2.2f * (rozmiar-1)/2;
            z = z - 2.2f;
        }

    }

    void iniciuj_plansze()
    {
        plansza = new int[rozmiar, rozmiar];
        for (int i = 0; i < rozmiar; ++i)
            for (int j = 0; j < rozmiar; ++j)
                plansza[i, j] = 0;
        tura_gracza = Getsettings.tura;
        koniec = false;
        AI_ostatni_x = 0;
        AI_ostatni_y = 0;
        ostatni_x = 0;
        ostatni_y = 0;
    }
    
    void ruch_AI()
    {
        int najlepszy=-10000;
        int ruch_x=-1;
        int ruch_y=-1;
        int wartosc_ruchu;
        
        for(int i=0; i<rozmiar; ++i)
            for(int j=0; j<rozmiar; ++j)
            {
                if(plansza[i,j]==0)
                {
                    plansza[i, j] = 2;
                    AI_ostatni_x = j;
                    AI_ostatni_y = i;

                    wartosc_ruchu = minimax(0, false, -10000,10000);

                    plansza[i, j] = 0;

                    if (najlepszy < wartosc_ruchu)
                    {
                        najlepszy = wartosc_ruchu;
                        ruch_x = j;
                        ruch_y = i;
                    }
                }
            }
        Debug.Log(najlepszy);
        if (ruch_x>=0 && ruch_y >=0)
        {
            Transform pole = model[ruch_y, ruch_x].transform;
            Instantiate(Pionek_AI, new Vector3(pole.position.x, pole.position.y + 0.25f, pole.position.z), Pionek_AI.transform.rotation);
            model[ruch_y, ruch_x].GetComponent<SpawnCross>().already_spawned = true;
            tura_gracza = true;
            AI_ostatni_x = ruch_x;
            AI_ostatni_y = ruch_y;
            plansza[ruch_y, ruch_x] = 2;
        }
    }

    void sprawdz_poziomo(int x, int y, int gracz, int poprzedni)
    {
        if (plansza[y, x] == gracz)
        {
            ++postep;
            if (poprzedni!=x+1 && x+1<rozmiar)
                sprawdz_poziomo(x + 1, y, gracz,x);
            if (poprzedni != x - 1 && x-1 >= 0) 
                sprawdz_poziomo(x - 1, y, gracz,x);
            
        }
    }

    void sprawdz_pionowo(int x, int y, int gracz, int poprzedni)
    {
        if (plansza[y, x] == gracz)
        {
            ++postep;
            if (poprzedni != y + 1 && y + 1 < rozmiar)
                sprawdz_pionowo(x, y+1, gracz, y);
            if (poprzedni != y - 1 && y - 1 >= 0)
                sprawdz_pionowo(x, y-1, gracz, y);

        }
    }

    void sprawdz_prawa_przekatna(int x, int y, int gracz, int pop_x)
    {
        if (plansza[y, x] == gracz)
        {
            ++postep;
            if (pop_x != x + 1 && x + 1 < rozmiar && y-1>=0)
                sprawdz_prawa_przekatna(x+1, y-1, gracz, x);
            if (pop_x != x - 1 && x - 1 >= 0 && y+1<rozmiar)
                sprawdz_prawa_przekatna(x-1, y+1, gracz, x);

        }
    }

    void sprawdz_lewa_przekatna(int x, int y, int gracz, int pop_x)
    {
        if (plansza[y, x] == gracz)
        {
            ++postep;
            if (pop_x != x + 1 && x + 1 < rozmiar && y + 1<rozmiar)
                sprawdz_lewa_przekatna(x + 1, y + 1, gracz, x);
            if (pop_x != x - 1 && x - 1 >= 0 && y - 1 >=0)
                sprawdz_lewa_przekatna(x - 1, y - 1, gracz, x);

        }
    }

    bool sprawdz_wygrana(int gracz)
    {
        bool rezultat=false;

        if (gracz == 1)
        {
            sprawdz_poziomo(ostatni_x, ostatni_y, gracz, -10);
            if (postep >= wygrana)
                rezultat = true;
            postep = 0;

            sprawdz_pionowo(ostatni_x, ostatni_y, gracz, -10);
            if (postep >= wygrana)
                rezultat = true;
            postep = 0;

            sprawdz_prawa_przekatna(ostatni_x, ostatni_y, gracz, -10);
            if (postep >= wygrana)
                rezultat = true;
            postep = 0;

            sprawdz_lewa_przekatna(ostatni_x, ostatni_y, gracz, -10);
            if (postep >= wygrana)
                rezultat = true;
            postep = 0;
        }
        else
        {
            sprawdz_poziomo(AI_ostatni_x, AI_ostatni_y, gracz, -10);
            if (postep >= wygrana)
                rezultat = true;
            postep = 0;

            sprawdz_pionowo(AI_ostatni_x, AI_ostatni_y, gracz, -10);
            if (postep >= wygrana)
                rezultat = true;
            postep = 0;

            sprawdz_prawa_przekatna(AI_ostatni_x,AI_ostatni_y, gracz, -10);
            if (postep >= wygrana)
                rezultat = true;
            postep = 0;

            sprawdz_lewa_przekatna(AI_ostatni_x,AI_ostatni_y, gracz, -10);
            if (postep >= wygrana)
                rezultat = true;
            postep = 0;
        }
        return rezultat;
    }

    int ilosc_symboli(int gracz)
    {

        int najlepszy=-1;

        sprawdz_poziomo(AI_ostatni_x, AI_ostatni_y, gracz, -10);
        if (postep > najlepszy)
            najlepszy = postep;
        postep = 0;

        sprawdz_pionowo(AI_ostatni_x, AI_ostatni_y, gracz, -10);
        if (postep > najlepszy)
            najlepszy = postep;
        postep = 0;

        sprawdz_prawa_przekatna(AI_ostatni_x, AI_ostatni_y, gracz, -10);
        if (postep > najlepszy)
            najlepszy = postep;
        postep = 0;

        sprawdz_lewa_przekatna(AI_ostatni_x, AI_ostatni_y, gracz, -10);
        if (postep > najlepszy)
            najlepszy = postep;
        postep = 0;

        return najlepszy;
    
    }

    void koniec_gry()
    {
        if(sprawdz_wygrana(1))
        {
            OverPanel.SetActive(true);
            zwyciezca.text = "Wygrana!";
            koniec = true;
        }

        if(sprawdz_wygrana(2))
        {
            OverPanel.SetActive(true);
            zwyciezca.text = "Przegrana!";
            koniec = true;
        }

        if(czy_jest_ruch()==false)
        {
            OverPanel.SetActive(true);
            zwyciezca.text = "Remis!";
            koniec = true;
        }
    }

    bool czy_jest_ruch()
    {
        for (int i = 0; i < rozmiar; ++i)
            for (int j = 0; j < rozmiar; ++j)
                if (plansza[i, j] == 0)
                    return true;
        return false;
    }

    int minimax(int glebokosc, bool czy_max, int alpha, int beta)
    {
        int ruch;

        if (sprawdz_wygrana(1))
            return -100;

        if (sprawdz_wygrana(2))
            return 100;

        if (czy_jest_ruch() == false)
            return 0;

        if (glebokosc >= 4)
            return ilosc_symboli(2) * 10;

        if(czy_max)
        {
            int najlepszy = -1000;

            for (int i = 0; i < rozmiar; ++i)
            {
                for (int j = 0; j < rozmiar; ++j)
                {
                    if (plansza[i,j] == 0)
                    {
                       plansza[i,j] = 2;
                       AI_ostatni_x = j;
                       AI_ostatni_y = i;

                       ruch=minimax(glebokosc + 1, !czy_max, alpha, beta);
                       if (najlepszy < ruch)
                           najlepszy = ruch;

                       plansza[i,j] = 0;

                        if (najlepszy > alpha)
                            alpha = najlepszy;

                        if (beta <= alpha)
                            return najlepszy - glebokosc;
                    }
                }
            }
            return najlepszy-glebokosc;
        }
        else
        {
            int najlepszy = 1000;

            for (int i = 0; i < rozmiar; ++i)
            {
                for (int j = 0; j < rozmiar; ++j)
                {
                    if (plansza[i, j] == 0)
                    {
                        plansza[i, j] = 1;
                        ostatni_x = j;
                        ostatni_y = i;

                        ruch = minimax(glebokosc + 1, !czy_max, alpha, beta);
                        if (najlepszy > ruch)
                            najlepszy = ruch;

                        plansza[i, j] = 0;

                        if (najlepszy < beta)
                            beta = najlepszy;

                        if (beta <= alpha)
                            return najlepszy + glebokosc;
                    }
                }
            }
            return najlepszy+glebokosc;
        }
    }
    

}


