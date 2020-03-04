using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnCross : MonoBehaviour
{

    public GameObject spawnee;
    Transform pos;
    public bool already_spawned=false;
    public int x;
    public int y;

    private void OnMouseDown()
    {
        if(already_spawned==false&&SceneSetup.koniec==false)
        {
            pos = this.transform;
            
            Instantiate(spawnee, new Vector3(pos.position.x,pos.position.y+0.25f,pos.position.z), spawnee.transform.rotation);
            already_spawned = true;
            SceneSetup.tura_gracza = false;
            SceneSetup.ostatni_x = x;
            SceneSetup.ostatni_y = y;
            SceneSetup.plansza[y, x] = 1;
        }
    }

}
