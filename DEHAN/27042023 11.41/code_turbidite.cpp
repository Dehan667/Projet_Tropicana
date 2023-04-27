#include <wiringPi.h>
#include <iostream>

#define ANALOG_PIN 13

int main() 
{
    wiringPiSetup(); // initialisation de wiringPi

    while (true) 
    {
        // lecture de la valeur analogique sur la broche ANALOG_PIN
        int value = analogRead(ANALOG_PIN);

        // conversion de la valeur analogique en pourcentage de turbidité
        float turbidity = (1023 - value) / 1023.0 * 100;

        // affichage de la valeur de turbidité
        std::cout << "Turbidity: " << turbidity << "%" << std::endl;

        // attente d'une seconde
        delay(1000);
    }
    
    return 0;
}

 // Pour compiler 
 // su -
 // root
 // root
 // /home/pi/Documents/Code_tropicana
 // g++ -o turbidited code_turbidite.cpp -lwiringPi