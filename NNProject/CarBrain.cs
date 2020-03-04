using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CarBrain : MonoBehaviour
{
    public float speed;//Szybkosc samochodu
    public float rotation;//Rotacja samochodu
    public LayerMask raycastMask;//Maski dla czujnikow

    private float[] input = new float[5];
    public NeuralNetwork network;

    public int position;//Ile checkpointow przejechal pojazd
    public bool collided;//Do zatrzymania pojazdu w razie kolizji

    void FixedUpdate()
    {
        if (!collided)//Pojazd jedzie i zbiera dane tylko jezeli nie zderzyl sie wczesniej z innym obiektem
        {
            for (int i = 0; i < 5; ++i)
            {
                Vector3 newVector = Quaternion.AngleAxis(i * 45 - 90, new Vector3(0, 1, 0)) * transform.right;//Ustawianie czujnikow z przodu co 45 stopni
                RaycastHit hit;
                Ray Ray = new Ray(transform.position, newVector);

                if (Physics.Raycast(Ray, out hit, 10, raycastMask))
                {
                    input[i] = (10 - hit.distance) / 10;
                }
                else
                {
                    input[i] = 0;
                }
            }

            float[] output = network.ProcessInput(input);//Przetworzanie danych z czujnikow

            transform.Rotate(0, output[0] * rotation, 0, Space.World);
            transform.position += this.transform.right * output[1] * speed;
        }
    }

    //Sprawdza czy pojazd przejechal przez checkpoint lub czy zderzyl sie z innym obiektem
    void OnCollisionEnter(Collision collision)
    {
        if (collision.collider.gameObject.layer == LayerMask.NameToLayer("CheckPoint"))
        {
            ++position;
            Debug.Log("Checkpoint!");
        }
        else if (collision.collider.gameObject.layer != LayerMask.NameToLayer("Learner"))
        {
            collided = true;
            speed = 0;
        }
    }

    //Aktualizuje sprawnosc danej sieci w celu posortowania
    public void UpdateFitness()
    {
        network.fitness = position;
    }
}

