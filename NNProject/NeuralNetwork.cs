using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;
using System.IO;

public class NeuralNetwork : IComparable<NeuralNetwork>
{
    private int[] layers; //Rozmiar tej tablicy to liczba warstw, a przechowywane wartosci to liczba neuronow w danej warstwie
    private float[][] neurons; //Przechowuje wartosci neuronow
    private float[][][] weights; //Przechowuje wagi polaczen miedzy neuronami
    private float bias = 0.25f; //Stala wartosc "przesuniecia"
    public float fitness=0; //Okresla jak dobra jest dana siec neuronowa


    //Konstruktor sieci neuronowej. 
    public NeuralNetwork(int[] layers_array)
    {
        layers = new int[layers_array.Length];
        for (int i = 0; i < layers_array.Length; ++i)
            layers[i] = layers_array[i];

        InitializeNeurons();
        InitializeWeights();
    }

    //Konstruktor kopiujacy siec neuronowa podana jako argument
    public NeuralNetwork(NeuralNetwork network_to_copy)
    {
        this.layers = new int[network_to_copy.layers.Length];
        for (int i = 0; i < network_to_copy.layers.Length; ++i)
            this.layers[i] = network_to_copy.layers[i];

        InitializeNeurons();
        InitializeWeights();
        CopyWeights(network_to_copy.weights);
    }

    //Inicjalizuje zbior neuronow
    private void InitializeNeurons()
    {
        neurons = new float[layers.Length][];
        for (int i = 0; i < layers.Length; ++i)
            neurons[i] = new float[layers[i]];
    }

    //Inicializuje wagi polaczen miedzy neuronami
    private void InitializeWeights()
    {
        List<float[][]> weightList = new List<float[][]>();
        for (int i = 1; i < layers.Length; ++i)
        {
            List<float[]> layerWeightList = new List<float[]>();
            int neuronsInPreviousLayer = layers[i - 1];  //Ostatni z neuronow kazdej z "ukrytych" warstw nie ma polaczenia z poprzednia warstwa
            for (int j = 0; j < neurons[i].Length; ++j)
            {
                float[] neuronWeights = new float[neuronsInPreviousLayer];
                for (int k = 0; k < neuronsInPreviousLayer; ++k)
                    neuronWeights[k] = UnityEngine.Random.Range(-0.5f, 0.5f);
                layerWeightList.Add(neuronWeights);
            }
            weightList.Add(layerWeightList.ToArray());
        }
        weights = weightList.ToArray();
    }

    //Inicializuje przesuniecia dla danych neuronow. Uzywac gdy chcemy miec rozne przesuniecia w neuronach
    /*private void InitBiases()
    {
        List<float[]> biasList = new List<float[]>();
        for (int i = 1; i < layers.Length; i++)
        {
            float[] bias = new float[layers[i]];
            for (int j = 0; j < layers[i]; j++)
            {
                bias[j] = UnityEngine.Random.Range(-0.5f, 0.5f);
            }
            biasList.Add(bias);
        }
        biases = biasList.ToArray();
    }*/

    //Kopiuje wszystkie wagi do nowej sieci neuronowej
    private void CopyWeights(float[][][] weights_to_copy)
    {
        for (int i = 0; i < weights.Length; ++i)
            for (int j = 0; j < weights[i].Length; ++j)
                for (int k = 0; k < weights[i][j].Length; ++k)
                    weights[i][j][k] = weights_to_copy[i][j][k];
                    
    }

    //Przetwarza dane wprowadzone do sieci neuronowej
    public float[] ProcessInput(float[] input)
    {
        for (int i = 0; i < input.Length; ++i)
            neurons[0][i] = input[i];
        
        for(int j=1; j<layers.Length; ++j) // W kazdej warstwie zaczynajac od warstwy drugiej(czyli o indeksie 1)
        {
            for(int k=0; k<neurons[j].Length; ++k) //Do kazdego neuronu
            {
                float passed_value = 0;

                for(int l=0; l<neurons[j-1].Length; ++l) //Przypisujemy wazona sume wartosci ze wszystkich neuronow wraz z przesunieciem
                {
                    passed_value += weights[j - 1][k][l] * neurons[j - 1][l] + bias;
                }

                neurons[j][k] = (float)System.Math.Tanh(passed_value); //Podanie naszej wartosci jako argument funkcji Tanh (tangens hiperboliczny), abu uzyskac wartosci z przedzialu od -1 do 1 
            }
        }

        return neurons[neurons.Length - 1]; //Zwraca ostatnia warstwe sieci neuronowej(o ineksie n-1)
    }

    //Funkcje zmieniajaca wagi polaczen miedzy neuronami
    public void Mutate()
    {
        for(int i=0; i<weights.Length; ++i)
        {
            for(int j=0; j<weights[i].Length; ++j)
            {
                for(int k=0; k<weights[i][j].Length; ++k)
                {
                    float weight_to_mutate=weights[i][j][k];
                    float mutation_type = UnityEngine.Random.Range(0f, 1000f);

                    //Trzy jednakowo prawdopodobne typy mutacji.
                    if (mutation_type <= 3f)
                        weight_to_mutate = -weight_to_mutate; //Odwraca wartosc danej wagi
                    else if (mutation_type <= 6f)
                        weight_to_mutate = UnityEngine.Random.Range(-0.5f, 0.5f); //Losuje zupelnie nowa liczbe
                    else if (mutation_type <= 9f)
                        weight_to_mutate *= UnityEngine.Random.Range(0, 1f); // Zmienia wage na losowy % jej poprzedniej wartosci

                    weights[i][j][k] = weight_to_mutate;

                }
            }
        }
    }

    //Tworzy kopie sieci neuronowej podanej jako argument
    public NeuralNetwork copy(NeuralNetwork network) 
    {
        for (int i = 0; i < weights.Length; ++i)
        {
            for (int j = 0; j < weights[i].Length; ++j)
            {
                for (int k = 0; k < weights[i][j].Length; ++k)
                {
                    network.weights[i][j][k] = weights[i][j][k];
                }
            }
        }
        return network;
    }

    //Porownuje sprawnosc tej sieci neuronowej ze sprawnoscia innej sieci
    public int CompareTo(NeuralNetwork other) 
    {
        if (other == null) return 1;

        if (fitness > other.fitness)
            return 1;
        else if (fitness < other.fitness)
            return -1;
        else
            return 0;
    }

    //Wczzytuje wagi polaczen z pliku do sieci neuronowej
    public void Load(string path)
    {
        TextReader tr = new StreamReader(path);
        int lines = (int)new FileInfo(path).Length;
        string[] listLines = new string[lines];
        int index = 1;
        for (int i = 1; i < lines; i++)
        {
            listLines[i] = tr.ReadLine();
        }
        tr.Close();
        if (new FileInfo(path).Length > 0)
        {
            for (int i = 0; i < weights.Length; ++i)
            {
                for (int j = 0; j < weights[i].Length; ++j)
                {
                    for (int k = 0; k < weights[i][j].Length; ++k)
                    {
                        weights[i][j][k] = float.Parse(listLines[index]); ;
                        index++;
                    }
                }
            }
        }
    }

    //Zapisuje wagi polaczen z sieci neuronowej do pliku
    public void Save(string path)
    {
        File.Create(path).Close();
        StreamWriter writer = new StreamWriter(path, true);

        for (int i = 0; i < weights.Length; ++i)
        {
            for (int j = 0; j < weights[i].Length; ++j)
            {
                for (int k = 0; k < weights[i][j].Length; ++k)
                {
                    writer.WriteLine(weights[i][j][k]);
                }
            }
        }
        writer.Close();
    }
}
