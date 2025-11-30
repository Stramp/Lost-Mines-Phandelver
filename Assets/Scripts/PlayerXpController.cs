using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;
public class PlayerXpController : MonoBehaviour
{

  public static PlayerXpController instance;
  public float xpMultiply = 1; // 2.41
  public float currentXp = 150;
  private float xpNextLvl;
  public float difFactor = 1.5f;
  private float progressXpToLvlUp;
  // Start is called before the first frame update
  void Start()
  {
    instance = this;
    DontDestroyOnLoad(gameObject);
    //Application.LoadLevel("MainMenu");
    SceneManager.LoadScene("GamePlay");
    
  }

  // Update is called once per frame
  void Update()
  {
    if (Input.GetKeyDown(KeyCode.A)) AddXp(225000);
    if (Input.GetKeyDown(KeyCode.R)) {
      PlayerPrefs.DeleteAll();
    }
  }

  public static void AddXp(float xp){
    float newXp = PlayerPrefs.GetFloat("currentXp") + (xp * PlayerXpController.instance.xpMultiply);
    PlayerPrefs.SetFloat("currentXp", newXp);
    float difExp = GetCurrentXp() - TableExp.GetNextXp(GetCurrentLvl());
    if(difExp >= 0){
      AddLvl();
      Debug.Log("difExp "+ difExp);
      Debug.Log("TableExp.GetNextXp(GetCurrentLvl()) "+ (TableExp.GetNextXp(GetCurrentLvl())- TableExp.GetNextXp(GetCurrentLvl()-1)));
      AddXp(0);
    }
    updateProgressXpToLvlUp();
  }

  private static void updateProgressXpToLvlUp(){
    
    float currentXpForPercentCalc = PlayerPrefs.GetFloat("currentXp") - TableExp.GetNextXp(GetCurrentLvl()-1);
    float xpNextLvlDiff = TableExp.GetNextXp(GetCurrentLvl()) - TableExp.GetNextXp(GetCurrentLvl()-1);
    PlayerXpController.instance.progressXpToLvlUp = currentXpForPercentCalc * 100 / xpNextLvlDiff;
  }

  public static float GetCurrentXp(){
    return PlayerPrefs.GetFloat("currentXp");
  }
  public static int GetCurrentLvl(){
    return PlayerPrefs.GetInt("currentLvl") <= 0 ? 1 : PlayerPrefs.GetInt("currentLvl");
  }
  public static void AddLvl(){
    int newLvl = GetCurrentLvl() + 1;
    PlayerPrefs.SetInt("currentLvl", newLvl);
  }

  void OnGUI()
  {
      GUI.Label(new Rect(5, 5, 400, 50), "Current Lvl: " + GetCurrentLvl());
      GUI.Label(new Rect(5, 15, 400, 50), "Next LVl: " + (GetCurrentLvl() + 1));
      GUI.Label(new Rect(5, 25, 400, 50), "Current XP: " + GetCurrentXp());
      GUI.Label(new Rect(5, 35, 400, 50), "Next XP: " + TableExp.GetNextXp(GetCurrentLvl()));
      GUI.Label(new Rect(5, 45, 400, 50), "porcentagem de progesso: " + progressXpToLvlUp);
  }


}
