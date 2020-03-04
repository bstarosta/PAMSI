using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Manager : MonoBehaviour
{
    public float timeframe;
    public int populationSize;
    public GameObject prefab;

    public int[] layers = new int[3] { 5, 3, 2 };

    [Range(0.1f, 10f)] public float Gamespeed = 1f;
    
    public List<NeuralNetwork> networks;
    private List<CarBrain> cars;

    void Start()
    {
        if (populationSize % 2 != 0)
            populationSize = 50; //Populacja musi byc parzysta. Jezeli nie jest, ustaw ja na 50

        InitializeNetworks();
        InvokeRepeating("CreateBots", 0.1f, timeframe); //Co okreslony czas usuwa stare pojazdy i tworzy nowe
    }

    public void InitializeNetworks()
    {
        networks = new List<NeuralNetwork>();
        for (int i = 0; i < populationSize; i++)
        {
            NeuralNetwork net = new NeuralNetwork(layers);
            net.Load("Assets/Save.txt");
            networks.Add(net);
        }
    }

    public void CreateBots()
    {
        Time.timeScale = Gamespeed;//Ustawia tempo gry, co moze przyspieszyc dlugi trening
        if (cars != null)
        {
            for (int i = 0; i < cars.Count; ++i)
            {
                GameObject.Destroy(cars[i].gameObject);
            }

            SortNetworks();
        }

        cars = new List<CarBrain>();
        for (int i = 0; i < populationSize; ++i)
        {
            CarBrain car = (Instantiate(prefab, new Vector3(0, 1.6f, -30), new Quaternion(0, 0, 1, 0))).GetComponent<CarBrain>();//Tworzy pojazdy
            car.network = networks[i];//Przypisuje sieci neuronowe do pojazdow
            cars.Add(car);
        }

    }

    public void SortNetworks()
    {
        for (int i = 0; i < populationSize; ++i)
        {
            cars[i].UpdateFitness();//Aktualizuje sprawnosc poszczegolnych sieci neuronowych
        }
        networks.Sort();
        networks[populationSize - 1].Save("Assets/Save.txt");
        for (int i = 0; i < populationSize / 2; ++i)
        {
            networks[i] = networks[i + populationSize / 2].copy(new NeuralNetwork(layers));
            networks[i].Mutate();
        }
    }
}
