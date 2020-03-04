using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;


public class BoardSize : MonoBehaviour
{

    public TextMeshProUGUI _rozmiar;
    public TextMeshProUGUI _do_wygranej;
    public Slider sizeslider;
    public Slider winslider;
    public Toggle turn;

    private void Start()
    {
        _rozmiar.text = Getsettings.rozmiar.ToString();
        _do_wygranej.text = Getsettings.do_wygranej.ToString();
        sizeslider.value = Getsettings.rozmiar;
        winslider.value = Getsettings.do_wygranej;
        turn.isOn = Getsettings.tura;
    }

    public void ustaw_rozmiar(float rozmiar)
    {
        Getsettings.rozmiar = (int)rozmiar;
        _rozmiar.text = Getsettings.rozmiar.ToString();
    }

    public void ustaw_do_wygranej(float wyg)
    {
        Getsettings.do_wygranej =(int)wyg;
        _do_wygranej.text = Getsettings.do_wygranej.ToString();
    }

    public void czyja_tura(bool tura)
    {
        Getsettings.tura = tura;
    }
}
