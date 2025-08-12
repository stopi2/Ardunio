// Sana Topia - 656545335 - stopi2
// LAB 3 - Scrolling Output
// Description: The lab requires displaying a favorite quote and your name on the
//               the LCD screen using the Ardunio. The quote and the name should display
//               scroll across the screen. the quote on the first line and the name on the second
// Assumption: None
 // TA = tanuj
 // Date: Sep 23 ,Time : 2:31pm

  #include <LiquidCrystal.h> // The library
// Define the pins connected to the LCD
  const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Create an LCD object

// Quote to be displayed on the lCD
  const char* quote = "Knowledge is knowing a tomato is a fruit" ;
  int quoteLen = strlen(quote);

// Variables for timing and scrolling
  unsigned long previousMillis = 0; // Stores the last display time
  const long interval = 300;
  int scroll = 0; // Position of the scrolling text

//Initiazlie the LCD with 16 columns and 2 rows
// Array to tsore the name to be displayed
  void setup(){
    lcd.begin(16, 2);
    char name[17];
    sprintf(name, "Sanass");
    lcd.setCursor(5, 1);
    lcd.print(name);
  }

// Gets the current time in milliseconds
// Updates the display time and checks
  void loop(){
    unsigned long currentMill = millis();
    if(currentMill - previousMillis >= interval) {
      previousMillis = currentMill;
      // Set the cursor to the beginning of the first row
      // Display 16 characters of the quote
      lcd.setCursor(0, 0);
      for (int i = 0; i < 16; i++){
        //Print the character with wrapping around
        lcd.print(quote[(scroll + i) % quoteLen]);
      }
      // Increment the scrolling position.k
      scroll++; 
        if(scroll >= quoteLen){
        scroll = 0;
        }
    }
  }