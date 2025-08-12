// Sana Topia - 656545335 - stopi2
// LAB 4 - Analog Input
// Description: The lab requires how to use a Photoresitor and set up the LCD
//              be able to convert analog sensor input the brightness level and 
//              show the milliseconds.
// References: Lab 3 setup
// TA = Rohan
// Date: Sep 27 ,Time : 12:03

#include <LiquidCrystal.h>

const int rs = 12;
const int en = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;

// Defines the pin connected to the photoresitor
const int photoresistor = A0;
const long interval = 1000; // Time interval for updating

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
unsigned long previousMillis = 0;

// Initialize the LCD screen
void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);

}

void loop() {
 // Get the current time in milliseconds
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    //Read the values from the photoresitors
    int sensorValue = analogRead(photoresistor); 

    String light_Level;

   //Determine the light level based on the sensor value
    if (sensorValue < 400) {
      light_Level = "Dark";
    } else if (sensorValue < 600) {
      light_Level = "Partially Dark";
    } else if (sensorValue <= 699) {
      light_Level = "Medium";
    } else if (sensorValue <= 900) {
      light_Level = "Fully Lit";
    } else if (sensorValue <= 1500){
      light_Level = "Brightly Lit";
    }

    lcd.clear();  
    lcd.setCursor(0, 0);
    lcd.print(lightLevel);
  }
// Sets the cursor to the second row
  lcd.setCursor(0, 1);
  lcd.print(millis());
}

