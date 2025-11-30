using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TableExp
{
    public static int[] exp = new int[20];
    
    public static int GetNextXp(int _lvl)
    {
        //int lvl = _lvl <= 0 ? lvl = 1: lvl = _lvl;
        exp[0] = 0;
        exp[1] = 300;
        exp[2] = 900;
        exp[3] = 2700;       
        exp[4] = 6500;
        exp[5] = 14000;
        exp[6] = 23000;
        exp[7] = 34000;
        exp[8] = 48000;
        exp[9] = 64000;
        exp[10] = 85000;
        exp[11] = 100000;
        exp[12] = 120000;
        exp[13] = 140000;
        exp[14] = 165000;
        exp[15] = 195000;
        exp[16] = 225000;
        exp[17] = 265000;
        exp[18] = 305000;
        exp[19] = 355000;
        return exp[_lvl];
    }
}
    


