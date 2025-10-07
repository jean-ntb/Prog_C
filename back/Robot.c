#pragma region Include
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#pragma endregion

#pragma region variables
#define MAX_MESURE 400
#define MIN_MESURE 0
#define NB_MESURES 5  
int distance_Critique;
int distance_Attention;
int distance_Libre;
int distance_Actuel;
#pragma endregion

typedef enum {
    ZONE_CRITIQUE,
    ZONE_ATTENTION,
    ZONE_LIBRE
} Zone;
typedef enum  { Arret, Avancer, Ralentir} Etat_Robot;

typedef struct 
{
    int portee_Min; 
    int portee_Max;
    int tableau_mesures[NB_MESURES];
    int nombre_Mesure;
    int mesure_Actuel;

    bool actif;

}Capteurs;
typedef struct 
{
    int vitessse_Actuel;
    int seuil_Stop ;
    int seuil_Attention;
    int Count_Obstacle;
    Etat_Robot etat;

}Robot;

void init_Robot(Robot*robot){
    robot->etat = Arret;
    robot->seuil_Stop = 30;
    robot->Count_Obstacle = 0;
    robot->vitessse_Actuel = 0;
    robot->seuil_Attention = 100;
}
void init_Capteurs(Capteurs*capteurs) {
    capteurs->actif = true;
    capteurs->portee_Max = MAX_MESURE;
    capteurs->portee_Min = MIN_MESURE;
    capteurs->mesure_Actuel = NULL;
    capteurs ->nombre_Mesure = 0;
    for(int i = 0; i < NB_MESURES; i ++ ){
        capteurs->tableau_mesures[i] = 0;
    }
}
int generate_Random_Distance(){
    srand ( time ( NULL ) ) ;
    distance_Actuel = rand() % MAX_MESURE;
    return distance_Actuel;
}

Zone Definition_Zone() {
   if (distance_Actuel < 30){
    return ZONE_CRITIQUE;
    if (distance_Actuel > 30 && distance_Actuel < 100 )
    {
        return ZONE_ATTENTION;
    }
    else {
            return ZONE_LIBRE;
    }
   }
}
void Descision_Robot(Robot*robot, int distance) {
    Zone zone = Definition_Zone(distance);
  switch (zone)
  {
  case ZONE_LIBRE:
    robot->etat = Avancer;
    robot->vitessse_Actuel = 100;
    break;
    case ZONE_CRITIQUE:
    robot->etat = Arret;
    robot ->Count_Obstacle = 1;
    robot-> vitessse_Actuel = 100;
    break;
    case ZONE_ATTENTION :
    robot->etat = Ralentir;
    robot ->vitessse_Actuel = 50;
    break;
  }


}
