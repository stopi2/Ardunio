// Sana Topia - 656545335 - stopi2
// LAB 8 - Interrupts
// Description: Display elasped time by default. Show interrupt message when button pressed;
//              Reset time and return to defaults when button 2 is pressed.
// References: https://projecthub.arduino.cc/arduino_uno_guy/i2c-liquid-crystal-displays-5eb615
// TA = Rohan
// Date: Nov 8 ,Time : 10:51 am

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Global variables for buttons
const int btnPin1 = 2; // Pin for button 1
const int btnPin2 = 3; // Pin for button 2
volatile bool btn1Pressed = false; // Flag for button 1 press
volatile bool btn2Pressed = false; // Flag for button 2 press

// Variables for scrolling display
int scrollPos = 0; // Current position in scrolling text
char displayBuffer[30]; // Buffer for scrolling text
unsigned long lastScrollUpdate = 0; // Timestamp for controlling scroll speed
const unsigned long scrollDelay = 300; // Interval for scrolling speed

// State variable (1 for interrupt message, 0 to display timer)
int systemState = 0;

// Timer variables
unsigned long lastTimerUpdate = 0; // Timestamp to track timer start
unsigned long elapsedTime = 0; // Elapsed time in seconds

// ISR for button 1
void isrBtn1() {
  btn1Pressed = true;
}

// ISR for button 2
void isrBtn2() {
  btn2Pressed = true;
}

// Function to print a phrase with scrolling on the LCD
void displayScrollText(const char* message) {
  int messageLen = strlen(message);

  // Create a substring of the message to fit the LCD screen width
  for (int i = 0; i < 16; i++) {
    displayBuffer[i] = message[(scrollPos + i) % messageLen]; // Wrap-around effect
  }
  displayBuffer[16] = '\0'; // Null-terminate the buffer

  // Display the substring on the first row
  lcd.setCursor(0, 0);
  lcd.print(displayBuffer);

  // Update scroll position only if the scroll delay has passed
  if (millis() - lastScrollUpdate >= scrollDelay) {
    lastScrollUpdate = millis(); // Update last scroll timestamp
    scrollPos++;
    if (scrollPos >= messageLen) {
      scrollPos = 0; // Reset scroll position if it reaches end of text
    }
  }
}

void setup() {
  // Initialize the LCD, buttons, and interrupts
  lcd.init();
  lcd.backlight();

  // Setup buttons with internal pull-up resistors
  pinMode(btnPin1, INPUT_PULLUP);
  pinMode(btnPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(btnPin1), isrBtn1, FALLING); // Attach ISR for button 1
  attachInterrupt(digitalPinToInterrupt(btnPin2), isrBtn2, FALLING); // Attach ISR for button 2

  // Initialize LCD display with the default message
  lcd.setCursor(0, 0);
  lcd.print("System on for:");
  lastTimerUpdate = millis(); // Record the start time for timer
}

void loop() {
  // If button 1 is pressed, switch to interrupt message display and pause timer
  if (btn1Pressed) {
    btn1Pressed = false; // Reset the button 1 flag
    if (systemState == 0) {
      systemState = 1; // Switch to interrupt state
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Press button 2");
      lastScrollUpdate = millis(); // Reset scroll timestamp
    }
  }

  // If button 2 is pressed, reset the timer and switch back to default state
  if (btn2Pressed) {
    btn2Pressed = false; // Reset the button 2 flag
    if (systemState == 1) {
      systemState = 2; // Temporary state to reset timer
    }
  }

  // Display elapsed time on LCD if in default state
  if (systemState == 0) {
    elapsedTime = (millis() - lastTimerUpdate) / 1000; // Calculate elapsed time in seconds
    lcd.setCursor(0, 0);
    lcd.print("System running for:    ");
    lcd.setCursor(0, 1);
    lcd.print("                "); // Clear line
    lcd.setCursor(0, 1);
    lcd.print(elapsedTime);
    lcd.print(" seconds");
  } 
  // If in interrupt state, display the scrolling interrupt message
  else if (systemState == 1){
    displayScrollText("Interrupt received!                ");
  }
  // If in reset state, clear display and reset timer, then return to default state
  else if (systemState == 2) { 
    lastTimerUpdate = millis(); // Reset timer start time
    systemState = 0; // Return to default state
    scrollPos = 0; // Reset scroll position
    lcd.clear();
  }
}
