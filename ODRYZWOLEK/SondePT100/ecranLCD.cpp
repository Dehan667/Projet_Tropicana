#include <LiquidCrystal.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <wiringPi.h>

// Initialize the LCD object with the pins it is connected to
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define the analog input pin the potentiometer is connected to
const int potPin = A0;

void setup() {
  // Initialize the LCD and set up the columns and rows
  lcd.begin(16, 2);
  // Print a message to the LCD
  lcd.print("Potentiometer:");
}

void loop() {
  // Read the value of the potentiometer
  int potValue = analogRead(potPin);
  // Clear the second row of the LCD
  lcd.setCursor(0, 1);
  lcd.print("               ");
  // Print the value of the potentiometer to the LCD
  lcd.setCursor(0, 1);
  lcd.print(potValue);
  // Wait a short time before reading the potentiometer again
  delay(1000);
}
