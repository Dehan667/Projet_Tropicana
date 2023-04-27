#include <iostream>
#include <stdio.h>
#include <string.h>
#include <wire.h>
#include <liquidCrystal.h>


int main(){

/*Récupérer une valeur de la Sonde PT100*/
void setup()
{
    serial.begin(9600); //ouvre le port série et fixe le debit de communication à 9600 bauds
    
}

void loop()
{
    float temp = max.temperature();
    Serial.print("Temperature =");
    Serial.print(temp);
    Serial.print("°C");
    delay(1000);
}
/*Régulation de la température */
const float setpoint = 25.0; //température ciblé en degrés Celsius
const float Kp = 2.0;        // coefficient proportionnel du régulateur 
const float Ki = 0.05;       // coefficient intégral du régulateur
const float Kd = 0.0;        // coefficient dérivé du régulateur
const float Tmin = 20.0;     // température minimale autorisée
const float Tmax = 70.0;     // température maximale autorisée
const float dt = 0.1;        // temps d'échantillonage en secondes

float error = 0.5;           // erreur de régulation
float error_sum = 0.0;       // somme des erreurs
float last_error = 0.0;      // dernière erreur
float output = 0.0;          // sortie du régulateur

void setup()
{
    Serial.begin(9600);
    
}

void loop()
{
    float temperature = max.temperature();         // mesure de la température
    error = setpoint - temperature;                // calcul de l'erreur
    error_sum += error * dt;                       // intégration de l'erreur        
    float error_rate = (error - last_error) / dt;  // calcul de la dérivée de l'erreur 
    output = Kp * error + Ki * error_sum + Kd * error_rate; // calcul de la sortie du régulateur
    output = constrain(output, Tmin, Tmax);        // limitation de la sortie à Tmin et Tmax
    
    analoWrite(analog pin,output);              // stockage de la dernière erreur
    last_error = error;                            // attente d'une durée d'échantillonage
    delay(dt* 1000);
}
}