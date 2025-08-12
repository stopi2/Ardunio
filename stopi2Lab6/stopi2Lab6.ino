// Sana Topia - 656545335 - stopi2
// LAB 6 - this lab is supposed to work along with the LCD displaying the date and time with the user inputs and working with the serial monitor. accurate date and time. 
// Description: the code should be able to manipulate the different formats of date and time. I assume that the code would require some sort of data or function to appear properly on the screen.
// Assumption: None
 // TA = Yashwi
 // Date: Oct 18 ,Time : 2:24pm

#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>  
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

char DateBuffer[11];  //Buffer to hold the formatted date string 
char TimeBuffer[9];  //Buffer to hold the formatted time string
unsigned long prevMillis = 0;  // Variable to store the last time the LCD
const long interval = 1000;  // Interval for updating the lCD

void setup() {
  Serial.begin(9600); //Intialize serial communications
  lcd.begin(16, 2); // Initialize serial communication
  lcd.init();
  setTime(0);
  // Set the default time
  Serial.println("Enter date (mm/dd/yyyy) and time (hh:mm:ss): ");
}

// Function to update the lCD display with the currect date
// Format the date 
//Format the time
void UpdateLCD() {
    sprintf(DateBuffer, "%02d/%02d/%04d", month(), day(), year());
    sprintf(TimeBuffer, "%02d:%02d:%02d", hour(), minute(), second());
    lcd.setCursor(0, 0);
    lcd.print(DateBuffer);
    lcd.setCursor(0, 1); // Display the time on the second row
    lcd.print(TimeBuffer);
}

//Function to validate if the given date is valid
// Makes sure thats it has special case for maoths with 30 days
// Special case for Feburary (handling leap years)
bool ValidDate(int month, int day, int year) {
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            return day <= 29;
        } else {
            return day <= 28;
        }
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return day <= 30;
    }
    return true; 
}

// Checks if there is user input avaible from the serial monitor
bool ValidTime(int hour, int minute, int second) {
    return (hour >= 0 && hour < 24) && (minute >= 0 && minute < 60) && (second >= 0 && second < 60);
}

void loop() {
    // Read the entire is user input avaible from the monitor
    // Checks if the input length is correct or not
    if (Serial.available() > 0) {
        String userinput = Serial.readStringUntil('\n'); 
        if (userinput.length() == 19 && userinput[2] == '/' && userinput[5] == '/' && userinput[10] == ' ' && userinput[13] == ':' && userinput[16] == ':') {
            int month = userinput.substring(0, 2).toInt();
            int day = userinput.substring(3, 5).toInt();
            int year = userinput.substring(6, 10).toInt();
            int hour = userinput.substring(11, 13).toInt();
            int minute = userinput.substring(14, 16).toInt();
            int second = userinput.substring(17, 19).toInt();
            if (ValidDate(month, day, year) && ValidTime(hour, minute, second)) {
                setTime(hour, minute, second, day, month, year); 
                Serial.println("Valid date/time entered.");
                UpdateLCD();
            } else {
                Serial.println("Invalid date/time entered. Please try again.");
            }
        } else {
            Serial.println("Invalid format. Please use mm/dd/yyyy hh:mm:ss.");
        }
    }
//Updates the lCD only when the interval 
//Used millis instead of delay
    unsigned long currMillis = millis();
    if (currMillis - prevMillis >= interval) {
        prevMillis = currMillis;
        UpdateLCD();
    }
}
