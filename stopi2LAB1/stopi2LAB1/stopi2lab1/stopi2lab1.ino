// Sana Topia - 656545335 - stopi2
// LAB 1 - Three Blinking Light
// Description: The code is supposed to make the three LED Lights White, RED and GREEN 
//              blink back to back, like turn on, turn off.
// Assumption: The board will work by taking turns to proccess the transitiors and 
//             allow for the lights to go through one by one
// TA : tanuj
// DATE : 1:48   Time: 1:48 

int onboardLED = 13; // WHITE LED connects to pin #13
int redled2 = 12; // RED LED connects to pin #12
int greenled3 = 9; // GREEN LED connects to pin #9

int interval = 1000;
int previousMillis = 0;
int currentLED = onboardLED;

void setup() {
  pinMode(onboardLED, OUTPUT);
  pinMode(redled2, OUTPUT);
  pinMode(greenled3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int currentMillis = millis();

  //check to see if current time interval that has passed is 
  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
  //greater than the interval to do the swap

  // put your main code here, to run repeatedly:
  digitalWrite(currentLED, LOW);
  
  if (currentLED == onboardLED) {
    Serial.print("case 0");
    currentLED = redled2;
  } else if (currentLED == redled2) {
    Serial.print("case 1");
    currentLED = greenled3;
  } else {
    Serial.print("case 2");
    currentLED = onboardLED
  }
  //Turn on the nearest LED
  digitalWrite(onboardLED, LOW);
  }
}
