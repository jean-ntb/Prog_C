// Includes
#pragma region Include
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#pragma endregion
// Mes Constantes
#pragma region Constante
#define TEMPERATURE_MAX 204.6
#define VALEUR_OPERATEUR_MAX 1023
#define TEMPERATUR_MIN 0.2
#pragma endregion
// Structure ou objet
#pragma region Structure
typedef enum {POWER_ON,POWER_OF}etat_Moteur;
typedef struct 
{
    bool Actif;
}Ventilation;
 
typedef struct 
{
    etat_Moteur etat;
}Moteur;

typedef struct 
{
    float temperature_Min;
    float temperature_MAX;
    float temperature_toleree;
    float temperature_actuel;

}Capteur;
#pragma endregion
// Les inits (Constructeur)
#pragma region Init
Ventilation init_Ventilateur(Ventilation ventilation) {
    ventilation.Actif = false;
    return ventilation;
}
Moteur init_Moteur(Moteur moteur) {
    moteur.etat = POWER_ON;
    return moteur;
}
Capteur init_Capteur(Capteur capteur){
    capteur.temperature_MAX = TEMPERATURE_MAX;
    capteur.temperature_Min = TEMPERATUR_MIN;
    capteur.temperature_toleree = 90;
    capteur.temperature_actuel = 0;
    return capteur;
}
#pragma endregion
// Fonction métier
#pragma region fonction
float Conversion_Temperature (float temperature_Operateur){
    float temperature_Degree = temperature_Operateur * 0.2;
    return temperature_Degree;
}
Capteur Control_Temperature(Capteur capteur, float temperature_operateur){
    capteur.temperature_actuel = temperature_operateur;
    if(capteur.temperature_actuel > capteur.temperature_MAX || capteur.temperature_actuel < capteur.temperature_Min)
    {
        printf("Erreur la température n'est pas comprise dans la plage fixée ");
    }
    return capteur;
}
Ventilation Control_Ventilation(Capteur capteur, Moteur Moteur, Ventilation Ventilation) {
    if (capteur.temperature_actuel > capteur.temperature_toleree && Moteur.etat == POWER_ON){
        Ventilation.Actif = true;
        printf("Ventilation active car la température est supérieur à 90 degrés et le moteur est actf");
    }
    else {
        Ventilation.Actif = false;
        printf("Pas de ventilation");
    }
        return Ventilation;
}
#pragma endregion
// Main
#pragma region Main
int main (){
    Capteur capteur_ ; 
    capteur_= init_Capteur(capteur_);
    Moteur moteur_;
    moteur_ =  init_Moteur(moteur_);
    Ventilation ventilateur;
    ventilateur = init_Ventilateur(ventilateur);
    float temperature_actuel;
    printf("Entrer une valeur de capteur : ");
    scanf("%f", &temperature_actuel);
    temperature_actuel = Conversion_Temperature(temperature_actuel);
    capteur_ = Control_Temperature(capteur_, temperature_actuel);
    ventilateur = Control_Ventilation(capteur_, moteur_, ventilateur);
    
}
#pragma endregion