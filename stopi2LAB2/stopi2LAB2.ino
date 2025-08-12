// Sana Topia - 656545335 - stopi2
// LAB 2 - Three Bit Counter
// Description: The code is supposed to represent the different bits and how that 
//              preseneted in the LEDS (On = 1, OFF == 0). Each LED per Binary digit with
//              light changing each time the button is presed.
// Assumption: None
// TA : tanuj
// DATE : Sept 13   Time: 1:37 

//Define the pin numbers for the LEDs and buttons
const int ledpin1 = 13;
const int ledpin2 = 12;
const int ledpin3 = 6;
const int upButtonPin = 2;
const int downButtonPin = 3;

//Declare variables for the button states and debounce mechanism
int count = 0;
bool lastUpButtonState = LOW;
bool lastDownButtonState = LOW;
unsigned long lastDebounceTime = 0;
const long debounceDelay = 50;

int upButtonState = 0;

void setup() {
  // put your setup code here, to run once:
  //Initialize serial communication for debugging
  Serial.begin(9600);

  //Set the LED pins as OUTPUT
  pinMode(ledpin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);
  pinMode(ledpin3, OUTPUT);
  // Set the button pins as INPUT
  pinMode(upButtonPin, OUTPUT);
  pinMode(downButtonPin, OUTPUT);

}

void loop() {
  // Serial.println("testing");
  // Read the currect state of the up button
  bool upButtonState = digitalRead(upButtonPin);
  delay(10); // Small delay for debouncing
  bool upButtonState2 = digitalRead(upButtonPin);
  // Serial.println("Up Button State:" + (upButtonState2?"t":"f"));
  Serial.println(count);
 
 //Check if the button state is stable (debouncing check)
  if(upButtonState == upButtonState2){
    if (upButtonState != lastUpButtonState) {
      if (upButtonState == LOW && count < 7){
        count++;
        Serial.print("UP Button: ");
        Serial.println(upButtonState);
      }
    }
  }

  bool downButtonState = digitalRead(downButtonPin);
  delay(10);
  bool downButtonState2 = digitalRead(downButtonPin);

 //Check if the button state is stable (debouncing check)
  if(downButtonState == downButtonState2){
    if (downButtonState != lastDownButtonState) {
      if (downButtonState == LOW && count > 0){
        count--;
        Serial.print("down Button: ");
        Serial.println(downButtonState);
      }
    }
  }

//Turn on or off LEDS based on the count value using bitwise
//LED 1
  if (count & 1){
    digitalWrite(ledpin1, HIGH);
  } else {
    digitalWrite(ledpin1, LOW);
  }
//LED 2 will turn on 
  if (count & 2){
      digitalWrite(ledpin2, HIGH);
    } else {
      digitalWrite(ledpin2, LOW);
    }

//LED 3 will turn on 
  if(count & 4){
    digitalWrite(ledpin3, HIGH);
  } else {
    digitalWrite(ledpin3, LOW);
  }
//Update the last button states to the currrent button states
  lastUpButtonState = upButtonState;
  lastDownButtonState = downButtonState;

}
