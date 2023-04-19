#include <wiringPi.h>
#include <iostream>

#define TRIGGER_PIN 4
#define ECHO_PIN 5
#define ANALOG_PIN 0

int main() 

{
    std::cout << "Valeur Capteur Ultrasons :\n";
    ultrasons;
    std::cout << "Valeur Capteur Turbidite :\n";
    turbidite;
}


void ultrasons() 
{
        wiringPiSetup();

        while (true) {
        // lecture de la valeur analogique sur la broche ANALOG_PIN
        int value = analogRead(ANALOG_PIN);

        // conversion de la valeur analogique en pourcentage de turbidité
        float turbidity = (1023 - value) / 1023.0 * 100;

        // affichage de la valeur de turbidité
        std::cout << "Turbidite: " << turbidity << "%" << std::endl;

        // attente d'une seconde
        delay(1000);
    }
}

void turbidite () 
{
    
    wiringPiSetup(); // initialisation de wiringPi
    pinMode(TRIGGER_PIN, OUTPUT); // configuration de la broche TRIGGER_PIN en sortie
    pinMode(ECHO_PIN, INPUT); // configuration de la broche ECHO_PIN en entrée
    
    while (true)

    {
        // envoi d'une impulsion de 10 us sur la broche TRIGGER_PIN
        digitalWrite(TRIGGER_PIN, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIGGER_PIN, LOW);

        // mesure de la durée de l'impulsion sur la broche ECHO_PIN
        int duration = pulseIn(ECHO_PIN, HIGH);

        // conversion de la durée en distance en cm (vitesse du son = 343 m/s)
        float distance = duration * 0.0343 / 2;

        // affichage de la distance en cm
        std::cout << "Distance : " << distance << " cm" << std::endl;

        // attente d'une seconde
        delay(1000);
    }
}